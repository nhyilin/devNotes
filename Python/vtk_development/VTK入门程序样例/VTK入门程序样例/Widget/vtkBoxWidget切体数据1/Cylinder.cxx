/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: BoxWidget.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkAppendPolyData.h"
#include "vtkBoxWidget.h"
#include "vtkCommand.h"
#include "vtkConeSource.h"
#include "vtkGlyph3D.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkRenderer.h"
#include "vtkSphereSource.h"
#include "vtkTransform.h"
#include "vtkCallbackCommand.h"
#include "vtkRegressionTestImage.h"
#include "vtkDebugLeaks.h"

#include "vtkDICOMImageReader.h"
#include "vtkPiecewiseFunction.h"
#include "vtkColorTransferFunction.h"
#include "vtkVolumeProperty.h"
#include "vtkVolumeRayCastCompositeFunction.h"
#include "vtkVolumeRayCastMapper.h"
#include "vtkVolume.h"
#include "vtkImageCast.h"

#include "vtkPlanes.h"
#include "vtkClipPolyData.h"
#include "vtkLODActor.h"
#include "vtkRegressionTestImage.h"
#include "vtkDebugLeaks.h"
#include "vtkProperty.h"
// Callback for the interaction
class vtkBWCallback : public vtkCommand
{
public:
  static vtkBWCallback *New() 
    { return new vtkBWCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkBoxWidget *boxWidget = reinterpret_cast<vtkBoxWidget*>(caller);
//      boxWidget->GetPlanes(this->Planes);
	  this->Vmapper->SetClippingPlanes(this->Planes);
	  
	  this->Vmapper->CroppingOn();
//	  this->Vmapper->RemoveAllClippingPlanes();   
//	  this->Vmapper->CroppingOff();
    }
  vtkBWCallback():Planes(0),Vmapper(0) {}
  vtkPlanes  *Planes;
  vtkVolumeRayCastMapper *Vmapper;
};

#include "vtkRegressionTestImage.h"
#include "vtkDebugLeaks.h"


int main( int argc, char *argv[] )
{
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);
	renWin-> SetDesiredUpdateRate(10);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkBoxWidget *boxWidget = vtkBoxWidget::New();
    boxWidget->SetInteractor( iren );
    boxWidget->SetPlaceFactor( 1.0 );

  vtkDICOMImageReader   *reader =  vtkDICOMImageReader::New();
	reader->SetDataByteOrderToLittleEndian();
	reader->SetDirectoryName("e://ct/head30/");
//	reader->SetDataOrigin(-100,-100, -40);

  vtkImageCast *readerImageCast = vtkImageCast::New();
	readerImageCast->SetInputConnection(reader->GetOutputPort());
	readerImageCast->SetOutputScalarTypeToUnsignedChar();
	readerImageCast->ClampOverflowOn();

//  reader->Delete();

  vtkPiecewiseFunction *opacityTransferFunction = vtkPiecewiseFunction::New();
 	opacityTransferFunction->AddPoint(20, 0.0);
	opacityTransferFunction->AddPoint(255, 0.2);

  vtkColorTransferFunction *colorTransferFunction = vtkColorTransferFunction::New();
	colorTransferFunction->AddRGBPoint(0.0, 0.0, 0.5, 0.0);
    colorTransferFunction->AddRGBPoint(60.0, 1.0, 0.0, 0.0);
    colorTransferFunction->AddRGBPoint(128.0, 0.2, 0.1, 0.9);
    colorTransferFunction->AddRGBPoint(196.0, 0.27, 0.21, 0.1);
    colorTransferFunction->AddRGBPoint(255.0, 0.8, 0.8, 0.8);


  vtkVolumeProperty *volumeProperty = vtkVolumeProperty::New();
	volumeProperty->SetColor(colorTransferFunction);
	volumeProperty->SetScalarOpacity(opacityTransferFunction);
	volumeProperty->ShadeOn();
	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->SetAmbient(0.2);
    volumeProperty->SetDiffuse(0.9);
    volumeProperty->SetSpecular(0.2);
    volumeProperty->SetSpecularPower(10);

  vtkPlanes *planes=vtkPlanes::New();

  vtkVolumeRayCastCompositeFunction *compositeFunction = vtkVolumeRayCastCompositeFunction::New();
	//运行沿着光线合成 

  vtkVolumeRayCastMapper *volumeMapper = vtkVolumeRayCastMapper::New();
	  volumeMapper->SetVolumeRayCastFunction(compositeFunction);
	  volumeMapper->SetInputConnection(readerImageCast->GetOutputPort());//图像数据输入
	  volumeMapper->CroppingOff();
	  volumeMapper->SetClippingPlanes(planes);   
	  //设绘制区域
//	  volumeMapper->SetCroppingRegionFlagsToSubVolume( ) ;

	vtkVolume *volume = vtkVolume::New();
	//表示透示图中的一组三维数据
	  volume->SetMapper(volumeMapper);
	  volume->SetProperty(volumeProperty);

	renderer->AddVolume(volume);
	renderer->SetBackground(1, 1, 1);
	renWin->SetSize(600, 600);

  // Configure the box widget including callbacks
  boxWidget->SetInput((vtkDataSet *)readerImageCast->GetOutput());
  boxWidget->PlaceWidget();
  boxWidget-> InsideOutOn();
  boxWidget->GetPlanes(planes);
  boxWidget->GetOutlineProperty( )->SetColor (0,0,1); 

  vtkBWCallback *myCallback = vtkBWCallback::New();
  myCallback->Planes = planes;
  myCallback->Vmapper=volumeMapper;

  boxWidget->AddObserver(vtkCommand::InteractionEvent,myCallback);

  iren->Initialize();
  renWin->Render();

  iren->Start();

  //vtkCallbackCommand* callback = vtkCallbackCommand::New();
  //callback->SetClientData((void *)renWin);

  // Clean up
  myCallback->Delete();
  boxWidget->Delete();
  renderer->Delete();
  renWin->Delete();
  iren->Delete();

  return 0;
}
