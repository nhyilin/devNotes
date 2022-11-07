//////////////////////////////////////////////////////////////////////////
//
//  ������Ĺ��ܣ���ȡ��ά���������
//
// This demo revised from the VTK example of creating a rectilinear grid.
//
//  Zhao Jian, 2007-8-12
//
//////////////////////////////////////////////////////////////////////////

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"

#include "vtkDoubleArray.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkOutlineFilter.h"

#include "vtkMarchingCubes.h"
#include "vtkSTLWriter.h"
#include "vtkSTLReader.h"
#include "vtkDecimatePro.h"

#include "vtkExtractGrid.h"
#include "vtkDataSetMapper.h"
#include "vtkPolyDataNormals.h"
#include "vtkPlane.h"
#include "vtkCutter.h"
#include "vtkStripper.h"
#include "vtkPolyData.h"
#include "vtkTriangleFilter.h"
#include "vtkClipPolyData.h"
#include "vtkConeSource.h"
#include "vtkOutlineFilter.h"
#include "vtkAxes.h"
#include "vtkCubeAxesActor2D.h"
#include "vtkTextProperty.h"
#include "vtkContourFilter.h"
#include "vtkExtractEdges.h"
#include "vtkTubeFilter.h"
#include "vtkCommand.h"
#include "vtkDICOMImageReader.h"
#include "vtkPlaneWidget.h"
#include "vtkProbeFilter.h"
#include "vtkImplicitPlaneWidget.h"

//vector<string>svec(sa,sa+6);
//Generate cut lines
vtkPlane * plane = vtkPlane::New ();
vtkPolyData *cutPoly = vtkPolyData::New();// #This trick defines polygons as polyline loop
vtkStripper * cutStrips = vtkStripper::New();// #Forms loops (closed polylines) from cutter
vtkCutter * cutEdges = vtkCutter::New ();
vtkPolyDataMapper *mapEdges = vtkPolyDataMapper::New();
vtkActor *coneActor = vtkActor::New();
vtkPlaneWidget * pWidget = vtkPlaneWidget::New();
class vtkMyCallback : public vtkCommand
{
public:
	static vtkMyCallback *New() 
	{ return new vtkMyCallback; }
	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkPlaneWidget * pPlaneWidget = reinterpret_cast<vtkPlaneWidget*>(caller);//ǿ��ת����
		pPlaneWidget->GetPlane(plane);
	}
};

