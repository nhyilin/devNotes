#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"

#include "vtkPolyDataReader.h"
#include "vtkMath.h"
#include "vtkCamera.h"
#include "vtkProperty.h"
#include "vtkGeometryFilter.h"
#include "vtkLinearExtrusionFilter.h"
#include "vtkTriangleFilter.h"

//#include "SaveImage.h"

int main( int argc, char *argv() )
{
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkPolyDataReader *reader=vtkPolyDataReader::New();
    reader-> SetFileName ("usa.vtk");
    reader->Update();

vtkMath *math=vtkMath::New();

vtkGeometryFilter *extractCell[51];
vtkLinearExtrusionFilter *extrude[51];
vtkTriangleFilter *tf[51];
vtkPolyDataMapper *mapper[51];
vtkActor *actor[51];

int i;
for (i=0;i<51;i++)
{
    extractCell[i] =vtkGeometryFilter::New();
		extractCell[i]-> SetInputConnection (reader-> GetOutputPort());
        extractCell[i]-> CellClippingOn();
        extractCell[i]-> SetCellMinimum (i);
        extractCell[i]-> SetCellMaximum (i);

    tf[i]=vtkTriangleFilter::New();
	  tf[i]-> SetInputConnection (extractCell[i] ->GetOutputPort());

    extrude[i]=vtkLinearExtrusionFilter::New();
		extrude[i]-> SetInputConnection (tf[i]-> GetOutputPort());
		extrude[i]-> SetExtrusionType (1);
		extrude[i]-> SetVector (0, 0, 1);
		extrude[i]-> CappingOn();
		extrude[i]-> SetScaleFactor( math-> Random (1, 10));

    mapper[i]=vtkPolyDataMapper ::New();
		mapper[i]-> SetInputConnection (extrude[i]-> GetOutputPort());

    actor[i]=vtkActor ::New();
		actor[i]-> SetMapper (mapper[i]);
		actor[i]-> GetProperty() ->SetColor 
		        (math->Random(0,1),math->Random(0,1),math->Random(0,1));


    renderer-> AddActor (actor[i]);
}

  renderer->SetBackground(1,1,1);
  renWin->SetSize(800,400);

	renderer-> GetActiveCamera()->SetClippingRange( 10.2299, 511.497);
	renderer-> GetActiveCamera()->SetPosition (-119.669, -25.5502, 79.0198);
	renderer-> GetActiveCamera()->SetFocalPoint( -115.96, 41.6709, 1.99546);
	renderer-> GetActiveCamera()->SetViewUp (-0.0013035, 0.753456, 0.657497);
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
