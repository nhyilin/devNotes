//////////////////////////////////////////////////////////////////////////
//
//  本程序的功能：获取三维物体的切面
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
		vtkPlaneWidget * pPlaneWidget = reinterpret_cast<vtkPlaneWidget*>(caller);//强制转换？
		pPlaneWidget->GetPlane(plane);
	}
};

int main( int argc, char *argv[] )
{
	//////////////////////////////////////////////////////////////////////////
	// 设置渲染环境的结构（渲染器、渲染窗口和交互器）
	vtkRenderer *aRenderer = vtkRenderer::New();
	//aRenderer->SetViewport (0, 0, 0.5, 1.0);
	vtkRenderer * aRenderer2 = vtkRenderer::New();
	//aRenderer2->SetViewport (0.5, 0, 1.0, 1.0);



	vtkRenderWindow *renWin = vtkRenderWindow::New();
	vtkRenderWindow *renWin2 = vtkRenderWindow::New();
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
//if 条件真假两种情况都有问题
//修改这里的看看
	if (true)
	{//可以看见，但是移动PlaneWidget消失
		renWin->AddRenderer(aRenderer);
		renWin2->AddRenderer(aRenderer2);
	}
	else
	{		//直接有个不显示Actor
		renWin->AddRenderer(aRenderer2);
		renWin2->AddRenderer(aRenderer2);
	}

	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);
	vtkRenderWindowInteractor *iren2 = vtkRenderWindowInteractor::New();
	iren2->SetRenderWindow(renWin2);

	//////////////////////////////////////////////////////////////////////////
	// 数据输入：STL格式
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
	// 截面处理
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
	vtkProperty * backPro = vtkProperty::New();//内部颜色设置
	backPro->SetDiffuseColor(0.5,1.0,1.0);
	restActor->SetBackfaceProperty(backPro);




	//////////////////////////////////////////////////////////////////////////
	// 设置渲染环境的属性
	vtkCamera *aCamera = vtkCamera::New();	// 设置相机属性
	//	aCamera->SetViewUp(0, 0, -1);
	//	aCamera->SetPosition(0, 1, 0);
	aCamera->SetPosition(-1, 0, 0);
	aCamera->SetFocalPoint(0, 0, 0);
	aCamera->ComputeViewPlaneNormal();//?

	//	aRenderer-> AddProp (axes2D); 	//坐标显示

	aRenderer->AddActor(edgeActor);
	aRenderer->AddActor(clipActor);
	aRenderer->AddActor(restActor);

	aRenderer->SetBackground(0.1,0.2,0.4);	// 青色背景	
	aRenderer->SetActiveCamera(aCamera);

	aRenderer->ResetCamera();
	aRenderer2->AddActor(clipActor);
	aRenderer2->AddActor(restActor);
	aRenderer2->AddActor(edgeActor);
	aRenderer2->SetBackground(0.1,0.2,0.4);	// 青色背景

	renWin->SetSize(800, 600);			// 当前视口大小

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