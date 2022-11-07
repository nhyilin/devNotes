#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkVectorText.h"
#include "vtkTransform.h"
#include "vtkTransformFilter.h"
#include "vtkCamera.h"
#include "vtkProperty.h"
#include "vtkStripper.h"
#include "vtkPolyDataMapper.h"
#include "vtkAppendPolyData.h"
#include "vtkLinearExtrusionFilter.h"
#include "vtkMath.h"
#include "vtkUnsignedCharArray.h"
#include "vtkArrowSource.h"
#include "vtkCellData.h"

int main( int argc, char *argv() )
{
    vtkRenderer *renderer = vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
        renWin->AddRenderer(renderer);
    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
        iren->SetRenderWindow(renWin);

vtkVectorText *disk=vtkVectorText::New();
  disk-> SetText ("Q");

vtkTransform *t=vtkTransform::New();
  t-> Translate( 1.1, 0, 0);
vtkTransformFilter *tf=vtkTransformFilter::New();
  tf-> SetTransform( t);
  tf-> SetInputConnection( disk-> GetOutputPort());
vtkStripper *strips=vtkStripper::New();
  strips-> SetInputConnection (tf-> GetOutputPort());

vtkAppendPolyData *app=vtkAppendPolyData::New();
  app-> AddInput ( disk ->GetOutput());
  app-> AddInput ( strips-> GetOutput());
  app-> Update();

int numcell=app-> GetOutput()->GetNumberOfCells();

vtkLinearExtrusionFilter *extrude=vtkLinearExtrusionFilter::New();
  extrude-> SetInput (app-> GetOutput());

vtkPolyDataMapper *mapper=vtkPolyDataMapper::New();
   mapper-> SetInputConnection (extrude-> GetOutputPort());

vtkActor *actor=vtkActor::New();
    actor-> SetMapper (mapper);

// create random cell scalars for the model before extrusion.

vtkMath *rn=vtkMath::New();
  rn-> RandomSeed (1230);
vtkUnsignedCharArray *cellColors=vtkUnsignedCharArray::New();
  cellColors-> SetNumberOfComponents (3);
  cellColors-> SetNumberOfTuples (numcell);
for(int i=0;i<numcell;i++)
{
    cellColors-> InsertComponent (i ,0 ,rn-> Random( 100 ,255));
    cellColors-> InsertComponent (i ,1 ,rn-> Random( 100 ,255));
    cellColors-> InsertComponent (i ,2 ,rn-> Random( 100 ,255));
}

app-> GetOutput()->GetCellData()->SetScalars(cellColors);



//Lets test the arrow source instead of creating another test.
vtkArrowSource *arrow1=vtkArrowSource::New();

vtkPolyDataMapper *mapper1=vtkPolyDataMapper::New();
  mapper1-> SetInputConnection (arrow1-> GetOutputPort());

vtkActor *actor1 =vtkActor::New();
  actor1-> SetMapper (mapper1 );
  actor1-> SetPosition (0, -0.2, 1);

vtkArrowSource *arrow2=vtkArrowSource::New();
  arrow2-> SetShaftResolution( 2);
  arrow2-> SetTipResolution( 1);

vtkPolyDataMapper *mapper2=vtkPolyDataMapper::New();
  mapper2-> SetInputConnection (arrow2-> GetOutputPort());

vtkActor *actor2 =vtkActor::New();
  actor2-> SetMapper (mapper2);
  actor2-> SetPosition( 1 ,-0.2 ,1);

	renderer-> AddActor (actor);
	renderer-> AddActor (actor1);
	renderer-> AddActor (actor2);
	renderer-> SetBackground (1 ,1 ,1);
	renWin-> SetSize (600 ,600);

  // interact with data
  renWin->Render();

 // SAVEIMAGE( renWin );

  iren->Start();

  // Clean up
  renderer->Delete();
  renWin->Delete();
  iren->Delete();

  return 0;
}
