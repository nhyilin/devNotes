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

	//�ڹ��캯���аѸ���vtk��������ͨ��

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
	renWin->SetParentId(aStatic->m_hWnd);			//�ؼ�����һ�����ø�����
	renWin->Render();                               // �ؼ����������ʼ���ƣ�����������

}

void CVTK::MyExecute(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
	CVTK *m_viewer = reinterpret_cast<CVTK*>(clientdata );
	double ScreenCoordinate[3],globalCoordinate[3]; //ʰȡ�����Ļ�����ȫ������	
	CString str;

    if (m_viewer->picker->GetCellId()<0)
	{
//		AfxMessageBox("CellID < 0");

		m_viewer->picker->GetSelectionPoint(ScreenCoordinate);	//�õ���Ļ����
		m_viewer->picker->GetPickPosition(globalCoordinate);	//�õ�ȫ������

		str.Format("X:%f,Y:%f,Z:%f",
			globalCoordinate[0],globalCoordinate[1],globalCoordinate[2]);

		AfxMessageBox("ѡ�еĵ���ͼ����"+str);
	}
    else
	{
//		AfxMessageBox("CellID > 0");

		m_viewer->picker->GetSelectionPoint(ScreenCoordinate);	//�õ���Ļ����
		m_viewer->picker->GetPickPosition(globalCoordinate);	//�õ�ȫ������

		str.Format("X:%f,Y:%f,Z:%f",
			globalCoordinate[0],globalCoordinate[1],globalCoordinate[2]);

		AfxMessageBox("ѡ�еĵ���ͼ����"+str);

	};
}

