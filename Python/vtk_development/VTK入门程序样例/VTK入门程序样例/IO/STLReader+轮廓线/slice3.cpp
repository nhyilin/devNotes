


#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSTLReader.h"
#include "vtkPolyDataMapper.h"
#include "vtkLODActor.h"
#include "vtkCamera.h"
#include "vtkExtractEdges.h"
#include "vtkTubeFilter.h"
#include "vtkProperty.h"

void main()
{
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkSTLReader *sr=vtkSTLReader::New();
    sr-> SetFileName("42400-IDGH.stl");

  vtkPolyDataMapper *stlMapper=vtkPolyDataMapper::New();
    stlMapper-> SetInputConnection (sr-> GetOutputPort());

  vtkLODActor *stlActor=vtkLODActor::New();
    stlActor-> SetMapper (stlMapper);

vtkExtractEdges *extract=vtkExtractEdges::New();
    extract-> SetInputConnection (sr-> GetOutputPort());
vtkTubeFilter *tubes=vtkTubeFilter::New();
    tubes-> SetInputConnection (extract-> GetOutputPort());
    tubes ->SetRadius (0.02);
    tubes-> SetNumberOfSides (6);
vtkPolyDataMapper *mapEdges=vtkPolyDataMapper::New();
    mapEdges-> SetInputConnection (tubes-> GetOutputPort());
vtkActor *edgeActor=vtkActor::New();
    edgeActor-> SetMapper (mapEdges);
    edgeActor-> GetProperty()-> SetColor (0.1,0.05,0.4);
    edgeActor-> GetProperty()-> SetSpecularColor( 1, 1, 1);
    edgeActor-> GetProperty()-> SetSpecular (0.3);
    edgeActor-> GetProperty()-> SetSpecularPower( 20);
    edgeActor-> GetProperty()-> SetAmbient (0.2);
    edgeActor-> GetProperty()-> SetDiffuse (0.8);

ren1-> AddActor (stlActor);
ren1-> AddActor (edgeActor);
ren1-> SetBackground (0.1, 0.2, 0.4);
renWin-> SetSize (500,500);

ren1-> ResetCamera();
ren1-> GetActiveCamera()->Zoom( 1.4);

  renWin->Render();
  iren->Start();
}
