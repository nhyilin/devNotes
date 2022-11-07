#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkCellPicker.h"
#include "vtkCommand.h"
#include "vtkImageActor.h"
#include "vtkImageMapToColors.h"
#include "vtkImagePlaneWidget.h"
#include "vtkImageReader.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkLookupTable.h"
#include "vtkOutlineFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkVolume16Reader.h"
#include "vtkImageData.h"
#include "vtkCallbackCommand.h"
#include "vtkActor2D.h"
#include "vtkPointWidget.h"
#include "vtkInteractorStyleImage.h"

#include "vtkImageMapper.h"
#include "vtkStructuredPointsReader.h"
#include"vtkBMPReader.h"
#include"vtkWindowToImageFilter.h"

vtkImagePlaneWidget* planeWidgetX;
vtkImagePlaneWidget* planeWidgetY;
vtkImagePlaneWidget* planeWidgetZ;

class vtkmyPWCallbackz : public vtkCommand
{
public:
  static vtkmyPWCallbackz *New() 
    { return new vtkmyPWCallbackz; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkPointWidget *pointWidget = reinterpret_cast<vtkPointWidget*>(caller);

	  double position[3];    
	  pointWidget->GetPosition(position);
	  this->WidgetX->SetSlicePosition(position[0]);
	  this->WidgetY->SetSlicePosition(position[1]);
    }
  vtkmyPWCallbackz():WidgetX(0), WidgetY(0){}
  vtkImagePlaneWidget* WidgetX;
  vtkImagePlaneWidget* WidgetY;
};

class vtkmyPWCallbackx : public vtkCommand
{
public:
  static vtkmyPWCallbackx *New() 
    { return new vtkmyPWCallbackx; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkPointWidget *pointWidget = reinterpret_cast<vtkPointWidget*>(caller);

	  double position[3];    
	  pointWidget->GetPosition(position);
	  this->WidgetY->SetSlicePosition(position[0]);
	  this->WidgetZ->SetSlicePosition(position[1]);
    }
  vtkmyPWCallbackx():WidgetY(0), WidgetZ(0){}
  vtkImagePlaneWidget* WidgetY;
  vtkImagePlaneWidget* WidgetZ;
};

class vtkmyPWCallbacky : public vtkCommand
{
public:
  static vtkmyPWCallbacky *New() 
    { return new vtkmyPWCallbacky; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkPointWidget *pointWidget = reinterpret_cast<vtkPointWidget*>(caller);

	  double position[3];    
	  pointWidget->GetPosition(position);
	  this->WidgetX->SetSlicePosition(position[1]);
	  this->WidgetZ->SetSlicePosition(position[0]);
    }
  vtkmyPWCallbacky():WidgetX(0), WidgetZ(0){}
  vtkImagePlaneWidget* WidgetX;
  vtkImagePlaneWidget* WidgetZ;
};


