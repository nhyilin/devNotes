

#include "vtkPolyDataMapper.h"
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkPoints.h"
#include "vtkWin32RenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkAppendPolyData.h"
#include "vtkPlaneSource.h"
#include "vtkIdentityTransform.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkMatrix4x4.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkPerspectiveTransform.h"
#include "vtkTransform.h"

void main()
{
	vtkWin32OpenGLRenderWindow *renWin=vtkWin32OpenGLRenderWindow::New();
	vtkWin32RenderWindowInteractor *iren=vtkWin32RenderWindowInteractor::New();
	  iren->SetRenderWindow(renWin);	

vtkPlaneSource *p1=vtkPlaneSource::New();
p1 ->SetOrigin ( 0.5 , 0.508 ,-0.5);
p1 ->SetPoint1 (-0.5 , 0.508 ,-0.5);
p1 ->SetPoint2 ( 0.5 , 0.508 , 0.5);
p1 ->SetXResolution( 5);
p1 ->SetYResolution( 5);

vtkPlaneSource *p2=vtkPlaneSource::New();
p2 ->SetOrigin (-0.508  ,0.5 ,-0.5);
p2 ->SetPoint1 (-0.508 ,-0.5 ,-0.5);
p2 ->SetPoint2 (-0.508  ,0.5 , 0.5);
p2 ->SetXResolution( 5);
p2 ->SetYResolution( 5);

vtkPlaneSource *p3=vtkPlaneSource::New();
p3 ->SetOrigin (-0.5 ,-0.508 ,-0.5);
p3 ->SetPoint1 ( 0.5 ,-0.508 ,-0.5);
p3 ->SetPoint2 (-0.5 ,-0.508 , 0.5);
p3 ->SetXResolution( 5);
p3 ->SetYResolution( 5);

vtkPlaneSource *p4=vtkPlaneSource::New();
p4 ->SetOrigin ( 0.508 ,-0.5 ,-0.5);
p4 ->SetPoint1 ( 0.508 , 0.5 ,-0.5);
p4 ->SetPoint2 ( 0.508, -0.5 , 0.5);
p4 ->SetXResolution( 5);
p4 ->SetYResolution( 5);

vtkPlaneSource *p5=vtkPlaneSource::New();
p5 ->SetOrigin ( 0.5,  0.5 ,-0.508);
p5 ->SetPoint1 ( 0.5 ,-0.5 ,-0.508);
p5 ->SetPoint2 (-0.5 , 0.5 ,-0.508);
p5 ->SetXResolution( 5);
p5 ->SetYResolution( 5);

vtkPlaneSource *p6=vtkPlaneSource::New();
p6-> SetOrigin ( 0.5  ,0.5 , 0.508);
p6-> SetPoint1 (-0.5 , 0.5  ,0.508);
p6-> SetPoint2 ( 0.5, -0.5 , 0.508);
p6-> SetXResolution (5);
p6-> SetYResolution (5);

// append together
vtkAppendPolyData *ap=vtkAppendPolyData::New();
ap ->AddInput( p1 ->GetOutput());
ap ->AddInput( p2 ->GetOutput());
ap ->AddInput( p3 ->GetOutput());
ap ->AddInput( p4 ->GetOutput());
ap-> AddInput( p5 ->GetOutput());
ap ->AddInput( p6 ->GetOutput());

//--------------------------
// identity transform
vtkIdentityTransform *t1=vtkIdentityTransform::New();

vtkTransformPolyDataFilter *f11=vtkTransformPolyDataFilter::New();
f11 ->SetInputConnection( ap ->GetOutputPort());
f11 ->SetTransform( t1);

vtkDataSetMapper *m11=vtkDataSetMapper::New();
m11 ->SetInputConnection (f11 ->GetOutputPort());

vtkActor *a11=vtkActor::New();
a11 ->SetMapper (m11);
a11-> GetProperty() ->SetColor (1, 0 ,0);
a11-> GetProperty() ->SetRepresentationToWireframe();

vtkRenderer *ren11=vtkRenderer::New();
ren11 ->SetViewport( 0.0 ,0.5 ,0.25 ,1.0);
ren11 ->ResetCamera( -0.5, 0.5 ,-0.5, 0.5, -1, 1);
ren11 ->AddActor( a11);
renWin ->AddRenderer( ren11);

// inverse identity transform
vtkTransformPolyDataFilter *f12=vtkTransformPolyDataFilter::New();
f12-> SetInputConnection (ap ->GetOutputPort());
f12-> SetTransform (t1 ->GetInverse());

vtkDataSetMapper *m12=vtkDataSetMapper::New();
m12-> SetInputConnection (f12-> GetOutputPort());

vtkActor *a12=vtkActor::New();
a12-> SetMapper (m12);
a12-> GetProperty() ->SetColor( 0.9 ,0.9,0);
a12-> GetProperty() ->SetRepresentationToWireframe();

vtkRenderer *ren12=vtkRenderer::New();
ren12-> SetViewport( 0.0 ,0.0 ,0.25, 0.5);
ren12-> ResetCamera( -0.5 ,0.5 ,-0.5 ,0.5 ,-1 ,1);
ren12-> AddActor( a12);
renWin-> AddRenderer (ren12);


//--------------------------
// linear transform
vtkTransform *t2=vtkTransform::New();
t2-> RotateX (50);
t2-> RotateY (30);
t2-> Translate (0.2 ,0.1, -0.15);

vtkTransformPolyDataFilter *f21=vtkTransformPolyDataFilter::New();
f21-> SetInputConnection (ap ->GetOutputPort());
f21-> SetTransform (t2);

vtkDataSetMapper *m21=vtkDataSetMapper::New();
m21-> SetInputConnection (f21 ->GetOutputPort());

vtkActor *a21=vtkActor::New();
a21-> SetMapper (m21);
a21-> GetProperty() ->SetColor (1 ,0 ,0);
a21-> GetProperty() ->SetRepresentationToWireframe();

vtkRenderer *ren21=vtkRenderer::New();
ren21-> SetViewport (0.25, 0.5,0.50, 1.0);
ren21-> ResetCamera (-0.5, 0.5 ,-0.5, 0.5, -1, 1);
ren21-> AddActor (a21);
renWin-> AddRenderer( ren21);

// inverse linear transform
vtkTransformPolyDataFilter *f22=vtkTransformPolyDataFilter::New();
f22 ->SetInputConnection (ap ->GetOutputPort());
f22 ->SetTransform( t2 ->GetInverse());

vtkDataSetMapper *m22=vtkDataSetMapper::New();
m22 ->SetInputConnection( f22 ->GetOutputPort());

vtkActor *a22=vtkActor::New();
a22-> SetMapper (m22);
a22-> GetProperty() ->SetColor( 0.9 ,0.9, 0);
a22-> GetProperty() ->SetRepresentationToWireframe();

vtkRenderer *ren22=vtkRenderer::New();
ren22-> SetViewport( 0.25, 0.0 ,0.50, 0.5);
ren22-> ResetCamera( -0.5, 0.5 ,-0.5, 0.5 ,-1, 1);
ren22-> AddActor (a22);
renWin-> AddRenderer (ren22);


//--------------------------
// perspective transform
vtkMatrix4x4 *matrix=vtkMatrix4x4::New();
matrix-> SetElement( 3, 0 ,0.1);
matrix-> SetElement( 3 ,1 ,0.2);
matrix-> SetElement( 3, 2 ,0.5);

vtkPerspectiveTransform *t3=vtkPerspectiveTransform::New();
t3 ->SetMatrix(matrix);

vtkTransformPolyDataFilter *f31=vtkTransformPolyDataFilter::New();
f31 ->SetInputConnection (ap ->GetOutputPort());
f31 ->SetTransform (t3);

vtkDataSetMapper *m31=vtkDataSetMapper::New();
m31-> SetInputConnection (f31 ->GetOutputPort());

vtkActor *a31=vtkActor::New();
a31-> SetMapper (m31);
a31-> GetProperty() ->SetColor (1, 0 ,0);
a31-> GetProperty() ->SetRepresentationToWireframe();

vtkRenderer *ren31=vtkRenderer::New();
ren31-> SetViewport( 0.50 ,0.5 ,0.75 ,1.0);
ren31-> ResetCamera( -0.5, 0.5, -0.5, 0.5, -1 ,1);
ren31-> AddActor( a31);
renWin-> AddRenderer( ren31);

// inverse linear transform
vtkTransformPolyDataFilter *f32=vtkTransformPolyDataFilter::New();
f32-> SetInputConnection (ap ->GetOutputPort());
f32-> SetTransform (t3-> GetInverse());

vtkDataSetMapper *m32=vtkDataSetMapper::New();
m32-> SetInputConnection (f32-> GetOutputPort());

vtkActor *a32=vtkActor::New();
a32-> SetMapper( m32);
a32-> GetProperty() ->SetColor( 0.9 ,0.9,0);
a32-> GetProperty() ->SetRepresentationToWireframe();

vtkRenderer *ren32=vtkRenderer::New();
ren32-> SetViewport (0.5 ,0.0 ,0.75, 0.5);
ren32-> ResetCamera (-0.5, 0.5 ,-0.5, 0.5, -1 ,1);
ren32-> AddActor (a32);
renWin-> AddRenderer (ren32);


//--------------------------
// perspective transform concatenation
vtkPerspectiveTransform *t4=vtkPerspectiveTransform::New();
t4-> Concatenate (t1);
t4-> Concatenate (t2);
t4-> Concatenate (t3);

vtkTransformPolyDataFilter *f41=vtkTransformPolyDataFilter::New();
f41-> SetInputConnection( ap-> GetOutputPort());
f41-> SetTransform( t4);

vtkDataSetMapper *m41=vtkDataSetMapper::New();
m41-> SetInputConnection (f41-> GetOutputPort());

vtkActor *a41=vtkActor::New();
a41-> SetMapper (m41);
a41-> GetProperty() ->SetColor (1, 0, 0);
a41-> GetProperty() ->SetRepresentationToWireframe();

vtkRenderer *ren41=vtkRenderer::New();
ren41-> SetViewport (0.75, 0.5,1.0 ,1.0);
ren41-> ResetCamera (-0.5, 0.5 ,-0.5, 0.5, -1, 1);
ren41-> AddActor (a41);
renWin-> AddRenderer (ren41);

// inverse linear transform
vtkTransformPolyDataFilter *f42=vtkTransformPolyDataFilter::New();
f42-> SetInputConnection( ap ->GetOutputPort());
f42-> SetTransform( t4 ->GetInverse());

vtkDataSetMapper *m42=vtkDataSetMapper::New();
m42 ->SetInputConnection (f42-> GetOutputPort());

vtkActor *a42=vtkActor::New();
a42 ->SetMapper( m42);
a42-> GetProperty() ->SetColor (0.9, 0.9, 0);
a42 ->GetProperty() ->SetRepresentationToWireframe();

vtkRenderer *ren42=vtkRenderer::New();
ren42-> SetViewport( 0.75, 0.0 ,1.0 ,0.5);
ren42-> ResetCamera( -0.5, 0.5, -0.5, 0.5,-1 ,1);
ren42-> AddActor (a42);
renWin-> AddRenderer( ren42);



	renWin->SetSize(800,400);
	renWin->Render();
	iren->Start();

	iren->Delete();
	renWin->Delete();
}






