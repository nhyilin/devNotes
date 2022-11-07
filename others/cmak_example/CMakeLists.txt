
set(SUBSYSTEM Knee)
set(PROJECT_NAME SPExpert${SUBSYSTEM})


find_package(Qt5 COMPONENTS Core Gui Multimedia MultimediaWidgets Network Sql SerialPort Widgets REQUIRED)
find_package(Qt5LinguistTools)

################################################################################
# Source groups
################################################################################

# Seperate file lists to different cmake files
include(SourceFiles.cmake)
include(HeaderFiles.cmake)
include(ResourceFiles.cmake)


set(ALL_SRC_FILES
	${INNER_SRC_FILES}
	${EXTERNAL_SRC_FILES}
) 

set(ALL_HEADER_FILES
	${INNER_HEADER_FILES}
	${EXTERNAL_HEADER_FILES}
) 

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Project Header Files"  FILES ${INNER_HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Project Source Files" FILES ${INNER_SRC_FILES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/../ PREFIX "Others Header Files"  FILES ${EXTERNAL_HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/../ PREFIX "Others Source Files" FILES ${EXTERNAL_SRC_FILES})

set(Cmake_Files
    SourceFiles.cmake
	HeaderFiles.cmake
	ResourceFiles.cmake
)
source_group("CMake Files" FILES ${Cmake_Files})


SET(QRC_SRCS)
qt5_add_resources(QRC_SRCS ${QRC_Files})

qt5_wrap_cpp(MOCSOURCES ${ALL_HEADER_FILES})
source_group("Generated Files" FILES ${MOCSOURCES} ${QRC_SRCS} ${EXPERT_QM_FILES})


################################################################################
# Target 
################################################################################
add_executable(${PROJECT_NAME} ${ALL_SRC_FILES} ${ALL_HEADER_FILES} ${QRC_SRCS} ${MOCSOURCES} ${ALL_RESOURCE_FILES} ${Cmake_Files})


use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE SPExpert${SUBSYSTEM})


################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "SPExpert${SUBSYSTEM}"
    TARGET_NAME_RELEASE "SPExpert${SUBSYSTEM}"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
)

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../TargetAlign
    ${CMAKE_CURRENT_SOURCE_DIR}/../CAPIcommon
    ${CMAKE_CURRENT_SOURCE_DIR}/../Robot/roboticArm
    ${CMAKE_CURRENT_SOURCE_DIR}/../common

    ${VTK_ROOT_DIR}/include/vtk-8.1
    ${ITK_ROOT_DIR}/include/ITK-4.13
    ${MYSQL_ROOT_DIR}/include
    ${NDI_ROOT_DIR}/include        
    ${QUAZIP_ROOT_DIR}/include    
    ${ZLIB_ROOT_DIR}/include

    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5SerialPort_INCLUDE_DIRS}
    ${Qt5Sql_INCLUDE_DIRS}
    ${Qt5Network_INCLUDE_DIRS}
    ${Qt5MultimediaWidgets_INCLUDE_DIRS}
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:
        QT_NO_DEBUG
        NDEBUG
    >
    _WINDOWS
    UNICODE
    _UNICODE
    WIN32
    QT_MESSAGELOGCONTEXT
    ONE_PROCESS
    WIN32_LEAN_AND_MEAN
    NEW_CUT_MODULE
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od
        >
        $<$<CONFIG:Release>:
            #/Gm;
            /O2;
            -Zc:strictStrings;
        >
        /MP;
        /W3;
        /Zi;
        -Zc:rvalueCast;
        -Zc:inline;
        /Zc:wchar_t
		-wd4251
        /openmp

    )
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(GeneratedFiles/qrc_res_findback.cpp ${FILE_CL_OPTIONS})
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /SAFESEH:NO;
            /INCREMENTAL:NO
        >
        /NOLOGO;
        /DEBUG;
        /SUBSYSTEM:WINDOWS;
        /NXCOMPAT;
        /DYNAMICBASE;
    )
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    TargetAlign
    CAPIcommon
)

SET(VTK_LIBS 
        vtkCommonCore-8.1
        vtkCommonDataModel-8.1
        vtkCommonExecutionModel-8.1
        vtkCommonMath-8.1
        vtkCommonMisc-8.1
        vtkCommonSystem-8.1
        vtkCommonTransforms-8.1
        vtkFiltersCore-8.1
        vtkFiltersGeneral-8.1
        vtkFiltersSources-8.1
        vtkFiltersModeling-8.1
        vtkFiltersExtraction-8.1
        vtkGUISupportQt-8.1
        vtkImagingCore-8.1
        vtkImagingGeneral-8.1
        vtkImagingMath-8.1
        vtkImagingColor-8.1
        vtkImagingStencil-8.1
        vtkInteractionStyle-8.1
        vtkInteractionWidgets-8.1
        vtkIOImage-8.1
        vtkIOCore-8.1
        vtkIOGeometry-8.1
        vtkRenderingAnnotation-8.1
        vtkRenderingCore-8.1
        vtkRenderingFreeType-8.1
        vtkRenderingImage-8.1
        vtkRenderingOpenGL2-8.1
        vtkRenderingContextOpenGL2-8.1
        vtkDICOMParser-8.1
        vtksys-8.1
		vtkInteractionImage-8.1
        vtkIOLegacy-8.1 #vtkpolydatawriter
	)


SET(ITK_LIBS 
		ITKCommon-4.13
        ITKIOGDCM-4.13		
        ITKIOImageBase-4.13
        ITKVTK-4.13		
        ITKIONRRD-4.13	
		itkvnl-4.13
		itkvcl-4.13
		itkvnl_algo-4.13
		itkv3p_netlib-4.13
		itksys-4.13
	)

if(MSVC_TOOLSET_VERSION EQUAL 120)
	set(VTK_LIBS_DEBUG ${VTK_LIBS})
	set(ITK_LIBS_DEBUG ${ITK_LIBS})	
elseif(MSVC_TOOLSET_VERSION EQUAL 141)
	set(VTK_LIBS_DEBUG ${VTK_LIBS})
	list(TRANSFORM VTK_LIBS_DEBUG APPEND "d")
	
	set(ITK_LIBS_DEBUG ${ITK_LIBS})
	list(TRANSFORM ITK_LIBS_DEBUG APPEND "d")
	#list(JOIN VTK_LIBS_DEBUG "\n" msg)
	#MESSAGE(${msg})
endif()


set(ADDITIONAL_LIBRARY_DEPENDENCIES
	TargetAlign
	CAPIcommon
	Qt5::WinMain 
	
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::SerialPort    
    Qt5::Sql
    Qt5::Network
    Qt5::Multimedia
    Qt5::MultimediaWidgets

    $<$<CONFIG:Debug>:
		${VTK_LIBS_DEBUG}
		${ITK_LIBS_DEBUG}
        zlibd
    >
    $<$<CONFIG:Release>:
		${VTK_LIBS}
		${ITK_LIBS}
        zlib
    >

    libmysql

    Dbghelp
)

target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")


target_link_directories(${PROJECT_NAME} PRIVATE
	)

