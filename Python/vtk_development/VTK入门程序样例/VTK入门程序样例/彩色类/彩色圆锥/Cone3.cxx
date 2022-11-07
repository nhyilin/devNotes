#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkElevationFilter.h"

//#include "SaveImage.h"

void main( int argc, char *argv[] )
{
  // create a rendering window and renderer
  vtkRenderer *ren = vtkRenderer::New();
  vtkRenderWindow *renWindow = vtkRenderWindow::New();
    renWindow->AddRenderer(ren);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWindow);
  renWindow->SetSize( 300, 300 );

  // create an actor and give it cone geometry
  vtkConeSource *cone = vtkConeSource::New();
    cone->SetResolution(128);
	cone->SetHeight(1.5);
	cone->SetRadius(1.5);


  vtkElevationFilter *colorIt = vtkElevationFilter::New();
    colorIt->SetInput((vtkDataSet *)cone->GetOutput());
    colorIt->SetLowPoint(0,0,-1);
    colorIt->SetHighPoint(0,0,1);

  vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
    coneMapper->SetInput((vtkPolyData *)colorIt->GetOutput());
  vtkActor *coneActor = vtkActor::New();
    //coneActor->SetMapper(coneMapper);
	coneActor->GetProperty()->SetInterpolationToPhong();
	coneActor->GetProperty()->SetSpecularPower(100.0);
    coneActor->SetMapper(coneMapper);

  // assign our actor to the renderer
  ren->AddActor(coneActor);

  // draw the resulting scene
  renWindow->Render();

//  SAVEIMAGE( renWindow );

  //  Begin mouse interaction
  iren->Start();

  // Clean up
  ren->Delete();
  renWindow->Delete();
  iren->Delete();
  cone->Delete();
  coneMapper->Delete();
  coneActor->Delete();
}
