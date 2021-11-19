


#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtk3DSImporter.h"
#include "vtkPolyDataMapper.h"
#include "vtkLODActor.h"
#include "vtkCamera.h"

void main()
{
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

	vtk3DSImporter *importer=vtk3DSImporter::New();
//	  importer-> ComputeNormalsOn();
	  importer-> SetFileName ("aa.3DS");
	  importer-> Read();

	importer-> GetRenderer()->SetBackground( 1, 1, 1);
	renWin-> SetSize (500,500);
	renWin->AddRenderer(importer-> GetRenderer());

	importer-> GetRenderer()-> ResetCamera();
//	importer-> GetRenderer()-> GetActiveCamera()->Zoom( 1);

  renWin->Render();
  iren->Start();
}
