#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkQuadric.h"
#include "vtkSampleFunction.h"
#include "vtkContourFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkOutlineFilter.h"
#include "vtkProperty.h"

//#include "SaveImage.h"

void main( int argc, char *argv[] )
{
  vtkRenderer *aren = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(aren);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);
//
// Create surfaces F(x,y,z) = constant
//
  // Sample quadric function
  vtkQuadric *quadric = vtkQuadric::New();
  //evaluate implicit quadric function 
  //评估暗示的二次功能。
      quadric->SetCoefficients(.5,1,.2,0.6,.1,2.0,0,.2,0,0);
	  //F(x,y,z) = a0*x^2 + a1*y^2 + a2*z^2 + a3*x*y + a4*y*z + a5*x*z + a6*x + a7*y + a8*z + a9

  vtkSampleFunction *sample = vtkSampleFunction::New();
  //vtkSampleFunction 是在 vtkStructuredPoints 的每点评估一个暗示的功能和常态的一个来源物体。
  //使用者能叙述空间的样品尺寸和位置运行那抽取样品。 产生关闭表面 (连同 vtkContourFilter), 
  //胜过能被打开在样品空间的边界上设定特别的价值。  
      sample->SetSampleDimensions(50,50,50);
      sample->SetImplicitFunction(quadric);

	vtkContourFilter *contour = vtkContourFilter::New();
      contour->SetInput((vtkDataSet *)sample->GetOutput());
      contour->GenerateValues(5,0,1.2);
  vtkPolyDataMapper *contourMapper = vtkPolyDataMapper::New();
      contourMapper->SetInput(contour->GetOutput());
      contourMapper->SetScalarRange(0,1.2);
  vtkActor *contourActor = vtkActor::New();
      contourActor->SetMapper(contourMapper);

  // Create outline
  vtkOutlineFilter *outline = vtkOutlineFilter::New();
      outline->SetInput((vtkDataSet *)sample->GetOutput());
  vtkPolyDataMapper *outlineMapper = vtkPolyDataMapper::New();
      outlineMapper->SetInput(outline->GetOutput());
  vtkActor *outlineActor = vtkActor::New();
      outlineActor->SetMapper(outlineMapper);
      outlineActor->GetProperty()->SetColor(0,0,0);
//
// Rendering stuff
//
  aren->SetBackground(1,1,1);
      aren->AddActor(contourActor);
      aren->AddActor(outlineActor);

  renWin->SetSize(300,300);
  renWin->Render();

//  SAVEIMAGE( renWin );

  // interact with data
  iren->Start();

  // Clean up
  aren->Delete();
  renWin->Delete();
  iren->Delete();
  quadric->Delete();
  sample->Delete();
  contour->Delete();
  contourMapper->Delete();
  contourActor->Delete();
  outline->Delete();
  outlineMapper->Delete();
  outlineActor->Delete();
}
