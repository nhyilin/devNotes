// VTK.cpp: implementation of the CVTK class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "step4.h"
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
	render = vtkRenderer::New();
	render->SetBackground(.1,.2,.3);

	renWin = vtkRenderWindow::New();
	renWin->AddRenderer(render);

	iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);
}

CVTK::~CVTK()
{

}

void CVTK::VTKToDialog(CStatic * aStatic)
{
	CRect rect;
	aStatic->GetClientRect(&rect);
	renWin->SetSize(rect.Width(),rect.Height());
	//�ؼ�����һ�����ø�����
	renWin->SetParentId(aStatic->m_hWnd);
	// �ؼ����������ʼ���ƣ�����������			
	renWin->Render();    
}
