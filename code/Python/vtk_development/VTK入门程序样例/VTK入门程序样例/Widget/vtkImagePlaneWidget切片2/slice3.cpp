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

#include "vtkImageMapper.h"
#include "vtkDICOMImageReader.h"
#include"vtkBMPReader.h"
#include"vtkWindowToImageFilter.h"

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
/////////////////
/*
  vtkBMPReader *reader = vtkBMPReader::New();	
    reader->SetDataExtent(0,512,0,512,1,57);
	reader->SetFilePrefix("E://ct/headbmpskin/CThead");
	reader->SetDataSpacing (1, 1, 6.24);//像素间的间隔
	reader->SetAllow8BitBMP (8) ;//很重要
    reader->Update();
*/
  vtkDICOMImageReader   *reader =  vtkDICOMImageReader::New();
	reader->SetDataByteOrderToLittleEndian();
	reader->SetDirectoryName("E://CT/head40");
	reader->Update();

  vtkOutlineFilter* outline = vtkOutlineFilter::New();
    outline->SetInputConnection(reader->GetOutputPort());

  vtkPolyDataMapper* outlineMapper = vtkPolyDataMapper::New();
    outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkCellPicker* picker = vtkCellPicker::New();
    picker->SetTolerance(0.005);

  vtkProperty* ipwProp = vtkProperty::New();
   //assign default props to the ipw's texture plane actor

  vtkImagePlaneWidget* planeWidgetX = vtkImagePlaneWidget::New();
    planeWidgetX->SetInteractor( iren);
    planeWidgetX->SetKeyPressActivationValue('x');
    planeWidgetX->SetPicker(picker);
    planeWidgetX->RestrictPlaneToVolumeOn();
    planeWidgetX->GetPlaneProperty()->SetColor(1,0,0);
    planeWidgetX->SetTexturePlaneProperty(ipwProp);
    planeWidgetX->TextureInterpolateOff();
    planeWidgetX->SetResliceInterpolateToNearestNeighbour();
    planeWidgetX->SetInput(reader->GetOutput());
    planeWidgetX->SetPlaneOrientationToXAxes();
    planeWidgetX->SetSlicePosition(100);
    planeWidgetX->DisplayTextOn();
    planeWidgetX->On();
    planeWidgetX->InteractionOff();
    planeWidgetX->InteractionOn();

  vtkImagePlaneWidget* planeWidgetY = vtkImagePlaneWidget::New();
    planeWidgetY->SetInteractor( iren);
    planeWidgetY->SetKeyPressActivationValue('y');
    planeWidgetY->SetPicker(picker);
    planeWidgetY->GetPlaneProperty()->SetColor(1,1,0);
    planeWidgetY->SetTexturePlaneProperty(ipwProp);
    planeWidgetY->TextureInterpolateOn();
    planeWidgetY->SetResliceInterpolateToLinear();
    planeWidgetY->SetInput(reader->GetOutput());
    planeWidgetY->SetPlaneOrientationToYAxes();
    planeWidgetY->SetSlicePosition(100);
    planeWidgetY->SetLookupTable( planeWidgetX->GetLookupTable());
    planeWidgetY->DisplayTextOff();
    planeWidgetY->UpdatePlacement();
    planeWidgetY->On();

  vtkImagePlaneWidget* planeWidgetZ = vtkImagePlaneWidget::New();
    planeWidgetZ->SetInteractor( iren);
    planeWidgetZ->SetKeyPressActivationValue('z');
    planeWidgetZ->SetPicker(picker);
    planeWidgetZ->GetPlaneProperty()->SetColor(0,0,1);
    planeWidgetZ->SetTexturePlaneProperty(ipwProp);
    planeWidgetZ->TextureInterpolateOn();
    planeWidgetZ->SetResliceInterpolateToCubic();
    planeWidgetZ->SetInput(reader->GetOutput());
    planeWidgetZ->SetPlaneOrientationToZAxes();
    planeWidgetZ->SetSliceIndex(25);
    planeWidgetZ->SetLookupTable( planeWidgetX->GetLookupTable());
    planeWidgetZ->DisplayTextOn();
    planeWidgetZ->On();

  double wl[2];
  planeWidgetZ->GetWindowLevel(wl);

  // Add a 2D image to test the GetReslice method
  //横断面
  vtkImageMapToColors* colorMapz = vtkImageMapToColors::New();
    colorMapz->PassAlphaToOutputOff();
    colorMapz->SetActiveComponent(2);
    colorMapz->SetOutputFormatToLuminance();
    colorMapz->SetInput(planeWidgetZ->GetResliceOutput());
    colorMapz->SetLookupTable(planeWidgetX->GetLookupTable());
