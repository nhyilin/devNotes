


#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphere.h"
#include "vtkImplicitBoolean.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkPoints.h"
#include "vtkCone.h"
#include "vtkProperty.h"
#include "vtkPolyData.h"
#include "vtkSampleFunction.h"
#include "vtkPlane.h"
#include "vtkContourFilter.h"
#include "vtkPolyDataNormals.h"
#include "vtkPolyDataMapper.h"

void main()
{
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

vtkCone *cone=vtkCone::New();
    cone-> SetAngle( 20);
vtkPlane *vertPlane=vtkPlane::New();
    vertPlane-> SetOrigin( .1, 0, 0);
    vertPlane-> SetNormal( -1, 0, 0);
vtkPlane *basePlane=vtkPlane::New();
    basePlane-> SetOrigin( 1.2, 0, 0);
    basePlane-> SetNormal( 1, 0, 0);
vtkSphere *iceCream=vtkSphere::New();
    iceCream-> SetCenter( 1.333, 0, 0);
    iceCream-> SetRadius( 0.5);
vtkSphere *bite=vtkSphere::New();
    bite-> SetCenter( 1.5, 0, 0.5);
    bite-> SetRadius( 0.25);

vtkImplicitBoolean *theCone=vtkImplicitBoolean::New();
    theCone-> SetOperationTypeToIntersection();
    theCone-> AddFunction( cone);
    theCone-> AddFunction( vertPlane);
    theCone-> AddFunction( basePlane);

vtkImplicitBoolean *theCream=vtkImplicitBoolean::New();
    theCream-> SetOperationTypeToDifference();
    theCream-> AddFunction( iceCream);
    theCream-> AddFunction( bite);

vtkSampleFunction *theConeSample=vtkSampleFunction::New();
    theConeSample-> SetImplicitFunction( theCone);
    theConeSample-> SetModelBounds( -1, 1.5, -1.25, 1.25, -1.25, 1.25 );
    theConeSample-> SetSampleDimensions( 60 ,60 ,60);
    theConeSample-> ComputeNormalsOff();
vtkContourFilter *theConeSurface=vtkContourFilter::New();
    theConeSurface-> SetInputConnection( theConeSample-> GetOutputPort());
    theConeSurface-> SetValue( 0 ,0.0);
vtkPolyDataMapper *coneMapper=vtkPolyDataMapper::New();
    coneMapper-> SetInputConnection (theConeSurface-> GetOutputPort());
    coneMapper-> ScalarVisibilityOff();
vtkActor *coneActor=vtkActor::New();
    coneActor-> SetMapper (coneMapper);
    coneActor-> GetProperty()->SetColor (0.4,0.2,0.1);

vtkSampleFunction *theCreamSample=vtkSampleFunction::New();
    theCreamSample-> SetImplicitFunction (theCream);
    theCreamSample-> SetModelBounds(  0 ,2.5, -1.25 ,1.25, -1.25, 1.25 );
    theCreamSample-> SetSampleDimensions( 60 ,60 ,60);
    theCreamSample-> ComputeNormalsOff();
vtkContourFilter *theCreamSurface=vtkContourFilter::New();
    theCreamSurface-> SetInputConnection (theCreamSample-> GetOutputPort());
    theCreamSurface-> SetValue( 0 ,0.0);
vtkPolyDataMapper *creamMapper=vtkPolyDataMapper::New();
    creamMapper-> SetInputConnection (theCreamSurface-> GetOutputPort());
    creamMapper-> ScalarVisibilityOff();
vtkActor *creamActor=vtkActor::New();
    creamActor-> SetMapper (creamMapper);
    creamActor-> GetProperty()-> SetColor (0.1,0.4,0.1);

  ren1-> AddActor (coneActor);
  ren1-> AddActor (creamActor);
  ren1-> SetBackground (1, 1, 1);
  renWin-> SetSize (600,500);

  ren1-> ResetCamera();
  ren1-> GetActiveCamera()->Zoom( 1.4);

  renWin->Render();
  iren->Start();
}
