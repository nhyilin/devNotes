


#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSampleFunction.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkPoints.h"
#include "vtkImplicitSum.h"
#include "vtkProperty.h"
#include "vtkPolyData.h"
#include "vtkPerlinNoise.h"
#include "vtkPlane.h"
#include "vtkContourFilter.h"
#include "vtkPolyDataNormals.h"
#include "vtkPolyDataMapper.h"

void main()
{
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

vtkPlane *plane=vtkPlane::New();

vtkPerlinNoise *p1=vtkPerlinNoise::New();
p1-> SetFrequency (1 ,1 ,0);

vtkPerlinNoise *p2=vtkPerlinNoise::New();
p2-> SetFrequency (3 ,5 ,0);
p2-> SetPhase (0.5 ,0.5 ,0);

vtkPerlinNoise *p3=vtkPerlinNoise::New();
p3-> SetFrequency (16 ,16 ,0);

vtkImplicitSum *sum=vtkImplicitSum::New();
sum-> SetNormalizeByWeight (1);
sum-> AddFunction (plane);
sum-> AddFunction (p1 ,0.2);
sum-> AddFunction (p2 ,0.1);
sum-> AddFunction( p3 ,0.02);

vtkSampleFunction *sample=vtkSampleFunction::New();
    sample-> SetImplicitFunction (sum);
    sample-> SetSampleDimensions (65 ,65 ,20);
    sample-> SetModelBounds (-1 ,1 ,-1 ,1 ,-0.5 ,0.5);
    sample-> ComputeNormalsOff();

vtkContourFilter *surface=vtkContourFilter::New();
    surface-> SetInputConnection (sample-> GetOutputPort());
    surface-> SetValue (0 ,0.0);

vtkPolyDataNormals *smooth=vtkPolyDataNormals::New();
    smooth-> SetInputConnection (surface-> GetOutputPort());
    smooth-> SetFeatureAngle (90);

vtkPolyDataMapper *mapper=vtkPolyDataMapper::New();
    mapper-> SetInputConnection (smooth-> GetOutputPort());
    mapper-> ScalarVisibilityOff();

  vtkActor *triangulation=vtkActor::New();
	triangulation-> SetMapper (mapper);
	triangulation-> GetProperty()-> SetColor (0.4 ,0.2 ,0.1);

  ren1-> AddActor (triangulation);
  ren1-> SetBackground (1, 1, 1);
  renWin-> SetSize (600,500);

  ren1-> ResetCamera();
  ren1-> GetActiveCamera()->Zoom( 1.4);

  renWin->Render();
  iren->Start();
}