int main()
{  
  vtkRenderer* ren1 = vtkRenderer::New();
  vtkRenderer* ren2 = vtkRenderer::New();
  vtkRenderer* ren3 = vtkRenderer::New();
  vtkRenderer* ren4 = vtkRenderer::New();
  vtkRenderer* ren5 = vtkRenderer::New();

  vtkRenderWindow* renWin = vtkRenderWindow::New();	
    renWin->AddRenderer(ren5);
    renWin->AddRenderer(ren2);
    renWin->AddRenderer(ren3);
    renWin->AddRenderer(ren4);
	renWin->AddRenderer(ren1);

  vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkInteractorStyleImage *interactor=vtkInteractorStyleImage::New();
    iren-> SetInteractorStyle (interactor);
/////////////////

	vtkStructuredPointsReader *reader=vtkStructuredPointsReader::New();
	    reader->SetFileName("E://CT/fei.VTK");
	reader->Update();

  vtkOutlineFilter* outline = vtkOutlineFilter::New();
    outline->SetInputConnection(reader->GetOutputPort());

  vtkPolyDataMapper* outlineMapper = vtkPolyDataMapper::New();
    outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkCellPicker* picker = vtkCellPicker::New();
    picker->SetTolerance(0.005);

  vtkProperty* ipwProp = vtkProperty::New();
   //assign default props to the ipw's texture plane actor

  planeWidgetX = vtkImagePlaneWidget::New();
    planeWidgetX->SetInteractor( iren);
    planeWidgetX->SetKeyPressActivationValue('x');
    planeWidgetX->SetPicker(picker);
    planeWidgetX->RestrictPlaneToVolumeOn();
    planeWidgetX->GetPlaneProperty()->SetColor(1,0,0);
    planeWidgetX->SetTexturePlaneProperty(ipwProp);
    planeWidgetX->TextureInterpolateOff();
    planeWidgetX->SetResliceInterpolateToCubic();
    planeWidgetX->SetInput((vtkDataSet *)reader->GetOutput());
    planeWidgetX->SetPlaneOrientationToXAxes();
    planeWidgetX->SetSlicePosition(100);
    planeWidgetX->DisplayTextOn();
    planeWidgetX->On();
    planeWidgetX->InteractionOff();
    planeWidgetX->InteractionOn();

  planeWidgetY = vtkImagePlaneWidget::New();
    planeWidgetY->SetInteractor( iren);
    planeWidgetY->SetKeyPressActivationValue('y');
    planeWidgetY->SetPicker(picker);
    planeWidgetY->GetPlaneProperty()->SetColor(1,1,0);
    planeWidgetY->SetTexturePlaneProperty(ipwProp);
    planeWidgetY->TextureInterpolateOn();
    planeWidgetY->SetResliceInterpolateToCubic();
    planeWidgetY->SetInput((vtkDataSet *)reader->GetOutput());
    planeWidgetY->SetPlaneOrientationToYAxes();
    planeWidgetY->SetSlicePosition(100);
    planeWidgetY->SetLookupTable( planeWidgetX->GetLookupTable());
    planeWidgetY->DisplayTextOff();
    planeWidgetY->UpdatePlacement();
    planeWidgetY->On();

  planeWidgetZ = vtkImagePlaneWidget::New();
    planeWidgetZ->SetInteractor( iren);
    planeWidgetZ->SetKeyPressActivationValue('z');
    planeWidgetZ->SetPicker(picker);
    planeWidgetZ->GetPlaneProperty()->SetColor(0,0,1);
    planeWidgetZ->SetTexturePlaneProperty(ipwProp);
    planeWidgetZ->TextureInterpolateOn();
    planeWidgetZ->SetResliceInterpolateToCubic();
//	planeWidgetZ->RestrictPlaneToVolumeOff();  
    planeWidgetZ->SetInput((vtkDataSet *)reader->GetOutput());
    planeWidgetZ->SetPlaneOrientationToZAxes();
    planeWidgetZ->SetSliceIndex(25);
    planeWidgetZ->SetLookupTable( planeWidgetX->GetLookupTable());
    planeWidgetZ->DisplayTextOn();
    planeWidgetZ->On();

  double wl[2];
  planeWidgetZ->GetWindowLevel(wl);

  // Add a 2D image to test the GetReslice method
  //ºá¶ÏÃæ
  vtkImageMapToColors* colorMapz = vtkImageMapToColors::New();
    colorMapz->PassAlphaToOutputOff();
    colorMapz->SetActiveComponent(2);
    colorMapz->SetOutputFormatToLuminance();
    colorMapz->SetInput(planeWidgetZ->GetResliceOutput());
    colorMapz->SetLookupTable(planeWidgetX->GetLookupTable());

  vtkImageActor* imageActorz = vtkImageActor::New();
      imageActorz->PickableOn();
	imageActorz->DragableOff();
    imageActorz->SetInput(colorMapz->GetOutput());
//¹Ú
  vtkImageMapToColors* colorMapx = vtkImageMapToColors::New();
    colorMapx->PassAlphaToOutputOff();
    colorMapx->SetActiveComponent(2);
    colorMapx->SetOutputFormatToLuminance();
    colorMapx->SetInput(planeWidgetX->GetResliceOutput());
    colorMapx->SetLookupTable(planeWidgetX->GetLookupTable());

  vtkImageActor* imageActorx = vtkImageActor::New();
    imageActorx->SetInput(colorMapx->GetOutput());

///Ê¸
   vtkImageMapToColors* colorMapy = vtkImageMapToColors::New();
    colorMapy->PassAlphaToOutputOff();
    colorMapy->SetActiveComponent(2);
    colorMapy->SetOutputFormatToLuminance();
    colorMapy->SetInput(planeWidgetY->GetResliceOutput());
    colorMapy->SetLookupTable(planeWidgetX->GetLookupTable());

  vtkImageActor* imageActory = vtkImageActor::New();
    imageActory->SetInput(colorMapy->GetOutput());

  vtkActor* outlineActor =  vtkActor::New();
    outlineActor->SetMapper( outlineMapper);
	outlineActor->VisibilityOff(); 

  // Add the actors
  ren2->AddActor2D( imageActorz);
  ren3->AddActor2D( imageActorx);
  ren4->AddActor2D( imageActory);
  ren1->AddActor( outlineActor);

  ren1->SetBackground( 1, 1, 0);
  ren2->SetBackground( 1, 1, 0);
  ren3->SetBackground( 1, 1, 0);
  ren4->SetBackground( 1, 1, 0);

  renWin->SetSize( 710, 710);

  ren4->SetViewport(0.51,0.51,1,1);
  ren2->SetViewport(0,0.51,0.49,1);
  ren3->SetViewport(0,0,0.49,0.49);
  ren1->SetViewport(0.51,0,1,0.49);



//  ren4->GetActiveCamera()->Roll(180);
//  ren3->GetActiveCamera()->Roll(90);

 ren2->SetViewPoint  (1,1,1 ); 
  // Set the actors' postions
  //
  renWin->Render();
  
  ren1->GetActiveCamera()->Elevation(110);
  ren1->GetActiveCamera()->SetViewUp(0, 0, -1);
  ren1->GetActiveCamera()->Azimuth(45);
  ren1->GetActiveCamera()->Dolly(1.15);
  ren1->ResetCameraClippingRange();

////////////////////////


  vtkmyPWCallbackz *myCallbackz = vtkmyPWCallbackz::New();
    myCallbackz->WidgetX = planeWidgetX;
    myCallbackz->WidgetY = planeWidgetY;

  vtkmyPWCallbackx *myCallbackx = vtkmyPWCallbackx::New();
    myCallbackx->WidgetY = planeWidgetY;
    myCallbackx->WidgetZ = planeWidgetZ;

  vtkmyPWCallbacky *myCallbacky = vtkmyPWCallbacky::New();
    myCallbacky->WidgetX = planeWidgetX;
    myCallbacky->WidgetZ = planeWidgetZ;

  vtkPointWidget *pointWidgetz = vtkPointWidget::New();
	pointWidgetz->SetInteractor(iren);
	pointWidgetz->SetInput((vtkDataSet *)planeWidgetZ->GetResliceOutput());
	pointWidgetz->AllOff();
	pointWidgetz->PlaceWidget();
	pointWidgetz->AddObserver(vtkCommand::InteractionEvent,myCallbackz);
	pointWidgetz->GetProperty()->SetColor(1,1,1);
//	pointWidgetz->SetPosition(100,100,0);
	pointWidgetz->SetCurrentRenderer (ren2); 
	pointWidgetz->On();

  vtkPointWidget *pointWidgetx = vtkPointWidget::New();
	pointWidgetx->SetInteractor(iren);
	pointWidgetx->SetInput((vtkDataSet *)planeWidgetX->GetResliceOutput());
	pointWidgetx->AllOff();
	pointWidgetx->PlaceWidget();	  
	pointWidgetx->AddObserver(vtkCommand::InteractionEvent,myCallbackx);
	pointWidgetx->GetProperty()->SetColor(1,1,1);
//	pointWidgetx->SetPosition(100,100,0);
	pointWidgetx->SetCurrentRenderer (ren3); 
	pointWidgetx->On();

  vtkPointWidget *pointWidgety = vtkPointWidget::New();
	pointWidgety->SetInteractor(iren);
	pointWidgety->SetInput((vtkDataSet *)planeWidgetY->GetResliceOutput());
	pointWidgety->AllOff();
	pointWidgety->PlaceWidget();
	pointWidgety->AddObserver(vtkCommand::InteractionEvent,myCallbacky);
	pointWidgety->GetProperty()->SetColor(1,1,1);
//	pointWidgety->SetPosition(100,100,0);
	pointWidgety->SetCurrentRenderer (ren4); 
	pointWidgety->On();  
///////////////////////////////

  vtkCallbackCommand* callback = vtkCallbackCommand::New();
  //callback->SetCallback();
	  callback->SetClientData((void *)ren1);
//	  renWin->GetInteractor()->AddObserver(vtkCommand::LeftButtonPressEvent, callback, 1.0);
//	  renWin->GetInteractor()->AddObserver(vtkCommand::MouseMoveEvent, callback, 1.0);
//	  renWin->GetInteractor()->AddObserver(vtkCommand::LeftButtonReleaseEvent, callback, 1.0);

  renWin->Render();
  // Interact with data
  // Render the image
  //

  iren->Initialize();
//iren->FlyToImage  (ren2,  256,256) ; 
//iren->FlyToImage  (ren3,  256,256) ; 
//iren->FlyToImage  (ren4,  256,256) ; 
  iren->Start();
  renWin->Render();

  callback->Delete();
  ipwProp->Delete();
  planeWidgetX->Delete();
  planeWidgetY->Delete();
  planeWidgetZ->Delete();
  colorMapz->Delete();
  imageActorz->Delete();
  picker->Delete();
  outlineActor->Delete();
  outlineMapper->Delete();
  outline->Delete();
  iren->Delete();
  renWin->Delete();
  ren1->Delete();
  ren2->Delete();
  reader->Delete();

  return 0;
}

