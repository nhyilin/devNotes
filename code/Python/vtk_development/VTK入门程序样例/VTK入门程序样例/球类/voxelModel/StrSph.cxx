#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"
#include "vtkContourFilter.h"
#include "vtkTransformFilter.h"
#include "vtkElevationFilter.h"
#include "vtkLookupTable.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkStripper.h"
#include "vtkVoxelModeller.h"
#include "vtkPolyDataNormals.h"

void main( int argc, char *argv[] )
{
   vtkRenderer *renderer = vtkRenderer::New();
   vtkRenderWindow *renWin = vtkRenderWindow::New();
     renWin->AddRenderer(renderer);
   vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
     iren->SetRenderWindow(renWin);

   vtkSphereSource *sphere = vtkSphereSource::New();
     sphere->SetThetaResolution(12); 
	 sphere->SetPhiResolution(12);

   vtkPolyDataMapper *sphereMapper=vtkPolyDataMapper::New();
     sphereMapper-> SetInputConnection (sphere-> GetOutputPort());

   vtkActor *sphereActor=vtkActor::New();
     sphereActor-> SetMapper(sphereMapper);

   vtkVoxelModeller *voxelModel=vtkVoxelModeller::New();
	 voxelModel-> SetInputConnection (sphere-> GetOutputPort());
	 voxelModel-> SetSampleDimensions (21, 21, 21);
	 voxelModel-> SetModelBounds (-1.5, 1.5, -1.5, 1.5, -1.5, 1.5);

   vtkContourFilter *voxelSurface=vtkContourFilter::New();
     voxelSurface-> SetInputConnection (voxelModel-> GetOutputPort());
     voxelSurface-> SetValue (0, .999);

   vtkPolyDataMapper *voxelMapper=vtkPolyDataMapper::New();
     voxelMapper-> SetInputConnection (voxelSurface-> GetOutputPort());

  vtkActor *actor = vtkActor::New();
    actor->SetMapper(voxelMapper);


  renderer->AddActor(actor);
  renderer->AddActor(sphereActor);
  renderer->SetBackground(1,1,1);
//  renderer->GetActiveCamera()->Elevation(60.0);
//  renderer->GetActiveCamera()->Azimuth(30.0);
//  renderer->GetActiveCamera()->Zoom(1.3);

  renWin->SetSize(300,300);

  renWin->Render();
  // interact with data
  iren->Start();
  renWin->Render();

  // Clean up
  renderer->Delete();
  renWin->Delete();
  iren->Delete();
  sphere->Delete();
}
