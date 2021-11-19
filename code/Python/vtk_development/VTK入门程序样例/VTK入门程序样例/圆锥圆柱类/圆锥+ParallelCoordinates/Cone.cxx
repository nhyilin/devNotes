#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderWindowInteractor.h"

#include "vtkDataSetToDataObjectFilter.h"
#include "vtkParallelCoordinatesActor.h"
#include "vtkProperty2D.h"
#include "vtkTextProperty.h"

void main( int argc, char *argv[] )
{
  // create a rendering window and renderer
  vtkRenderer *ren = vtkRenderer::New();
  vtkRenderWindow *renWindow = vtkRenderWindow::New();
    renWindow->AddRenderer(ren);
  renWindow->SetSize( 300, 300 );

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWindow);//½»»¥×÷ÓÃ

  // create an actor and give it cone geometry
  vtkConeSource *cone = vtkConeSource::New();
    cone->SetResolution(200);
  vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
    coneMapper->SetInput(cone->GetOutput());
  vtkActor *coneActor = vtkActor::New();
    coneActor->SetMapper(coneMapper);


vtkDataSetToDataObjectFilter *ds2do=vtkDataSetToDataObjectFilter::New();
    ds2do-> SetInputConnection(cone-> GetOutputPort());

vtkParallelCoordinatesActor *actor=vtkParallelCoordinatesActor::New();
    actor-> SetInput((vtkDataObject *)ds2do-> GetOutput());
    actor-> SetTitle("Parallel Coordinates");
    actor-> SetIndependentVariablesToColumns();
//	actor-> SetIndependentVariablesToRows ();
    actor-> GetPositionCoordinate()-> SetValue( 0.05, 0.05, 0.0);
//    actor-> GetPosition2Coordinate()-> SetValue( 0.95, 0.85, 0.0);
    actor-> GetProperty()-> SetColor( 0.5, 0, 0.3);
    actor-> GetTitleTextProperty()-> SetColor(0,0,1);
    actor-> GetLabelTextProperty()-> SetColor(0,0,1); 



  // assign our actor to the renderer
  ren->AddActor(coneActor);
  ren->AddActor(actor);

  // draw the resulting scene
  renWindow->Render();

  iren->Start();

//  SAVEIMAGE( renWindow );
   // Clean up
  ren->Delete();
  renWindow->Delete();
  cone->Delete();
  coneMapper->Delete();
  coneActor->Delete();
}
