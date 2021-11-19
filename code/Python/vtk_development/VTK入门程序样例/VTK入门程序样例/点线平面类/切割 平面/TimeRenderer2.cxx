
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkCullerCollection.h"
#include "vtkPlaneSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkStripper.h"
#include "vtkTimerLog.h"
#include "vtkTriangleFilter.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkClipPolyData.h"
#include "vtkCylinder.h"
#include "vtkTransform.h"

int main( int argc, char *argv[] )
{
  // create a rendering window and both renderers
  vtkRenderer *ren1 = vtkRenderer::New();
  ren1->GetCullers()->InitTraversal();
  //ren1->RemoveCuller(ren1->GetCullers()->GetNextItem());
  vtkRenderWindow *renWindow = vtkRenderWindow::New();
  renWindow->AddRenderer(ren1);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
      iren->SetRenderWindow(renWindow);

  vtkPlaneSource *plane = vtkPlaneSource::New();
  plane->SetResolution(4,4);
  
  vtkPolyDataMapper *mapper;
  vtkActor *actor;
  vtkTriangleFilter *tfilter;
  vtkStripper *stripper;

  mapper = vtkPolyDataMapper::New();
  actor = vtkActor::New();
  tfilter = vtkTriangleFilter::New();
  stripper = vtkStripper::New();
  
  tfilter->SetInputConnection(plane->GetOutputPort());
  stripper->SetInputConnection(tfilter->GetOutputPort());
  
  vtkCylinder * pCylinder = vtkCylinder::New();
		pCylinder->SetRadius(0.2);
		pCylinder->SetCenter(0, 0, 0);

  vtkTransform * pTransform = vtkTransform::New();
	    pTransform->Identity();
		pTransform->RotateX(90);

    pCylinder->SetTransform(pTransform);

  vtkClipPolyData * pClipPolyData = vtkClipPolyData::New();
		pClipPolyData->SetInput(stripper->GetOutput());
		pClipPolyData->SetClipFunction(pCylinder);
		pClipPolyData->InsideOutOff();

  mapper->SetInputConnection(pClipPolyData->GetOutputPort());

  actor->SetMapper(mapper);
  ren1->AddActor(actor);

  renWindow->SetSize(500,500);
  
  ren1->SetBackground(0.2,0.3,0.5);


  renWindow->Render();
  ren1->GetActiveCamera()->Azimuth(3);
  renWindow->Render();
  
  renWindow->Render();

  iren->Start();

  ren1->Delete();
  renWindow->Delete();
  return 1;
}
