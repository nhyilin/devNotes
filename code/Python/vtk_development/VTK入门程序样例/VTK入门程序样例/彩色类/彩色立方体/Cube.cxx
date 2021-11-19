#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyData.h"
#include "vtkPoints.h"
#include "vtkCellArray.h"
#include "vtkIntArray.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkPointData.h"

//#include "SaveImage.h"

void main( int argc, char *argv[] )
{
  int i;
  static float x[8][3]={{0,0,0}, {1,0,0}, {1,1,0}, {0,1,0},
                        {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1}};
  static int pts[6][4]={{0,1,2,3}, {4,5,6,7}, {0,1,5,4},
                        {1,2,6,5}, {2,3,7,6}, {3,0,4,7}};
  
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkPolyData *cube = vtkPolyData::New();//poly多个的意思
    //具体物数据组表现顶点，线，多角形和三角形
    //vtkPolyData 是 vtkDataSet 的具体落实的一个数据物体。
    //vtkPolyData 表现有顶点，线，多角形和三角形长条的几何学的结构。
  vtkPoints *points = vtkPoints::New();
  vtkCellArray *polys = vtkCellArray::New();
  vtkIntArray *scalars = vtkIntArray::New();//在这里是控制色彩
    //vtkIntArray 是完整的事物数字的排列。 它提供方法给插入和完整的事物价值的取回, 
    //而且将会自动地再按规定尺寸制作它本身支撑新的数据

  for (i=0; i<8; i++) points->InsertPoint(i,x[i]);//8顶点
  for (i=0; i<6; i++) polys->InsertNextCell(4,pts[i]);//表示正方体的六个面
  for (i=0; i<8; i++) scalars->InsertValue(i,i);

  cube->SetPoints(points);
  points->Delete();
  cube->SetPolys(polys);
  polys->Delete();
  cube->GetPointData()->SetScalars(scalars);
  scalars->Delete();

  vtkPolyDataMapper *cubeMapper = vtkPolyDataMapper::New();
      cubeMapper->SetInput(cube);
      cubeMapper->SetScalarRange(0,7);
  vtkActor *cubeActor = vtkActor::New();
      cubeActor->SetMapper(cubeMapper);

  vtkCamera *camera = vtkCamera::New();
      camera->SetPosition(1,1,1);
      camera->SetFocalPoint(0,0,0);
	  camera->SetClippingRange(0.0, 0.1);
	  camera->SetRoll(10);
  renderer->AddActor(cubeActor);
      renderer->SetActiveCamera(camera);
      renderer->ResetCamera();
      renderer->SetBackground(1,1,1);
  
  renWin->SetSize(300,300);

  // interact with data
  renWin->Render();

//  SAVEIMAGE( renWin );

  iren->Start();

  // Clean up
  renderer->Delete();
  renWin->Delete();
  iren->Delete();
  cube->Delete();
  //points->Delete();
  //scalars->Delete();
  cubeMapper->Delete();
  cubeActor->Delete();
  camera->Delete();
}
