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

CVTK::CVTK()
{

	sphere = vtkSphereSource::New();
	  sphere->SetRadius(100);

	//在构造函数中把各个vtk对象连成通道

	coneMapper = vtkPolyDataMapper::New();
	coneMapper->SetInput(sphere->GetOutput());
	
	coneActor = vtkActor::New();
	coneActor->SetMapper(coneMapper); 

	coneActor->GetProperty()->SetAmbient(0.5);
	coneActor->GetProperty()->SetAmbientColor(0.1,0.9,0.2);
	coneActor->GetProperty()->SetDiffuse(1);
	coneActor->GetProperty()->SetDiffuseColor(0.3,0.6,0.2);
	coneActor->GetProperty()->SetSpecular(0.6);
	coneActor->GetProperty()->SetSpecularColor(0.8,0.3,0.5);
	coneActor->GetProperty()->SetSpecularPower(1);
	
	renderer = vtkRenderer::New();
	renderer->AddActor(coneActor);
	renderer->SetBackground(0.2,0.4,0.3);
	
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
	double ScreenCoordinate[3],globalCoordinate[3]; //拾取点的屏幕坐标和全局坐标	
	CString str;

    if (m_viewer->picker->GetCellId()<0)
	{
//		AfxMessageBox("CellID < 0");

		m_viewer->picker->GetSelectionPoint(ScreenCoordinate);	//得到屏幕坐标
		m_viewer->picker->GetPickPosition(globalCoordinate);	//得到全局坐标

		str.Format("X:%f,Y:%f,Z:%f",
			globalCoordinate[0],globalCoordinate[1],globalCoordinate[2]);

		AfxMessageBox("选中的点在图形外"+str);
	}
    else
	{
//		AfxMessageBox("CellID > 0");

		m_viewer->picker->GetSelectionPoint(ScreenCoordinate);	//得到屏幕坐标
		m_viewer->picker->GetPickPosition(globalCoordinate);	//得到全局坐标

		str.Format("X:%f,Y:%f,Z:%f",
			globalCoordinate[0],globalCoordinate[1],globalCoordinate[2]);

		AfxMessageBox("选中的点在图形内"+str);

	};
}

