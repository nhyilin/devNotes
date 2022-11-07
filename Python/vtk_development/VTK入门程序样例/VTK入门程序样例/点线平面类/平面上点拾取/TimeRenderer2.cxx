

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
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkCallbackCommand.h"
#include "vtkPointWidget.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"

vtkRenderer *ren1;
vtkRenderWindowInteractor *iren;
vtkInteractorStyleTrackballCamera *style;
vtkPlaneSource *plane;
vtkActor *actor; 
vtkRenderWindow *renWindow;
vtkCamera *aCamera;
vtkPointWidget *pointWidget;
 
void left(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata);
void keypress(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata);
void move(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata);

int main( )
{
  
  ren1 = vtkRenderer::New();
    ren1->GetCullers()->InitTraversal();
  renWindow = vtkRenderWindow::New();
    renWindow->AddRenderer(ren1);

  iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWindow);

  plane = vtkPlaneSource::New();
	plane->SetResolution(5,5);
//	plane->SetPoint1 (0,0,0);
//	plane->SetPoint2 (200,200,0);
	plane->SetNormal (0,0,1);
	plane->Update();
  vtkPolyDataMapper *mapper;
	mapper = vtkPolyDataMapper::New();
	mapper->SetInputConnection(plane->GetOutputPort());

	actor = vtkActor::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor (1 ,1,1 );
//	actor->GetProperty()->SetOpacity (0.6);
//	actor->SetPosition(i/2*3, 3*(i%2), 0);

  ren1->AddActor(actor);

  renWindow->SetSize(500,500);  
  ren1->SetBackground(0.2,0.3,0.5);

  vtkCallbackCommand * cmd1 = vtkCallbackCommand::New();
	cmd1->SetCallback(left);

  vtkCallbackCommand * cmd2 = vtkCallbackCommand::New();
	cmd2->SetCallback(move);

  style=vtkInteractorStyleTrackballCamera::New();
    style-> AddObserver (vtkCommand::LeftButtonPressEvent,cmd1);
    style-> AddObserver (vtkCommand::MouseMoveEvent, cmd2);
//  style-> AddObserver (vtkCommand::LeftButtonReleaseEvent,cmd);
//	style-> AddObserver (vtkCommand::KeyPressEvent,cmd1);

  iren-> SetInteractorStyle(style);

  aCamera = vtkCamera::New();
	ren1->SetActiveCamera(aCamera);
	ren1->ResetCamera();

  vtkSphereSource *sphere1 = vtkSphereSource::New();
    sphere1->SetRadius(0.05);

  vtkPolyDataMapper *innerMapper = vtkPolyDataMapper::New();
    innerMapper->SetInput(sphere1->GetOutput());

  vtkActor *innerSphere = vtkActor::New();
    innerSphere->SetMapper(innerMapper);
    innerSphere->GetProperty()->SetColor (1, .9216, .8039);
	ren1->AddActor2D(innerSphere);

  pointWidget = vtkPointWidget::New();
	  pointWidget->SetInteractor(iren);
	  pointWidget->SetInput((vtkDataSet *)plane->GetOutput());
	  pointWidget->GetPolyData(sphere1->GetOutput());
	  pointWidget->PlaceWidget();
	  pointWidget->GetProperty()->SetColor(1,0,0);
	  pointWidget->On();



  renWindow->Render();
  iren->Start();

  ren1->Delete();
  renWindow->Delete();

  return 1;
}

void left(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
	style->OnLeftButtonDown();
}
void move(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
	plane->SetNormal(ren1->GetActiveCamera()->GetViewPlaneNormal());
	plane->Update();
	pointWidget->SetInput((vtkDataSet *)plane->GetOutput());
	actor->SetPosition(aCamera->GetFocalPoint()); 
	style->OnMouseMove();
}
