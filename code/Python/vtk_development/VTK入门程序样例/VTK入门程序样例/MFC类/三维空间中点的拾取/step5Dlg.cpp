// step5Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "step5.h"
#include "step5Dlg.h"
#include "vtkProperty.h"
#include "vtkSphereSource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep5Dlg dialog

CStep5Dlg::CStep5Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStep5Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStep5Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStep5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep5Dlg)
	DDX_Control(pDX, IDC_EDIT8, m_Edit8);
	DDX_Control(pDX, IDC_SLIDER2, m_Slider2);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider1);
	DDX_Control(pDX, IDC_EDIT7, m_Edit7);
	DDX_Control(pDX, IDC_EDIT6, m_Edit6);
	DDX_Control(pDX, IDC_EDIT5, m_Edit5);
	DDX_Control(pDX, IDC_EDIT4, m_Edit4);
	DDX_Control(pDX, IDC_EDIT3, m_Edit3);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_RenderArea, m_RenderArea);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStep5Dlg, CDialog)
	//{{AFX_MSG_MAP(CStep5Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, OnCustomdrawSlider2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep5Dlg message handlers

BOOL CStep5Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	this->m_Slider1.SetRange(0,100, FALSE);
	this->m_Slider1.SetPos(100);
	
	this->m_Slider2.SetRange(1,10, FALSE);
	this->m_Slider2.SetPos(3);
	// TODO: Add extra initialization here
	this->m_vtk.BeginRenderOn(&(this->m_RenderArea));
	
	int count = this->m_vtk.sphere->GetOutput()->GetNumberOfCells() ;
	CString str;
	str.Format("生成CELL个数: %d",count);
    this->m_Edit8.SetWindowText(str);	

	this->m_Edit7.SetWindowText("请打开一个VTK文件!");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStep5Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStep5Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


BOOL CStep5Dlg::PreTranslateMessage(MSG* pMsg) 
{
	 bool propagateMessage = true;

    switch (pMsg->message)
    {
        case WM_CHAR:
            switch (pMsg->wParam)
            {
                case 'p':
                case 'P':
                    SetWindowLong(this->m_hWnd, GWL_USERDATA, (long)(m_vtk.renWin));
                    vtkHandleMessage2(this->m_hWnd, WM_CHAR, 'p', 0, m_vtk.iren);
                    propagateMessage = false;
                    break;
			    case 'W':
                case 'w':
                    SetWindowLong(this->m_hWnd, GWL_USERDATA, (long)(m_vtk.renWin));
                    vtkHandleMessage2(this->m_hWnd, WM_CHAR, 'w', 0, m_vtk.iren);
                    break;
			    case 's':
                case 'S':
                    SetWindowLong(this->m_hWnd, GWL_USERDATA, (long)(m_vtk.renWin));
                    vtkHandleMessage2(this->m_hWnd, WM_CHAR, 's', 0, m_vtk.iren);
                    break;
			    case 'r':
                case 'R':
                    SetWindowLong(this->m_hWnd, GWL_USERDATA, (long)(m_vtk.renWin));
                    vtkHandleMessage2(this->m_hWnd, WM_CHAR, 'r', 0, m_vtk.iren);
                    break;
			    case 'c':
                case 'C':
                    SetWindowLong(this->m_hWnd, GWL_USERDATA, (long)(m_vtk.renWin));
                    vtkHandleMessage2(this->m_hWnd, WM_CHAR, 'c', 0, m_vtk.iren);
                    break;
				case 'a':
                case 'A':
                    SetWindowLong(this->m_hWnd, GWL_USERDATA, (long)(m_vtk.renWin));
                    vtkHandleMessage2(this->m_hWnd, WM_CHAR, 'a', 0, m_vtk.iren);
                    break;
				case 'j':
                case 'J':
                    SetWindowLong(this->m_hWnd, GWL_USERDATA, (long)(m_vtk.renWin));
                    vtkHandleMessage2(this->m_hWnd, WM_CHAR, 'j', 0, m_vtk.iren);
                    break;
				case 't':
                case 'T':
                    SetWindowLong(this->m_hWnd, GWL_USERDATA, (long)(m_vtk.renWin));
                    vtkHandleMessage2(this->m_hWnd, WM_CHAR, 't', 0, m_vtk.iren);
                    break;
            }
            break;
    }

    if (propagateMessage)
	{
	    return CDialog::PreTranslateMessage(pMsg);
    } 
	else 
	{

		CString str;
		str.Format("X:%f",this->m_vtk.ScreenCoordinate[0]);
		this->m_Edit1.SetWindowText(str);
		str.Format("Y:%f",this->m_vtk.ScreenCoordinate[1]);
		this->m_Edit2.SetWindowText(str);
		str.Format("Z:%f",this->m_vtk.ScreenCoordinate[2]);
		this->m_Edit3.SetWindowText(str);

		str.Format("X:%f",this->m_vtk.globalCoordinate[0]);
		this->m_Edit4.SetWindowText(str);
		str.Format("Y:%f",this->m_vtk.globalCoordinate[1]);
		this->m_Edit5.SetWindowText(str);
		str.Format("Z:%f",this->m_vtk.globalCoordinate[2]);
		this->m_Edit6.SetWindowText(str);

		this->m_vtk.pointActor->VisibilityOn();
		this->m_vtk.pointActor->SetPosition (this->m_vtk.globalCoordinate);

	    this->m_vtk.BeginRenderOn(&(this->m_RenderArea));
        return true;
    }
}

