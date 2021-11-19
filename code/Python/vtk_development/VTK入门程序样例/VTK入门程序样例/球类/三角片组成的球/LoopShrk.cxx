#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"
#include "vtkShrinkFilter.h"
#include "vtkElevationFilter.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkCullerCollection.h"

//#include "SaveImage.h"

void main( int argc, char *argv[] )
{
	vtkRenderer *renderer = vtkRenderer::New();
		renderer->GetCullers()->RemoveAllItems();
	vtkRenderWindow *renWin = vtkRenderWindow::New();
		renWin->AddRenderer(renderer);
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
		iren->SetRenderWindow(renWin);

	vtkSphereSource *sphere = vtkSphereSource::New();
		sphere->SetThetaResolution(12); sphere->SetPhiResolution(12);

	vtkShrinkFilter *shrink = vtkShrinkFilter::New();
		shrink->SetInput((vtkDataSet *)sphere->GetOutput());
		shrink->SetShrinkFactor(0.9);

	vtkElevationFilter *colorIt = vtkElevationFilter::New();
		colorIt->SetInput((vtkDataSet *)shrink->GetOutput());
		colorIt->SetLowPoint(0,0,-0.5);
		colorIt->SetHighPoint(0,0,0.5);

	vtkDataSetMapper *mapper = vtkDataSetMapper::New();
		mapper->SetInput(colorIt->GetOutput());

	vtkActor *actor = vtkActor::New();
		actor->SetMapper(mapper);


	vtkShrinkFilter *shrink2 = vtkShrinkFilter::New();
		shrink2->SetInput((vtkDataSet *)sphere->GetOutput());
		shrink2->SetShrinkFactor(0.1);

	vtkDataSetMapper *mapper2 = vtkDataSetMapper::New();
		mapper2->SetInput((vtkDataSet *)shrink2->GetOutput());

	vtkActor *actor2 = vtkActor::New();
		actor2->SetMapper(mapper2);

//	renderer->AddActor(actor);
	renderer->AddActor(actor2);
	renderer->SetBackground(1,1,1);
	renWin->SetSize(400,400);
  
	renWin->Render(); // execute first time

//	shrink->SetInput(colorIt->GetOutput()); // create loop
//	renWin->Render(); // begin looping

//	SAVEIMAGE( renWin );

	// interact with data
	iren->Start();

	// Clean up
	renderer->Delete();
	renWin->Delete();
	iren->Delete();
	sphere->Delete();
	shrink->Delete();
	colorIt->Delete();
	mapper->Delete();
	actor->Delete();
}
