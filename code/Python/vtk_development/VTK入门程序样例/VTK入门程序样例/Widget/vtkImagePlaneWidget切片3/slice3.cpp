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

  vtkDICOMImageReader   *reader =  vtkDICOMImageReader::New();
	reader->SetDataByteOrderToLittleEndian();
	reader->SetDirectoryName("E://CT/head40");
	reader->Update();

  vtkOutlineFilter* outline = vtkOutlineFilter::New();
    outline->SetInputConnection(reader->GetOutputPort());

  vtkPolyDataMapper* outlineMapper = vtkPolyDataMapper::New();
    outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkActor* outlineActor =  vtkActor::New();
    outlineActor->SetMapper( outlineMapper);

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
  //ºá¶ÏÃæ
  vtkImageMapper* mapperz = vtkImageMapper::New();
	  mapperz->SetInput(planeWidgetZ->GetResliceOutput());
	  mapperz->Update();

  vtkActor2D* Actorz = vtkActor2D::New();
	  Actorz->SetMapper(mapperz);

////¹Ú
  vtkImageMapper* mapperx = vtkImageMapper::New();
	  mapperx->SetInput(planeWidgetX->GetResliceOutput());
	  mapperx->Update();

  vtkActor2D* Actorx = vtkActor2D::New();
	  Actorx->SetMapper(mapperx);

///Ê¸
  vtkImageMapper* mappery = vtkImageMapper::New();
	  mappery->SetInput(planeWidgetY->GetResliceOutput());
	  mappery->Update();

  vtkActor2D* Actory = vtkActor2D::New();
	  Actory->SetMapper(mappery);


  // Add the actors
  ren2->AddActor2D( Actorz);
  ren3->AddActor2D( Actorx);
  ren4->AddActor2D( Actory);

  ren1->AddActor( outlineActor);  

  ren1->SetBackground( 1, 1, 0);
  ren2->SetBackground( 1, 1, 1);
  ren3->SetBackground( 1, 1, 1);
  ren4->SetBackground( 1, 1, 1);

  renWin->SetSize( 710, 710);

  ren4->SetViewport(0.51,0.51,1,1);
  ren2->SetViewport(0,0.51,0.49,1);
  ren3->SetViewport(0,0,0.49,0.49);
  ren1->SetViewport(0.51,0,1,0.49);

// ren2->SetViewPoint  (1,1,1 ); 
// ren3->SetViewPoint  (1,1,1 ); 
// ren4->SetViewPoint  (1,1,1 ); 
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


//  iren->Initialize();
iren->FlyToImage  (ren2,  350,350) ; 
iren->FlyToImage  (ren3,  350,350) ; 
iren->FlyToImage  (ren4,  350,350) ; 
  iren->Start();
//  renWin->Render();

  callback->Delete();
  ipwProp->Delete();
  planeWidgetX->Delete();
  planeWidgetY->Delete();
  planeWidgetZ->Delete();
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

