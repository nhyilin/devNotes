#include "vtkActor.h" 
#include "vtkContourFilter.h" 
#include "vtkExtractVOI.h" 
#include "vtkOutlineFilter.h" 
#include "vtkPolyDataMapper.h" 
#include "vtkQuadric.h" 
#include "vtkRenderWindow.h" 
#include "vtkRenderWindowInteractor.h" 
#include "vtkRenderer.h" 
#include "vtkSampleFunction.h"

#include "vtkCamera.h"
#include "vtkProperty.h" 

int main()
{

vtkQuadric *quadric = vtkQuadric::New();
	quadric->SetCoefficients(.5, 1, .2, 0, .1, 0, 0, .2, 0, 0);

vtkSampleFunction *sample = vtkSampleFunction::New();
	sample->SetSampleDimensions(30, 30, 30);
	sample->SetImplicitFunction(quadric);
	sample->ComputeNormalsOff();

vtkExtractVOI *extract = vtkExtractVOI::New();
	extract->SetInputConnection(sample->GetOutputPort());
	extract->SetVOI(0, 29, 0, 29, 5, 25); //**********µ÷ÕûÈıÎ¬ÇĞ¸î
//	extract->SetSampleRate(1, 2, 3);

vtkContourFilter *contours = vtkContourFilter::New();
	contours->SetInputConnection(extract->GetOutputPort());
	contours->GenerateValues(13, 0.0, 1.2);

vtkPolyDataMapper *contMapper = vtkPolyDataMapper::New();
	contMapper->SetInputConnection(contours->GetOutputPort());
	contMapper->SetScalarRange(0.0, 1.2);

vtkActor *contActor = vtkActor::New();
	contActor->SetMapper(contMapper);

vtkOutlineFilter *outline = vtkOutlineFilter::New();
	outline->SetInputConnection(sample->GetOutputPort());

vtkPolyDataMapper *outlineMapper = vtkPolyDataMapper::New();
	outlineMapper->SetInputConnection(outline->GetOutputPort());

vtkActor *outlineActor = vtkActor::New();
	outlineActor->SetMapper(outlineMapper);
	outlineActor->GetProperty()->SetColor(0, 0, 0);

vtkRenderer *ren1 = vtkRenderer::New();
vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer(ren1);
vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);

	ren1->SetBackground(1, 1, 1);
	ren1->AddActor(contActor);
	ren1->AddActor(outlineActor);

	ren1->ResetCamera();
	ren1->GetActiveCamera()->Zoom( 1.5 );
	renWin->Render();
	iren->Initialize();
	iren->Start();

	return 0;
} 
