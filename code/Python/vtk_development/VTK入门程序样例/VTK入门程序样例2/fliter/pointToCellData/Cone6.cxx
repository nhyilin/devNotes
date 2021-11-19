
#include "vtkPerlinNoise.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkPolyData.h"
#include "vtkPolyDataNormals.h"
#include "vtkContourFilter.h"
#include "vtkLookupTable.h"
#include "vtkProperty.h"
#include "vtkGeometryFilter.h"
#include <vtkDataSetMapper.h>
#include <vtkConnectivityFilter.h>
#include <vtkThreshold.h>
#include <vtkWarpVector.h>
#include <vtkPointDataToCellData.h>
#include <vtkUnstructuredGridReader.h>

void main()
{

	vtkRenderer *ren = vtkRenderer::New();
	vtkRenderWindow *renWindow = vtkRenderWindow::New();
	    renWindow->AddRenderer(ren);
	    renWindow->SetSize( 600, 600 );

	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	    iren->SetRenderWindow(renWindow);

	vtkUnstructuredGridReader *reader=vtkUnstructuredGridReader::New();
		reader-> SetFileName ("blow.vtk");
		reader-> SetScalarsName ("thickness9");
		reader-> SetVectorsName ("displacement9");

	vtkPointDataToCellData *p2c=vtkPointDataToCellData::New();
		p2c-> SetInputConnection (reader-> GetOutputPort());
		p2c ->PassPointDataOn();
	vtkWarpVector *warp=vtkWarpVector::New();
		warp-> SetInputConnection (p2c-> GetOutputPort());
	vtkThreshold *thresh=vtkThreshold::New();
		thresh-> SetInputConnection (warp-> GetOutputPort());
		thresh-> ThresholdBetween (0.25, 0.75);
		thresh-> SetInputArrayToProcess (1, 0, 0 ,0,"thickness9");

	vtkConnectivityFilter *connect=vtkConnectivityFilter::New();
		connect-> SetInputConnection (thresh-> GetOutputPort());
		connect-> SetExtractionModeToSpecifiedRegions();
		connect-> AddSpecifiedRegion (0);
		connect-> AddSpecifiedRegion (1);

	vtkDataSetMapper *moldMapper=vtkDataSetMapper::New();
		moldMapper-> SetInputConnection (reader-> GetOutputPort());
		moldMapper-> ScalarVisibilityOff();

	vtkActor *moldActor=vtkActor::New();
		moldActor-> SetMapper (moldMapper);
		moldActor-> GetProperty()-> SetColor (.2, .2, .2);
		moldActor-> GetProperty()-> SetRepresentationToWireframe();
	/////////////////

	vtkConnectivityFilter *connect2=vtkConnectivityFilter::New();
		connect2-> SetInputConnection (thresh->GetOutputPort());
	vtkGeometryFilter *parison=vtkGeometryFilter::New();
		parison-> SetInputConnection (connect2-> GetOutputPort());
	vtkPolyDataNormals *normals2=vtkPolyDataNormals::New();
		normals2-> SetInputConnection (parison ->GetOutputPort());
		normals2-> SetFeatureAngle (60);
	vtkLookupTable *lut=vtkLookupTable::New();
		lut-> SetHueRange (0.0, 0.66667);
	vtkPolyDataMapper *parisonMapper=vtkPolyDataMapper::New();
		parisonMapper-> SetInputConnection (normals2-> GetOutputPort());
		parisonMapper-> SetLookupTable (lut);
		parisonMapper-> SetScalarRange (0.12, 1.0);
	vtkActor *parisonActor=vtkActor::New();
		parisonActor-> SetMapper( parisonMapper);

	///////////////
	vtkContourFilter *cf=vtkContourFilter::New();
		cf-> SetInputConnection (connect2-> GetOutputPort());
		cf-> SetValue(0, .5);
	vtkPolyDataMapper *contourMapper=vtkPolyDataMapper::New();
		contourMapper-> SetInputConnection (cf-> GetOutputPort());
	vtkActor *contours=vtkActor::New();
		contours ->SetMapper(contourMapper);

	ren->AddActor(moldActor);
	ren->AddActor(parisonActor);
	ren->AddActor(contours);

	ren->ResetCamera();
	ren->GetActiveCamera()-> Azimuth (60);
	ren->GetActiveCamera()->Roll (-90);
	ren->GetActiveCamera()->Dolly (2);
	ren->ResetCameraClippingRange();

	ren->SetBackground (1, 1, 1);
	renWindow->SetSize(750, 400);

	iren->Initialize();
	renWindow->Render();

	iren->Start();
}


