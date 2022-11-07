
#include "vtkConeSource.h"
#include "vtkDataSetMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkRotationFilter.h"

int main()
{

  vtkConeSource *cone = vtkConeSource::New();
	cone ->SetRadius (0.05 );
	cone ->SetHeight (0.25 );
	cone ->SetResolution (256 );
	cone ->SetCenter (0.15 ,0.0 ,0.15 );

  vtkRotationFilter *rotate=vtkRotationFilter::New();
	rotate-> SetInputConnection (cone-> GetOutputPort());
	rotate-> SetAxisToZ();
	rotate-> SetCenter (0.0 ,0.0 ,0.0);
	rotate-> SetAngle (45);
	rotate-> SetNumberOfCopies (7);
	rotate-> CopyInputOn();

  vtkDataSetMapper *coneMapper = vtkDataSetMapper::New();
    coneMapper->SetInputConnection( rotate->GetOutputPort() );

  vtkActor *coneActor = vtkActor::New();
    coneActor->SetMapper( coneMapper );

  vtkRenderer *ren1= vtkRenderer::New();
    ren1->AddActor( coneActor );
    ren1->SetBackground( 0.1, 0.2, 0.4 );

  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer( ren1 );
    renWin->SetSize( 512, 512 );

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  iren->Initialize();
  iren->Start();
  
  cone->Delete();
  coneMapper->Delete();
  coneActor->Delete();
  ren1->Delete();
  renWin->Delete();
  iren->Delete();

  return 0;
}


