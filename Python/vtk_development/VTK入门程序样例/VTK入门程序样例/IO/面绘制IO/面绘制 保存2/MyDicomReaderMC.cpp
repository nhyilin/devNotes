
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

/////////////////////
   vtkPolyDataWriter *wSP=vtkPolyDataWriter::New();
	  wSP->SetInput(deci->GetOutput());
	  wSP->SetFileName("PolyDataWriter.vtk");
	  wSP->Write();
	  wSP->Delete();

   vtkDataSetWriter *dsw=vtkDataSetWriter::New();
     dsw-> SetInputConnection(deci ->GetOutputPort());
     dsw-> SetFileName ("vtkDataSetWriter.dsw");
     dsw-> Write();

   vtkBYUWriter *byu=vtkBYUWriter::New();
     byu-> SetGeometryFileName("BYUWriter.g");
     byu-> SetScalarFileName("BYUWriter.s");
     byu-> SetDisplacementFileName ("BYUWriter.d");
     byu-> SetInputConnection(deci ->GetOutputPort());
     byu-> Write();

   vtkMCubesWriter *mcubes=vtkMCubesWriter::New();
     mcubes-> SetInputConnection(deci-> GetOutputPort());
     mcubes-> SetFileName ("MCubesWriter.tri");
     mcubes-> SetLimitsFileName ("MCubesWriter.lim");
     mcubes-> Write();

   vtkSTLWriter *stl=vtkSTLWriter::New();
     stl-> SetInputConnection(deci-> GetOutputPort());
     stl-> SetFileName("STLWriter.stl");
     stl-> Write();

   vtkCGMWriter *cgm=vtkCGMWriter::New();
     cgm-> SetInputConnection(deci-> GetOutputPort());
     cgm-> SetFileName("CGMWriter.cgm");
     cgm-> Write();

   vtkXMLPolyDataWriter *pdWriter=vtkXMLPolyDataWriter::New();
	 pdWriter-> SetFileName("XMLPolyDataWriter.xpd");
	 pdWriter-> SetDataModeToAscii();
	 pdWriter-> SetInputConnection(deci-> GetOutputPort());
	 pdWriter-> Write();
////////////////

  shrink->Delete();
  deci->Delete();
  reader->Delete();

  return 0;
}
