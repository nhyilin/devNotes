// step4Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "step4.h"
#include "step4Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep4Dlg dialog

CStep4Dlg::CStep4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStep4Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStep4Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStep4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep4Dlg)
	DDX_Control(pDX, IDC_SLIDER6, m_Slider6);
	DDX_Control(pDX, IDC_SLIDER5, m_Slider5);
	DDX_Control(pDX, IDC_SLIDER4, m_Slider4);
	DDX_Control(pDX, IDC_EDIT6, m_Edit6);
	DDX_Control(pDX, IDC_EDIT5, m_Edit5);
	DDX_Control(pDX, IDC_EDIT4, m_Edit4);
	DDX_Control(pDX, IDC_EDIT3, m_Edit3);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_SLIDER3, m_Slider3);
	DDX_Control(pDX, IDC_SLIDER2, m_Slider2);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_SLIDER1, m_PosionSlider);
	DDX_Control(pDX, IDC_LIST1, m_List1);
	DDX_Control(pDX, IDC_MYSTATIC, m_MyStatic);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStep4Dlg, CDialog)
	//{{AFX_MSG_MAP(CStep4Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, OnCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, OnCustomdrawSlider3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER4, OnCustomdrawSlider4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER5, OnCustomdrawSlider5)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER6, OnCustomdrawSlider6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep4Dlg message handlers

BOOL CStep4Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	this->m_MyMedical.VTKToDialog(&(this->m_MyStatic));
	dc = this->m_MyStatic.GetDC();
	this->m_PosionSlider.SetRange(1, 205, FALSE);
	this->m_Slider2.SetRange(1, 205, FALSE);
	this->m_Slider3.SetRange(1, 140, FALSE);
	this->m_Slider4.SetRange(-100, 100, FALSE);
	this->m_Slider5.SetRange(-100, 100, FALSE);
	this->m_Slider6.SetRange(-100, 100, FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStep4Dlg::OnPaint() 
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
HCURSOR CStep4Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
	
}

	int flag = 0;
void CStep4Dlg::OnButton1() 
{
	int *a;
	a = (int*)malloc(sizeof(int) * 6);
	a = this->m_MyMedical.imageData->GetExtent();
	CString str;
	str.Format("%d,%d,%d,%d,%d,%d",*(a + 0),*(a + 1),*(a + 2),*(a + 3),*(a + 4),*(a + 5));
	AfxMessageBox(str);
}

void CStep4Dlg::OnButton2() 
{

	
}

void CStep4Dlg::OnButton3() 
{
	
	
}

void CStep4Dlg::OnButton4() 
{
}

//组合公式
float CStep4Dlg::c(int n, int m)
{
	return factorial(n)/(factorial(m) * factorial(n - m));
}

//阶乘公式
float CStep4Dlg::factorial(int n)
{
	float result = 1;
	for(int i = n; i > 1; i --)
		result *= i;
	return result;
}

//求n的0至n数组合的和
float CStep4Dlg::CropValue(int n)
{
	float result = 0;
	for(int i = 0; i <= n; i++)
		result += c(n,i);
	return result;
}

void CStep4Dlg::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int pos1 = this->m_PosionSlider.GetPos();
	int pos2 = this->m_Slider2.GetPos();
	int pos3 = this->m_Slider3.GetPos();
	int pos4 = this->m_Slider4.GetPos();
	int pos5 = this->m_Slider5.GetPos();
	int pos6 = this->m_Slider6.GetPos();
	CString str;
	str.Format("%d",pos1);
	this->m_Edit1.SetWindowText(str);
	this->m_MyMedical.plane2->SetOrigin(pos1, pos2, pos3);
	this->m_MyMedical.plane2->SetNormal(pos4, pos5, pos6);
	this->m_MyMedical.volumeMapper->AddClippingPlane(this->m_MyMedical.plane2);	
	this->m_MyMedical.VTKToDialog(&(this->m_MyStatic));
	
	*pResult = 0;
}

