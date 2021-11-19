
#include "vtkCamera.h"
#include "vtkPiecewiseFunction.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkVolume.h"
#include "vtkVolumeProperty.h"
#include "vtkVolumeRayCastCompositeFunction.h"
#include "vtkExtractGrid.h"
#include "vtkVolumeRayCastMapper.h"
#include "vtkColorTransferFunction.h"
#include "vtkActor.h" 
#include "vtkOutlineFilter.h" 
#include "vtkPolyDataMapper.h" 
#include "vtkPlane.h"
#include "vtkCutter.h"
#include "vtkLookupTable.h"
#include "vtkProperty.h"
#include "vtkPolyDataMapper.h" 
#include "vtkContourFilter.h" 
#include "vtkPolyDataNormals.h"
#include "vtkPolyDataMapper.h"
#include "vtkStructuredGridOutlineFilter.h"
#include "vtkTubeFilter.h"
#include "vtkPLOT3DReader.h"

void main() 
{ 
	vtkRenderWindow *renWin = vtkRenderWindow::New();
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	  iren->SetRenderWindow(renWin);
	vtkRenderer *ren = vtkRenderer::New();
	  renWin->AddRenderer(ren);

  vtkPLOT3DReader *pl3d = vtkPLOT3DReader::New();
	pl3d->SetXYZFileName("combxyz.bin");
	pl3d->SetQFileName("combq.bin");
	pl3d-> SetScalarFunctionNumber (120); 
	pl3d-> SetVectorFunctionNumber (202);
	pl3d->Update(); //force a read to occur

	vtkExtractGrid *extract=vtkExtractGrid::New();
	  extract-> SetVOI (1, 55, -1000, 1000 ,-1000 ,1000);
	  extract-> SetInputConnection(pl3d->GetOutputPort());

	// The (implicit) plane is used to do the cutting
	vtkPlane *plane=vtkPlane::New();
	  plane-> SetOrigin (0 ,4 ,2);
	  plane-> SetNormal (0 ,1 ,0);

	// The cutter is set up to process each contour value over all cells
	// (SetSortByToSortByCell). This results in an ordered output of polygons 
	// which is key to the compositing.
	vtkCutter *cutter=vtkCutter::New();
	  cutter-> SetInputConnection (extract-> GetOutputPort());
	  cutter-> SetCutFunction (plane);
	  cutter-> GenerateCutScalarsOff();
	  cutter-> SetSortByToSortByCell();

	vtkLookupTable *clut=vtkLookupTable::New();
	  clut-> SetHueRange( 0 ,.67);
	  clut-> Build();

	vtkPolyDataMapper *cutterMapper=vtkPolyDataMapper::New();
	  cutterMapper-> SetInputConnection (cutter->GetOutputPort());
	  cutterMapper-> SetScalarRange (0.18 ,0.7);
	  cutterMapper-> SetLookupTable (clut);

	vtkActor *cut=vtkActor::New();
	  cut-> SetMapper (cutterMapper);

	// Add in some surface geometry for interest.
	vtkContourFilter *iso=vtkContourFilter::New();
		iso-> SetInputConnection (pl3d-> GetOutputPort());
		iso-> SetValue (0,-100000);
		iso->Update();


	vtkPolyDataNormals *normals=vtkPolyDataNormals::New();
		normals-> SetInputConnection (iso-> GetOutputPort());
		normals-> SetFeatureAngle (45);

	vtkPolyDataMapper *isoMapper=vtkPolyDataMapper::New();
		isoMapper-> SetInputConnection (normals-> GetOutputPort());
		isoMapper-> ScalarVisibilityOff();

	vtkActor *isoActor=vtkActor::New();
		isoActor-> SetMapper (isoMapper);
		isoActor-> GetProperty()-> SetDiffuseColor (1,0.5,0);
		isoActor-> GetProperty()-> SetSpecularColor (1,1,0.9);
		isoActor-> GetProperty()-> SetDiffuse (.8);
		isoActor-> GetProperty()-> SetSpecular (.5);
		isoActor-> GetProperty()-> SetSpecularPower (30);

	vtkStructuredGridOutlineFilter *outline=vtkStructuredGridOutlineFilter::New();
		outline-> SetInputConnection (pl3d-> GetOutputPort());

	vtkTubeFilter *outlineTubes=vtkTubeFilter::New();
	  outlineTubes-> SetInputConnection (outline-> GetOutputPort());
	  outlineTubes-> SetRadius (.1);

	vtkPolyDataMapper *outlineMapper=vtkPolyDataMapper::New();
		outlineMapper-> SetInputConnection (outlineTubes-> GetOutputPort());

	vtkActor *outlineActor=vtkActor::New();
		outlineActor-> SetMapper(outlineMapper);
		outlineActor-> GetProperty()->SetColor(1,1,0);

	  ren-> AddActor (isoActor);
	  isoActor-> VisibilityOn();
	  ren-> AddActor (cut);
	  cut-> GetProperty()-> SetOpacity (0.1);
	  ren->AddActor(outlineActor);
	//  outlineActor-> GetProperty()->SetColor(1,1,0);

	  ren->SetBackground(1, 1, 1);
	  renWin->SetSize(600,600);

	ren-> GetActiveCamera()->SetClippingRange( 3.95297, 50);
	ren-> GetActiveCamera()->SetFocalPoint( 9.71821, 0.458166, 29.3999);
	ren-> GetActiveCamera()->SetPosition( 2.7439, -37.3196, 38.7167);
	ren-> GetActiveCamera()->ComputeViewPlaneNormal();
	ren-> GetActiveCamera()->SetViewUp( -0.16123, 0.264271, 0.950876);

	//  global cam1 opacity
	  plane-> SetNormal(ren-> GetActiveCamera()->GetViewPlaneNormal());
	  plane-> SetOrigin(ren-> GetActiveCamera()->GetFocalPoint());
	  cutter-> GenerateValues (20, -5, 5);
	  clut->SetAlphaRange(.5,.1);



  ren->ResetCamera();
  ren->GetActiveCamera()->Zoom(1.5);
  
  renWin->Render();


  iren->Start();

  // Clean up
  ren->Delete();
  iren->Delete();
  renWin->Delete();
  
  return;
}



