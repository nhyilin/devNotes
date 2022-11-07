

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
#include "vtkArcPlotter.h"
#include "vtkPolyDataReader.h"
#include "vtkProperty.h"

int main( )
{
  
  vtkRenderer *ren1 = vtkRenderer::New();
    ren1->GetCullers()->InitTraversal();
  vtkRenderWindow *renWindow = vtkRenderWindow::New();
    renWindow->AddRenderer(ren1);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWindow);

  vtkPlaneSource *plane = vtkPlaneSource::New();
    plane->SetResolution(50,50);
    plane->Update();

  vtkPolyDataReader *linder=vtkPolyDataReader::New();
    linder ->SetFileName("track3.binary.vtk");
    linder->Update();

  vtkCamera *camera;
  camera = vtkCamera::New();

  vtkArcPlotter *ap=vtkArcPlotter::New();
    ap-> SetInputConnection (linder-> GetOutputPort());
    ap-> SetCamera (camera);
    ap-> SetRadius (250.0);
    ap-> SetHeight (200.0);
//    ap-> UseDefaultNormalOn();
//    ap-> SetDefaultNormal(1, 1, 0);
    ap->Update();

  vtkPolyDataMapper *mapper;
    mapper = vtkPolyDataMapper::New();
    mapper->SetInputConnection(ap->GetOutputPort());
  
  vtkActor *actor;
  actor = vtkActor::New();
    actor->SetMapper(mapper);
	actor->GetProperty()->SetColor (1 ,0 ,1);

  ren1->AddActor(actor);
  renWindow->SetSize(500,500);  
  ren1->SetBackground(0.2,0.3,0.5);

	camera-> SetClippingRange( 14144, 32817);
	camera-> SetFocalPoint( -1023, 680, 5812);
	camera-> SetPosition( 15551, -2426, 19820);
	camera-> SetViewUp( -0.651889, -0.07576, 0.754521);
	camera-> SetViewAngle( 20);


  // draw the resulting scene
  renWindow->Render();
  ren1->SetActiveCamera(camera);
  renWindow->Render();

  iren->Start();
//  plane->SetNormal(ren1->GetActiveCamera()->GetViewPlaneNormal());

  // Clean up
  ren1->Delete();
  renWindow->Delete();

  return 1;
}
