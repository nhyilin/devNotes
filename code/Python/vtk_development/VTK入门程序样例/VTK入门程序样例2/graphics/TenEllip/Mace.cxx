
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkPointLoad.h"
#include "vtkImageDataGeometryFilter.h"
#include "vtkPlanes.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkSphereSource.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkTensorGlyph.h"
#include "vtkPolyDataNormals.h"

#include "vtkLogLookupTable.h"
#include "vtkOutlineFilter.h"
#include "vtkConeSource.h"
#include "vtkPolyDataNormals.h"

void main()
{
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

// Create tensor ellipsoids
//
// generate tensors
vtkPointLoad *ptLoad=vtkPointLoad::New();
    ptLoad ->SetLoadValue( 100.0);
    ptLoad ->SetSampleDimensions (6 ,6 ,6);
    ptLoad ->ComputeEffectiveStressOn();
    ptLoad ->SetModelBounds (-10 ,10 ,-10 ,10 ,-10 ,10);

// extract plane of data
vtkImageDataGeometryFilter *plane=vtkImageDataGeometryFilter::New();
    plane ->SetInputConnection (ptLoad ->GetOutputPort());
    plane ->SetExtent( 2, 2 ,0, 99 ,0 ,99);

// Generate ellipsoids
vtkSphereSource *sphere=vtkSphereSource::New();
    sphere-> SetThetaResolution (8);
    sphere ->SetPhiResolution( 8);

vtkTensorGlyph *ellipsoids=vtkTensorGlyph::New();
    ellipsoids-> SetInputConnection (ptLoad ->GetOutputPort());
    ellipsoids-> SetSource (sphere ->GetOutput());
    ellipsoids-> SetScaleFactor (10);
    ellipsoids-> ClampScalingOn();
  
vtkPolyDataNormals *ellipNormals=vtkPolyDataNormals::New();
  ellipNormals ->SetInputConnection (ellipsoids-> GetOutputPort());

// Map contour
vtkLogLookupTable *lut=vtkLogLookupTable::New();
    lut ->SetHueRange (0.6667, 0.0);
vtkPolyDataMapper *ellipMapper=vtkPolyDataMapper::New();
    ellipMapper ->SetInputConnection (ellipNormals-> GetOutputPort());
    ellipMapper ->SetLookupTable( lut);
    plane ->Update();//force update for scalar range
    ellipMapper ->SetScalarRange (plane ->GetOutput() ->GetScalarRange());

vtkActor *ellipActor=vtkActor::New();
    ellipActor ->SetMapper( ellipMapper);
//
// Create outline around data
//
vtkOutlineFilter *outline=vtkOutlineFilter::New();
    outline ->SetInputConnection (ptLoad ->GetOutputPort());

vtkPolyDataMapper *outlineMapper=vtkPolyDataMapper::New();
    outlineMapper ->SetInputConnection (outline ->GetOutputPort());

vtkActor *outlineActor=vtkActor::New();
    outlineActor-> SetMapper( outlineMapper);
    outlineActor-> GetProperty()->SetColor( 0, 0 ,0);

//
// Create cone indicating application of load
//
vtkConeSource *coneSrc=vtkConeSource::New();
    coneSrc->  SetRadius( 0.5);
    coneSrc->  SetHeight( 2);
vtkPolyDataMapper *coneMap=vtkPolyDataMapper::New();
    coneMap-> SetInputConnection (coneSrc ->GetOutputPort());
vtkActor *coneActor=vtkActor::New();
    coneActor-> SetMapper (coneMap);    
    coneActor-> SetPosition (0 ,0 ,11);
    coneActor-> RotateY (90);
    coneActor-> GetProperty() ->SetColor( 1 ,0 ,0);

vtkCamera *camera=vtkCamera::New();
    camera-> SetFocalPoint( 0.113766 ,-1.13665 ,-1.01919);
    camera-> SetPosition (-29.4886 ,-63.1488 ,26.5807);
    camera-> SetViewAngle( 24.4617);
    camera-> SetViewUp (0.17138 ,0.331163 ,0.927879);
    camera-> SetClippingRange (1 ,100);

ren1-> AddActor (ellipActor);
ren1-> AddActor( outlineActor);
ren1-> AddActor( coneActor);
ren1-> SetBackground( 1.0 ,1.0 ,1.0);
ren1-> SetActiveCamera (camera);

renWin-> SetSize (400, 400);

  renWin->Render();

  iren->Start();
  // Clean up
  ren1->Delete();
  renWin->Delete();
  iren->Delete();
  sphere->Delete();

}
