#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"
#include "vtkElevationFilter.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkPolyDataNormals.h"
#include "vtkButterflySubdivisionFilter.h"

//#include "SaveImage.h"

void main( int argc, char *argv[] )
{
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkSphereSource *sphere = vtkSphereSource::New();
    sphere->SetPhiResolution(11); 
	//Set the number of points in the latitude direction
	sphere->SetThetaResolution(11);
	//Set the number of points in the longitude direction

  vtkElevationFilter *colorIt = vtkElevationFilter::New();
    colorIt->SetInput((vtkDataSet *)sphere->GetOutput());
    colorIt->SetLowPoint(0,0,-1);
    colorIt->SetHighPoint(0,0,1);
	//����ɫ�ʽ���Ч��

  vtkPolyDataNormals *skinNormals = vtkPolyDataNormals::New();
    skinNormals->SetInputConnection(colorIt->GetOutputPort());
    skinNormals->SetFeatureAngle(0.0);
	//ʹ������Ƭ���ཻ����ƽ��
//	skinNormals->ConsistencyOff();
//   skinNormals->SplittingOn();

  vtkDataSetMapper *mapper = vtkDataSetMapper::New();
  //�ɽ����е�����ת���ɵ㣬�ߺͶ����/������Ȼ��ӳ�䵽ͼ���ƶ�
    mapper->SetInput(skinNormals->GetOutput());

  vtkActor *actor = vtkActor::New();
    actor->SetMapper(mapper);

  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1);
  renWin->SetSize(300,300);

  renWin->Render();

//  SAVEIMAGE( renWin );

  // interact with data
  iren->Start();

  // Clean up
  renderer->Delete();
  renWin->Delete();
  iren->Delete();
  sphere->Delete();
  colorIt->Delete();
  mapper->Delete();
  actor->Delete();
}
