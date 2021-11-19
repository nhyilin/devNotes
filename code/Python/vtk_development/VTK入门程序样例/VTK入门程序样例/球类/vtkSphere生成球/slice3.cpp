


#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphere.h"
#include "vtkImplicitBoolean.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkProperty.h"
#include "vtkPolyData.h"
#include "vtkSampleFunction.h"
#include "vtkContourFilter.h"
#include "vtkPolyDataNormals.h"
#include "vtkPolyDataMapper.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkCommand.h"
#include "vtkCallbackCommand.h"
#include "vtkHexahedron.h"

void main()
{
  vtkRenderWindowInteractor *iren;
  vtkRenderWindow *renWin;

  vtkRenderer *ren1 = vtkRenderer::New();
  renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkSphere *iceCream=vtkSphere::New();
    iceCream-> SetCenter( 1, 0, 0);
    iceCream-> SetRadius( 1);

  vtkHexahedron *hexahedron=vtkHexahedron::New();
//    iceCream-> SetCenter( 1, 0, 0);
//    iceCream-> SetRadius( 1);

  vtkSampleFunction *theCreamSample=vtkSampleFunction::New();
    theCreamSample-> SetImplicitFunction ((vtkImplicitFunction *)iceCream);
    theCreamSample-> SetModelBounds(  -1.25 ,2.25, -1.25 ,1.25, -1.25, 1.25 );
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
    creamActor-> GetProperty()-> SetColor (0.6,0.6,1);


  ren1-> AddActor (creamActor);
  ren1-> SetBackground (1, 1, 1);
  renWin-> SetSize (600,600);

  ren1-> ResetCamera();
//  ren1-> GetActiveCamera()->Zoom( 1.4);

  renWin->Render();
  iren->Start();
}