void CStep5Dlg::OnButton1() 
{

//    SetWindowLong(this->m_hWnd, GWL_USERDATA, (long)(m_vtk.renWin));
//    vtkHandleMessage2(this->m_hWnd, WM_CHAR, 'p', 0, m_vtk.iren);

	// TODO: Add your control notification handler code here
	CString str;
	str.Format("%f",this->m_vtk.ScreenCoordinate[0]);
	this->m_Edit1.SetWindowText(str);
	str.Format("%f",this->m_vtk.ScreenCoordinate[1]);
	this->m_Edit2.SetWindowText(str);
	str.Format("%f",this->m_vtk.ScreenCoordinate[2]);
	this->m_Edit3.SetWindowText(str);

	str.Format("%f",this->m_vtk.globalCoordinate[0]);
	this->m_Edit4.SetWindowText(str);
	str.Format("%f",this->m_vtk.globalCoordinate[1]);
	this->m_Edit5.SetWindowText(str);
	str.Format("%f",this->m_vtk.globalCoordinate[2]);
	this->m_Edit6.SetWindowText(str);


}

void CStep5Dlg::OnButton2() 
{
	char szFileters[]="DICOM files(*.vtk)|*.vtk||";
	CFileDialog opendlg(TRUE,"","",
		OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,szFileters,this);
	if(opendlg.DoModal()!=IDOK)
	{
		return;
	}	

	this->m_vtk.polyReader->SetFileName(opendlg.GetPathName());
	this->m_vtk.polyReader->Update();

    this->m_vtk.stripper->SetInput(this->m_vtk.polyReader->GetOutput());
    this->m_vtk.coneMapper->SetInputConnection(this->m_vtk.stripper->GetOutputPort());

	this->m_vtk.pointActor->VisibilityOff();

	this->m_vtk.renderer->ResetCamera ();
	this->m_vtk.aCamera->Dolly(1.45);
	this->m_vtk.BeginRenderOn(&(this->m_RenderArea));

    this->m_Edit7.SetWindowText("VTK目录: "+opendlg.GetPathName());

	int count = this->m_vtk.stripper->GetOutput()->GetNumberOfCells() ;
	CString str;
	str.Format("生成CELL个数: %d",count);
    this->m_Edit8.SetWindowText(str);

}

void CStep5Dlg::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int pos = this->m_Slider1.GetPos();
    m_vtk.coneActor->GetProperty()->SetOpacity(pos*0.01);
	this->m_vtk.BeginRenderOn(&(this->m_RenderArea));

	*pResult = 0;
}

void CStep5Dlg::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int pos = this->m_Slider2.GetPos();
    this->m_vtk.spoint->SetRadius(pos);
	this->m_vtk.BeginRenderOn(&(this->m_RenderArea));

	*pResult = 0;
}

void CStep5Dlg::OnButton3() 
{
	this->m_vtk.pointActor->VisibilityOff();

	this->m_vtk.renderer->ResetCamera ();
	this->m_vtk.aCamera->Dolly(1.45);
	this->m_vtk.BeginRenderOn(&(this->m_RenderArea));	
}

void CStep5Dlg::OnButton4() 
{
	int count = this->m_vtk.stripper->GetOutput()->GetNumberOfCells() ;
	CString str;
	str.Format("生成CELL个数: %d",count);
    this->m_Edit8.SetWindowText(str);	
}
