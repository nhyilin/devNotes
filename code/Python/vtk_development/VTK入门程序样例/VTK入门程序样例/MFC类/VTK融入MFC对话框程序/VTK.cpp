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
	//�ڹ��캯���аѸ���vtk��������ͨ��
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
	renWin->SetParentId(aStatic->m_hWnd);			//�ؼ�����һ�����ø�����
	renWin->Render();                               // �ؼ����������ʼ���ƣ�����������

}
