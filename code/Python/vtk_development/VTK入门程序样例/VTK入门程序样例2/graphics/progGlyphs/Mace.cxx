#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPlaneSource.h"
#include "vtkElevationFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"

#include "vtkSuperquadricSource.h"
#include "vtkProgrammableGlyphFilter.h"
#include "vtkCamera.h"
#include "vtkProperty.h"
#include "vtkTriangularTexture.h"
#include "vtkTriangularTCoords.h"
#include "vtkTexture.h"
#include "vtkCubeSource.h"
#include "math.h"

//#include "SaveImage.h"
int res; 

int main( int argc, char *argv() )
{
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

res=6;
vtkPlaneSource *plane=vtkPlaneSource::New();
    plane-> SetResolution (res ,res);

vtkElevationFilter *colors=vtkElevationFilter::New();
    colors-> SetInputConnection (plane ->GetOutputPort());
    colors-> SetLowPoint (-0.25, -0.25, -0.25);
    colors-> SetHighPoint (0.25, 0.25 ,0.25);

vtkPolyDataMapper *planeMapper=vtkPolyDataMapper::New();
    planeMapper-> SetInput(colors->GetPolyDataOutput());

vtkActor *planeActor=vtkActor::New();
    planeActor-> SetMapper (planeMapper);
    planeActor-> GetProperty()-> SetRepresentationToWireframe();

// procedure for generating glyphs
/*
proc Glyph {} {
   global res
   set ptId [glypher GetPointId]
   set pd [glypher GetPointData]
   set xyz [glypher GetPoint]
   set x [lindex $xyz 0] 
   set y [lindex $xyz 1] 
   set length [[glypher GetInput 0] GetLength]
   set scale [expr $length / (2.0*$res)]

   squad SetScale $scale $scale $scale
   eval squad SetCenter $xyz
   squad SetPhiRoundness [expr abs($x)*5.0]
   squad SetThetaRoundness [expr abs($y)*5.0]
}
*/

// create simple poly data so we can apply glyph
vtkSuperquadricSource *squad=vtkSuperquadricSource::New();

vtkProgrammableGlyphFilter *glypher=vtkProgrammableGlyphFilter::New();
    glypher-> SetInputConnection (colors ->GetOutputPort());
//	glypher-> SetSource (squad-> GetOutput());

	double x,y;
	x=glypher->GetPoint()[0];
	y=glypher->GetPoint()[1];
	double length=5.0;
	double scale=length/(2.0*res);

	squad-> SetScale(scale,scale,scale);
	squad-> SetCenter(glypher->GetPoint());
    squad-> SetPhiRoundness (abs(x)*5.0);
    squad-> SetThetaRoundness ( abs(y)*5.0);
    squad-> Update();

    glypher-> SetSource(squad ->GetOutput());	
	glypher->Update();

vtkPolyDataMapper *glyphMapper=vtkPolyDataMapper::New();
    glyphMapper ->SetInputConnection(glypher ->GetOutputPort());

vtkActor *glyphActor=vtkActor::New();
    glyphActor-> SetMapper( glyphMapper);

  renderer->AddActor(planeActor);
  renderer->AddActor(glyphActor);
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

  return 0;
}
