/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: VolCutKnee.cxx,v $
  Language:  C++
  Date:      $Date: 2003/03/10 14:03:33 $
  Version:   $Revision: 1.0 $

  Copyright (c) 2003 Huiqun Zhou
  Department of Earth Sciences
  Nanjing University
  All rights reserved.
  
     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// This example shows how to.
//

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkContourFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkPointData.h"
#include "vtkProperty.h"
#include "vtkVolumeProperty.h"
#include "vtkSLCReader.h"
#include "vtkPiecewiseFunction.h"
#include "vtkCamera.h"
#include "vtkFloatArray.h"
#include "vtkVolumeRayCastCompositeFunction.h"
#include "vtkVolumeRayCastMapper.h"
#include "vtkImageShrink3D.h"
#include "vtkPoints.h"
#include "vtkPlanes.h"
#include "vtkClipPolyData.h"

int main()
{
	vtkRenderer *ren1 = vtkRenderer::New();
  		ren1->BackingStoreOn();

	vtkRenderWindow *renWin = vtkRenderWindow::New();
		renWin->AddRenderer(ren1);

	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
		iren->SetRenderWindow(renWin);

	vtkSLCReader *reader = vtkSLCReader::New();
		reader->SetFileName("nut.slc");
		reader->Update();

	vtkPiecewiseFunction *white_tfun = vtkPiecewiseFunction::New();
		white_tfun->AddPoint(0, 1.0);
		white_tfun->AddPoint(255, 1.0);

	vtkPiecewiseFunction *tfun = vtkPiecewiseFunction::New();
		tfun->AddPoint(70, 0.0);
		tfun->AddPoint(80, 1.0); 

	ren1->SetBackground(0.1, 0.2, 0.4);

	vtkVolumeProperty *vol_prop = vtkVolumeProperty::New();
		vol_prop->SetColor(white_tfun);
		vol_prop->SetScalarOpacity(tfun);
		vol_prop->SetInterpolationTypeToLinear();
		vol_prop->ShadeOn();

	vtkVolumeRayCastCompositeFunction *comp_func = 
					vtkVolumeRayCastCompositeFunction::New();

	vtkVolumeRayCastMapper *volmap = vtkVolumeRayCastMapper::New();
		volmap->SetVolumeRayCastFunction(comp_func);
		volmap->SetInput(reader->GetOutput());
		volmap->SetSampleDistance(1.0);

	vtkVolume *vol = vtkVolume::New();
		vol->SetProperty(vol_prop);
		vol->SetMapper(volmap);

	ren1->AddVolume(vol);

	vtkImageShrink3D *shrink = vtkImageShrink3D::New();
  		shrink->SetInput((vtkDataObject *)reader->GetOutput());
  		shrink->SetShrinkFactors(4, 4, 2);
  		shrink->AveragingOn();

	vtkContourFilter *contour = vtkContourFilter::New();
  		contour->SetInput((vtkDataSet *)shrink->GetOutput());
  		contour->SetValue(0, 30.0);

	vtkPoints *points = vtkPoints::New();
  		points->InsertPoint(0, 100.0, 150.0, 130.0);
  		points->InsertPoint(1, 100.0, 150.0, 130.0);
  		points->InsertPoint(2, 100.0, 150.0, 130.0);

	vtkFloatArray *normals = vtkFloatArray::New();
		normals->SetNumberOfComponents(3);
		float normtemp[3];
		normtemp[0] = 1.0; normtemp[1] = 0.0; normtemp[2] = 0.0;
		normals->InsertTuple(0, normtemp);
		normtemp[0] = 0.0; normtemp[1] = 1.0; normtemp[2] = 0.0;
		normals->InsertTuple(1, normtemp);
		normtemp[0] = 0.0; normtemp[1] = 0.0; normtemp[2] = 1.0;
		normals->InsertTuple(2, normtemp);
  
	vtkPlanes *planes = vtkPlanes::New();
  		planes->SetPoints(points);
  		planes->SetNormals(normals);

	vtkClipPolyData *clipper = vtkClipPolyData::New();
  		clipper->SetInput(contour->GetOutput());
  		clipper->SetClipFunction(planes);
  		clipper->GenerateClipScalarsOn();

	vtkPolyDataMapper *skin_mapper = vtkPolyDataMapper::New();
  		skin_mapper->SetInput(clipper->GetOutput());
  		skin_mapper->ScalarVisibilityOff();

	vtkActor *skin = vtkActor::New();
  		skin->SetMapper(skin_mapper);
  		skin->GetProperty()->SetColor(0.8, 0.4, 0.2);

	ren1->AddActor(skin);

	renWin->SetSize(400, 400);


	ren1->GetActiveCamera()->SetPosition(-47.5305, -319.315, 92.0083);
	ren1->GetActiveCamera()->SetFocalPoint(78.9121, 89.8372, 95.1229);
	ren1->GetActiveCamera()->SetViewUp(-0.00708891, 0.00980254, -0.999927);
	ren1->GetActiveCamera()->SetClippingRange(42.8255, 2141.28);

	renWin->Render();

	// interact with data
	iren->Initialize();
	iren->Start();

	skin->Delete();
	skin_mapper->Delete();
	clipper->Delete();
	planes->Delete();
	normals->Delete();
	points->Delete();
	contour->Delete();
	shrink->Delete();
	vol->Delete();
	volmap->Delete();
	comp_func->Delete();
	vol_prop->Delete();
	tfun->Delete();
	white_tfun->Delete();
	reader->Delete();
	iren->Delete();
	renWin->Delete();
	ren1->Delete();

	return 0;
}
