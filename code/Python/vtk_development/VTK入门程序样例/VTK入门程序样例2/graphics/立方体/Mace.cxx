#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCubeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkLoopSubdivisionFilter.h"
#include "vtkButterflySubdivisionFilter.h"
#include "vtkProperty.h"
#include "vtkTriangleFilter.h"

void main( )
{
  vtkRenderer *aren = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(aren);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkCubeSource *cube = vtkCubeSource::New();
/*
  vtkTriangleFilter *tstrip= vtkTriangleFilter::New();
    tstrip-> SetInput( cube->GetOutput());

//  vtkButterflySubdivisionFilter *subdivide=vtkButterflySubdivisionFilter::New();
  vtkLoopSubdivisionFilter *subdivide=vtkLoopSubdivisionFilter::New();
	subdivide-> SetInput( tstrip->GetOutput());
	subdivide-> SetNumberOfSubdivisions( 4);
*/



  vtkPolyDataMapper *cubeMapper = vtkPolyDataMapper::New();
    cubeMapper->SetInput(subdivide->GetOutput());

  vtkActor *cubeActor = vtkActor::New();
    cubeActor->SetMapper(cubeMapper);
    cubeActor->GetProperty()->SetColor(0.9804,0.5020,0.4471);

  aren->AddActor(cubeActor);
  aren->SetBackground (0,0,0);


  renWin->SetSize(600,600);

  renWin->Render();

  iren->Start();

  aren->Delete();
  renWin->Delete();
  iren->Delete();

}
