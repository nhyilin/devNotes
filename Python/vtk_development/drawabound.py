# ******************************
# python interpriter:!/Users/peiyilin/opt/anaconda3/envs/vtk_test/bin/python
# pic input:
#       pc:input = "E://tmc//vtk_development//femur01.stl"
#       "E:\code\tmc\vtk_development\input01.stl"
#       mac:input = "/Users/peiyilin/code/PyCharm/vtk_development/femur01.stl"
# detail discription: to draw a bone which was cut by a plane,in the same,we`ll show the cut stip in the same time.
# ******************************
import vtk
import math
colors = vtk.vtkNamedColors()
input = "E://tmc//vtk_development//femur01.stl"

old_origin = [10, 10, 10]
old_normal = [3, 40, 50]
old_center = [3, 4, 5]
old_point1 = [0, 5, 0]
old_point2 = [5, 0, 0]
move_and_rotate = [1, 0, 0, 0,
                   0, math.cos(math.pi/6), -math.sin(math.pi/6), 0,
                   0, math.sin(math.pi/6), math.cos(math.pi/6), 0,
                   0, 0, 0, 1]


#imoprt my data
sr = vtk.vtkSTLReader()
sr.SetFileName(input)
sr.Update() # 什么时候需要刷新
stlMapper = vtk.vtkPolyDataMapper()
stlMapper.SetInputConnection(sr.GetOutputPort())
stlActor = vtk.vtkLODActor()
stlActor.SetMapper(stlMapper)


axialx = vtk.vtkMatrix4x4()
axialx.DeepCopy(move_and_rotate)


trans01 = vtk.vtkTransform()
trans01.SetMatrix(axialx)
new_origin =  trans01.TransformDoublePoint(old_origin[0],old_origin[1],old_origin[2])
new_point1 =  trans01.TransformDoublePoint(old_point1)
new_point2 =  trans01.TransformDoublePoint(old_point2)
new_normal = trans01.TransformDoubleVector(old_normal)


planesource = vtk.vtkPlaneSource()
planesource.SetCenter(new_origin)
planesource.SetPoint1(new_point1)
planesource.SetPoint2(new_point2)


planesource.Update()
planeMapper = vtk.vtkPolyDataMapper()
planeMapper.SetInputConnection(planesource.GetOutputPort())
planesourceActor = vtk.vtkActor()
planesourceActor.SetMapper(planeMapper)
planesourceActor.GetProperty().SetColor(0.3, 0.4, 0.5)



cut_plane = vtk.vtkPlane()
cut_plane.SetOrigin(new_origin)
cut_plane.SetNormal(new_normal)
#create cutter
cutter = vtk.vtkCutter()
cutter.SetCutFunction(cut_plane)
cutter.SetInputConnection(sr.GetOutputPort())
cutter.Update()


cutStrips = vtk.vtkStripper()  #Forms loops (closed polylines) from cutter
cutStrips.SetInputConnection(cutter.GetOutputPort())
cutStrips.Update()
cutPoly = vtk.vtkPolyData()  #This trick defines polygons as polyline loop
cutPoly.SetPoints((cutStrips.GetOutput()).GetPoints())
cutPoly.SetPolys((cutStrips.GetOutput()).GetLines())


#切割后的旋转，逆矩阵
axialInvert = vtk.vtkMatrix4x4()
axialInvert = axialx
axialInvert.Invert()
transInvert = vtk.vtkTransform()
transInvert.SetMatrix(axialInvert)
transformFilterInvert = vtk.vtkTransformFilter()
transformFilterInvert.SetTransform(transInvert)
transformFilterInvert.SetInputConnection(cutStrips.GetOutputPort())
transformFilterInvert.Update()

finalMapper = vtk.vtkPolyDataMapper()
finalMapper.SetInputConnection(transformFilterInvert.GetOutputPort())
stripActor = vtk.vtkActor()
stripActor.SetMapper(finalMapper)
stripActor.GetProperty().SetColor(1.0, 0.5, 0)
# stripActor.SetPosition(20, 20, 20)


bound = vtk.vtkOutlineFilter()
bound.SetInputConnection(transformFilterInvert.GetOutputPort())
boundMapper = vtk.vtkPolyDataMapper()
boundMapper.SetInputConnection(bound.GetOutputPort())
boundActor = vtk.vtkActor()
boundActor.SetMapper(boundMapper)
boundActor.GetProperty().SetColor(colors.GetColor3d('Gold'))
# boundActor.SetPosition(20, 20, 20)


cutMapper = vtk.vtkPolyDataMapper()
cutMapper.SetInputData(cutPoly)
cutActor = vtk.vtkActor()
cutActor.SetMapper(cutMapper)
cutActor.GetProperty().SetColor(0.5, 1, 1)
cutActor.GetProperty().SetEdgeColor(0, 1, 0)
cutActor.GetProperty().SetLineWidth(2)
cutActor.GetProperty().EdgeVisibilityOn()
cutActor.GetProperty().SetOpacity(0.7)


# Three dimensional coordinate axis
axes = vtk.vtkAxesActor()
axes.SetTotalLength(10, 10, 10)
axes.SetShaftType(0)
axes.SetAxisLabels(0)
axes.SetCylinderRadius(0.02)

#create renderers and add actors of plane and cube
ren = vtk.vtkRenderer()
ren.AddActor(planesourceActor)
ren.AddActor(stripActor)
ren.AddActor(stlActor)
ren.AddActor(axes)
ren.AddActor(boundActor)


#Add renderer to renderwindow and render
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
renWin.SetSize(600, 600)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
style = vtk.vtkInteractorStyleTrackballCamera()
style.SetDefaultRenderer(ren)
iren.SetInteractorStyle(style)
iren.Initialize()
ren.SetBackground(0, 0, 0)
renWin.Render()
iren.Start()
