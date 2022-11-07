#!/Users/peiyilin/opt/anaconda3/envs/vtk_test/bin/python
# -*- coding: utf-8 -*-

import vtk

Points = vtk.vtkPoints()
Points.InsertNextPoint(1.0, 0.0, 0.0)
Points.InsertNextPoint(0.0, 0.0, 0.0)
Points.InsertNextPoint(0.0, 1.0, 0.0)

polydata = vtk.vtkPolyData()
polydata.SetPoints(Points)
if vtk.VTK_MAJOR_VERSION <= 5:
    polydata.Update()

writer = vtk.vtkXMLPolyDataWriter()
writer.SetFileName("TrianglePoints.vtp")
if vtk.VTK_MAJOR_VERSION <= 5:
    writer.SetInput(polydata)
else:
    writer.SetInputData(polydata)
writer.Write()
