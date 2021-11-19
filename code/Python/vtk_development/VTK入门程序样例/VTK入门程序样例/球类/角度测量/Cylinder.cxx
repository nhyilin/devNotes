
#include "vtkActor.h"
#include "vtkCommand.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkLineWidget.h"
#include "vtkDICOMImageReader.h"
#include "vtkRenderWindowInteractor.h"
#include <vtkPolyDataMapper.h>
#include <vtkImageData.h>
#include <vtkSphereSource.h>
#include <vtkActor2D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkImageActor.h>
#include <vtkImageShiftScale.h>

#include <vtkProperty.h>
#include <vtkScaledTextActor.h>
#include <vtkTextMapper.h>
#include <math.h>
#include <string.h>

vtkLineWidget *lineWidget1;
vtkLineWidget *lineWidget2;

class vtkLWCallback : public vtkCommand
{
public:
  static vtkLWCallback *New() 
    { return new vtkLWCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkLineWidget *lineWidget = reinterpret_cast<vtkLineWidget*>(caller);

	  double O[3],A[3],B[3];
	  lineWidget->GetPoint1 (O);
//	  lineWidget->GetPoint2 (second);

	  lineWidget1->SetPoint1 (O);
	  lineWidget2->SetPoint1 (O);

	  lineWidget1->GetPoint2 (A);
	  lineWidget2->GetPoint2 (B);

	  double OA,OB,AB;
	  AB=sqrt((A[0]-B[0])*(A[0]-B[0])+(A[1]-B[1])*(A[1]-B[1])+(A[2]-B[2])*(A[2]-B[2]));
	  OA=sqrt((A[0]-O[0])*(A[0]-O[0])+(A[1]-O[1])*(A[1]-O[1])+(A[2]-O[2])*(A[2]-O[2]));
	  OB=sqrt((O[0]-B[0])*(O[0]-B[0])+(O[1]-B[1])*(O[1]-B[1])+(O[2]-B[2])*(O[2]-B[2]));

  	  double cosAOB=(OA*OA+OB*OB-AB*AB)/(2*OA*OB); 
  	  double angle;
	  angle=acos(cosAOB)*180/3.14159;
	  char cAct[100];
	  sprintf((char *)cAct,"%.4f",angle);

	  this->Text->SetInput (cAct);
    }
  vtkLWCallback():Text(0) {}

  vtkTextMapper *Text;
};

int main( int argc, char *argv[] )
{
  vtkSphereSource *sphere = vtkSphereSource::New();
    sphere->SetThetaResolution(12); 
	sphere->SetPhiResolution(12);
    sphere->SetRadius(100);

  vtkPolyDataMapper *innerMapper = vtkPolyDataMapper::New();
    innerMapper->SetInput(sphere->GetOutput());

  vtkActor *innerSphere = vtkActor::New();
    innerSphere->SetMapper(innerMapper);
    innerSphere->GetProperty()->SetColor (1,1,1);
    innerSphere->GetProperty()->SetOpacity (0.5);

    vtkTextMapper *textMapper=vtkTextMapper::New();
      textMapper->SetInput ("Welcome you!");//所要显示的注释文字
    vtkScaledTextActor *mmm=vtkScaledTextActor::New();
  	  mmm->SetMapper(textMapper);
	  mmm->SetDisplayPosition(100, 10 );//设定注释位置


  vtkRenderer *ren1 = vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkLWCallback *myCallback1 = vtkLWCallback::New();
    myCallback1->Text = textMapper;

  lineWidget1 = vtkLineWidget::New();
	lineWidget1->SetInteractor(iren);
	lineWidget1->SetInput(sphere->GetOutput());
	lineWidget1->SetAlignToYAxis();
	lineWidget1->PlaceWidget();
	lineWidget1->GetLineProperty()->SetColor(1,0,0);
	lineWidget1->GetHandleProperty()->SetColor(0,0,1);
	lineWidget1->AddObserver(vtkCommand::InteractionEvent,myCallback1);
	lineWidget1->On();

  vtkLWCallback *myCallback2 = vtkLWCallback::New();
    myCallback2->Text = textMapper;

  lineWidget2 = vtkLineWidget::New();
	lineWidget2->SetInteractor(iren);
	lineWidget2->SetInput(sphere->GetOutput());

	lineWidget2->PlaceWidget();
	lineWidget2->GetLineProperty()->SetColor(1,0,0);
	lineWidget2->GetHandleProperty()->SetColor(0,0,1);
	lineWidget2->AddObserver(vtkCommand::InteractionEvent,myCallback2);
	lineWidget2->SetPoint1(lineWidget1->GetPoint1 ());
	lineWidget2->On();

  ren1->AddActor(innerSphere);
  ren1->AddActor(mmm);//显示注释文字

  ren1->SetBackground(0, 0, 0);
  renWin->SetSize(600, 600);

  ren1->InteractiveOff();

  iren->Initialize();
  renWin->Render();


  iren->InvokeEvent(vtkCommand::CharEvent,NULL);  
  ren1->InteractiveOff();

  iren->Start();


  myCallback1->Delete();
  lineWidget1->Delete();
  myCallback2->Delete();
  lineWidget2->Delete();
  sphere->Delete();
  iren->Delete();
  renWin->Delete();
  ren1->Delete();
  
  return 0;
}
