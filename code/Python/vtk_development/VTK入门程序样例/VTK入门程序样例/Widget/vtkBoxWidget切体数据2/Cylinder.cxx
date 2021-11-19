
#include "vtkActor.h"
#include "vtkAppendPolyData.h"
#include "vtkClipPolyData.h"
#include "vtkCommand.h"
#include "vtkConeSource.h"
#include "vtkGlyph3D.h"
#include "vtkBoxWidget.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkLODActor.h"
#include "vtkPlanes.h"
#include "vtkPlane.h"
#include "vtkPolyData.h"
#include "vtkImageShiftScale.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkSphereSource.h"

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

class vtkTIPWCallback : public vtkCommand
{
public:
  static vtkTIPWCallback *New() 
    { return new vtkTIPWCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkBoxWidget *boxWidget = 
        reinterpret_cast<vtkBoxWidget*>(caller);
        boxWidget->GetPlanes(this->Planes);

		Plane0=this->Planes->GetPlane(0); 
		Plane1=this->Planes->GetPlane(1); 
		Plane2=this->Planes->GetPlane(2); 
		Plane3=this->Planes->GetPlane(3); 
		Plane4=this->Planes->GetPlane(4); 
		Plane5=this->Planes->GetPlane(5); 

printf("Plane0 normal: %f,  %f,  %f,   \n",Plane0->GetNormal()[0],Plane0->GetNormal()[1],Plane0->GetNormal()[2]);  
printf("Plane0 GetOrigin: %f,  %f,  %f,   \n",Plane0->GetOrigin()[0],Plane0->GetOrigin()[1],Plane0->GetOrigin()[2]);  

printf("Plane5 normal: %f,  %f,  %f,   \n",Plane5->GetNormal()[0],Plane5->GetNormal()[1],Plane5->GetNormal()[2]);  
printf("Plane5 GetOrigin: %f,  %f,  %f,   \n",Plane5->GetOrigin()[0],Plane5->GetOrigin()[1],Plane5->GetOrigin()[2]); 

Plane0->SetNormal(-Plane0->GetNormal()[0],-Plane0->GetNormal()[1],-Plane0->GetNormal()[2]);
/*
Plane0->SetNormal(0,0,1);
Plane1->SetNormal(-Plane1->GetNormal()[0],-Plane1->GetNormal()[1],-Plane1->GetNormal()[2]);
Plane2->SetNormal(-Plane2->GetNormal()[0],-Plane2->GetNormal()[1],-Plane2->GetNormal()[2]);
Plane3->SetNormal(-Plane3->GetNormal()[0],-Plane3->GetNormal()[1],-Plane3->GetNormal()[2]);
Plane4->SetNormal(-Plane4->GetNormal()[0],-Plane4->GetNormal()[1],-Plane4->GetNormal()[2]);
Plane5->SetNormal(-Plane5->GetNormal()[0],-Plane5->GetNormal()[1],-Plane5->GetNormal()[2]);
*/		
		vMapper->RemoveAllClippingPlanes();
		vMapper->AddClippingPlane(Plane0);
//		vMapper->AddClippingPlane(Plane1);
//		vMapper->AddClippingPlane(Plane2);
//		vMapper->AddClippingPlane(Plane3);
//		vMapper->AddClippingPlane(Plane4);
//		vMapper->AddClippingPlane(Plane5);


//	  printf("planes number: %d \n",this->Planes->GetNumberOfPlanes() );  
      this->Volume->VisibilityOn();
    }
  vtkTIPWCallback():Planes(0),vMapper(0),Volume(0),Plane0(0),Plane1(0),
	                Plane2(0),Plane3(0),Plane4(0),Plane5(0){}
  vtkPlanes *Planes;
  vtkPlane *Plane0;
  vtkPlane *Plane1;
  vtkPlane *Plane2;
  vtkPlane *Plane3;
  vtkPlane *Plane4;
  vtkPlane *Plane5;
  vtkVolume *Volume;
  vtkVolumeRayCastMapper *vMapper;
};

