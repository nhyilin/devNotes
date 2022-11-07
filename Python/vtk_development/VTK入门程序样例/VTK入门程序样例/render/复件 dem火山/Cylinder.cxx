
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
#include "vtkFloatArray.h"
#include "vtkContourFilter.h"
#include "vtkCastToConcrete.h"
#include "vtkProgrammableAttributeDataFilter.h"
#include "vtkMath.h"
#include "vtkRendererSource.h"

#include "vtkPolyDataNormals.h"
#include "vtkProperty.h"
#include "vtkCastToConcrete.h"
#include "vtkElevationFilter.h"
#include "vtkWarpScalar.h"
#include "vtkImageDataGeometryFilter.h"
#include "vtkImageShrink3D.h"
#include "vtkLODActor.h"
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
vtkLookupTable *lut=vtkLookupTable::New();
  lut-> SetHueRange( 0.6, 0);
  lut-> SetSaturationRange (1.0, 0);
  lut-> SetValueRange (0.5 ,1.0);

vtkDEMReader *demModel=vtkDEMReader::New();
  demModel-> SetFileName( "SainteHelens.dem");
  demModel-> Update();

double lo = Scale*demModel->GetElevationBounds()[0];
double hi = Scale*demModel->GetElevationBounds()[1];
/*
catch { demModel Print }
set lo [expr $Scale * [lindex [demModel GetElevationBounds] 0]]
set hi [expr $Scale * [lindex [demModel GetElevationBounds] 1]]
*/

vtkLODActor *demActor=vtkLODActor::New();

// create a pipeline for each lod mapper
//set lods "4 8 16"

  vtkImageShrink3D *shrink4=vtkImageShrink3D::New();
    shrink4-> SetShrinkFactors(4,4, 1);
    shrink4-> SetInputConnection (demModel->GetOutputPort());
    shrink4-> AveragingOn();

  vtkImageDataGeometryFilter *geom4=vtkImageDataGeometryFilter::New();
    geom4-> SetInputConnection (shrink4-> GetOutputPort());
    geom4-> ReleaseDataFlagOn();

  vtkWarpScalar *warp4=vtkWarpScalar::New();
    warp4-> SetInputConnection (geom4-> GetOutputPort());
    warp4-> SetNormal(0 ,0 ,1);
    warp4-> UseNormalOn();
    warp4-> SetScaleFactor (Scale);
    warp4-> ReleaseDataFlagOn();

  vtkElevationFilter *elevation4=vtkElevationFilter::New();
    elevation4-> SetInputConnection (warp4->GetOutputPort());
    elevation4-> SetLowPoint (0 ,0 ,lo);
    elevation4-> SetHighPoint (0 ,0 ,hi);
    elevation4-> SetScalarRange(lo ,hi);
    elevation4-> ReleaseDataFlagOn();

  vtkCastToConcrete *toPoly4=vtkCastToConcrete::New();
    toPoly4 ->SetInputConnection (elevation4-> GetOutputPort());
  
  vtkPolyDataNormals *normals4=vtkPolyDataNormals::New();
    normals4-> SetInput(toPoly4-> GetPolyDataOutput());
    normals4-> SetFeatureAngle( 60);
    normals4-> ConsistencyOff();
    normals4-> SplittingOff();
    normals4-> ReleaseDataFlagOn();

  vtkPolyDataMapper *demMapper4=vtkPolyDataMapper::New();
    demMapper4-> SetInputConnection (normals4-> GetOutputPort());
    demMapper4-> SetScalarRange (lo ,hi);
    demMapper4-> SetLookupTable (lut);
    demMapper4-> ImmediateModeRenderingOn();

demMapper4-> Update();

demActor-> AddLODMapper (demMapper4);

