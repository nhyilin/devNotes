
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkCullerCollection.h"
#include "vtkPlaneSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkStripper.h"
#include "vtkCellArray.h"
#include "vtkTriangleFilter.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkClipPolyData.h"
#include "vtkCylinder.h"
#include "vtkProperty.h"

int main( int argc, char *argv[] )
{
  // create a rendering window and both renderers
  vtkRenderer *ren1 = vtkRenderer::New();
  ren1->GetCullers()->InitTraversal();
  //ren1->RemoveCuller(ren1->GetCullers()->GetNextItem());
  vtkRenderWindow *renWindow = vtkRenderWindow::New();
  renWindow->AddRenderer(ren1);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
      iren->SetRenderWindow(renWindow);

 vtkPoints *points=vtkPoints::New();
    points-> SetNumberOfPoints( 4);

    points-> InsertPoint (0, 574977491, 328641875, 0.000000);
    points-> InsertPoint (1, 580271124, 323671875, 0.000000);
    points-> InsertPoint (2, 604170252, 323921875, 0.000000);
    points-> InsertPoint (3, 598828062, 328911875, 0.000000);

/*
    points-> InsertPoint (0, 33753574.977491, 18753286.439951, 0.000000);
    points-> InsertPoint (1, 33753580.271124, 18753236.772283, 0.000000);
    points-> InsertPoint (2, 33753604.170252, 18753239.195716, 0.000000);
    points-> InsertPoint (3, 33753598.828062, 18753289.148470, 0.000000);
*//*
    points-> InsertPoint (0, 200.057, 200.028, 0.000000);
    points-> InsertPoint (1, 200.058, 200.023, 0.000000);
    points-> InsertPoint (2, 200.060, 200.023, 0.000000);
    points-> InsertPoint (3, 200.059, 200.028, 0.000000);
*/
vtkCellArray *cellArray=vtkCellArray::New();
    cellArray-> InsertNextCell (4);
    cellArray-> InsertCellPoint( 0);
    cellArray-> InsertCellPoint( 1);
    cellArray-> InsertCellPoint( 2);
    cellArray-> InsertCellPoint( 3);

vtkPolyData *polyData=vtkPolyData::New();
    polyData-> SetPoints (points);
    polyData-> SetPolys (cellArray);
    
    

// The mapper is responsible for pushing the geometry into the graphics
// library. It may also do color mapping, if scalars or other attributes
// are defined.

vtkPolyDataMapper *cylinderMapper=vtkPolyDataMapper::New();
    cylinderMapper-> SetInput (polyData);

// The actor is a grouping mechanism: besides the geometry (mapper), it
// also has a property, transformation matrix, and/or texture map.
// Here we set its color and rotate it -22.5 degrees.
vtkActor *cylinderActor=vtkActor::New();
    cylinderActor-> SetMapper (cylinderMapper);
    cylinderActor-> GetProperty()-> SetColor (1,0.5,0.2);
    cylinderActor-> RotateX  (30.0);
    cylinderActor-> RotateY (-45.0);
    cylinderActor-> GetProperty()-> SetOpacity( 1.0);
    cylinderActor-> GetProperty()-> SetAmbient( 0.5);
    cylinderActor-> GetProperty()-> SetDiffuse( 0.6);
    cylinderActor-> GetProperty()-> SetSpecular( 0.6    );
    cylinderActor-> GetProperty()-> SetSpecularPower( 10.0);
    cylinderActor-> GetProperty()-> SetColor( 1.0, 0.2, 0.4);

  ren1->AddActor(cylinderActor);

  renWindow->SetSize(500,500);
  ren1->SetBackground(0.1, 0.2, 0.4);

  renWindow->Render();
  ren1->GetActiveCamera()->Zoom (1.5);
  renWindow->Render();

  iren->Start();

  ren1->Delete();
  renWindow->Delete();
  return 1;
}
