#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"
#include "vtkElevationFilter.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkLinearSubdivisionFilter.h"

//#include "SaveImage.h"

void main( int argc, char *argv[] )
{
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkSphereSource *sphere = vtkSphereSource::New();
    sphere->SetPhiResolution(10); 
	//Set the number of points in the latitude direction
	sphere->SetThetaResolution(10);
	//Set the number of points in the longitude direction

  vtkElevationFilter *colorIt = vtkElevationFilter::New();
    colorIt->SetInput((vtkDataSet *)sphere->GetOutput());
    colorIt->SetLowPoint(0,0,-1);
    colorIt->SetHighPoint(0,0,1);
	//产生色彩渐变效果

  vtkLinearSubdivisionFilter *butterfly=vtkLinearSubdivisionFilter::New();
    butterfly->SetInput(colorIt->GetOutput());
    butterfly->SetNumberOfSubdivisions(1);

  vtkDataSetMapper *mapper = vtkDataSetMapper::New();
  //可将所有的数据转换成点，线和多角形/三角形然后映射到图形制度
    mapper->SetInput(butterfly->GetOutput());

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
