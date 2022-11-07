#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkSTLReader.h"
#include "vtkOBBDicer.h"
#include "vtkCamera.h"
#include "vtkProperty.h"
#include "vtkOutlineCornerFilter.h"


//#include "SaveImage.h"

int main( int argc, char *argv() )
{
    vtkRenderer *renderer = vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
        renWin->AddRenderer(renderer);
    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
        iren->SetRenderWindow(renWin);

	vtkSTLReader *reader=vtkSTLReader::New();
		reader-> SetFileName ("42400-IDGH.stl");

	vtkOBBDicer *dicer=vtkOBBDicer::New();
		dicer-> SetInputConnection( reader-> GetOutputPort());
		dicer-> SetNumberOfPointsPerPiece( 1000);
		dicer-> Update();

	vtkDataSetMapper *isoMapper=vtkDataSetMapper::New();
		isoMapper-> SetInputConnection (dicer-> GetOutputPort());
		isoMapper-> SetScalarRange( 0 ,dicer-> GetNumberOfActualPieces());

	vtkActor *isoActor=vtkActor::New();
		isoActor-> SetMapper (isoMapper);
		isoActor-> GetProperty() ->SetColor( 0.7 ,0.3 ,0.3);

	vtkOutlineCornerFilter *outline=vtkOutlineCornerFilter::New();
		outline ->SetInputConnection (reader-> GetOutputPort());

	vtkPolyDataMapper *outlineMapper=vtkPolyDataMapper::New();
		outlineMapper ->SetInputConnection (outline ->GetOutputPort());

	vtkActor *outlineActor=vtkActor::New();
		outlineActor ->SetMapper (outlineMapper);
		outlineActor ->GetProperty() ->SetColor (0 ,0 ,0);

	renderer-> AddActor (outlineActor);
	renderer-> AddActor (isoActor);
	renderer-> SetBackground (1 ,1 ,1);
	renWin-> SetSize (400 ,400);

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
