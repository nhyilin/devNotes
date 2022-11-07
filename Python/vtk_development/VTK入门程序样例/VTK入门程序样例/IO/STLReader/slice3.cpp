


#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSTLReader.h"
#include "vtkPolyDataMapper.h"
#include "vtkLODActor.h"
#include "vtkCamera.h"
#include "vtkSTLWriter.h"

void main()
{
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkSTLReader *sr=vtkSTLReader::New();
    sr-> SetFileName("42400-ewrewr.stl");

  vtkPolyDataMapper *stlMapper=vtkPolyDataMapper::New();
    stlMapper-> SetInputConnection (sr-> GetOutputPort());

  vtkLODActor *stlActor=vtkLODActor::New();
    stlActor-> SetMapper (stlMapper);
/*
	vtkSTLWriter *stlwriter	= vtkSTLWriter::New();
		stlwriter->SetInputConnection (sr-> GetOutputPort());
		stlwriter-> SetFileName("42400-ewrewr.stl");
		stlwriter->Write();
*/

ren1-> AddActor (stlActor);
ren1-> SetBackground (0.1, 0.2, 0.4);
renWin-> SetSize (500,500);

ren1-> ResetCamera();
ren1-> GetActiveCamera()->Zoom( 1.4);

  renWin->Render();
  iren->Start();
}