///////////////
  vtkImageShrink3D *shrink8=vtkImageShrink3D::New();
    shrink8-> SetShrinkFactors(8,8, 1);
    shrink8-> SetInputConnection (demModel->GetOutputPort());
    shrink8-> AveragingOn();

  vtkImageDataGeometryFilter *geom8=vtkImageDataGeometryFilter::New();
    geom8-> SetInputConnection (shrink8-> GetOutputPort());
    geom8-> ReleaseDataFlagOn();

  vtkWarpScalar *warp8=vtkWarpScalar::New();
    warp8-> SetInputConnection (geom8-> GetOutputPort());
    warp8-> SetNormal(0 ,0 ,1);
    warp8-> UseNormalOn();
    warp8-> SetScaleFactor (Scale);
    warp8-> ReleaseDataFlagOn();

  vtkElevationFilter *elevation8=vtkElevationFilter::New();
    elevation8-> SetInputConnection (warp8->GetOutputPort());
    elevation8-> SetLowPoint (0 ,0 ,lo);
    elevation8-> SetHighPoint (0 ,0 ,hi);
    elevation8-> SetScalarRange(lo ,hi);
    elevation8-> ReleaseDataFlagOn();

  vtkCastToConcrete *toPoly8=vtkCastToConcrete::New();
    toPoly8 ->SetInputConnection (elevation8-> GetOutputPort());
  
  vtkPolyDataNormals *normals8=vtkPolyDataNormals::New();
    normals8-> SetInput(toPoly8-> GetPolyDataOutput());
    normals8-> SetFeatureAngle( 60);
    normals8-> ConsistencyOff();
    normals8-> SplittingOff();
    normals8-> ReleaseDataFlagOn();

  vtkPolyDataMapper *demMapper8=vtkPolyDataMapper::New();
    demMapper8-> SetInputConnection (normals8-> GetOutputPort());
    demMapper8-> SetScalarRange (lo ,hi);
    demMapper8-> SetLookupTable (lut);
    demMapper8-> ImmediateModeRenderingOn();

demMapper8-> Update();

demActor-> AddLODMapper (demMapper8);
///////////////
  vtkImageShrink3D *shrink16=vtkImageShrink3D::New();
    shrink16-> SetShrinkFactors(16,16, 1);
    shrink16-> SetInputConnection (demModel->GetOutputPort());
    shrink16-> AveragingOn();

  vtkImageDataGeometryFilter *geom16=vtkImageDataGeometryFilter::New();
    geom16-> SetInputConnection (shrink16-> GetOutputPort());
    geom16-> ReleaseDataFlagOn();

  vtkWarpScalar *warp16=vtkWarpScalar::New();
    warp16-> SetInputConnection (geom16-> GetOutputPort());
    warp16-> SetNormal(0 ,0 ,1);
    warp16-> UseNormalOn();
    warp16-> SetScaleFactor (Scale);
    warp16-> ReleaseDataFlagOn();

  vtkElevationFilter *elevation16=vtkElevationFilter::New();
    elevation16-> SetInputConnection (warp16->GetOutputPort());
    elevation16-> SetLowPoint (0 ,0 ,lo);
    elevation16-> SetHighPoint (0 ,0 ,hi);
    elevation16-> SetScalarRange(lo ,hi);
    elevation16-> ReleaseDataFlagOn();

  vtkCastToConcrete *toPoly16=vtkCastToConcrete::New();
    toPoly16 ->SetInputConnection (elevation16-> GetOutputPort());
  
  vtkPolyDataNormals *normals16=vtkPolyDataNormals::New();
    normals16-> SetInput(toPoly16-> GetPolyDataOutput());
    normals16-> SetFeatureAngle( 60);
    normals16-> ConsistencyOff();
    normals16-> SplittingOff();
    normals16-> ReleaseDataFlagOn();

  vtkPolyDataMapper *demMapper16=vtkPolyDataMapper::New();
    demMapper16-> SetInputConnection (normals16-> GetOutputPort());
    demMapper16-> SetScalarRange (lo ,hi);
    demMapper16-> SetLookupTable (lut);
    demMapper16-> ImmediateModeRenderingOn();

demMapper16-> Update();

demActor-> AddLODMapper (demMapper16);
//////////////
	  ren1->AddActor(demActor);

	  ren1->SetBackground( 1, 1, 1 );
	  ren1-> ResetCamera();

    renWin->SetSize( 600, 600 );
	renWin-> Render();

	iren->Initialize();
    iren->Start(); 

	ren1->Delete();
    renWin->Delete();
	iren->Delete();
    
	return 0;
}


	
	
