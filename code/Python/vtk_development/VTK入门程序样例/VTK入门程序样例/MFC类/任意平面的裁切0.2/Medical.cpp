// Medical.cpp: implementation of the CMedical class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "step4.h"
#include "Medical.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMedical::CMedical()
{
	/*
	//16λ��ѹ��λͼ�Ķ�ȡ������
	//16λ��ѹ��λͼ
	v16 = vtkVolume16Reader::New();	
	//��СΪ64*64,ÿ���ļ���СΪ64*64*2=8192�ֽ�
	v16->SetDataDimensions(64,64);

	imageData = vtkImageData::New();
	imageData = v16->GetOutput();
	imageData->SetOrigin(.0,.0,.0);
	imageData->SetDimensions(64,64,93);

	//�����ֽ�֮����ֽ���,����ӡ�ذ��ֽ���	
	v16->SetDataByteOrderToLittleEndian();			
	v16->SetFilePrefix (".//res/BMPDATA/quarter");
	//����ͼƬ��Χ(1-93)
	v16->SetImageRange (1,93);
	//����						
	v16->SetDataSpacing (3.2,3.2,1.5);			
	v16->Update();
*/

	vtkDICOMImageReader   *reader =  vtkDICOMImageReader::New();
	reader->SetDataByteOrderToLittleEndian();
	reader->SetDirectoryName("E://CT/head30/");

	vtkImageCast *imageData = vtkImageCast::New();
	imageData->SetInputConnection(reader->GetOutputPort());
	imageData->SetOutputScalarTypeToUnsignedChar();
	imageData->ClampOverflowOn();


	tfun = vtkPiecewiseFunction::New();
		tfun->AddPoint(20, 0.0);
		tfun->AddPoint(100, 1);
	    tfun->AddPoint(255, 0.8);
	/*
	tfun->AddPoint(  70.0,  .0);
	tfun->AddPoint( 599.0,  .5);
	tfun->AddPoint( 600.0,  .0);
	tfun->AddPoint(1195.0,  .0);
	tfun->AddPoint(1200.0,  .2);
	tfun->AddPoint(1300.0,  .3);
	tfun->AddPoint(2000.0,  .3);
	tfun->AddPoint(4095.0, 1.0);
*/
	ctfun = vtkColorTransferFunction::New();
	  ctfun->AddRGBPoint(0.0, 0.0, 0.5, 0.0);
      ctfun->AddRGBPoint(60.0, 1.0, 0.0, 0.0);
      ctfun->AddRGBPoint(128.0, 0.2, 0.1, 0.9);
      ctfun->AddRGBPoint(196.0, 0.27, 0.21, 0.1);
      ctfun->AddRGBPoint(255.0, 0.8, 0.8, 0.8);

	compositeFunction = vtkVolumeRayCastCompositeFunction::New();

	volumeMapper = vtkVolumeRayCastMapper::New();
	//ͼ����������ӳ����
	volumeMapper->SetInputConnection(imageData->GetOutputPort());
	volumeMapper->SetVolumeRayCastFunction(compositeFunction);


	//����ƽ�������
	plane1 = vtkPlane::New();
	//����ƽ���ʼ��
	plane1->SetOrigin(50,50,50);
	//����ƽ�淨��
	plane1->SetNormal(1, 1, 1);
	//����ƽ��
//	volumeMapper->AddClippingPlane(plane1);

		//����ƽ�������
	plane2 = vtkPlane::New();
	//����ƽ���ʼ��
//	plane2->SetOrigin(80, 80, 80);
	//����ƽ�淨��
//	plane2->SetNormal(-1, -1, -1);
	//����ƽ��
//	volumeMapper->AddClippingPlane(plane2);

	volumeProperty = vtkVolumeProperty::New();
	volumeProperty->SetColor(ctfun);
	volumeProperty->SetScalarOpacity(tfun);
	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->ShadeOn();

	newvol = vtkVolume::New();
	newvol->SetMapper(volumeMapper);
	newvol->SetProperty(volumeProperty);

	//�߽����������ʾ
	outline = vtkOutlineFilter::New();
	outline->SetInputConnection(imageData->GetOutputPort());

	outlineMapper = vtkPolyDataMapper::New();
	outlineMapper->SetInput(outline->GetOutput());

	outlineActor = vtkActor::New();
	outlineActor->SetMapper(outlineMapper);

//	iren->Initialize();
//    iren->Start(); 

	/*
	boxWidget = vtkBoxWidget::New();
	boxWidget->SetInteractor(iren);
	boxWidget->SetPlaceFactor(1.0);
	boxWidget->SetInput(imageData);
	boxWidget->PlaceWidget();
	boxWidget->InsideOutOn();
//	boxWidget->AddObserver()
/**/
	render->AddActor(outlineActor);
	render->AddVolume(newvol);
}

CMedical::~CMedical()
{

}
