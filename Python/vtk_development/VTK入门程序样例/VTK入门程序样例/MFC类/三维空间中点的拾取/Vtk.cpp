// VTK.cpp: implementation of the CVTK class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "step5.h"
#include "VTK.h"
#include <vtkCallbackCommand.h>
#include "vtkProperty.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


double CVTK::ScreenCoordinate[3] ;
double CVTK::globalCoordinate[3] ;


CVTK::CVTK()
{
    polyReader=vtkPolyDataReader::New();

    stripper=vtkStripper::New(); 
//    stripper->SetInput(sphere->GetOutput());

	sphere = vtkSphereSource::New();		
      sphere->SetThetaResolution(20); 
	  sphere->SetPhiResolution(20);
      sphere->SetRadius(100);
	//在构造函数中把各个vtk对象连成通道

	coneMapper = vtkPolyDataMapper::New();
	coneMapper->SetInput(sphere->GetOutput());
	
	coneActor = vtkActor::New();
	coneActor->SetMapper(coneMapper); 

	coneActor->GetProperty()->SetAmbient(0.5);
	coneActor->GetProperty()->SetAmbientColor(0.2,0.2,0.2);
	coneActor->GetProperty()->SetDiffuse(0.8);
	coneActor->GetProperty()->SetDiffuseColor(1,1,0.94);
	coneActor->GetProperty()->SetSpecular(0.4);
	coneActor->GetProperty()->SetSpecularColor(0.4,0.4,0.5);
	coneActor->GetProperty()->SetSpecularPower(1);

	spoint = vtkSphereSource::New();		
      spoint->SetThetaResolution(20); 
	  spoint->SetPhiResolution(20);
      spoint->SetRadius(5);
	//在构造函数中把各个vtk对象连成通道

	pointMapper = vtkPolyDataMapper::New();
	pointMapper->SetInput(spoint->GetOutput());
	
	pointActor = vtkActor::New();
	pointActor->SetMapper(pointMapper); 

	pointActor->GetProperty()->SetAmbient(0.5);
	pointActor->GetProperty()->SetAmbientColor(1,0,0);
	pointActor->GetProperty()->SetDiffuse(1);
	pointActor->GetProperty()->SetDiffuseColor(1,0,0);
	pointActor->GetProperty()->SetSpecular(0.5);
	pointActor->GetProperty()->SetSpecularColor(1,0,0);
	pointActor->GetProperty()->SetSpecularPower(1);

	aCamera = vtkCamera::New();
    aCamera->SetViewUp (0, 0, -1);
    aCamera->SetPosition (1, 1, 1);
    aCamera->SetFocalPoint (99,99,40);	

	renderer = vtkRenderer::New();
	renderer->AddActor(pointActor);
	renderer->AddActor(coneActor);
	renderer->SetBackground(0,0,0);
	renderer->SetActiveCamera(aCamera);
    renderer->ResetCamera ();
    aCamera->Dolly(1.45);


	
	renWin = vtkRenderWindow::New();
	renWin->AddRenderer(renderer);
	
	iren = vtkWin32RenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);

	picker=vtkCellPicker::New();
	

    //picker->SetTolerance(0.00001);
	
	vtkCallbackCommand * cmd = vtkCallbackCommand::New();
	cmd->SetCallback(CVTK::MyExecute);
	cmd->SetClientData( this );
	picker->AddObserver(vtkCommand::EndPickEvent, cmd);

	iren->SetPicker(picker);
	cmd->Delete();		
}

CVTK::~CVTK()
{
	renWin->Delete();
	renderer->Delete();
	iren->Delete();
	sphere->Delete();
	coneMapper->Delete();
	coneActor->Delete();
	picker->Delete();
}

void CVTK::BeginRenderOn(CStatic * aStatic)
{
	CRect rect;
	aStatic->GetClientRect(&rect);
	renWin->SetSize(rect.Width(),rect.Height());
	renWin->SetParentId(aStatic->m_hWnd);			//关键代码一：设置父窗口
	renWin->Render();                               // 关键代码二：开始绘制，启动交互器

}

void CVTK::MyExecute(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
	CVTK *m_viewer = reinterpret_cast<CVTK*>(clientdata );

    if (m_viewer->picker->GetCellId()<0)
	{
		//AfxMessageBox("CellID < 0");
		/*
		globalCoordinate[0]=0;
		globalCoordinate[1]=0;
		globalCoordinate[2]=0;

		ScreenCoordinate[0]=0;
		ScreenCoordinate[1]=0;
		ScreenCoordinate[2]=0;
		*/

		m_viewer->picker->GetSelectionPoint(ScreenCoordinate);	//得到屏幕坐标
		m_viewer->picker->GetPickPosition(globalCoordinate);
	}
    else
	{
//		AfxMessageBox("CellID > 0");
//		double ScreenCoordinate[3],globalCoordinate[3]; //拾取点的屏幕坐标和全局坐标
		m_viewer->picker->GetSelectionPoint(ScreenCoordinate);	//得到屏幕坐标
		m_viewer->picker->GetPickPosition(globalCoordinate);	//得到全局坐标
	};
}

