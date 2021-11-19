#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkRenderWindowInteractor.h"

//#include "SaveImage.h"

void main( int argc, char *argv[] )
{
  int i;

  // create a rendering window and both renderers
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWindow = vtkRenderWindow::New();
    renWindow->AddRenderer(ren1);
  vtkRenderer *ren2 = vtkRenderer::New();
    renWindow->AddRenderer(ren2);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWindow);//交互作用

  // create an actor and give it cone geometry
  vtkConeSource *cone = vtkConeSource::New();
     cone->SetResolution(50);
  vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
    coneMapper->SetInput(cone->GetOutput());
  vtkActor *coneActor = vtkActor::New();
    coneActor->SetMapper(coneMapper);

  // assign our actor to both renderers
  ren1->AddActor(coneActor);
  ren2->AddActor(coneActor);

  // set the size of our window
  renWindow->SetSize(300,150);

  // set the viewports and background of the renderers
  ren1->SetViewport(0,0,0.5,1);
  //在视野坐标中叙述一个点位置。 在视口的中央中的起源是和它扩充从 -1 到 1 在所有的立体中。
  ren1->SetBackground(0.2,0.3,0.5);
  ren2->SetViewport(0.5,0,1,1);
  ren2->SetBackground(0.2,0.5,0.3);

  // draw the resulting scene
  renWindow->Render();
  ren1->LightFollowCameraOff();
  
  // make one view 90 degrees from other
  ren1->GetActiveCamera()->Azimuth(90);

  // do a azimuth of the cameras 9 degrees per iteration
  for (i = 0; i < 36000; i += 9) 
    {
    ren1->GetActiveCamera()->Azimuth(9);
    ren2->GetActiveCamera()->Azimuth(18);
	//Rotate the camera about the view up vector centered at the focal point.
    renWindow->Render();
    }

  //SAVEIMAGE( renWindow );
char c;
  cin >> c;
iren->Start();
  // Clean up
  ren1->Delete();
  renWindow->Delete();
  cone->Delete();
  coneMapper->Delete();
  coneActor->Delete();

}
