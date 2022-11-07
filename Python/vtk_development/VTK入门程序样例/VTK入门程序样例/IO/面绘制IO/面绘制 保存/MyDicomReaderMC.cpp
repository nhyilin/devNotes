
/*
  使用vtkDICOMImageReader 读取序列CT图像
*/

#include "vtkProperty.h"
#include "vtkPolyDataNormals.h"
#include "vtkContourFilter.h"
#include "vtkMarchingCubes.h"
#include "vtkDICOMImageReader.h"
#include "vtkImageCast.h"
#include "vtkDecimatePro.h"
#include "vtkStripper.h"
#include "vtkImageShrink3D.h"
#include "vtkSmoothPolyDataFilter.h" 
#include "vtkTriangleFilter.h"
#include "vtkImageData.h"

#include "vtkPolyDataWriter.h"
#include <vtkBYUWriter.h> 
#include "vtkXMLPolyDataWriter.h"
#include "vtkDataSetWriter.h"
#include <vtkMCubesWriter.h> 
#include "vtkSTLWriter.h"
#include <vtkCGMWriter.h> 

int main ()
{
  vtkDICOMImageReader   *reader =  vtkDICOMImageReader::New();
	reader->SetDataByteOrderToLittleEndian();
	reader->SetDirectoryName("E://CT/head40/");
	reader->Update();

  vtkImageShrink3D *shrink=vtkImageShrink3D::New();
		shrink->SetInput((vtkDataObject *)reader->GetOutput());
		shrink->SetShrinkFactors(4,4,1);
		shrink->AveragingOn();

  vtkContourFilter *skinExtractor = vtkContourFilter::New();
    skinExtractor->SetInputConnection(shrink->GetOutputPort());
    skinExtractor->SetValue(0,-500);

  vtkDecimatePro *deci=vtkDecimatePro::New();
 	deci->SetInputConnection(skinExtractor->GetOutputPort());
 	deci->SetTargetReduction(0.3);

  vtkSmoothPolyDataFilter *smooth=vtkSmoothPolyDataFilter::New(); 
    smooth->SetInputConnection(deci->GetOutputPort());
	smooth->SetNumberOfIterations(200)  ;

  vtkPolyDataNormals *skinNormals = vtkPolyDataNormals::New();
    skinNormals->SetInputConnection(smooth->GetOutputPort());
    skinNormals->SetFeatureAngle(60.0);

  vtkStripper *stripper=vtkStripper::New(); 
    stripper->SetInput(skinNormals->GetOutput());

/////////////////////
   vtkPolyDataWriter *wSP=vtkPolyDataWriter::New();
	  wSP->SetInput(stripper->GetOutput());
	  wSP->SetFileName("E://CT/PolyDataWriter.vtk");
	  wSP->Write();
	  wSP->Delete();

   vtkDataSetWriter *dsw=vtkDataSetWriter::New();
     dsw-> SetInputConnection(stripper ->GetOutputPort());
     dsw-> SetFileName ("E://CT/vtkDataSetWriter.dsw");
     dsw-> Write();

   vtkBYUWriter *byu=vtkBYUWriter::New();
     byu-> SetGeometryFileName("E://CT/BYUWriter.g");
     byu-> SetScalarFileName("E://CT/BYUWriter.s");
     byu-> SetDisplacementFileName ("E://CT/BYUWriter.d");
     byu-> SetInputConnection(stripper ->GetOutputPort());
     byu-> Write();

   vtkMCubesWriter *mcubes=vtkMCubesWriter::New();
     mcubes-> SetInputConnection(stripper-> GetOutputPort());
     mcubes-> SetFileName ("E://CT/MCubesWriter.tri");
     mcubes-> SetLimitsFileName ("E://CT/MCubesWriter.lim");
     mcubes-> Write();

   vtkSTLWriter *stl=vtkSTLWriter::New();
     stl-> SetInputConnection(stripper-> GetOutputPort());
     stl-> SetFileName("E://CT/STLWriter.stl");
     stl-> Write();

   vtkCGMWriter *cgm=vtkCGMWriter::New();
     cgm-> SetInputConnection(stripper-> GetOutputPort());
     cgm-> SetFileName("E://CT/CGMWriter.cgm");
     cgm-> Write();

   vtkXMLPolyDataWriter *pdWriter=vtkXMLPolyDataWriter::New();
	 pdWriter-> SetFileName("E://CT/XMLPolyDataWriter.xpd");
	 pdWriter-> SetDataModeToAscii();
	 pdWriter-> SetInputConnection(stripper-> GetOutputPort());
	 pdWriter-> Write();
////////////////

  shrink->Delete();
  smooth->Delete();
  deci->Delete();
  stripper->Delete();
  skinNormals->Delete();

  reader->Delete();

  return 0;
}
