#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkConeSource.h"
#include "vtkGlyph3D.h"
#include "vtkCamera.h"
#include "vtkTextProperty.h"
#include "vtkTextMapper.h"
#include "vtkScaledTextActor.h"
#include "vtkVectorText.h"
#include "vtkFollower.h"
#include "vtkProperty.h"


void main( int argc, char *argv[] )
{
  // create the rendering objects
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  // create the pipline, ball and spikes
  vtkSphereSource *sphere = vtkSphereSource::New();
    sphere->SetThetaResolution(7); 
	sphere->SetPhiResolution(7);
  vtkPolyDataMapper *sphereMapper = vtkPolyDataMapper::New();
    sphereMapper->SetInput(sphere->GetOutput());
  vtkActor *sphereActor = vtkActor::New();
    sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetColor(0.8,0.1,0.8);

  vtkConeSource *cone = vtkConeSource::New();
    cone->SetResolution(20);
  vtkGlyph3D *glyph = vtkGlyph3D::New();
    glyph->SetInput((vtkDataSet *)sphere->GetOutput());
    glyph->SetSource(cone->GetOutput());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleModeToScaleByVector();
    glyph->SetScaleFactor(0.25);
  vtkPolyDataMapper *spikeMapper = vtkPolyDataMapper::New();
    spikeMapper->SetInput(glyph->GetOutput());
  vtkActor *spikeActor = vtkActor::New();
    spikeActor->SetMapper(spikeMapper);
//  spikeActor->GetProperty()->SetColor(0.8,0.8,0.8);

  vtkTextMapper *textActor=vtkTextMapper::New();
    textActor->GetTextProperty()->SetFontSize(50);
    textActor->SetInput ("This is a sphere");

  vtkScaledTextActor *mmm=vtkScaledTextActor::New();
	mmm->SetMapper(textActor);
	mmm->SetDisplayPosition(90, 50 );


vtkVectorText *atext=vtkVectorText::New();
    atext->SetText( "CHIQIU");
vtkPolyDataMapper *textMapper=vtkPolyDataMapper::New();
    textMapper-> SetInputConnection (atext->GetOutputPort());
vtkFollower *textActor2=vtkFollower::New();
    textActor2->SetMapper( textMapper);
    textActor2->SetScale (0.2, 0.2, 0.2);
    textActor2->AddPosition( 0,0.5, 0);


  ren1->AddActor(sphereActor);
  ren1->AddActor(spikeActor);
  ren1->AddActor2D(mmm);
  ren1->SetBackground(0,1,1);
  renWin->SetSize(600,600);

  // do the first render and then zoom in a little
  renWin->Render();
  ren1->GetActiveCamera()->Zoom(1.4);
  //renWin->StereoRenderOn();
  //renWin->SetStereoTypeToRedBlue();
  renWin->Render();
  
  iren->Start();

  //SAVEIMAGE( renWin );

  // Clean up
  ren1->Delete();
  renWin->Delete();
  iren->Delete();
  sphere->Delete();
  sphereMapper->Delete();
  sphereActor->Delete();
  cone->Delete();
  glyph->Delete();
  spikeMapper->Delete();
  spikeActor->Delete();
}