/*
vtkWindowToImageFilter *w2i=vtkWindowToImageFilter::New();
//   w2i-> SetInput (renWin);
   w2i-> SetInputBufferTypeToRGBA();
   w2i-> Update();

vtkImageMapper *im=vtkImageMapper::New();
   im-> SetColorWindow (255);
   im-> SetColorLevel (127.5);
   im-> SetInputConnection (w2i-> GetOutputPort());

vtkActor2D *ia2=vtkActor2D::New();
   ia2-> SetMapper (im);
*/
  vtkImageActor* imageActorz = vtkImageActor::New();
 //   imageActorz->PickableOff();
      imageActorz->PickableOn();
	imageActorz->DragableOff();
    imageActorz->SetInput(colorMapz->GetOutput());
/*
  vtkImageMapper* mapper = vtkImageMapper::New();
	  mapper->SetInput(planeWidgetZ->GetResliceOutput());
	  mapper->Update();
	vtkActor2D* pActor = vtkActor2D::New();
	  pActor->SetMapper(mapper);
*/
////冠
  vtkImageMapToColors* colorMapx = vtkImageMapToColors::New();
    colorMapx->PassAlphaToOutputOff();
    colorMapx->SetActiveComponent(2);
    colorMapx->SetOutputFormatToLuminance();
    colorMapx->SetInput(planeWidgetX->GetResliceOutput());
    colorMapx->SetLookupTable(planeWidgetX->GetLookupTable());

  vtkImageActor* imageActorx = vtkImageActor::New();
    imageActorx->SetInput(colorMapx->GetOutput());

///矢
   vtkImageMapToColors* colorMapy = vtkImageMapToColors::New();
    colorMapy->PassAlphaToOutputOff();
    colorMapy->SetActiveComponent(2);
    colorMapy->SetOutputFormatToLuminance();
    colorMapy->SetInput(planeWidgetY->GetResliceOutput());
    colorMapy->SetLookupTable(planeWidgetX->GetLookupTable());

  vtkImageActor* imageActory = vtkImageActor::New();
 //   imageActorz->PickableOff();
    imageActory->SetInput(colorMapy->GetOutput());

  vtkActor* outlineActor =  vtkActor::New();
    outlineActor->SetMapper( outlineMapper);

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

  ren4->InteractiveOff();
  ren2->InteractiveOff();
  ren3->InteractiveOff();

 ren2->SetViewPoint  (1,1,1 ); 
  // Set the actors' postions
  //
  renWin->Render();
  
  ren1->GetActiveCamera()->Elevation(110);
  ren1->GetActiveCamera()->SetViewUp(0, 0, -1);
  ren1->GetActiveCamera()->Azimuth(45);
  ren1->GetActiveCamera()->Dolly(1.15);
  ren1->ResetCameraClippingRange();

  



  
  vtkCallbackCommand* callback = vtkCallbackCommand::New();
  //callback->SetCallback();
  callback->SetClientData((void *)ren1);
  renWin->GetInteractor()->AddObserver(vtkCommand::LeftButtonPressEvent, callback, 1.0);
  renWin->GetInteractor()->AddObserver(vtkCommand::MouseMoveEvent, callback, 1.0);
  renWin->GetInteractor()->AddObserver(vtkCommand::LeftButtonReleaseEvent, callback, 1.0);

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

