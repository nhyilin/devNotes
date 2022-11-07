

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkConeSource.h"
#include "vtkGlyph3D.h"
#include "vtkCamera.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
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

  vtkPoints *points=vtkPoints::New();
		points->InsertNextPoint( 10.48, -187.4, -126.9);
		points->InsertNextPoint( 12.81, -187.7, -126.4 );
		points->InsertNextPoint( 15.44 ,-187.9, -125.9 );
		points->InsertNextPoint( 18.02, -187.7, -125.7 );
		points->InsertNextPoint( 20.23, -187.6, -125.5 );
		points->InsertNextPoint( 21.46, -189.3, -124.2 );
		points->InsertNextPoint( 20.05, -190, -123.9 );
		points->InsertNextPoint( 18.6, -190.1, -124.1 );
		points->InsertNextPoint( 17.14, -190.3, -124.1 );
		points->InsertNextPoint( 15.66, -190.4, -124.3 );

  vtkPolyData *model=vtkPolyData::New();
	  model-> SetPoints( points);

  vtkGlyph3D *glyph = vtkGlyph3D::New();
    glyph->SetInput(model);
    glyph->SetSource(sphere->GetOutput());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleModeToScaleByVector();
    glyph->SetScaleFactor(0.25);
  vtkPolyDataMapper *spikeMapper = vtkPolyDataMapper::New();
    spikeMapper->SetInput(glyph->GetOutput());
  vtkActor *spikeActor = vtkActor::New();
    spikeActor->SetMapper(spikeMapper);
	spikeActor-> GetProperty() ->SetDiffuseColor( 1 ,0 ,0);


  ren1->AddActor(spikeActor);
  ren1->SetBackground(1,1,1);
  renWin->SetSize(600,400);

  renWin->Render();
  ren1->GetActiveCamera()->Zoom(1.4);
  renWin->Render();
  
  iren->Start();

  ren1->Delete();
  renWin->Delete();
  iren->Delete();
  sphere->Delete();
  glyph->Delete();
  spikeMapper->Delete();
  spikeActor->Delete();
}
