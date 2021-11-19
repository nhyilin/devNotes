


#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkVRMLImporter.h"
#include "vtkPolyDataMapper.h"
#include "vtkLODActor.h"
#include "vtkCamera.h"
#include "vtkPolyData.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkPolyData.h"
#include "vtkButterflySubdivisionFilter.h"
#include "vtkLoopSubdivisionFilter.h"
#include "vtkProperty.h"

void main()
{
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

	vtkVRMLImporter *importer=vtkVRMLImporter::New();
//	  importer-> SetRenderWindow(renWin);
	  importer-> SetFileName ("NEFERTITI.WRL");
	  importer-> Read();
	  importer->Update();

/*
  vtkButterflySubdivisionFilter *subdivide=vtkButterflySubdivisionFilter::New();
    subdivide->SetInput(importer-> GetRenderer()->GetActors()->GetLastActor()->GetMapper()->GetInput());
    subdivide->SetNumberOfSubdivisions(3);
*/
  vtkLoopSubdivisionFilter *subdivide=vtkLoopSubdivisionFilter::New();
	subdivide-> SetInput(importer-> GetRenderer()->GetActors()->GetLastActor()->GetMapper()->GetInput());
	subdivide-> SetNumberOfSubdivisions(3);

  vtkDataSetMapper *mapper = vtkDataSetMapper::New();
    mapper->SetInput(subdivide->GetOutput());
	mapper->ScalarVisibilityOff();

  vtkActor *actor = vtkActor::New();
    actor->SetMapper(mapper);
	actor-> GetProperty() ->SetDiffuseColor( 1, 0.49, 0.20);

  ren1->AddActor(actor);
  ren1->SetBackground(1,1,1);
  renWin->SetSize(300,300);
	
	
/*
	importer-> GetRenderer()->SetBackground( 0.1, 0.2, 0.4);
	renWin-> SetSize (500,500);
	renWin->AddRenderer(importer-> GetRenderer());

	importer-> GetRenderer()-> ResetCamera();
	importer-> GetRenderer()-> GetActiveCamera()->Zoom( 1.4);
*/
  renWin->Render();
  iren->Start();
}
