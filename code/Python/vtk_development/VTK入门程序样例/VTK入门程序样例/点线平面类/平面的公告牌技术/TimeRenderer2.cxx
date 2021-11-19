

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

vtkRenderer *ren1;
vtkRenderWindowInteractor *iren;
vtkInteractorStyleTrackballCamera *style;
vtkPlaneSource *plane[10];
vtkRenderWindow *renWindow;
 
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

  vtkPolyDataMapper *mapper[16];
  vtkActor *actor[16];

  for(int i=0;i<16;i++)
	{
	  plane[i] = vtkPlaneSource::New();
		plane[i]->SetResolution(5,5);
		plane[i]->Update();

		mapper[i] = vtkPolyDataMapper::New();
		mapper[i]->SetInputConnection(plane[i]->GetOutputPort());
  
	  actor[i] = vtkActor::New();
		actor[i]->SetMapper(mapper[i]);
		actor[i]->GetProperty()->SetColor (i/8 ,(i)/4%2,(i)%2 );
		actor[i]->SetPosition(i/2*3, 3*(i%2), 0);

      ren1->AddActor(actor[i]);
  }
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
  renWindow->Render();
  iren->Start();
//  plane->SetNormal(ren1->GetActiveCamera()->GetViewPlaneNormal());

  ren1->Delete();
  renWindow->Delete();

  return 1;
}

void left(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
//    plane->SetNormal(ren1->GetActiveCamera()->GetViewPlaneNormal());
	style->OnLeftButtonDown();
}
void move(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
	for(int i=0;i<16;i++)
	  plane[i]->SetNormal(ren1->GetActiveCamera()->GetViewPlaneNormal());
	style->OnMouseMove();
}