void CStep4Dlg::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	int pos1 = this->m_PosionSlider.GetPos();
	int pos2 = this->m_Slider2.GetPos();
	int pos3 = this->m_Slider3.GetPos();
	int pos4 = this->m_Slider4.GetPos();
	int pos5 = this->m_Slider5.GetPos();
	int pos6 = this->m_Slider6.GetPos();
	CString str;
	str.Format("%d",pos2);
	this->m_Edit2.SetWindowText(str);
	this->m_MyMedical.plane2->SetOrigin(pos1, pos2, pos3);
	this->m_MyMedical.plane2->SetNormal(pos4, pos5, pos6);
	this->m_MyMedical.volumeMapper->AddClippingPlane(this->m_MyMedical.plane2);	
	this->m_MyMedical.VTKToDialog(&(this->m_MyStatic));
	
	*pResult = 0;
}

void CStep4Dlg::OnCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult) 
{

	int pos1 = this->m_PosionSlider.GetPos();
	int pos2 = this->m_Slider2.GetPos();
	int pos3 = this->m_Slider3.GetPos();
	int pos4 = this->m_Slider4.GetPos();
	int pos5 = this->m_Slider5.GetPos();
	int pos6 = this->m_Slider6.GetPos();
	CString str;
	str.Format("%d",pos3);
	this->m_Edit3.SetWindowText(str);
	this->m_MyMedical.plane2->SetOrigin(pos1, pos2, pos3);
	this->m_MyMedical.plane2->SetNormal(pos4, pos5, pos6);
	this->m_MyMedical.volumeMapper->AddClippingPlane(this->m_MyMedical.plane2);	
	this->m_MyMedical.VTKToDialog(&(this->m_MyStatic));	

	*pResult = 0;
}

void CStep4Dlg::OnCustomdrawSlider4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int pos1 = this->m_PosionSlider.GetPos();
	int pos2 = this->m_Slider2.GetPos();
	int pos3 = this->m_Slider3.GetPos();
	int pos4 = this->m_Slider4.GetPos();
	int pos5 = this->m_Slider5.GetPos();
	int pos6 = this->m_Slider6.GetPos();
	CString str;
	str.Format("%d",pos4);
	this->m_Edit4.SetWindowText(str);
	this->m_MyMedical.plane2->SetOrigin(pos1, pos2, pos3);
	this->m_MyMedical.plane2->SetNormal(pos4, pos5, pos6);
	this->m_MyMedical.volumeMapper->AddClippingPlane(this->m_MyMedical.plane2);	
	this->m_MyMedical.VTKToDialog(&(this->m_MyStatic));	

	*pResult = 0;
}

void CStep4Dlg::OnCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int pos1 = this->m_PosionSlider.GetPos();
	int pos2 = this->m_Slider2.GetPos();
	int pos3 = this->m_Slider3.GetPos();
	int pos4 = this->m_Slider4.GetPos();
	int pos5 = this->m_Slider5.GetPos();
	int pos6 = this->m_Slider6.GetPos();
	CString str;
	str.Format("%d",pos5);
	this->m_Edit5.SetWindowText(str);
	this->m_MyMedical.plane2->SetOrigin(pos1, pos2, pos3);
	this->m_MyMedical.plane2->SetNormal(pos4, pos5, pos6);
	this->m_MyMedical.volumeMapper->AddClippingPlane(this->m_MyMedical.plane2);	
	this->m_MyMedical.VTKToDialog(&(this->m_MyStatic));	
	
	*pResult = 0;
}

void CStep4Dlg::OnCustomdrawSlider6(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int pos1 = this->m_PosionSlider.GetPos();
	int pos2 = this->m_Slider2.GetPos();
	int pos3 = this->m_Slider3.GetPos();
	int pos4 = this->m_Slider4.GetPos();
	int pos5 = this->m_Slider5.GetPos();
	int pos6 = this->m_Slider6.GetPos();
	CString str;
	str.Format("%d",pos6);
	this->m_Edit6.SetWindowText(str);
	this->m_MyMedical.plane2->SetOrigin(pos1, pos2, pos3);
	this->m_MyMedical.plane2->SetNormal(pos4, pos5, pos6);
	this->m_MyMedical.volumeMapper->AddClippingPlane(this->m_MyMedical.plane2);	
	this->m_MyMedical.VTKToDialog(&(this->m_MyStatic));	
	
	*pResult = 0;
}
