


#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkMath.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkPoints.h"
#include "vtkContourFilter.h"
#include "vtkProperty.h"
#include "vtkPolyData.h"
#include "vtkDelaunay3D.h"
#include "vtkShrinkFilter.h"

void main()
{
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

	int i;
	vtkMath *math=vtkMath::New();
	vtkPoints *points=vtkPoints::New();
	for (i=0;i<25;i++) 
	{
		points->InsertPoint (i ,math->Random(0, 1), math->Random(0, 1),math->Random(0, 1));
	}

	vtkPolyData *profile=vtkPolyData::New();
		profile->SetPoints(points);

	vtkDelaunay3D *del=vtkDelaunay3D::New();
		del ->SetInput (profile);
		del ->SetTolerance (0.01);
		del ->SetAlpha (0.2);
		del ->BoundingTriangulationOff();
    
	vtkShrinkFilter *shrink=vtkShrinkFilter::New();
		shrink-> SetInputConnection (del->GetOutputPort());
		shrink-> SetShrinkFactor (0.9);

	vtkDataSetMapper *map=vtkDataSetMapper::New();
		map-> SetInputConnection (shrink->GetOutputPort());

	vtkActor *triangulation=vtkActor::New();
		triangulation-> SetMapper (map);
		triangulation-> GetProperty()-> SetColor (1 ,0 ,0);

  ren1-> AddActor (triangulation);
  ren1-> SetBackground (1, 1, 1);
  renWin-> SetSize (600,500);

  ren1-> ResetCamera();
  ren1-> GetActiveCamera()->Zoom( 1.4);

  renWin->Render();
  iren->Start();
}
