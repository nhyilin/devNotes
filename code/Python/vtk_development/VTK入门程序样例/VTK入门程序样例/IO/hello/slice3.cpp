


#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyDataReader.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkImplicitModeller.h"
#include "vtkContourFilter.h"
#include "vtkProperty.h"

void main()
{
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

vtkPolyDataReader *reader=vtkPolyDataReader::New();
    reader-> SetFileName( "hello.vtk");
vtkPolyDataMapper *lineMapper=vtkPolyDataMapper::New();
    lineMapper-> SetInputConnection (reader->GetOutputPort());
vtkActor *lineActor=vtkActor::New();
    lineActor-> SetMapper (lineMapper);
    lineActor-> GetProperty() ->SetColor (1,0,0);

vtkImplicitModeller *imp=vtkImplicitModeller::New();
    imp-> SetInputConnection (reader-> GetOutputPort());
    imp-> SetSampleDimensions (110 ,40 ,20);
    imp-> SetMaximumDistance (0.25);
    imp-> SetModelBounds (-1.0 ,10.0, -1.0, 3.0 ,-1.0 ,1.0);
vtkContourFilter *contour=vtkContourFilter::New();
    contour-> SetInputConnection (imp-> GetOutputPort());
    contour-> SetValue (0 ,0.25);
vtkPolyDataMapper *impMapper=vtkPolyDataMapper::New();
    impMapper-> SetInputConnection (contour-> GetOutputPort());
    impMapper-> ScalarVisibilityOff();
vtkActor *impActor  =vtkActor::New();
    impActor-> SetMapper (impMapper);
    impActor-> GetProperty()->SetColor (0.1,0.1,0.4);
    impActor-> GetProperty() ->SetOpacity (0.5);

  ren1-> AddActor (impActor);
  ren1-> AddActor (lineActor);
  ren1-> SetBackground (1, 1, 1);
  renWin-> SetSize (600,500);

  ren1-> ResetCamera();
  ren1-> GetActiveCamera()->Zoom( 1.4);

  renWin->Render();
  iren->Start();
}
