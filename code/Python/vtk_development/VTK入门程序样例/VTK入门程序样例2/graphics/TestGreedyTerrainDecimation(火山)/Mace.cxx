#include "vtkDEMReader.h" 
#include "vtkGreedyTerrainDecimation.h" 
#include "vtkLODActor.h" 
#include "vtkLookupTable.h" 
#include "vtkPolyDataMapper.h" 
#include "vtkPolyDataNormals.h" 
#include "vtkRenderWindow.h" 
#include "vtkRenderWindowInteractor.h" 
#include "vtkRenderer.h" 
#include "vtkCamera.h"
#include "vtkImageData.h"


int main()
{
vtkLookupTable *lut = vtkLookupTable::New();
	lut->SetHueRange(0.6, 0);
	lut->SetSaturationRange(1.0, 0);
	lut->SetValueRange(0.5, 1.0);

// Read the data: a height field results
vtkDEMReader *demReader = vtkDEMReader::New();
	demReader->SetFileName("SainteHelens.dem");
	demReader->Update();

	double *lindex = demReader->GetOutput()->GetScalarRange();
	double lo,hi;
	lo = lindex[0];
	hi = lindex[1];

// Decimate the terrain
vtkGreedyTerrainDecimation *deci = vtkGreedyTerrainDecimation::New();
	deci->SetInputConnection(demReader->GetOutputPort());
	deci->BoundaryVertexDeletionOn();
	//  deci SetErrorMeasureToSpecifiedReduction
	//  deci SetReduction 0.95
	deci->SetErrorMeasureToNumberOfTriangles();
	deci->SetNumberOfTriangles(5000);
	//  deci SetErrorMeasureToAbsoluteError
	//  deci SetAbsoluteError 25.0
	//  deci SetErrorMeasureToRelativeError
	//  deci SetAbsoluteError 0.01

vtkPolyDataNormals *normals = vtkPolyDataNormals::New();
	normals->SetInputConnection(deci->GetOutputPort());
	normals->SetFeatureAngle(60);
	normals->ConsistencyOn();
	normals->SplittingOff();

vtkPolyDataMapper *demMapper = vtkPolyDataMapper::New();
	demMapper->SetInputConnection(normals->GetOutputPort());
	demMapper->SetScalarRange(lo, hi);
	demMapper->SetLookupTable(lut);

vtkLODActor *actor = vtkLODActor::New();
	actor->SetMapper(demMapper);

// Create the RenderWindow, Renderer and both Actors
//
vtkRenderer *ren1 = vtkRenderer::New();
vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer(ren1);
vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);

// Add the actors to the renderer, set the background and size
//
	ren1->AddActor(actor);
	ren1->SetBackground(.1, .2, .4);

//iren->AddObserver(UserEvent, {wm, deiconify, .vtkInteract});
	iren->SetDesiredUpdateRate(5);

	ren1->GetActiveCamera()->SetViewUp(0, 0, 1);
	ren1->GetActiveCamera()->SetPosition(-99900, -21354, 131801);
	ren1->GetActiveCamera()->SetFocalPoint(41461, 41461, 2815);
	ren1->ResetCamera();
	ren1->GetActiveCamera()->Dolly( 1.2 );
	ren1->ResetCameraClippingRange();
	renWin->SetSize(800,400);

	renWin->Render();
	
	iren->Initialize();
	iren->Start();

	return 0;

}