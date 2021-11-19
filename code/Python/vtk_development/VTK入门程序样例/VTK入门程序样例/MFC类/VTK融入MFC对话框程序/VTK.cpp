// VTK.cpp: implementation of the CVTK class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "step5.h"
#include "VTK.h"

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
	//在构造函数中把各个vtk对象连成通道
	cone = vtkConeSource::New();
	cone->SetResolution(180);

	coneMapper = vtkPolyDataMapper::New();
	coneMapper->SetInput(cone->GetOutput());
	
	coneActor = vtkActor::New();
	coneActor->SetMapper(coneMapper); 
	
	renderer = vtkRenderer::New();
	renderer->AddActor(coneActor);
	renderer->SetBackground(0.2,0.4,0.3);
	
	renWin = vtkRenderWindow::New();
	renWin->AddRenderer(renderer);
	
	iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);
	
}

CVTK::~CVTK()
{
	renWin->Delete();
	renderer->Delete();
	iren->Delete();
	cone->Delete();
	coneMapper->Delete();
	coneActor->Delete();
}

void CVTK::BeginRenderOn(CStatic * aStatic)
{
	CRect rect;
	aStatic->GetClientRect(&rect);
	renWin->SetSize(rect.Width(),rect.Height());
	renWin->SetParentId(aStatic->m_hWnd);			//关键代码一：设置父窗口
	renWin->Render();                               // 关键代码二：开始绘制，启动交互器

}
