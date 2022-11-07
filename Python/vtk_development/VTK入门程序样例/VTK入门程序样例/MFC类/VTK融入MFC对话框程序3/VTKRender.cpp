// VTKRender.cpp: implementation of the CVTKRender class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "step5.h"
#include "VTKRender.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVTKRender::CVTKRender()
{

	sphere = vtkSphereSource::New();
	  sphere->SetRadius(100);


	coneMapper = vtkPolyDataMapper::New();
	coneMapper->SetInput(sphere->GetOutput());
	
	coneActor = vtkActor::New();
	coneActor->SetMapper(coneMapper); 

	coneActor->GetProperty()->SetAmbient(0.5);
	coneActor->GetProperty()->SetAmbientColor(0.4,0.9,0.8);
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

}

CVTKRender::~CVTKRender()
{
	renWin->Delete();
	renderer->Delete();
	iren->Delete();
	sphere->Delete();
	coneMapper->Delete();
	coneActor->Delete();
}

void CVTKRender::BeginRenderOn(CStatic * aStatic)
{
	CRect rect;
	aStatic->GetClientRect(&rect);
	renWin->SetSize(rect.Width(),rect.Height());
	renWin->SetParentId(aStatic->m_hWnd);			//关键代码一：设置父窗口
	renWin->Render();                               // 关键代码二：开始绘制，启动交互器

}
