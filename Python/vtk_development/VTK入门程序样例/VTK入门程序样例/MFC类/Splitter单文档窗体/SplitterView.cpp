// SplitterView.cpp : implementation of the CSplitterView class
//

#include "stdafx.h"
#include "Splitter.h"

#include "SplitterDoc.h"
#include "SplitterView.h"


//


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitterView

IMPLEMENT_DYNCREATE(CSplitterView, CView)

BEGIN_MESSAGE_MAP(CSplitterView, CView)
	//{{AFX_MSG_MAP(CSplitterView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitterView construction/destruction

CSplitterView::CSplitterView()
{
	// TODO: add construction code here
	  this->ren = vtkRenderer::New();
	  this->renWin = vtkWin32OpenGLRenderWindow::New();
	  this->iren = vtkWin32RenderWindowInteractor::New();
	  
	  // Create the the objects used to form the visualisation.
	  this->sphere = vtkSphereSource::New();
	  this->sphereElevation = vtkElevationFilter::New();
	  this->sphereMapper = vtkPolyDataMapper::New();
	  this->sphereActor = vtkActor::New();
	  
	  this->cone = vtkConeSource::New();
	  this->glyph = vtkGlyph3D::New();
	  this->spikeMapper = vtkPolyDataMapper::New();
	  this->spikeActor = vtkActor::New();
	  
	  this->sphereAxis = vtkCubeAxesActor2D::New();

	 
}

CSplitterView::~CSplitterView()
{
	// Delete the the renderer, window and interactor objects.
	this->ren->Delete();
	this->iren->Delete();
	this->renWin->Delete();
	
	// Delete the the objects used to form the visualisation.
	this->sphere->Delete();
	this->sphereElevation->Delete();
	this->sphereMapper->Delete();
	this->sphereActor->Delete();
	
	this->cone->Delete();
	this->glyph->Delete();
	this->spikeMapper->Delete();
	this->spikeActor->Delete();
	
	this->sphereAxis->Delete();


}

BOOL CSplitterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSplitterView drawing

void CSplitterView::OnDraw(CDC* pDC)
{
	CSplitterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	 if(!this->iren->GetInitialized())
	 {
		 CRect rect;
		 this->GetClientRect(&rect);
		 this->iren->Initialize();
		 this->renWin->SetSize(rect.right-rect.left,rect.bottom-rect.top);

		 this->ren->ResetCamera();
	 
	 }
	 
	 // Invoke the pipeline
	 Pipeline();

/*

	 CFirstView yes1;
	 if (yes1.flagyes==1) 
	 {
		 Pipeline1();
	 }
*/

	 
	 
	 if ( pDC->IsPrinting() )
	 {
		 this->BeginWaitCursor();
		 
		 // Obtain the size of the printer page in pixels.
		 int cxPage = pDC->GetDeviceCaps(HORZRES);
		 int cyPage = pDC->GetDeviceCaps(VERTRES);
		 
		 // Get the size of the window in pixels.
		 int *size = this->renWin->GetSize();
		 int cxWindow = size[0];
		 int cyWindow = size[1];
		 float fx = float(cxPage) / float(cxWindow);
		 float fy = float(cyPage) / float(cyWindow);
		 
		 float scale = min(fx,fy);
		 int x = int(scale * float(cxWindow));
		 int y = int(scale * float(cyWindow));
		 
		 this->renWin->SetupMemoryRendering(cxWindow, cyWindow, pDC->GetSafeHdc());
		 this->renWin->Render();
		 
		 HDC memDC = this->renWin->GetMemoryDC();
		 StretchBlt(pDC->GetSafeHdc(),0,0,x,y,memDC,0,0,cxWindow,cyWindow,SRCCOPY);

		 this->renWin->ResumeScreenRendering();

		 this->EndWaitCursor();
	 
	 }
	 
	 else
	 {
		 this->renWin->Render();
	 
	 }


}

/////////////////////////////////////////////////////////////////////////////
// CSplitterView printing

BOOL CSplitterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSplitterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSplitterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSplitterView diagnostics

#ifdef _DEBUG
void CSplitterView::AssertValid() const
{
	CView::AssertValid();
}

void CSplitterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSplitterDoc* CSplitterView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSplitterDoc)));
	return (CSplitterDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplitterView message handlers

void CSplitterView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	 CRect rect;
	 
	 this->GetClientRect(&rect);

	 this->renWin->SetSize(rect.right-rect.left,rect.bottom-rect.top);


			
}

BOOL CSplitterView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	
//	return CView::OnEraseBkgnd(pDC);
}

//没有用
BOOL CSplitterView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

//

