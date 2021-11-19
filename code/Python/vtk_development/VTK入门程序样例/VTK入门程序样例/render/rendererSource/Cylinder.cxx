
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkPLOT3DReader.h"
#include "vtkPolyDataNormals.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkTextProperty.h"
#include "vtkTexture.h"
#include "vtkActor2D.h"
#include "vtkContourFilter.h"
#include "vtkCastToConcrete.h"
#include "vtkProbeFilter.h"
#include "vtkPlaneSource.h"
#include "vtkRendererSource.h"
#include "vtkStructuredGridOutlineFilter.h"
#include "vtkProperty.h"
#include "vtkStructuredGrid.h"
#include "vtkPointData.h"

int main()
{
	vtkRenderer *ren1= vtkRenderer::New();
	vtkRenderer *ren2= vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
      renWin->AddRenderer( ren1 );
	  renWin->AddRenderer( ren2 );
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
      iren->SetRenderWindow(renWin);

  vtkPLOT3DReader *pl3d2 = vtkPLOT3DReader::New();
  //vtkPLOT3DReader is a reader object that reads PLOT3D formatted files 
  //and generates structured grid(s) on output. PLOT3D is a computer graphics 
  //program designed to visualize the grids and solutions of computational fluid dynamics.
	pl3d2->SetXYZFileName("combxyz.bin");
	pl3d2->SetQFileName("combq.bin");
	pl3d2-> SetScalarFunctionNumber (153);
	pl3d2->Update(); //force a read to occur


  vtkPLOT3DReader *pl3d = vtkPLOT3DReader::New();
	pl3d->SetXYZFileName("combxyz.bin");
	pl3d->SetQFileName("combq.bin");
	pl3d-> SetScalarFunctionNumber (120); 
	pl3d-> SetVectorFunctionNumber (202);
	pl3d->Update(); //force a read to occur

	vtkContourFilter *iso= vtkContourFilter::New();
      iso->SetInputConnection(pl3d->GetOutputPort());
      iso->SetValue(0,-100000);
	  iso->Update();

vtkProbeFilter *probe2=vtkProbeFilter::New();
  probe2-> SetInputConnection (iso-> GetOutputPort());
  probe2-> SetSource ((vtkDataSet *)pl3d2-> GetOutput());

vtkCastToConcrete *cast2 =vtkCastToConcrete::New();
  cast2-> SetInputConnection (probe2-> GetOutputPort());

vtkPolyDataNormals *normals=vtkPolyDataNormals::New();
    normals-> SetInput (cast2-> GetPolyDataOutput());
    normals-> SetFeatureAngle (45);

vtkPolyDataMapper *isoMapper=vtkPolyDataMapper::New();
    isoMapper ->SetInputConnection (normals-> GetOutputPort());
    isoMapper ->ScalarVisibilityOn();
	isoMapper ->SetScalarRange(pl3d2 ->GetOutput()-> GetPointData()-> GetScalars()-> GetRange());


    vtkActor *isoActor = vtkActor::New();
      isoActor->SetMapper(isoMapper);
	  isoActor->GetProperty()->SetColor(1,0,1);
	  
  // create outline
  vtkStructuredGridOutlineFilter *outline = vtkStructuredGridOutlineFilter::New();
    outline->SetInput(pl3d->GetOutput());
  vtkPolyDataMapper *outlineMapper = vtkPolyDataMapper::New();
    outlineMapper->SetInput(outline->GetOutput());
  vtkActor *outlineActor = vtkActor::New();
    outlineActor->SetMapper(outlineMapper);
    outlineActor->GetProperty()->SetColor(0,0,0);

	  ren1->AddActor(outlineActor);
	  ren1->AddActor(isoActor);
	  ren1->SetBackground( 1, 1, 1 );
	  ren1-> ResetCamera();

ren1-> GetActiveCamera()->SetClippingRange (3.95297, 50);
ren1-> GetActiveCamera()->SetFocalPoint(9.71821, 0.458166, 29.3999);
ren1-> GetActiveCamera()->SetPosition( 2.7439, -37.3196, 38.7167);
ren1-> GetActiveCamera()->SetViewUp (-0.16123, 0.264271, 0.950876);

vtkPlaneSource *aPlane=vtkPlaneSource::New();
vtkPolyDataMapper *aPlaneMapper=vtkPolyDataMapper::New();
  aPlaneMapper-> SetInputConnection(aPlane-> GetOutputPort());
  aPlaneMapper-> ImmediateModeRenderingOn();

vtkActor *screen=vtkActor::New();
  screen-> SetMapper (aPlaneMapper);

ren2-> AddActor (screen);
ren2-> SetViewport (.5,0 ,1, 1);
ren2-> GetActiveCamera()-> Azimuth(30);
ren2-> GetActiveCamera()->Elevation(30);
ren2-> SetBackground (.8,.4 ,.3);
ren1-> ResetCameraClippingRange();
ren2-> ResetCamera();
ren2-> ResetCameraClippingRange();
	//调整视窗大小
    renWin->SetSize( 800, 400 );
	renWin-> Render();

vtkRendererSource *ren1Image=vtkRendererSource::New();
  ren1Image-> SetInput (ren1);
  ren1Image-> DepthValuesOn();
vtkTexture *aTexture=vtkTexture::New();
  aTexture-> SetInputConnection (ren1Image-> GetOutputPort());

screen-> SetTexture (aTexture);
//	ren1-> GetActiveCamera()-> Zoom (1.5);

	iren->Initialize();
    iren->Start(); 


	ren1->Delete();
    renWin->Delete();
	iren->Delete();
    
	return 0;
}


	
	
