
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkPolyDataNormals.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkTextProperty.h"
#include "vtkTexture.h"
#include "vtkFloatArray.h"
#include "vtkContourFilter.h"
#include "vtkCastToConcrete.h"
#include "vtkProgrammableAttributeDataFilter.h"
#include "vtkLODActor.h"
#include "vtkRendererSource.h"

#include "vtkPolyDataNormals.h"
#include "vtkProperty.h"
#include "vtkCastToConcrete.h"
#include "vtkElevationFilter.h"
#include "vtkWarpScalar.h"
#include "vtkImageDataGeometryFilter.h"
#include "vtkImageShrink3D.h"
#include "vtkBandedPolyDataContourFilter.h"
#include "vtkDEMReader.h"
#include "vtkLookupTable.h"

int main()
{
	vtkRenderer *ren1= vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
      renWin->AddRenderer( ren1 );
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
      iren->SetRenderWindow(renWin);

	int Scale=5;
	vtkLookupTable *lutWater=vtkLookupTable::New();
	  lutWater-> SetNumberOfColors (10);
	  lutWater-> SetHueRange( 0.58, 0.58);
	  lutWater-> SetSaturationRange (0.5, 0.1);
	  lutWater-> SetValueRange (0.5, 1.0);
	  lutWater-> Build();
	vtkLookupTable *lutLand=vtkLookupTable::New();
	  lutLand-> SetNumberOfColors( 10);
	  lutLand-> SetHueRange( 0.1, 0.1);
	  lutLand-> SetSaturationRange( 0.4, 0.1);
	  lutLand-> SetValueRange( 0.55, 0.9);
	  lutLand-> Build();


	vtkDEMReader *demModel=vtkDEMReader::New();
	  demModel-> SetFileName( "SainteHelens.dem");
	  demModel-> Update();

	int shrinkFactor=4;
	vtkImageShrink3D *shrink=vtkImageShrink3D::New();
	  shrink-> SetShrinkFactors (shrinkFactor,shrinkFactor, 1);
	  shrink-> SetInputConnection (demModel->GetOutputPort());
	  shrink-> AveragingOn();

	vtkImageDataGeometryFilter *geom=vtkImageDataGeometryFilter::New();
	  geom-> SetInputConnection (shrink-> GetOutputPort());

	vtkWarpScalar *warp=vtkWarpScalar::New();
	  warp-> SetInputConnection (geom-> GetOutputPort());
	  warp-> SetNormal (0, 0, 1);
	  warp-> UseNormalOn();
	  warp-> SetScaleFactor (Scale);

	vtkBandedPolyDataContourFilter *bcf=vtkBandedPolyDataContourFilter::New();
	  bcf-> SetInput (warp-> GetPolyDataOutput());
	  bcf-> GenerateValues(15 ,demModel->GetOutput()-> GetScalarRange());
	  bcf-> SetScalarModeToIndex();
	  bcf-> GenerateContourEdgesOn();

	vtkPolyDataNormals *normals=vtkPolyDataNormals::New();
	  normals-> SetInputConnection (bcf-> GetOutputPort());
	  normals-> SetFeatureAngle (60);
	  normals-> ConsistencyOff();
	  normals-> SplittingOff();

	vtkPolyDataMapper *demMapper=vtkPolyDataMapper::New();
	  demMapper-> SetInputConnection (normals-> GetOutputPort());
	  demMapper-> SetScalarRange(0, 10);
	  demMapper ->SetLookupTable (lutLand);
	  demMapper-> SetScalarModeToUseCellData();

	vtkLODActor *demActor=vtkLODActor::New();
	  demActor-> SetMapper (demMapper);

	vtkPolyDataMapper *edgeMapper=vtkPolyDataMapper::New();
	  edgeMapper-> SetInput (bcf-> GetContourEdgesOutput());
	  edgeMapper-> SetResolveCoincidentTopologyToPolygonOffset ();
	vtkActor *edgeActor=vtkActor::New();
	  edgeActor-> SetMapper (edgeMapper);
	  edgeActor-> GetProperty()->SetColor (0, 0, 0);

	vtkBandedPolyDataContourFilter *bcf2=vtkBandedPolyDataContourFilter::New();
	  bcf2-> SetInput (warp ->GetPolyDataOutput());
	  bcf2-> ClippingOn();
	  bcf2-> GenerateValues (10, 1000, 2000);
	  bcf2-> SetScalarModeToValue();

	vtkPolyDataNormals *normals2=vtkPolyDataNormals::New();
	  normals2-> SetInputConnection (bcf2-> GetOutputPort());
	  normals2-> SetFeatureAngle( 60);
	  normals2-> ConsistencyOff();
	  normals2-> SplittingOff();

	vtkLookupTable *lut=vtkLookupTable::New();
	lut-> SetNumberOfColors (10);
	vtkPolyDataMapper *demMapper2=vtkPolyDataMapper::New();
	  demMapper2->SetInputConnection (normals2 ->GetOutputPort());
	  demMapper2-> SetScalarRange (demModel-> GetOutput() ->GetScalarRange());
	  demMapper2-> SetLookupTable (lut);
	  demMapper2-> SetScalarModeToUseCellData();

	vtkLODActor *demActor2=vtkLODActor::New();
	  demActor2-> SetMapper (demMapper2);
	  demActor2-> AddPosition (0 ,15000 ,0);


		ren1->AddActor(demActor);
		ren1->AddActor(demActor2);
		ren1->AddActor(edgeActor);
		ren1->SetBackground( 0.4, 0.4, 0.4 );

	renWin-> SetSize(730, 400);

	vtkCamera *cam=vtkCamera::New();
	  cam ->SetPosition (-17438.8 ,2410.62 ,25470.8);
	  cam ->SetFocalPoint (3985.35 ,11930.6 ,5922.14);
	  cam ->SetViewUp (0 ,0 ,1);
	ren1 ->SetActiveCamera (cam);
	ren1 ->ResetCamera();
	cam-> Zoom (2);

	iren-> SetDesiredUpdateRate(1);
	renWin-> Render();

	iren->Initialize();
    iren->Start(); 

	ren1->Delete();
    renWin->Delete();
	iren->Delete();
    
	return 0;
}


	
	
