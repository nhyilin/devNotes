
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkLight.h"
#include "vtkProperty.h"

void main( )
{
  vtkRenderer *aren = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(aren);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkSphereSource *sphere1 = vtkSphereSource::New();
    sphere1->SetThetaResolution(30); 
	sphere1->SetPhiResolution(30);
    sphere1->SetRadius(6);

  vtkPolyDataMapper *innerMapper = vtkPolyDataMapper::New();
    innerMapper->SetInput(sphere1->GetOutput());

  vtkActor *innerSphere = vtkActor::New();
    innerSphere->SetMapper(innerMapper);
    innerSphere->GetProperty()->SetColor (1, 1, 1);

  aren->AddActor(innerSphere);
  aren->SetBackground (0,0,0);

  vtkLight *lightred = vtkLight::New();
    lightred->SetColor (1, 0, 0);
    lightred->SetFocalPoint(0,0,0);
    lightred->SetPosition(10,0,0);

  vtkLight *lightgreen = vtkLight::New();
    lightgreen->SetColor (0, 1, 0);
    lightgreen->SetFocalPoint(0,0,0);
    lightgreen->SetPosition(0,10,0);

  vtkLight *lightblue = vtkLight::New();
    lightblue->SetColor ( 0, 0, 1);
    lightblue->SetFocalPoint(0,0,0);
    lightblue->SetPosition(0,0,10);

  vtkLight *lightwhite = vtkLight::New();
    lightwhite->SetColor ( 1, 1, 1);
    lightwhite->SetFocalPoint(0,0,0);
    lightwhite->SetPosition(-10,-10,-10);

    aren->AddLight(lightred); 
    aren->AddLight(lightgreen); 
    aren->AddLight(lightblue); 
    aren->AddLight(lightwhite); 


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