int main( int argc, char *argv[] )
{

  vtkDICOMImageReader   *reader =  vtkDICOMImageReader::New();
	reader->SetDataByteOrderToLittleEndian();
	reader->SetDirectoryName("e://ct/head30/");
//	reader->SetDataOrigin(-100, -100, -61);
/*
  int extent[6];
	reader->GetDataExtent(extent);

  double spacing [3];  
	reader->GetDataSpacing(spacing); 

	int xx,yy,zz;
	xx=(int)((extent[1]+1)*spacing[0]);
	yy=(int)((extent[3]+1)*spacing[1]);
	zz=(int)((extent[5]+1)*spacing[2]);
*/
  vtkImageShiftScale *ShiftScale = vtkImageShiftScale::New();
	ShiftScale->SetInput((vtkDataObject *)reader->GetOutput());
	ShiftScale->SetOutputScalarTypeToShort();
	ShiftScale->SetShift (1024);
	ShiftScale->ClampOverflowOn();

  vtkImageCast *readerImageCast = vtkImageCast::New();
	readerImageCast->SetInput((vtkDataObject *)ShiftScale->GetOutput());
	readerImageCast->SetOutputScalarTypeToUnsignedShort();
	readerImageCast->ClampOverflowOn();

  vtkPiecewiseFunction *opacityTransferFunction = vtkPiecewiseFunction::New();
	opacityTransferFunction->AddPoint(1024+20, 0.0);
	opacityTransferFunction->AddPoint(1024+255, 0.2);

  vtkColorTransferFunction *colorTransferFunction = vtkColorTransferFunction::New();
	colorTransferFunction->AddRGBPoint(1024+0.0, 0.0, 0.5, 0.0);
    colorTransferFunction->AddRGBPoint(1024+60.0, 1.0, 0.0, 0.0);
    colorTransferFunction->AddRGBPoint(1024+128.0, 0.2, 0.1, 0.9);
    colorTransferFunction->AddRGBPoint(1024+196.0, 0.27, 0.21, 0.1);
    colorTransferFunction->AddRGBPoint(1024+255.0, 0.8, 0.8, 0.8);

  vtkVolumeProperty *volumeProperty = vtkVolumeProperty::New();
	volumeProperty->SetColor(colorTransferFunction);
	volumeProperty->SetScalarOpacity(opacityTransferFunction);
	volumeProperty->ShadeOn();
	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->SetAmbient(0.2);
    volumeProperty->SetDiffuse(0.9);
    volumeProperty->SetSpecular(0.2);
    volumeProperty->SetSpecularPower(10);

  vtkVolumeRayCastCompositeFunction *compositeFunction = vtkVolumeRayCastCompositeFunction::New();

  vtkPlanes *planes=vtkPlanes::New();
	vtkPlane *plane0=vtkPlane::New();
	  plane0->SetNormal(0,1,0);//设置切平面的法向量
	  plane0->SetOrigin(0,50,0);

	vtkPlane *plane1=vtkPlane::New();
	  plane1->SetNormal(0,-1,0);
	  plane1->SetOrigin(0,150,0);

	vtkPlane *plane2=vtkPlane::New();
	  plane2->SetNormal(1,0,0);
	  plane2->SetOrigin(50,0,0);

	vtkPlane *plane3=vtkPlane::New();
	  plane3->SetNormal(-1,0,0);
	  plane3->SetOrigin(150,0,0);

	vtkPlane *plane4=vtkPlane::New();
	  plane4->SetNormal(0,0,1);
	  plane4->SetOrigin(0,0,40);

	vtkPlane *plane5=vtkPlane::New();
	  plane5->SetNormal(0,0,-1);
	  plane5->SetOrigin(0,0,120);

  vtkVolumeRayCastMapper *volumeMapper = vtkVolumeRayCastMapper::New();
	volumeMapper->SetVolumeRayCastFunction(compositeFunction);
	volumeMapper->SetInputConnection(readerImageCast->GetOutputPort());//图像数据输入
//	volumeMapper->CroppingOn();
	volumeMapper->AddClippingPlane(plane0);
	volumeMapper->AddClippingPlane(plane1);
	volumeMapper->AddClippingPlane(plane2);
	volumeMapper->AddClippingPlane(plane3);
	volumeMapper->AddClippingPlane(plane4);
	volumeMapper->AddClippingPlane(plane5);

//	volumeMapper->SetClippingPlanes(planes); 

  vtkVolume *volume = vtkVolume::New();
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);

  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkTIPWCallback *myCallback = vtkTIPWCallback::New();
    myCallback->Planes = planes;
    myCallback->Volume = volume;
	myCallback->vMapper=volumeMapper;
	myCallback->Plane0=plane0;
	myCallback->Plane1=plane1;
	myCallback->Plane2=plane2;
	myCallback->Plane3=plane3;
	myCallback->Plane4=plane4;
	myCallback->Plane5=plane5;


  vtkBoxWidget *boxWidget = vtkBoxWidget::New();
	boxWidget->SetInteractor(iren);
	boxWidget->SetPlaceFactor(0.5);
//	boxWidget->GetPlaneProperty()->SetOpacity  ( 0.1 ) ;  
	boxWidget->GetOutlineProperty()->SetColor(0,0,1);    
	boxWidget->SetInput((vtkDataSet *)readerImageCast->GetOutput());
	boxWidget->PlaceWidget();
	boxWidget-> InsideOutOff();
	boxWidget->AddObserver(vtkCommand::InteractionEvent,myCallback);

  // Add the actors to the renderer, set the background and size
  //
  ren1->AddVolume(volume);
  ren1->SetBackground(1, 1, 1);
  renWin->SetSize(600, 600);

  // render the image
  //
  iren->SetKeyCode('i');
  iren->Initialize();
  renWin->Render();
  iren->Start();

  myCallback->Delete();
  planes->Delete();
  boxWidget->Delete();
  iren->Delete();
  renWin->Delete();
  ren1->Delete();
  
  return 0;
}
