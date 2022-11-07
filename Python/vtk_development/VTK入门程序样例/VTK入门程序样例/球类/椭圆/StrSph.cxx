#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"
#include "vtkTransform.h"
#include "vtkTransformFilter.h"
#include "vtkElevationFilter.h"
#include "vtkLookupTable.h"
#include "vtkDataSetMapper.h"
#include "vtkActor2D.h"
#include "vtkCamera.h"
#include "vtkScalarBarActor.h"
#include "SaveImage.h"
#include "vtkCoordinate.h"
#include "vtkPolyDataMapper2D.h" 

void main( int argc, char *argv[] )
{
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkSphereSource *sphere = vtkSphereSource::New();
    sphere->SetThetaResolution(12); 
	sphere->SetPhiResolution(12);

  vtkTransform *aTransform = vtkTransform::New();
    aTransform->Scale(1,1.5,2);

  vtkTransformFilter *transFilter = vtkTransformFilter::New();
    transFilter->SetInput(sphere->GetOutput());
    transFilter->SetTransform(aTransform);  

  vtkElevationFilter *colorIt = vtkElevationFilter::New();
    colorIt->SetInput(transFilter->GetOutput());
    colorIt->SetLowPoint(0,0,-1);
    colorIt->SetHighPoint(0,0,1);

  vtkLookupTable *lut = vtkLookupTable::New();
    lut->SetHueRange(0,0);
    lut->SetSaturationRange(0,0);
    lut->SetValueRange(.1,1);

vtkCoordinate *normCoords=vtkCoordinate::New();
    normCoords->SetCoordinateSystemToWorld();
//    normCoords->SetCoordinateSystemToDisplay (); 
//    normCoords->SetCoordinateSystemToNormalizedDisplay (); 
//    normCoords->SetCoordinateSystemToViewport (); 
//    normCoords->SetCoordinateSystemToNormalizedViewport (); 
//    normCoords->SetCoordinateSystemToView ();

  vtkPolyDataMapper2D *mapper = vtkPolyDataMapper2D::New();
    mapper->SetLookupTable(lut);
    mapper->SetInput((vtkPolyData *)colorIt->GetOutput());
	mapper->SetTransformCoordinate(normCoords);

  vtkActor2D *actor = vtkActor2D::New();
    actor->SetMapper(mapper);

//Create a scalar bar
vtkScalarBarActor *scalarBar=vtkScalarBarActor::New();
    scalarBar-> SetLookupTable(mapper-> GetLookupTable());
    scalarBar-> SetTitle ("Color Table");
    scalarBar-> GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
    scalarBar-> GetPositionCoordinate()-> SetValue(0.1, 0.01);  
//    scalarBar-> GetPositionCoordinate()->
	scalarBar->SetNumberOfLabels(6);  
    scalarBar-> SetOrientationToHorizontal();
    scalarBar-> SetWidth (0.8);
    scalarBar-> SetHeight (0.12);


  renderer->AddActor(actor);
  renderer->AddActor2D(scalarBar);
  renderer->SetBackground(1,1,0);
  renderer->GetActiveCamera()->Elevation(60.0);
  renderer->GetActiveCamera()->Azimuth(30.0);
  renderer->GetActiveCamera()->Zoom(1.3);

  renWin->SetSize(300,300);

  renWin->Render();

  SAVEIMAGE( renWin );

  // interact with data
  iren->Start();

  // Clean up
  renderer->Delete();
  renWin->Delete();
  iren->Delete();
  sphere->Delete();
  aTransform->Delete();
  transFilter->Delete();
  colorIt->Delete();
  lut->Delete();
  mapper->Delete();
  actor->Delete();
}
