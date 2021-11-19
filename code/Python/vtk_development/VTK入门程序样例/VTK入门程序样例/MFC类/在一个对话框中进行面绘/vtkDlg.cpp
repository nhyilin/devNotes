// vtkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "vtk.h"
#include "vtkDlg.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CvtkDlg dialog


CvtkDlg::CvtkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CvtkDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CvtkDlg)
	//}}AFX_DATA_INIT
	m_hIcon=AfxGetApp()->LoadIcon(IDI_ICON1);
	m_vtk=new CVTK(500);
}


void CvtkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CvtkDlg)
	DDX_Control(pDX, IDC_INTERRENDER, m_RenderArea);
	DDX_Control(pDX, IDC_SLIDER1, m_ContourSlider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CvtkDlg, CDialog)
	//{{AFX_MSG_MAP(CvtkDlg)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CvtkDlg message handlers

void CvtkDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete(m_vtk);
}

BOOL CvtkDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetIcon(m_hIcon,FALSE);
    SetIcon(m_hIcon,true);
	
	m_ContourSlider.SetRange(500,3000,true);
	m_ContourSlider.SetPos(500);

	m_vtk->BeginRenderOn(&m_RenderArea);//句柄连接
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CvtkDlg::OnPaint() 
{
// 	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
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
	// Do not call CDialog::OnPaint() for painting messages
}

void CvtkDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	//delete(m_vtk);
	int contour=this->m_ContourSlider.GetPos();
	m_vtk=new CVTK(contour);
//	m_vtk->skinExtractor->SetValue(0,contour);
	m_vtk->BeginRenderOn(&m_RenderArea);
	// 正文中
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
