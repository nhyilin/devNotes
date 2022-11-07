
#include "vtkCamera.h"
#include "vtkPiecewiseFunction.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkVolume.h"
#include "vtkVolumeProperty.h"
#include "vtkVolumeRayCastCompositeFunction.h"
#include "vtkFixedPointVolumeRayCastMapper.h"
#include "vtkVolumeRayCastMapper.h"
#include "vtkColorTransferFunction.h"
#include "vtkActor.h" 
#include "vtkOutlineFilter.h" 
#include "vtkPolyDataMapper.h" 
#include "vtkQuadric.h"
#include "vtkSampleFunction.h"
#include "vtkExtractVOI.h"
#include "vtkProperty.h"

// Create an 8x7 grid of render windows in a renderer and render a volume
// using various techniques for testing purposes
int main( int argc, char *argv[] )
{ 
  // Create the renderers, render window, and interactor
	  vtkRenderWindow *renWin = vtkRenderWindow::New();
	  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	  iren->SetRenderWindow(renWin);
	  vtkRenderer *ren = vtkRenderer::New();
	  renWin->AddRenderer(ren);
  
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

	vtkPiecewiseFunction *opacityTransferFunction = vtkPiecewiseFunction::New();
		opacityTransferFunction->AddPoint(0, 1);
		/*
	    opacityTransferFunction->AddPoint(0.2, 0.2);		
		opacityTransferFunction->AddPoint(0.4, 0.4);
		opacityTransferFunction->AddPoint(0.6, 0.6);
	    opacityTransferFunction->AddPoint(0.8, 0.2);
		*/
		opacityTransferFunction->AddPoint(1.0, 1);
//		opacityTransferFunction->ClampingOn();	
		
	vtkColorTransferFunction *colorTransferFunction = vtkColorTransferFunction::New();
	  colorTransferFunction->AddRGBPoint(0, 1.0, 0, 0);
	  colorTransferFunction->AddRGBPoint(0.20, 0.0, 1.0, 0.0);
      colorTransferFunction->AddRGBPoint(0.40, 0.0, 0.0, 0.1);
      colorTransferFunction->AddRGBPoint(0.6, 1, 1, 0.0);
      colorTransferFunction->AddRGBPoint(0.8, 0, 1, 1);
      colorTransferFunction->AddRGBPoint(1.0, 1, 0, 1);

	vtkVolumeProperty *volumeProperty = vtkVolumeProperty::New();
	  volumeProperty->SetColor(colorTransferFunction);
	  volumeProperty->SetScalarOpacity(opacityTransferFunction);
	  volumeProperty->ShadeOn();
  	  volumeProperty->SetInterpolationTypeToLinear();
	  volumeProperty->SetAmbient(0.2);
      volumeProperty->SetDiffuse(0.9);
      volumeProperty->SetSpecular(0.2);
      volumeProperty->SetSpecularPower(10);	
/*
	vtkVolumeRayCastCompositeFunction *compositeFunction = vtkVolumeRayCastCompositeFunction::New();
		
	vtkVolumeRayCastMapper *volumeMapper = vtkVolumeRayCastMapper::New();
	  volumeMapper->SetVolumeRayCastFunction(compositeFunction);
	  volumeMapper->SetInputConnection(extract->GetOutputPort());
*/
    vtkFixedPointVolumeRayCastMapper *volumeMapper = vtkFixedPointVolumeRayCastMapper::New();
      volumeMapper->SetInput(extract->GetOutput());

	vtkVolume *volume = vtkVolume::New();
		  volume->SetMapper(volumeMapper);
		  volume->SetProperty(volumeProperty);
 
	vtkOutlineFilter *outline = vtkOutlineFilter::New();
		outline->SetInputConnection(sample->GetOutputPort());

	vtkPolyDataMapper *outlineMapper = vtkPolyDataMapper::New();
		outlineMapper->SetInputConnection(outline->GetOutputPort());

	vtkActor *outlineActor = vtkActor::New();
		outlineActor->SetMapper(outlineMapper);		
		outlineActor->GetProperty()->SetColor(0, 0, 0);

  ren->AddVolume(volume);
  ren->AddActor(outlineActor);
  ren->SetBackground(1, 1, 1);
  renWin->SetSize(600,600);

  ren->ResetCamera();
  ren->GetActiveCamera()->Zoom(1.5);
  
  renWin->Render();


  iren->Start();

  // Clean up
  ren->Delete();
  iren->Delete();
  renWin->Delete();
  
  return 0;
}



