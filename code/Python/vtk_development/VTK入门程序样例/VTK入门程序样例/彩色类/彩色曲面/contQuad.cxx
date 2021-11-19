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
  //������ʾ�Ķ��ι��ܡ�
      quadric->SetCoefficients(.5,1,.2,0.6,.1,2.0,0,.2,0,0);
	  //F(x,y,z) = a0*x^2 + a1*y^2 + a2*z^2 + a3*x*y + a4*y*z + a5*x*z + a6*x + a7*y + a8*z + a9

  vtkSampleFunction *sample = vtkSampleFunction::New();
  //vtkSampleFunction ���� vtkStructuredPoints ��ÿ������һ����ʾ�Ĺ��ܺͳ�̬��һ����Դ���塣
  //ʹ�����������ռ����Ʒ�ߴ��λ�������ǳ�ȡ��Ʒ�� �����رձ��� (��ͬ vtkContourFilter), 
  //ʤ���ܱ�������Ʒ�ռ�ı߽����趨�ر�ļ�ֵ��  
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
