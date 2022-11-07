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

  vtkPolyData *cube = vtkPolyData::New();//poly�������˼
    //��������������ֶ��㣬�ߣ�����κ�������
    //vtkPolyData �� vtkDataSet �ľ�����ʵ��һ���������塣
    //vtkPolyData �����ж��㣬�ߣ�����κ������γ����ļ���ѧ�Ľṹ��
  vtkPoints *points = vtkPoints::New();
  vtkCellArray *polys = vtkCellArray::New();
  vtkIntArray *scalars = vtkIntArray::New();//�������ǿ���ɫ��
    //vtkIntArray ���������������ֵ����С� ���ṩ����������������������ֵ��ȡ��, 
    //���ҽ����Զ����ٰ��涨�ߴ�����������֧���µ�����

  for (i=0; i<8; i++) points->InsertPoint(i,x[i]);//8����
  for (i=0; i<6; i++) polys->InsertNextCell(4,pts[i]);//��ʾ�������������
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
