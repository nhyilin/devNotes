#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkQuadric.h"
#include "vtkSampleFunction.h"
#include "vtkContourFilter.h"
#include "vtkOutlineFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkProperty2D.h"
#include "vtkTextProperty.h"
#include "vtkDataSetToDataObjectFilter.h"

#include "SaveImage.h"
#include "vtkParallelCoordinatesActor.h"

int main( int argc, char *argv[] )
{
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);
  renWin->SetSize( 300, 300 );
  
  // Quadric definition
  vtkQuadric *quadric = vtkQuadric::New();
    quadric->SetCoefficients(0.5,1,.2,0,.1,0,0,.2,0,0);

  vtkSampleFunction *sample = vtkSampleFunction::New();
    sample->SetSampleDimensions(30,30,30);
    sample->SetImplicitFunction(quadric);

  // Create five surfaces F(x,y,z) = constant between range specified
  vtkContourFilter *contours = vtkContourFilter::New();
    contours->SetInput((vtkDataSet *)sample->GetOutput());
    contours->GenerateValues(5, 0.0, 1.2);
    contours->Update();

  vtkPolyDataMapper *contMapper = vtkPolyDataMapper::New();
    contMapper->SetInput(contours->GetOutput());
    contMapper->SetScalarRange(0.0, 1.2);

  vtkActor *contActor = vtkActor::New();
    contActor->SetMapper(contMapper);

  // Create outline
  vtkOutlineFilter *outline = vtkOutlineFilter::New();
    outline->SetInput((vtkDataSet *)sample->GetOutput());

  vtkPolyDataMapper *outlineMapper = vtkPolyDataMapper::New();
    outlineMapper->SetInput(outline->GetOutput());

  vtkActor *outlineActor = vtkActor::New();
    outlineActor->SetMapper(outlineMapper);
    outlineActor->GetProperty()->SetColor(0,0,0);

vtkDataSetToDataObjectFilter *ds2do=vtkDataSetToDataObjectFilter::New();
    ds2do-> SetInputConnection(sample-> GetOutputPort());

vtkParallelCoordinatesActor *actor=vtkParallelCoordinatesActor::New();
    actor-> SetInput(ds2do-> GetOutput());
    actor-> SetTitle("Parallel Coordinates");
    actor-> SetIndependentVariablesToColumns();
    actor-> GetPositionCoordinate()-> SetValue( 0.05, 0.05, 0.0);
    actor-> GetPosition2Coordinate()-> SetValue( 0.95, 0.85, 0.0);
    actor-> GetProperty()-> SetColor( 1, 0, 0);
    actor-> GetTitleTextProperty()-> SetColor(0,0,1);
    actor-> GetLabelTextProperty()-> SetColor(0,0,1); 


  ren1->SetBackground(1,1,1);
  ren1->AddActor(contActor);
//  ren1->AddActor(actor);
//  ren1->AddActor(outlineActor);

  renWin->Render();

  SAVEIMAGE( renWin );

  // interact with data
  iren->Initialize();
  iren->Start();

  // Clean up
  ren1->Delete();
  renWin->Delete();
  iren->Delete();
  quadric->Delete();
  sample->Delete();
  contours->Delete();
  contMapper->Delete();
  contActor->Delete();
  outline->Delete();
  outlineMapper->Delete();
  outlineActor->Delete();

  return( 1 );
}
