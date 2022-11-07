#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyData.h"
#include "vtkPoints.h"
#include "vtkCellArray.h"
#include "vtkFloatArray.h"
#include "vtkProperty.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkPointData.h"
#include "vtkMath.h"
#include "vtkShepardMethod.h"
#include "vtkDataSetMapper.h"

void main( int argc, char *argv[] )
{ 
    vtkRenderer *renderer = vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
      renWin->AddRenderer(renderer);

    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
      iren->SetRenderWindow(renWin);

	int i;
	vtkMath *math=vtkMath::New();
	vtkPoints *points=vtkPoints::New();
	for (i=0;i<50;i++)
	{
		points->InsertPoint (i, math-> Random (0, 1), 
							 math-> Random (0, 1), math ->Random (0, 1));
	}

	vtkFloatArray *scalars=vtkFloatArray::New();
	for (i=0;i<50;i++)
	{
		scalars-> InsertValue (i ,math-> Random(0, 1));
	}

	vtkPolyData *profile=vtkPolyData::New();
		profile-> SetPoints (points);
		profile-> GetPointData() ->SetScalars (scalars);

	vtkShepardMethod *shepard=vtkShepardMethod::New();
		shepard-> SetInput (profile);
		shepard-> SetModelBounds( 0, 1 ,0, 1 ,.1 ,.5);
		shepard-> SetNullValue( 1);
		shepard-> SetSampleDimensions( 20, 20, 20);
		shepard-> Update();
    
	vtkDataSetMapper *map=vtkDataSetMapper::New();
		map-> SetInputConnection( shepard-> GetOutputPort());

	vtkActor *block=vtkActor::New();
		block-> SetMapper (map);
		block-> GetProperty()-> SetColor (1, 0, 0);


    vtkCamera *camera = vtkCamera::New();
      camera->SetPosition(1,1,1);
      camera->SetFocalPoint(0,0,0);
	  camera->SetClippingRange(0.0, 0.1);
	  camera->SetRoll(10);

    renderer->AddActor(block);
      renderer->SetActiveCamera(camera);
      renderer->ResetCamera();
      renderer->SetBackground(1,1,1);
  
    renWin->SetSize(300,300);

    renWin->Render();
    iren->Start();


	renderer->Delete();
	renWin->Delete();
	iren->Delete();
	camera->Delete();
}
