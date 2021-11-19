
import vtk




def printme(string):
    print(string)
    return


printme("abc")
# print(a)



def move_actor(name):
    axes = vtk.vtkAxesActor()
    axes.SetTotalLength(10, 10, 10)
    axes.SetShaftType(0)
    axes.SetAxisLabels(0)
    axes.SetCylinderRadius(0.02)
    print("123")
    return

move_actor("a")