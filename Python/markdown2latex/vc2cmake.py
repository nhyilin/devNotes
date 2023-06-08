#!/usr/bin/env python
# -*- coding: utf-8 -*-

import codecs
import sys

sys.stdout = codecs.getwriter('utf-8')(sys.stdout)
sys.stderr = codecs.getwriter('utf-8')(sys.stderr)
import os
import sys
from xml.etree import ElementTree


def create_cmake_project_from_vcxproj(file_path, output_path):
    tree = ElementTree.parse(file_path)

    # Get project name
    project_name = os.path.splitext(os.path.basename(file_path))[0]

    # Find sources
    sources = []
    for cl_compile in tree.findall('.//{http://schemas.microsoft.com/developer/msbuild/2003}ClCompile'):
        if 'Include' in cl_compile.attrib:
            sources.append(cl_compile.attrib['Include'])
    # Find include directories
    include_dirs = set()
    for cl_compile in tree.findall('.//{http://schemas.microsoft.com/developer/msbuild/2003}ClCompile'):
        if 'Include' in cl_compile.attrib:
            path = os.path.dirname(cl_compile.attrib['Include'])
            if len(path) > 0 and path[0] == '\\':
                path = path[1:]
            if len(path) > 0 and path[0] == '\"':
                path = path[1:]
            if len(path) > 0 and path[-1] == '\"':
                path = path[:-1]
            if len(path) > 0:
                include_dirs.add(path)

    # Find library directories and names
    library_dirs = []
    libraries = []
    for lib in tree.findall('.//{http://schemas.microsoft.com/developer/msbuild/2003}Library'):
        if 'Include' in lib.attrib:
            libraries.append(lib.attrib['Include'])
            library_dirs.append(os.path.dirname(lib.attrib['Include']))
    library_dirs = list(set(library_dirs))

    # Find precompiled header file
    pch = None
    pch_source = None
    for cl_compile in tree.findall('.//{http://schemas.microsoft.com/developer/msbuild/2003}ClCompile'):
        if 'PrecompiledHeader' in cl_compile.attrib:
            if cl_compile.attrib['PrecompiledHeader'] == 'Create':
                pch = cl_compile.attrib['Include']
                pch_source = cl_compile.attrib['CreatePch']

    # Find preprocessor definitions
    definitions = ''
    for item in tree.findall(".//{http://schemas.microsoft.com/developer/msbuild/2003}ClCompile"):
        if 'PreprocessorDefinitions' in item.attrib:
            definitions = item.attrib['PreprocessorDefinitions']
            break

    # Find compiler options
    compiler_options = ''
    for item in tree.findall(".//{http://schemas.microsoft.com/developer/msbuild/2003}ClCompile"):
        if 'AdditionalOptions' in item.attrib:
            compiler_options = item.attrib['AdditionalOptions']
            break

    # Find linker options
    linker_options = ''
    for item in tree.findall(".//{http://schemas.microsoft.com/developer/msbuild/2003}Link"):
        if 'AdditionalOptions' in item.attrib:
            linker_options = item.attrib['AdditionalOptions']
            break

    # Generate CMakeLists.txt
    with open(output_path, 'w') as f:
        f.write('cmake_minimum_required(VERSION 3.15)\n')
        f.write('project(%s)\n' % project_name)
        f.write('\n')
        # Add sources
        f.write('set(SOURCES\n')
        for source_file in sources:
            f.write('  %s\n' % source_file)
        f.write(')\n')
        f.write('\n')
        # Add executable
        f.write('add_executable(${PROJECT_NAME} ${SOURCES})\n')
        f.write('\n')
        # Add include directories
        f.write('target_include_directories(${PROJECT_NAME} PRIVATE\n')
        for include_dir in include_dirs:
            f.write('  %s\n' % include_dir)
        f.write(')\n')
        f.write('\n')
        # Add library directories
        if len(library_dirs) > 0:
            f.write('target_link_directories(${PROJECT_NAME} PRIVATE\n')
            for library_dir in library_dirs:
                f.write('  %s\n' % library_dir)
            f.write(')\n')
            f.write('\n')
        # Add libraries
        if len(libraries) > 0:
            f.write('target_link_libraries(${PROJECT_NAME} PRIVATE\n')
            for lib in libraries:
                f.write('  %s.lib\n' % os.path.splitext(lib)[0])
            f.write(')\n')
            f.write('\n')
        # Add precompiled header file
        if pch is not None and pch_source is not None:
            f.write('set(PCH_HEADER "%s")\n' % pch)
            f.write('set(PCH_SOURCE "%s")\n' % pch_source)
            f.write('target_precompile_headers(${PROJECT_NAME} PRIVATE "${PCH_HEADER}" "${PCH_SOURCE}")\n')
            f.write('\n')
        # Add preprocessor definitions
        if len(definitions) > 0:
            f.write('target_compile_definitions(${PROJECT_NAME} PRIVATE\n')
            for definition in definitions.split(';'):
                f.write('  %s\n' % definition)
            f.write(')\n')
        # Add compiler options
        if len(compiler_options) > 0:
            compiler_options = compiler_options.replace('"', '\\"')
            f.write('target_compile_options(${PROJECT_NAME} PRIVATE "%s")\n' % compiler_options)
        # Add linker options
        if len(linker_options) > 0:
            linker_options = linker_options.replace('"', '\\"')
            f.write('target_link_options(${PROJECT_NAME} PRIVATE "%s")\n' % linker_options)
    print('CMakeLists.txt generated to %s' % output_path)


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: python vcxproj2cmake.py <vcxproj_file_path> [output_path]')
        sys.exit(1)

    vcxproj_file_path = sys.argv[1]
    output_path = os.path.splitext(vcxproj_file_path)[0] + '.cmake'
    if len(sys.argv) > 2:
        output_path = sys.argv[2]

    create_cmake_project_from_vcxproj(vcxproj_file_path, output_path)