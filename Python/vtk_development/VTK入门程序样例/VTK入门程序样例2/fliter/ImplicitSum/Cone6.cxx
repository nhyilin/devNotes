
#include "vtkCone.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphere.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkPolyData.h"
#include "vtkImplicitSum.h"
#include "vtkContourFilter.h"
#include "vtkPoints.h"
#include "stdio.h"
#include <vtkSampleFunction.h>
#include <vtkGlyph3D.h>
#include <vtkProperty.h>
#include <vtkCellArray.h>
#include <vtkTubeFilter.h>
#include <vtkSampleFunction.h>

void main()
{

//	rand()/RAND_MAX;//	0 - RAND_MAX
  vtkRenderer *ren = vtkRenderer::New();
  vtkRenderWindow *renWindow = vtkRenderWindow::New();
    renWindow->AddRenderer(ren);
  renWindow->SetSize( 600, 600 );

    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWindow);

vtkCone *geomObject1=vtkCone::New();

vtkSphere *geomObject2=vtkSphere::New();
    geomObject2-> SetRadius( 0.5);
    geomObject2-> SetCenter( 0.5, 0 ,0);

vtkImplicitSum *sum=vtkImplicitSum::New();
    sum-> SetNormalizeByWeight( 1);
    sum-> AddFunction (geomObject1 ,2);
    sum-> AddFunction (geomObject2 ,1);

vtkSampleFunction *sample=vtkSampleFunction::New();
    sample-> SetImplicitFunction( sum);
    sample-> SetSampleDimensions( 60, 60 ,60);
    sample-> ComputeNormalsOn();

vtkContourFilter *surface=vtkContourFilter::New();
    surface-> SetInputConnection (sample->GetOutputPort());
    surface-> SetValue (0 ,0.0);

vtkPolyDataMapper *mapper=vtkPolyDataMapper::New();
    mapper-> SetInputConnection(surface-> GetOutputPort());
    mapper-> ScalarVisibilityOff();

vtkActor *actor=vtkActor::New();
    actor-> SetMapper (mapper);
    actor-> GetProperty()-> SetColor( 0.2 ,0.4 ,0.6);
    actor-> GetProperty()-> SetSpecular ( 0.4);
    actor-> GetProperty()-> SetDiffuse  ( 0.7);
    actor-> GetProperty()-> SetSpecularPower ( 40);
//////////////
ren->AddActor(actor);

iren->Initialize();
renWindow->Render();

iren->Start();
}


