#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkQuantizePolyDataPoints.h"
#include "vtkPolyDataNormals.h"
#include "vtkActor.h"
#include "vtkRenderWindowInteractor.h"
//#include "SaveImage.h"

void main( int argc, char *argv[] )
{
 // char a;
  
  // create a rendering window and renderer
  vtkRenderer *ren = vtkRenderer::New();
  vtkRenderWindow *renWindow = vtkRenderWindow::New();
    renWindow->AddRenderer(ren);
  renWindow->SetSize( 300, 300 );

    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWindow);

  // create an actor and give it sphere geometry
  vtkSphereSource *sphere = vtkSphereSource::New();
    sphere->SetThetaResolution(100);
    sphere->SetPhiResolution(50);
    sphere->SetRadius(1.0);

  vtkQuantizePolyDataPoints *quantizer = vtkQuantizePolyDataPoints::New();
  //量化 x ， y,点的 z 坐标
    quantizer->SetQFactor(0.01);
    quantizer->SetInput(sphere->GetOutput());

  vtkPolyDataNormals *normalmaker = vtkPolyDataNormals::New();
    normalmaker->SetInput(quantizer->GetOutput());
    normalmaker->SetFeatureAngle(5.0);
    normalmaker->SetSplitting(1);

  vtkPolyDataMapper *sphereMapper = vtkPolyDataMapper::New();
    sphereMapper->SetInput(normalmaker->GetOutput());
  vtkActor *sphereActor = vtkActor::New();
    sphereActor->SetMapper(sphereMapper);

  // assign our actor to the renderer
  ren->AddActor(sphereActor);

  // draw the resulting scene
  renWindow->Render();

 //SAVEIMAGE( renWindow );
iren->Start();

  if(ren->GetActors()->IsItemPresent(sphereActor))
   {
   ren->RemoveActor(sphereActor);
   }
  sphereActor->Delete();
  sphereMapper->Delete();
  sphere->Delete();
  quantizer->Delete();
  normalmaker->Delete();

  renWindow->Delete();
  ren->Delete();

  // Clean up
}