int main( int argc, char *argv[] )
{
	//////////////////////////////////////////////////////////////////////////
	// ������Ⱦ�����Ľṹ����Ⱦ������Ⱦ���ںͽ�������
	vtkRenderer *aRenderer = vtkRenderer::New();
	//aRenderer->SetViewport (0, 0, 0.5, 1.0);
	vtkRenderer * aRenderer2 = vtkRenderer::New();
	//aRenderer2->SetViewport (0.5, 0, 1.0, 1.0);



	vtkRenderWindow *renWin = vtkRenderWindow::New();
	vtkRenderWindow *renWin2 = vtkRenderWindow::New();
//������������������������������������������������������������������������������������������������������������������
//������������������������������������������������������������������������������������������������������������������
//������������������������������������������������������������������������������������������������������������������
//if ����������������������
//�޸�����Ŀ���
	if (true)
	{//���Կ����������ƶ�PlaneWidget��ʧ
		renWin->AddRenderer(aRenderer);
		renWin2->AddRenderer(aRenderer2);
	}
	else
	{		//ֱ���и�����ʾActor
		renWin->AddRenderer(aRenderer2);
		renWin2->AddRenderer(aRenderer2);
	}

	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);
	vtkRenderWindowInteractor *iren2 = vtkRenderWindowInteractor::New();
	iren2->SetRenderWindow(renWin2);

	//////////////////////////////////////////////////////////////////////////
	// �������룺STL��ʽ
	vtkSTLReader * stlBinaryIn = vtkSTLReader::New();
	stlBinaryIn->SetFileName("ball.STL");


	//////////////////////////////////////////////////////////////////////////
	//normals
	vtkPolyDataNormals *normals = vtkPolyDataNormals::New();
	normals->SetInput(stlBinaryIn->GetOutput());



	pWidget->SetInput(normals->GetOutput());
	pWidget->SetInteractor(iren);
	pWidget->PlaceWidget();
	pWidget->On();
	vtkMyCallback *mo1 = vtkMyCallback::New();
	pWidget->AddObserver(vtkCommand::InteractionEvent,mo1);

	//////////////////////////////////////////////////////////////////////////
	// ���洦��
	//	vtkCutter * cutEdges = vtkCutter::New ();
	cutEdges-> SetInput ( (vtkDataSet *)stlBinaryIn-> GetOutput());
	cutEdges-> SetCutFunction (plane);
	cutEdges-> GenerateCutScalarsOn();
	cutEdges-> SetValue (0, 0.5);
	//		cutEdges-> SetValue (1, 10.5);
	//	vtkPolyDataMapper *mapEdges = vtkPolyDataMapper::New();
	mapEdges-> SetInput (cutEdges-> GetOutput());
	mapEdges-> ScalarVisibilityOff();
	vtkActor *edgeActor = vtkActor::New();
	edgeActor-> SetMapper (mapEdges);
	edgeActor-> GetProperty()->SetColor(0.5,0.8,0.8);	
	edgeActor-> GetProperty()-> SetSpecularColor (1, 1, 1);
	edgeActor-> GetProperty()-> SetSpecular (0.3);
	edgeActor-> GetProperty()-> SetSpecularPower (20);
	edgeActor-> GetProperty()-> SetAmbient (1);
	//		edgeActor-> GetProperty()-> SetDiffuse (0.8);

	//////////////////////////////////////////////////////////////////////////
	//clip
	vtkClipPolyData * clipper = vtkClipPolyData::New();
	clipper-> SetInput (normals-> GetOutput());
	clipper-> SetClipFunction (plane);
	clipper-> GenerateClipScalarsOn();
	clipper-> GenerateClippedOutputOn();
	clipper-> SetValue (0.5);
	vtkPolyDataMapper *  clipMapper = vtkPolyDataMapper::New();
	clipMapper-> SetInput(clipper-> GetOutput());
	clipMapper-> ScalarVisibilityOff();
	vtkActor  * clipActor = vtkActor::New();
	clipActor-> SetMapper (clipMapper);
	//		clipActor-> GetProperty() -> SetColor(0.5,0.8,1);//cyan
	clipActor-> GetProperty()-> SetOpacity(0.1);


	//////////////////////////////////////////////////////////////////////////
	//rest	
	vtkPolyDataMapper * restMapper = vtkPolyDataMapper::New();
	restMapper-> SetInput (clipper-> GetClippedOutput());
	restMapper-> ScalarVisibilityOff();
	vtkActor * restActor = vtkActor::New();
	restActor-> SetMapper (restMapper);						//default white
	//		restActor-> GetProperty()-> SetRepresentationToWireframe();	
	restActor-> GetProperty()->SetOpacity(1.0);
	vtkProperty * backPro = vtkProperty::New();//�ڲ���ɫ����
	backPro->SetDiffuseColor(0.5,1.0,1.0);
	restActor->SetBackfaceProperty(backPro);




	//////////////////////////////////////////////////////////////////////////
	// ������Ⱦ����������
	vtkCamera *aCamera = vtkCamera::New();	// �����������
	//	aCamera->SetViewUp(0, 0, -1);
	//	aCamera->SetPosition(0, 1, 0);
	aCamera->SetPosition(-1, 0, 0);
	aCamera->SetFocalPoint(0, 0, 0);
	aCamera->ComputeViewPlaneNormal();//?

	//	aRenderer-> AddProp (axes2D); 	//������ʾ

	aRenderer->AddActor(edgeActor);
	aRenderer->AddActor(clipActor);
	aRenderer->AddActor(restActor);

	aRenderer->SetBackground(0.1,0.2,0.4);	// ��ɫ����	
	aRenderer->SetActiveCamera(aCamera);

	aRenderer->ResetCamera();
	aRenderer2->AddActor(clipActor);
	aRenderer2->AddActor(restActor);
	aRenderer2->AddActor(edgeActor);
	aRenderer2->SetBackground(0.1,0.2,0.4);	// ��ɫ����

	renWin->SetSize(800, 600);			// ��ǰ�ӿڴ�С

	aRenderer->ResetCameraClippingRange();

	iren->Initialize();
	iren2->Initialize();
	iren2->Start();
	iren->Start(); 


	mo1->Delete();
	aRenderer2->Delete();
	aRenderer->Delete();
	renWin->Delete();
	aCamera->Delete();
	iren->Delete();	
	cutEdges->Delete();
	restActor->Delete();
	clipActor->Delete();

	restMapper->Delete();
	clipMapper->Delete();
	clipper->Delete();
	cutStrips->Delete();
	cutPoly->Delete();
	normals->Delete();
	plane->Delete();



	return 0;
}