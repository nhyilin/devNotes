
#include "vtkActor.h"
#include "vtkCellLocator.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkTIFFReader.h"
#include "vtkImageRGBToHSV.h"
#include "vtkImageConstantPad.h"
#include "vtkImageSeedConnectivity.h"
#include "vtkImageThreshold.h"
#include "vtkImageGaussianSmooth.h"
#include "vtkCastToConcrete.h"
#include "vtkTextureMapToPlane.h"
#include "vtkImageDataGeometryFilter.h"
#include "vtkImageShrink3D.h"

#include "vtkImageData.h"
#include "vtkDecimatePro.h"
#include "vtkTriangleFilter.h"
#include "vtkClipPolyData.h"
#include "vtkLinearExtrusionFilter.h"
#include "vtkPolyDataNormals.h"
#include "vtkStripper.h"
#include "vtkImageExtractComponents.h"
#include "vtkCastToConcrete.h"
#include "vtkTexture.h"
#include "vtkCamera.h"
#include "vtkRegressionTestImage.h"
#include "vtkCastToConcrete.h"
#include "vtkPointData.h"

int PowerOfTwo (int amt) 
{
  int pow=0;
  amt--;
  while (1) 
  {
	amt=amt/2;  
//	amt >> 1;
	pow++;
	if (amt <= 0)
		return (1 << pow);
  }
}


void main( )
{
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

vtkTIFFReader *imageIn=vtkTIFFReader::New();
  imageIn-> SetFileName ("beach.tif");
  imageIn-> ReleaseDataFlagOff();
  imageIn-> Update();


int orgX=imageIn->GetOutput()-> GetWholeExtent()[1]- 
         imageIn->GetOutput()-> GetWholeExtent()[0]; 
int orgY=imageIn->GetOutput()-> GetWholeExtent()[1]- 
         imageIn->GetOutput()-> GetWholeExtent()[0];
int padX=PowerOfTwo (orgX);
int padY=PowerOfTwo (orgY);

vtkImageConstantPad *imagePowerOf2=vtkImageConstantPad::New();
  imagePowerOf2-> SetInputConnection (imageIn-> GetOutputPort());
  imagePowerOf2-> SetOutputWholeExtent (0 ,(padX - 1), 0 ,(padY - 1), 0 ,0);

vtkImageRGBToHSV *toHSV=vtkImageRGBToHSV::New();
  toHSV-> SetInputConnection (imageIn-> GetOutputPort());
  toHSV-> ReleaseDataFlagOff();

vtkImageExtractComponents *extractImage=vtkImageExtractComponents::New();
  extractImage-> SetInputConnection (toHSV-> GetOutputPort());
  extractImage-> SetComponents (2);
  extractImage-> ReleaseDataFlagOff();

vtkImageThreshold *threshold1=vtkImageThreshold::New();
  threshold1-> SetInputConnection (extractImage-> GetOutputPort());
  threshold1-> ThresholdByUpper (230);
  threshold1-> SetInValue (255);
  threshold1-> SetOutValue (0);
  threshold1-> Update();

int extent[6];
  threshold1-> GetOutput()-> GetWholeExtent(extent);
 
vtkImageSeedConnectivity *connect=vtkImageSeedConnectivity::New();
  connect-> SetInputConnection (threshold1->GetOutputPort());
  connect-> SetInputConnectValue (255);
  connect-> SetOutputConnectedValue (255);
  connect-> SetOutputUnconnectedValue (0);
  connect-> AddSeed (extent [0], extent [2]);
  connect-> AddSeed (extent [1], extent [2]); 
  connect-> AddSeed (extent [1], extent [3]);
  connect-> AddSeed (extent [0], extent [3]);
// return;
vtkImageGaussianSmooth *smooth=vtkImageGaussianSmooth::New();
  smooth-> SetDimensionality (2);
  smooth-> SetStandardDeviation (1, 1);
  smooth-> SetInputConnection (connect-> GetOutputPort());

vtkImageShrink3D *shrink=vtkImageShrink3D::New();
  shrink-> SetInputConnection (smooth-> GetOutputPort());
  shrink-> SetShrinkFactors (2, 2 ,1);
  shrink-> AveragingOn();

vtkImageDataGeometryFilter *geometry=vtkImageDataGeometryFilter::New();
  geometry-> SetInputConnection (shrink-> GetOutputPort());

vtkTextureMapToPlane *geometryTexture=vtkTextureMapToPlane::New();
  geometryTexture-> SetInputConnection (geometry-> GetOutputPort());
  geometryTexture-> SetOrigin (0, 0 ,0);
  geometryTexture-> SetPoint1 ((padX - 1), 0, 0);
  geometryTexture-> SetPoint2 (0 ,(padY - 1), 0);

vtkCastToConcrete *geometryPD=vtkCastToConcrete::New();
  geometryPD-> SetInputConnection (geometryTexture-> GetOutputPort());

vtkClipPolyData *clip=vtkClipPolyData::New();
  clip-> SetInput (geometryPD-> GetPolyDataOutput());
  clip-> SetValue (5.5);
  clip-> GenerateClipScalarsOff();
  clip-> InsideOutOff();
  clip-> InsideOutOn();
  clip-> GetOutput()-> GetPointData()-> CopyScalarsOff();
  clip-> Update();

vtkTriangleFilter *triangles=vtkTriangleFilter::New();
  triangles-> SetInputConnection (clip-> GetOutputPort());

vtkDecimatePro *decimate=vtkDecimatePro::New();
  decimate-> SetInputConnection (triangles->GetOutputPort());
  decimate-> BoundaryVertexDeletionOn();
  decimate-> SetDegree (25);
  decimate-> PreserveTopologyOn();

vtkLinearExtrusionFilter *extrude=vtkLinearExtrusionFilter::New();
  extrude-> SetInputConnection (decimate-> GetOutputPort());
  extrude-> SetExtrusionType (2);
  extrude-> SetScaleFactor (-20);

vtkPolyDataNormals *normals=vtkPolyDataNormals::New();
  normals-> SetInputConnection (extrude-> GetOutputPort());
  normals-> SetFeatureAngle (80);

vtkStripper *strip=vtkStripper::New();
  strip-> SetInputConnection (extrude-> GetOutputPort());

vtkPolyDataMapper *map=vtkPolyDataMapper::New();
  map-> SetInputConnection (strip-> GetOutputPort());
  map-> SetInputConnection (normals-> GetOutputPort());
  map-> ScalarVisibilityOff();

vtkTexture *imageTexture=vtkTexture::New();
  imageTexture-> InterpolateOn();
  imageTexture-> SetInputConnection (imagePowerOf2-> GetOutputPort());

vtkActor *clipart=vtkActor::New();
    clipart-> SetMapper (map);
    clipart-> SetTexture (imageTexture);
	clipart-> GetProperty()-> SetDiffuseColor (1, 1, 1);
	clipart-> GetProperty()-> SetSpecular( .5);
	clipart-> GetProperty()-> SetSpecularPower( 30);
	clipart-> GetProperty()-> SetDiffuse (.9);


  
  renderer->AddActor(clipart);

  renderer->SetBackground(1,1,1);
  renWin->SetSize(600,600);

  renderer-> ResetCamera();
  renderer->GetActiveCamera()->Azimuth (30);
  renderer->GetActiveCamera()->Elevation (-30);
  renderer->GetActiveCamera()->Dolly (1.5);
  renderer-> ResetCameraClippingRange();
  // interact with data


  renWin->Render();

  iren->Start();


  // Clean up
  renderer->Delete();
  renWin->Delete();
  iren->Delete();

}
