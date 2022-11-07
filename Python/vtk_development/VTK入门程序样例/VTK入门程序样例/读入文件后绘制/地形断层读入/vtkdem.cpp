#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkLookupTable.h"
#include "vtkDEMReader.h"
#include "vtkImageShrink3D.h"
#include "vtkLODActor.h"
#include "vtkImageDataGeometryFilter.h"
#include "vtkWarpScalar.h"
#include "vtkElevationFilter.h"
#include "vtkCastToConcrete.h"
#include "vtkPolyDataNormals.h"
#include "vtkPolyDataMapper.h"
#include "vtkGreedyTerrainDecimation.h"
#include "vtkCamera.h"
#include "vtkVolume16Reader.h"
#include "vtkContourFilter.h"
#include "vtkMaskPoints.h"
#include "vtkSelectVisiblePoints.h"
#include "vtkLabeledDataMapper.h"
#include "vtkTextProperty.h"
#include "vtkActor2D.h"
#include "vtkBandedPolyDataContourFilter.h"
#include "vtkImageData.h"
#include "vtkActor2D.h"

void main()
{

	vtkRenderer *ren1=vtkRenderer::New();
	vtkRenderWindow *renWin=vtkRenderWindow::New();
		renWin->AddRenderer(ren1);
	vtkRenderWindowInteractor *iren=vtkRenderWindowInteractor::New();
		iren->SetRenderWindow(renWin);

	int Scale=3;
	vtkLookupTable *lut=vtkLookupTable::New();
	  lut->SetHueRange(0.6,0);
	  lut->SetSaturationRange(1.0,0);
	  lut->SetValueRange(0.5,1.0);

	vtkDEMReader *demModel=vtkDEMReader::New();
		demModel->SetFileName("SainteHelens.dem"); //"$VTK_DATA_ROOT/Data/SainteHelens.dem"
		demModel->Update();
		float data[2];
		demModel->GetElevationBounds(data);
	
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
	  demMapper ->SetLookupTable (lut);
	  demMapper-> SetScalarModeToUseCellData();

	vtkLODActor *demActor=vtkLODActor::New();
	  demActor-> SetMapper (demMapper);


	vtkVolume16Reader *reader=vtkVolume16Reader::New();
		reader->SetDataDimensions(460,460);
		reader->SetDataByteOrderToLittleEndian();
		reader->SetFilePrefix ("E://headsq/refarray");
		reader->SetImageRange(1, 41);
		reader->SetDataSpacing (22, 22, 14*3);
//		reader->SetDataOrigin(-230,-230,-160);

	vtkImageShrink3D *Shrink=vtkImageShrink3D::New();
		Shrink->SetInputConnection(reader->GetOutputPort());
		Shrink->SetShrinkFactors(4,4,1);
	
	vtkContourFilter *iso=vtkContourFilter::New();
		iso->SetInputConnection(Shrink->GetOutputPort());
		iso->GenerateValues( 6,1 ,255);
		iso->Update();
	int numPts= iso->GetOutput()->GetNumberOfPoints();

	vtkPolyDataMapper *isoMapper=vtkPolyDataMapper::New();
		isoMapper->SetInputConnection(iso->GetOutputPort());
		isoMapper->ScalarVisibilityOn();
		isoMapper->SetScalarRange(iso->GetOutput()->GetScalarRange());
	vtkActor *isoActor=vtkActor::New();
	   isoActor->SetMapper(isoMapper);

// Subsample the points and label them
	vtkMaskPoints *mask=vtkMaskPoints::New();
		mask->SetInputConnection(iso->GetOutputPort());
		mask->SetOnRatio(numPts/50);
		mask->SetMaximumNumberOfPoints(50);
		mask->RandomModeOn();

// Create labels for points - only show visible points

	vtkSelectVisiblePoints *visPts=vtkSelectVisiblePoints::New();
		visPts->SetInputConnection(mask->GetOutputPort());
		visPts->SetRenderer(ren1);

	vtkLabeledDataMapper *ldm=vtkLabeledDataMapper::New();
		ldm->SetInputConnection(mask->GetOutputPort());
		ldm->SetLabelFormat("%g"); 
		ldm->SetLabelModeToLabelScalars();
		ldm->GetLabelTextProperty()->SetFontFamilyToArial();
		ldm->GetLabelTextProperty()->SetFontSize(10);
		ldm->GetLabelTextProperty()->SetColor(1,0,0);
   
	vtkActor2D *contourLabels=vtkActor2D::New();
		contourLabels->SetMapper(ldm);

//	demActor->SetPosition(isoActor->GetPosition());

double location1[3];
	demActor->GetPosition(location1);
double location2[3];
	isoActor->GetPosition(location2);
	printf("demActor position:%f, %f ,%f \n",location1[0],location1[1],location1[2]);
	printf("isoActor position:%f, %f ,%f \n",location2[0],location2[1],location2[2]);


double *center1;
	center1=demActor->GetCenter();
double *center2;
	center2=isoActor->GetCenter();

	printf("demActor center:%f, %f ,%f \n",center1[0],center1[1],center1[2]);
	printf("isoActor center:%f, %f ,%f \n",center2[0],center2[1],center2[2]);

isoActor->SetPosition(center1[0]-center2[0],center1[1]-center2[1],center1[2]-center2[2]);
//contourLabels->SetPosition(center1[0]-center2[0],center1[1]-center2[1],center1[2]-center2[2]);

	ren1->AddActor(demActor);
	ren1->SetBackground (1,1,1);
	ren1->AddActor2D(isoActor);
//	ren1->AddActor2D(contourLabels);

	iren->SetDesiredUpdateRate(5);

	//ren1->GetActiveCamera()->SetViewUp(0,0,1);
//	ren1->GetActiveCamera()->SetPosition(800000,0,31801);
	//ren1->GetActiveCamera()->SetFocalPoint(0,0,2815);
	//ren1->GetActiveCamera()->Dolly(5);
	ren1->ResetCamera();


	renWin->Render();
	iren->Start();
}