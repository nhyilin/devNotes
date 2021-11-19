
#include "vtkPerlinNoise.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkPolyData.h"
#include "vtkBoxWidget.h"
#include "vtkContourFilter.h"
#include "vtkPoints.h"
#include "stdio.h"
#include <time.h>
#include <vtkGlyph3D.h>
#include <vtkProperty.h>
#include <vtkCellArray.h>
#include <vtkTubeFilter.h>
#include <vtkSampleFunction.h>

void main()
{

  srand(time(NULL)) ;

//	rand()/RAND_MAX;//	0 - RAND_MAX
  vtkRenderer *ren = vtkRenderer::New();
  vtkRenderWindow *renWindow = vtkRenderWindow::New();
    renWindow->AddRenderer(ren);
  renWindow->SetSize( 600, 600 );

    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWindow);

vtkPerlinNoise *perlin=vtkPerlinNoise::New();
perlin-> SetFrequency (2 ,6.25, 5.5);
perlin-> SetPhase (0 ,0, 0);

vtkSampleFunction *sample=vtkSampleFunction::New();
    sample-> SetImplicitFunction (perlin);
    sample-> SetSampleDimensions( 65,65 ,20);
    sample-> ComputeNormalsOff();
vtkContourFilter *surface=vtkContourFilter::New();
    surface-> SetInputConnection(sample-> GetOutputPort());
    surface-> SetValue (0, 0.0);

vtkPolyDataMapper *mapper=vtkPolyDataMapper::New();
    mapper-> SetInputConnection(surface-> GetOutputPort());
    mapper-> ScalarVisibilityOff();

vtkActor *actor=vtkActor::New();
    actor-> SetMapper (mapper);
    actor-> GetProperty()-> SetColor( 0.2 ,0.4 ,0.6);

//////////////
ren->AddActor(actor);

iren->Initialize();
renWindow->Render();

iren->Start();
}


