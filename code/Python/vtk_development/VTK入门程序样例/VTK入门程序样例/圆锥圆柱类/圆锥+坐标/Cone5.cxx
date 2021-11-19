#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkLineSource.h"
#include "vtkCubeAxesActor2D.h"
#include "vtkTextProperty.h"

//#include "SaveImage.h"

void main( int argc, char *argv[] )
{
  
  // create a rendering window and renderer
  vtkRenderer *ren = vtkRenderer::New();
  vtkRenderWindow *renWindow = vtkRenderWindow::New();
    renWindow->AddRenderer(ren);
  renWindow->SetSize( 300, 300 );

    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWindow);

  // create an actor and give it cone geometry
  vtkConeSource *cone = vtkConeSource::New();
    cone->SetResolution(18);

  vtkLineSource *Line=vtkLineSource::New();
  
  Line->SetPoint1(13.9548, -0.47371, 31.7642);
  Line->SetPoint2(6.3766, -0.5886, 26.6274);
  Line->SetResolution(20);


  vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
    coneMapper->SetInput(cone->GetOutput());
  vtkActor *coneActor = vtkActor::New();
    coneActor->SetMapper(coneMapper);

  // assign our actor to the renderer
  ren->AddActor(coneActor);

  vtkTextProperty *tprop=vtkTextProperty::New();
    tprop-> SetColor(0, 0, 1);
    tprop-> ShadowOn();

  vtkCubeAxesActor2D *axes=vtkCubeAxesActor2D::New();
    axes-> SetInput (cone-> GetOutput());
    axes-> SetCamera (ren-> GetActiveCamera());
//  axes-> SetFlyModeToOuterEdges();
//	axes->SetFlyModeToClosestTriad();
	axes->ScalingOff();
	axes->DragableOff();  
	axes->SetNumberOfLabels  (4);  
    axes-> SetFontFactor(0.8);
    axes-> SetAxisTitleTextProperty(tprop);
    axes-> SetAxisLabelTextProperty(tprop);
	axes->SetFontFactor (5);

	cout<<"SetFlyMode:"<<axes->GetFlyMode  ()<<endl;

ren->AddActor(axes);

  // draw the resulting scene
  renWindow->Render();

//  SAVEIMAGE( renWindow );
iren->Start();
  // loop until key is pressed
  //cout << "Press any key followed by <Enter> to exit>> ";
 // cin >> a;

  if(ren->GetActors()->IsItemPresent(coneActor))
   {
   ren->RemoveActor(coneActor);
   }
  coneActor->Delete();
  coneMapper->Delete();
  cone->Delete();

  renWindow->Delete();
  ren->Delete();

  // Clean up
}
