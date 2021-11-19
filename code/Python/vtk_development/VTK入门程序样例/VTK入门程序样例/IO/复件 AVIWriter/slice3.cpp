/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: TestAVIWriter.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME Test of vtkAVIWriter
// .SECTION Description
//

#include "vtkAVIWriter.h"
#include "vtkImageCast.h"
#include "vtkImageData.h"
#include "vtkImageMandelbrotSource.h"
#include "vtkImageMapToColors.h"
#include "vtkLookupTable.h"
#include "vtksys/SystemTools.hxx"
#include "vtkDICOMImageReader.h"
#include "vtkImageMapToWindowLevelColors.h"
#include "vtkImageReslice.h"

int main(int vtkNotUsed(argc), char* vtkNotUsed(argv)[])
{
  int err = 0;
  int cc = 0;
  int exists = 0;
  unsigned long length = 0;

	vtkDICOMImageReader* reader = vtkDICOMImageReader::New();	
	  reader->SetFileName("E://CT/100098.dcm");
	  reader->SetDataByteOrderToLittleEndian();
	  reader->Update();


	vtkImageReslice *res=vtkImageReslice::New();
	  res->SetInputConnection(reader-> GetOutputPort());
	  res->InterpolateOn();
	  res->SetInterpolationModeToCubic(); 
	  res->SetBackgroundLevel(1023);
	  res->WrapOn();
	  res->SetOutputExtent( 0 ,511 ,0 ,511, 0 ,0);

	vtkLookupTable *hueLut=vtkLookupTable::New();
      hueLut->SetTableRange (0, 2000);
      hueLut->SetHueRange (0, 1);
      hueLut->SetSaturationRange (1, 1);
      hueLut->SetValueRange (1, 1);
	  hueLut->SetAlpha(1);
      hueLut->Build(); //effective built 

  vtkImageMapToColors* colorize = vtkImageMapToColors::New();
  colorize->SetOutputFormatToRGB();
  colorize->SetLookupTable(hueLut);
  colorize->SetReferenceCount(20);
  colorize->SetInputConnection(res->GetOutputPort());


  vtkAVIWriter *w = vtkAVIWriter::New();
  w->SetInputConnection(colorize->GetOutputPort());
  w->SetFileName("TestAVIWriter.avi");
  cout << "Writing file TestAVIWriter.avi..." << endl;
  w->Start();
  for(cc=0;cc<40;cc++)
  {
	vtkImageReslice *res1=vtkImageReslice::New();
	  res1->SetInputConnection(reader-> GetOutputPort());
	  res1->InterpolateOn();
	  res1->SetInterpolationModeToCubic(); 
	  res1->SetBackgroundLevel(1023);
	  res1->WrapOn();
	  res1->SetOutputExtent( 0 ,511 ,0 ,511, cc ,cc);

	colorize->SetInputConnection(res1->GetOutputPort());
	colorize->Update();
    w->Write();
  }

  w->End();
  cout << endl;
  cout << "Done writing file TestAVIWriter.avi..." << endl;
  w->Delete();

  exists = (int) vtksys::SystemTools::FileExists("TestAVIWriter.avi");
  length = vtksys::SystemTools::FileLength("TestAVIWriter.avi");
  cout << "TestAVIWriter.avi file exists: " << exists << endl;
  cout << "TestAVIWriter.avi file length: " << length << endl;
  if (!exists)
    {
    err = 3;
    cerr << "ERROR: 3 - Test failing because TestAVIWriter.avi file doesn't exist..." << endl;
    }
  if (0==length)
    {
    err = 4;
    cerr << "ERROR: 4 - Test failing because TestAVIWriter.avi file has zero length..." << endl;
    }


  // err == 0 means test passes...
  //
  return err;
}
