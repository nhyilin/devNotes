// FirstView.cpp : implementation file
//

#include "stdafx.h"
#include "Splitter.h"
#include "FirstView.h"
#include "SplitterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFirstView

IMPLEMENT_DYNCREATE(CFirstView, CFormView)

CFirstView::CFirstView()
	: CFormView(CFirstView::IDD)
{
	//{{AFX_DATA_INIT(CFirstView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	flagyes=0;

}

CFirstView::~CFirstView()
{
}

void CFirstView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFirstView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFirstView, CFormView)
	//{{AFX_MSG_MAP(CFirstView)
	ON_BN_CLICKED(IDC_YES, OnYes)
	ON_BN_CLICKED(IDC_NO, OnNo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFirstView diagnostics

#ifdef _DEBUG
void CFirstView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFirstView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFirstView message handlers

void CFirstView::OnYes() 
{
	// TODO: Add your control notification handler code here
	flagyes=1;
	
	CSplitterView *pView ;

	POSITION p  ;
	p = GetDocument()->GetFirstViewPosition() ;

	while(p )
	{
		pView = (CSplitterView *)GetDocument()->GetNextView(p) ;
		
		if((pView->IsKindOf(RUNTIME_CLASS(CSplitterView))))
			break ;
	}
	pView->sphereAxis->VisibilityOn();
//	pView->ShowMessage() ;
//	pView->spikeActor->VisibilityOff();

//	MessageBox("Yes");
	
	pView->renWin->Render();
	
}

void CFirstView::OnNo() 
{
	flagyes=0;
	
	CSplitterView *pView ;

	POSITION p  ;
	p = GetDocument()->GetFirstViewPosition() ;

	while(p )
	{
		pView = (CSplitterView *)GetDocument()->GetNextView(p) ;
		
		if((pView->IsKindOf(RUNTIME_CLASS(CSplitterView))))
			break ;
	}
	pView->sphereAxis->VisibilityOff();	
	pView->renWin->Render();
}