int CSplitterView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	this->renWin->AddRenderer(this->ren);

	// setup the parent window

    this->renWin->SetParentId(this->m_hWnd);

    this->iren->SetRenderWindow(this->renWin);

	return 0;
}

LRESULT CSplitterView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch (message)
	{
		//case WM_PAINT: 
	case WM_LBUTTONDOWN: 
		
	case WM_LBUTTONUP: 
		
    case WM_MBUTTONDOWN: 
		
    case WM_MBUTTONUP: 
		
    case WM_RBUTTONDOWN: 
		
    case WM_RBUTTONUP: 
		
    case WM_MOUSEMOVE:
		
    case WM_CHAR:
		
    case WM_TIMER:
		
	if (this->iren->GetInitialized())
			
	{
			
		return vtkHandleMessage2(this->m_hWnd, message, wParam, lParam, this->iren);
			
	}
		
		break;
		
	}
	
	
	return CView::WindowProc(message, wParam, lParam);
}


void CSplitterView::Pipeline()

{
	// Construct the sphere
	
	this->sphere->SetRadius(1);
	
	this->sphere->SetThetaResolution(18);
	
	this->sphere->SetPhiResolution(18);
	
	this->sphere->LatLongTessellationOn();
	
	// Generate elevations
	
	this->sphereElevation->SetInput((vtkDataSet*)this->sphere->GetOutput());
	
	this->sphereElevation->SetLowPoint(0,0,-1);
	
	this->sphereElevation->SetHighPoint(0,0,1);
	
	this->sphereElevation->SetScalarRange(-1,1);
	
	// Link the mapper
	
	this->sphereMapper->SetInput(this->sphereElevation->GetPolyDataOutput());
	
	this->sphereMapper->SetColorModeToMapScalars();
	
	this->sphereMapper->SetScalarRange(-1,1);
	
	// Link the actor
	
	this->sphereActor->SetMapper(this->sphereMapper);
	
	// Add it to the renderer
	
	this->ren->AddActor(this->sphereActor);
	
	
	
	// Construct the cone
	
	this->cone->SetResolution(8);
	
	
	// Construct the glyphs on the spherical surface
	
	this->glyph->SetInput((vtkDataSet*)this->sphere->GetOutput());
	
	this->glyph->SetSource(this->cone->GetOutput());
	
	this->glyph->SetVectorModeToUseNormal();
	
	this->glyph->SetScaleModeToScaleByVector();
	
	this->glyph->SetScaleFactor(0.1);
	
	// Link the mapper to the glyph
	
	this->spikeMapper->SetInput(this->glyph->GetOutput());
	
	// Link the actor
	
	this->spikeActor->SetMapper(this->spikeMapper);
	
	// Add it to the renderer
	
	this->ren->AddActor(this->spikeActor);
	

/*
	CFirstView yes;
	if (yes.flagyes==1) 
	{
	
	
	// Add in the cube axis actor
	
	this->sphereAxis->SetInput(this->sphereElevation->GetOutput());
	
	
	this->sphereAxis->SetCamera(this->ren->GetActiveCamera());
	
	// Add it to the renderer
	
	this->ren->AddActor(this->sphereAxis);
	}
*/

	
	// Add in the cube axis actor
	
//	this->sphereAxis->SetInput(this->sphereElevation->GetOutput());
		
//	this->sphereAxis->SetCamera(this->ren->GetActiveCamera());

  vtkTextProperty *tprop=vtkTextProperty::New();
    tprop-> SetColor(0, 0, 1);
    tprop-> ShadowOn();

    this->sphereAxis-> SetInput (sphereElevation-> GetOutput());
    this->sphereAxis-> SetCamera (ren-> GetActiveCamera());
//    this->sphereAxis-> SetLabelFormat "%6.4g"
    this->sphereAxis-> SetFlyModeToOuterEdges();
    this->sphereAxis-> SetFontFactor(0.8);
    this->sphereAxis-> SetAxisTitleTextProperty(tprop);
    this->sphereAxis-> SetAxisLabelTextProperty(tprop);
	this->sphereAxis->SetFontFactor (8);

	this->sphereAxis->VisibilityOff();

    this->ren->AddActor(this->sphereAxis);

	//绘制窗口,将绘制者加入绘制窗口
	renWin->AddRenderer(ren);
	//交互器,告诉绘制者将要在绘制窗口中进行显示的演员
	iren->SetRenderWindow(renWin);

	ren->ResetCamera(); 
    this->renWin->Render();

}



void CSplitterView::Pipeline1()
{	
	// Add it to the renderer
	
	this->ren->AddActor(this->sphereAxis);

//	Invalidate(0);
	
}


void CSplitterView::ShowMessage()
{
	AfxMessageBox(_T("Get")) ;
}
