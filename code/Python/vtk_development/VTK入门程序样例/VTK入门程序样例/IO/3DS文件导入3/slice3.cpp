
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
	  importer-> SetFileName ("aa.3ds");
	  importer-> Read();
/*
  vtkDataSetMapper *mapper = vtkDataSetMapper::New();
    mapper->SetInput(importer-> GetRenderer()->GetActors()->GetLastActor()->GetMapper()->GetInput());
	mapper->ScalarVisibilityOff();

  vtkActor *actor = vtkActor::New();
    actor->SetMapper(mapper);
	actor-> GetProperty() ->SetDiffuseColor( 1, 0.49, 0.20);
*/

	int numOfActors = importer-> GetRenderer()->GetActors()->GetNumberOfItems();  

	for(int i = 0 ; i < numOfActors ; i++)
	{
		vtkActor *actor = (vtkActor *)importer-> GetRenderer()->GetActors()->GetItemAsObject(i);		
		ren1->AddActor(actor);
	}




  ren1->SetBackground(0.6,0.8,1);
  renWin->SetSize(500,500);

  renWin->Render();
  iren->Start();
}
