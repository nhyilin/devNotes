

#include "vtkAxesActor.h"
#include "vtkCamera.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkTextProperty.h"


int main( int argc, char *argv[] )
{

  vtkAxesActor* axes = vtkAxesActor::New();

  axes->SetTotalLength( 12, 12 , 12 );
  axes->SetNormalizedShaftLength( 0.95, 0.95, 0.95 );
  axes->SetNormalizedTipLength( 0.05, 0.05, 0.05 );
  axes->AxisLabelsOn();
  axes->SetShaftTypeToCylinder();
  axes->SetCylinderRadius(0.01);
  axes->SetAxisLabels(5);
//  axes->SetShaftTypeToUserDefined();
//  axes->SetTipTypeToUserDefined();


  vtkProperty* property = axes->GetXAxisTipProperty();
  property->SetRepresentationToWireframe();
  property->SetDiffuse(0);
  property->SetAmbient(1);
  property->SetColor( 1, 0, 1 );

  property = axes->GetYAxisTipProperty();
  property->SetRepresentationToWireframe();
  property->SetDiffuse(0);
  property->SetAmbient(1);
  property->SetColor( 1, 1, 0 );

  property = axes->GetZAxisTipProperty();
  property->SetRepresentationToWireframe();
  property->SetDiffuse(0);
  property->SetAmbient(1);
  property->SetColor( 0, 1, 1 );

  // set up the renderer, window, and interactor
  //
  vtkRenderer* renderer = vtkRenderer::New();
  renderer->SetBackground( 0.0980, 0.0980, 0.4392 );

  vtkRenderWindow* renWin = vtkRenderWindow::New();
  renWin->AddRenderer( renderer );
  renWin->SetSize( 400, 400 );

  vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow( renWin );

  renderer->AddViewProp( axes );

  // set up an interesting view
  //
  vtkCamera* camera = renderer->GetActiveCamera();
  camera->SetViewUp( 0, 0, 1 );
  camera->SetFocalPoint( 0, 0, 0 );
  camera->SetPosition( 4.5, 4.5, 2.5 );
  renderer->ResetCameraClippingRange();



  iren->Initialize();
  renWin->Render();
  iren->Start();


  return 0;
}
