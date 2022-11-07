#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"
#include "vtkCylinderSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkConeSource.h"
#include "vtkGlyph3D.h"
#include "vtkCamera.h"
#include "vtkProperty.h"
#include "vtkTriangularTexture.h"
#include "vtkTriangularTCoords.h"
#include "vtkTexture.h"
#include "vtkCubeSource.h"

//#include "SaveImage.h"

int main( int argc, char *argv() )
{
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkSphereSource *sphere = vtkSphereSource::New();
    sphere->SetThetaResolution(8); 
	sphere->SetPhiResolution(8);

  vtkPolyDataMapper *sphereMapper = vtkPolyDataMapper::New();
    sphereMapper->SetInput(sphere->GetOutput());

  vtkActor *sphereActor = vtkActor::New();
    sphereActor->SetMapper(sphereMapper);

/////////////////
vtkTriangularTexture *aTriangularTexture=vtkTriangularTexture::New();
    aTriangularTexture-> SetTexturePattern( 2);
    aTriangularTexture-> SetScaleFactor( 1.3);
    aTriangularTexture-> SetXSize( 64);
    aTriangularTexture-> SetYSize( 64);
  
vtkSphereSource *aSphere=vtkSphereSource::New();
    aSphere-> SetThetaResolution( 20);
    aSphere-> SetPhiResolution( 20);

vtkTriangularTCoords *tCoords=vtkTriangularTCoords::New();
    tCoords-> SetInputConnection( aSphere-> GetOutputPort());

vtkPolyDataMapper *triangleMapper=vtkPolyDataMapper::New();
    triangleMapper-> SetInputConnection( tCoords-> GetOutputPort());

vtkTexture *aTexture=vtkTexture::New();
    aTexture-> SetInputConnection (aTriangularTexture-> GetOutputPort());
    aTexture-> InterpolateOn();

vtkActor *texturedActor=vtkActor::New();
    texturedActor-> SetMapper (triangleMapper);
    texturedActor-> SetTexture (aTexture);
    texturedActor-> GetProperty() ->BackfaceCullingOn();
    texturedActor-> GetProperty() ->SetDiffuseColor (0.9,0.8,0.0);
    texturedActor-> GetProperty() ->SetSpecular (.4);
    texturedActor-> GetProperty() ->SetSpecularPower( 40);

vtkCubeSource *aCube=vtkCubeSource::New();
    aCube-> SetXLength (.5);
    aCube-> SetYLength (.5);

vtkPolyDataMapper *aCubeMapper=vtkPolyDataMapper::New();
    aCubeMapper-> SetInputConnection (aCube ->GetOutputPort());

vtkActor *cubeActor=vtkActor::New();
    cubeActor-> SetMapper( aCubeMapper);
    cubeActor-> GetProperty() ->SetDiffuseColor (0.5,0.4,0.1);

  renderer->AddActor(texturedActor);
  renderer->AddActor(cubeActor);
  renderer->SetBackground(1,1,1);
  renWin->SetSize(600,600);

  // interact with data
  renWin->Render();

 // SAVEIMAGE( renWin );

  iren->Start();

  // Clean up
  renderer->Delete();
  renWin->Delete();
  iren->Delete();
  sphere->Delete();
  sphereMapper->Delete();
  sphereActor->Delete();

  return 0;
}
