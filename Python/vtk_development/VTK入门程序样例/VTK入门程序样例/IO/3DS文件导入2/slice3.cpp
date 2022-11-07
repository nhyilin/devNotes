
#include "vtkPolyDataMapper.h"
#include "vtkCamera.h"
#include "vtkPolyData.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkPolyData.h"
#include "vtkButterflySubdivisionFilter.h"
#include "vtkLoopSubdivisionFilter.h"
#include "vtkProperty.h"

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtk3DSImporter.h"
#include "vtkPolyDataMapper.h"
#include "vtkLODActor.h"
#include "vtkCamera.h"
#include "vtkTriangleFilter.h"

void main()
{
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

	vtk3DSImporter *importer=vtk3DSImporter::New();
	  importer-> ComputeNormalsOn();
	  importer-> SetFileName ("workman.3ds");
	  importer-> Read();

	vtkTriangleFilter *tri = vtkTriangleFilter::New();
	  tri->SetInput(importer-> GetRenderer()->GetActors()->GetLastActor()->GetMapper()->GetInput());

  vtkLoopSubdivisionFilter *subdivide=vtkLoopSubdivisionFilter::New();
	subdivide-> SetInput(tri->GetOutput());
	subdivide-> SetNumberOfSubdivisions(2);

  vtkDataSetMapper *mapper = vtkDataSetMapper::New();
    mapper->SetInput(subdivide->GetOutput());
	mapper->ScalarVisibilityOff();

  vtkActor *actor = vtkActor::New();
    actor->SetMapper(mapper);
	actor-> GetProperty() ->SetDiffuseColor( 1, 0.49, 0.20);

  ren1->AddActor(actor);
  ren1->SetBackground(1,1,1);
  renWin->SetSize(500,500);

  renWin->Render();
  iren->Start();
}
