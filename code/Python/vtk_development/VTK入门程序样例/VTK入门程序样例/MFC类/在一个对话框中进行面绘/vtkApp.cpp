#include "stdafx.h"
#include "vtkApp.h"
#include "vtkDlg.h"


BEGIN_MESSAGE_MAP(CVTKApp, CWinApp)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVTKGUIApp construction

CVTKApp::CVTKApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVTKGUIApp object

CVTKApp theApp;

BOOL CVTKApp::InitInstance()
{
	
	
	CvtkDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	
	return FALSE;
}