


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

vtkInteractorStyleTrackballCamera *style;
vtkImplicitBoolean *theCream;
vtkRenderWindowInteractor *iren;
vtkRenderWindow *renWin;
int kind=0;

void keypress(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
	char key=iren->GetKeyCode();		  

	switch (key)
    {
      case 'k':
		  kind=kind+1;
		  if (kind>3)
			  kind=0;
		  switch (kind)
			{
			  case 0:theCream->SetOperationTypeToUnion (); 
				break;
			  case 1:theCream->SetOperationTypeToIntersection (); 
				break;
			  case 2:theCream->SetOperationTypeToDifference (); 
				break;
			  case 3:theCream->SetOperationTypeToUnionOfMagnitudes ();
				break;
			}  

		  //theCream-> SetOperationType(kind);
		  printf(" The Operation Type Is (%d)   ",kind);
		  printf(theCream->GetOperationTypeAsString ());
		  printf("\n");
		  break;
	}

	renWin->Render();
}

void main()
{
  vtkRenderer *ren1 = vtkRenderer::New();
  renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);
  style=vtkInteractorStyleTrackballCamera::New();
    iren-> SetInteractorStyle(style);

  vtkSphere *iceCream=vtkSphere::New();
    iceCream-> SetCenter( 1, 0, 0);
    iceCream-> SetRadius( 1);
  vtkSphere *bite=vtkSphere::New();
    bite-> SetCenter( 0, 0, 0);
    bite-> SetRadius( 1);

  theCream=vtkImplicitBoolean::New();
    theCream-> SetOperationType(0);
    theCream-> AddFunction( iceCream);
    theCream-> AddFunction( bite);

  vtkSampleFunction *theCreamSample=vtkSampleFunction::New();
    theCreamSample-> SetImplicitFunction (theCream);
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


  vtkCallbackCommand * cmd1 = vtkCallbackCommand::New();
	cmd1->SetCallback(keypress);
  style-> AddObserver (vtkCommand::KeyPressEvent,cmd1);

  ren1-> AddActor (creamActor);
  ren1-> SetBackground (1, 1, 1);
  renWin-> SetSize (600,600);

  ren1-> ResetCamera();
//  ren1-> GetActiveCamera()->Zoom( 1.4);

  renWin->Render();
  iren->Start();
}
