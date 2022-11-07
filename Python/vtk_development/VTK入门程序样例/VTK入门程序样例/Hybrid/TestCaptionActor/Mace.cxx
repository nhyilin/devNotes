
#include "vtkActor.h"
#include "vtkCellLocator.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkRenderer.h"
#include "vtkSphereSource.h"
#include "vtkCaptionActor2D.h"
#include "vtkConeSource.h"
#include "vtkProperty2D.h"
#include "vtkTextProperty.h"
#include "vtkCamera.h"
#include "vtkCoordinate.h"

void main()
{
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

vtkSphereSource *sphere=vtkSphereSource::New();
	sphere-> SetThetaResolution( 20);
    sphere-> SetPhiResolution( 20);
vtkPolyDataMapper *sphereMapper=vtkPolyDataMapper::New();
    sphereMapper-> SetInputConnection (sphere-> GetOutputPort());
vtkActor *sphereActor=vtkActor::New();
    sphereActor-> SetMapper (sphereMapper);

vtkConeSource *coneGlyph=vtkConeSource::New();
    coneGlyph-> SetResolution( 6);

vtkSphereSource *sphereGlyph=vtkSphereSource::New();
    sphereGlyph-> SetThetaResolution( 20);
    sphereGlyph-> SetPhiResolution( 20);

vtkCaptionActor2D *caption=vtkCaptionActor2D::New();
    caption-> SetCaption ("This is the\nsouth pole");
    caption-> SetAttachmentPoint( 0 ,0 ,-0.5);
    caption-> GetPositionCoordinate() ->SetCoordinateSystemToNormalizedViewport();
	vtkCoordinate *c1 = vtkCoordinate::New();
    caption-> GetPositionCoordinate() ->SetReferenceCoordinate(c1 );
    caption-> GetPositionCoordinate() ->SetValue (-0.45 ,-0.45);
    caption-> SetWidth (0.25);
    caption-> SetHeight (0.15);
    caption-> ThreeDimensionalLeaderOn();
    caption-> SetLeaderGlyph (coneGlyph ->GetOutput());
    caption-> SetMaximumLeaderGlyphSize (10);
    caption-> SetLeaderGlyphSize (0.025);
    caption-> GetProperty() ->SetColor( 1, 0, 0);

    caption ->GetCaptionTextProperty()->SetColor
		                               ((caption ->GetProperty())->GetColor());
    caption ->GetCaptionTextProperty()->SetJustificationToCentered();

vtkCaptionActor2D *caption2=vtkCaptionActor2D::New();
    caption2 ->SetCaption( "Santa lives here");
    caption2 ->GetProperty() ->SetColor( 1, 0, 0);
    caption2 ->SetAttachmentPoint( 0, 0, 0.5);
    caption2 ->SetHeight (0.05);
    caption2 ->BorderOff();
    caption2 ->SetPosition (25, 10);
    caption2 ->ThreeDimensionalLeaderOff();
    caption2 ->SetLeaderGlyph (coneGlyph ->GetOutput());
    caption2 ->SetWidth (0.35);
    caption2 ->SetHeight( 0.10);
    caption2 ->SetMaximumLeaderGlyphSize (10);
    caption2 ->SetLeaderGlyphSize (0.025);

    caption2 ->GetCaptionTextProperty() ->SetColor
		                                 (caption2 ->GetProperty()->GetColor());

renderer-> AddActor2D (caption2);
renderer-> AddActor2D (caption);
renderer-> AddActor (sphereActor);
renderer-> SetBackground (1, 1, 1);
renderer-> GetActiveCamera() ->SetFocalPoint( 0, 0, 0);
renderer-> GetActiveCamera() ->SetPosition (1, 0, 0);
renderer-> GetActiveCamera() ->SetViewUp (0 ,0 ,1);
renderer-> ResetCamera();

  renderer->SetBackground(1,1,1);
  renWin->SetSize(600,600);

  // interact with data
  renWin->Render();
  iren->Start();

  // Clean up
  renderer->Delete();
  renWin->Delete();
  iren->Delete();
}
