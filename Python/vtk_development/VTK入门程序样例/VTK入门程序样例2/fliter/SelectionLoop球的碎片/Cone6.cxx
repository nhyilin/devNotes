
#include "vtkDataSetMapper.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkPolyData.h"
#include "vtkConnectivityFilter.h"
#include "vtkContourFilter.h"
#include "vtkPoints.h"
#include "stdio.h"
#include <time.h>
#include <vtkExtractGeometry.h>
#include <vtkProperty.h>
#include <vtkCellArray.h>
#include <vtkImplicitSelectionLoop.h>
#include <vtkSphereSource.h>

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

vtkSphereSource *sphere=vtkSphereSource::New();
    sphere-> SetRadius(1);
    sphere-> SetPhiResolution (100);
    sphere ->SetThetaResolution (100);

vtkPoints *selectionPoints=vtkPoints::New();
    selectionPoints-> InsertPoint( 0 ,0.07325 ,0.8417, 0.5612);
    selectionPoints-> InsertPoint(  1, 0.07244, 0.6568, 0.7450);
    selectionPoints ->InsertPoint(  2, 0.1727, 0.4597, 0.8850);
    selectionPoints-> InsertPoint(  3, 0.3265, 0.6054, 0.7309);
    selectionPoints-> InsertPoint(  4, 0.5722, 0.5848, 0.5927);
    selectionPoints-> InsertPoint(  5, 0.4305, 0.8138, 0.4189);

vtkImplicitSelectionLoop *loop=vtkImplicitSelectionLoop::New();
    loop-> SetLoop (selectionPoints);

vtkExtractGeometry *extract=vtkExtractGeometry::New();
    extract-> SetInputConnection (sphere->GetOutputPort());
    extract-> SetImplicitFunction (loop);

vtkConnectivityFilter *connect=vtkConnectivityFilter::New();
    connect-> SetInputConnection (extract-> GetOutputPort());
    connect-> SetExtractionModeToClosestPointRegion();
    connect-> SetClosestPoint(selectionPoints->GetPoint (0));

vtkDataSetMapper *clipMapper=vtkDataSetMapper::New();
    clipMapper-> SetInputConnection(connect-> GetOutputPort());

vtkProperty *backProp=vtkProperty::New();
    backProp->SetDiffuseColor(1,0.7,0);

vtkActor *clipActor=vtkActor::New();
    clipActor-> SetMapper(clipMapper);
    clipActor-> GetProperty()->SetColor(0.0,0.3,0.7);
    clipActor-> SetBackfaceProperty(backProp);

//////////////
ren->AddActor(clipActor);

iren->Initialize();
renWindow->Render();

iren->Start();
}


