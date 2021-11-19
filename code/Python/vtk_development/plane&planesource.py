# ******************************
# python interpriter:"!/Users/peiyilin/opt/anaconda3/envs/vtk_test/bin/python"
# detail:about the plane(drawing and cutting)
# functions:
# author: yilin_pei
# ******************************


import vtk
import math

colors = vtk.vtkNamedColors()

old_origin = [10, 10, 10]
old_normal = [3, 4, 5]
old_center = [3, 4, 5]




# 平面01，利用方法一
plane01 = vtk.vtkPlaneSource()
plane01.SetNormal(old_normal)
plane01.SetCenter(old_center)

# 平面02，利用方法二
plane02 = vtk.vtkPlaneSource()
plane02.SetOrigin(old_origin)
plane02.SetPoint1(0, 5, 0)
plane02.SetPoint2(5, 0, 0)

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

# Three dimensional coordinate axis
axes = vtk.vtkAxesActor()
axes.SetTotalLength(10, 10, 10)
axes.SetShaftType(0)
axes.SetAxisLabels(0)
axes.SetCylinderRadius(0.02)

# create renderers and add actors of plane and cube
ren01 = vtk.vtkRenderer()
ren01.AddActor(plane01Actor)
ren01.AddActor(axes)
ren01.SetViewport(0, 0, 0.5, 1)
ren01.SetBackground(0.1, 0.2, 0.4)

ren02 = vtk.vtkRenderer()
ren02.AddActor(plane02Actor)
ren02.AddActor(axes)
ren02.SetViewport(0.5, 0, 1, 1)
ren02.SetBackground(0.1, 0.2, 0.4)

#Add renderer to renderwindow and render
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren01)
renWin.AddRenderer(ren02)
renWin.SetSize(600, 600)

iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
style = vtk.vtkInteractorStyleTrackballActor()
iren.SetInteractorStyle(style)
iren.Initialize()
renWin.Render()
iren.Start()


# plane有两种绘制方式：
# 1、SetNormal()、SetCenter(),分别设置法向量以及中心点，优点是方便控制，参数简单，缺点是平面面积大小、以及边界难以控制（配合push()函数控制平移）,画出来的平面只能为单位面积。（图中金色平面）

# 2、SetOrigin() SetPoint1() 和SetPoint2()确定不在一条直线上的三个点，决定一个四边形平面，画图中要注意，主视图方向（蓝色坐标轴）为Z，右手放心（红色）为X，纵向（浅绿色）为Y。三点画面，画出矩形。优点是可控参数，大小以及位置，缺点是参数难以控制，需要提前计算。