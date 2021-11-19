# ******************************
# python interpriter:"#!/Users/peiyilin/opt/anaconda3/envs/vtk_test/bin/python"
# detail discription: to prove the function of invert movement was true.
# ******************************
import vtk
import math
colors = vtk.vtkNamedColors()



# Initialize variable
old_origin = [0, 0, 0]
old_point1 = [3, 5, 4]
old_point2 = [5, 3, 4]

move_and_rotate = [1, 0, 0, 3,
                   0, math.cos(math.pi/2), -math.sin(math.pi/2), 4,
                   0, math.sin(math.pi/2), math.cos(math.pi/2), 5,
                   0, 0, 0, 1]
matrix = vtk.vtkMatrix4x4()
matrix.DeepCopy(move_and_rotate)
# print(matrix)
invert = vtk.vtkMatrix4x4()
invert = matrix
invert.Invert()
# print(invert)



def struct_plane(old_origin,old_point1,old_point2):
    plane = vtk.vtkPlaneSource()
    plane.SetOrigin(old_origin)
    plane.SetPoint1(old_point1)
    plane.SetPoint2(old_point2)
    print("the function was real exist")
    return plane

struct_plane(old_origin,old_point1,old_point2)
# Why is it that when I call this function, I get a different result than if I just did it in order
# i suppose that while i set the class in the function,then the class was not that class beofre 

# the raw plane·
plane01 = vtk.vtkPlaneSource()
plane01.SetOrigin(old_origin)
plane01.SetPoint1(old_point1)
plane01.SetPoint2(old_point2)

# after the transform
trans01 = vtk.vtkTransform()
trans01.SetMatrix(matrix)
new_origin = trans01.TransformDoublePoint(old_origin)
new_point1 = trans01.TransformDoublePoint(old_point1)
new_point2 = trans01.TransformDoublePoint(old_point2)


plane02 = vtk.vtkPlaneSource()
plane02.SetOrigin(new_origin)
plane02.SetPoint1(new_point1)
plane02.SetPoint2(new_point2)

# Invert after the transform
trans02 = vtk.vtkTransform()
trans02.SetMatrix(invert)
invert_origin = trans02.TransformDoublePoint(new_origin)
invert_point1 = trans02.TransformDoublePoint(new_point1)
invert_point2 = trans02.TransformDoublePoint(new_point2)

plane03 = vtk.vtkPlaneSource()
plane03.SetOrigin(invert_origin)
plane03.SetPoint1(invert_point1)
plane03.SetPoint2(invert_point2)

# test my data
# print("old_origin:",old_origin)
# print("new_origin:",new_origin)
# print("old_point1:",old_point1)
# print("new_point1:",new_point1)
# print("old_point2:",old_point2)
# print("new_point2:",new_point2)
# print("the trasnform matrix is:",matrix)
# print("the invert of the transform matrix",invert)

# Complete the definition, and draw three  planes
plane01Mapper = vtk.vtkPolyDataMapper()
plane01Mapper.SetInputConnection(plane01.GetOutputPort())
plane01Actor = vtk.vtkActor()
plane01Actor.SetMapper(plane01Mapper)
plane01Actor.GetProperty().SetColor(colors.GetColor3d('Gold'))

plane02Mapper = vtk.vtkPolyDataMapper()
plane02Mapper.SetInputConnection(plane02.GetOutputPort())
plane02Actor = vtk.vtkActor()
plane02Actor.SetMapper(plane02Mapper)
plane02Actor.GetProperty().SetColor(colors.GetColor3d('Blue'))

plane03Mapper = vtk.vtkPolyDataMapper()
plane03Mapper.SetInputConnection(plane01.GetOutputPort())
plane03Actor = vtk.vtkActor()
plane03Actor.SetMapper(plane01Mapper)
plane03Actor.GetProperty().SetColor(colors.GetColor3d('Purple'))

# Three dimensional coordinate axis
axes = vtk.vtkAxesActor()
axes.SetTotalLength(5, 5, 5)
axes.SetShaftType(0)
axes.SetAxisLabels(0)
axes.SetCylinderRadius(0.02)


# create renderers and add actors
ren01 = vtk.vtkRenderer()
ren01.AddActor(plane01Actor)
ren01.AddActor(axes)
ren01.SetViewport(0, 0, 0.33, 1)
ren01.SetBackground(0.1, 0.2, 0.4)

ren02 = vtk.vtkRenderer()
ren02.AddActor(plane02Actor)
ren02.AddActor(axes)
ren02.SetViewport(0.33, 0, 0.66, 1)
ren02.SetBackground(0.1, 0.2, 0.4)

ren03 = vtk.vtkRenderer()
ren03.AddActor(plane03Actor)
ren03.AddActor(axes)
ren03.SetViewport(0.66, 0, 1, 1)
ren03.SetBackground(0.1, 0.2, 0.4)

#Add renderer to renderwindow and render
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren01)
renWin.AddRenderer(ren02)
renWin.AddRenderer(ren03)
renWin.SetSize(600, 600)

iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
style = vtk.vtkInteractorStyleTrackballActor()
iren.SetInteractorStyle(style)
iren.Initialize()
renWin.Render()
iren.Start()


# 平面1，未参加旋转变换，由三个点，分别为old_origin、old_point1、old_point2定义

# 平面2,第一次空间变换，绕着x轴旋转90°，加入平移向量[3,4,5]

# 平面3,加入invert逆矩阵(理解为第一次空间变换的逆),试图返回第一次的初始化平面,结果得到验证

