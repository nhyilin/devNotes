
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkLight.h"
#include "vtkProperty.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkCommand.h"
#include "vtkCallbackCommand.h"

vtkInteractorStyleTrackballCamera *style;
vtkActor *innerSphere;
vtkRenderWindowInteractor *iren;
vtkRenderWindow *renWin;
double r=0.5,g=0.5,b=0.5;

void keypress(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
	char key=iren->GetKeyCode();		  

	switch (key)
    {
      case '1':
		  r=r+0.1;
		  break;
      case '2':
		  r=r-0.1;
		  break;
      case '4':
		  g=g+0.1;
		  break;
      case '5':
		  g=g-0.1;
		  break;
      case '7':
		  b=b+0.1;
		  break;
      case '8':
		  b=b-0.1;
		  break;

	}
	printf(" point:%f, %f, %f; \n",r,
								   g,b);
	innerSphere->GetProperty()->SetColor (r, g, b);
	renWin->Render();
}

void main( )
{
  vtkRenderer *aren = vtkRenderer::New();
  renWin = vtkRenderWindow::New();
    renWin->AddRenderer(aren);
  iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);
  style=vtkInteractorStyleTrackballCamera::New();
    iren-> SetInteractorStyle(style);

  vtkSphereSource *sphere1 = vtkSphereSource::New();
    sphere1->SetThetaResolution(30); 
	sphere1->SetPhiResolution(30);
    sphere1->SetRadius(6);

  vtkPolyDataMapper *innerMapper = vtkPolyDataMapper::New();
    innerMapper->SetInput(sphere1->GetOutput());

  innerSphere = vtkActor::New();
    innerSphere->SetMapper(innerMapper);
    innerSphere->GetProperty()->SetColor (0.5, 0.5, 0.5);

  aren->AddActor(innerSphere);
  aren->SetBackground (0,0,0);

  vtkCallbackCommand * cmd1 = vtkCallbackCommand::New();
	cmd1->SetCallback(keypress);

  style-> AddObserver (vtkCommand::KeyPressEvent,cmd1);

  renWin->SetSize(600,600);

  renWin->Render();

  iren->Start();

  aren->Delete();
  renWin->Delete();
  iren->Delete();
  sphere1->Delete();
  innerMapper->Delete();
  innerSphere->Delete();

}
