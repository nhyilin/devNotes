
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkPolyData.h"
#include "vtkBoxWidget.h"
#include "vtkCardinalSpline.h"
#include "vtkPoints.h"
#include "stdio.h"
#include <time.h>
#include <vtkGlyph3D.h>
#include <vtkProperty.h>
#include <vtkCellArray.h>
#include <vtkTubeFilter.h>
#include <vtkPolyLine.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkLookupTable.h>

void main()
{

	  srand(time(NULL)) ;

	//	rand()/RAND_MAX;//	0 - RAND_MAX
	  vtkRenderer *ren = vtkRenderer::New();
	  vtkRenderWindow *renWindow = vtkRenderWindow::New();
		renWindow->AddRenderer(ren);
	  renWindow->SetSize( 600, 600 );

		vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
		iren->SetRenderWindow(renWindow);

	  int numberOfInputPoints = 30;

		vtkCardinalSpline *aSplineX = vtkCardinalSpline::New();
		vtkCardinalSpline *aSplineY = vtkCardinalSpline::New();
		vtkCardinalSpline *aSplineZ = vtkCardinalSpline::New();

	vtkPoints *inputPoints = vtkPoints::New();

	double x,y,z;
	int i;
	for(i=0;i<numberOfInputPoints;i++)
	{
		x = (float)rand()/(float)RAND_MAX;
		y = (float)rand()/(float)RAND_MAX;
		z = (float)rand()/(float)RAND_MAX;
		printf(" x:%f,y:%f,z:%f\n",x,y,z);
		aSplineX->AddPoint(i, x);
		aSplineY->AddPoint(i, y);
		aSplineZ->AddPoint(i, z);
		inputPoints->InsertPoint(i, x, y, z);
	}


	vtkPolyData *inputData =vtkPolyData::New();
	inputData->SetPoints(inputPoints);

	vtkSphereSource *balls =vtkSphereSource::New();
	balls->SetRadius(.01);
	balls->SetPhiResolution(10);
	balls->SetThetaResolution(10);

	vtkGlyph3D *glyphPoints =vtkGlyph3D::New();
	glyphPoints->SetInput(inputData);
	glyphPoints->SetSource(balls->GetOutput());

	vtkPolyDataMapper *glyphMapper = vtkPolyDataMapper::New();
	glyphMapper->SetInputConnection(glyphPoints->GetOutputPort());

	vtkActor *glyph = vtkActor::New();
	glyph->SetMapper(glyphMapper);
	glyph->GetProperty()->SetDiffuseColor(1,0,0);
	glyph->GetProperty()->SetSpecular(.3);
	glyph->GetProperty()->SetSpecularPower(30);

	///////////////
	vtkPoints *points = vtkPoints::New();

	// Number of points on the spline
	int numberOfOutputPoints = 400;
	float t;

	for(i=0;i<numberOfOutputPoints;i++)
	{
		t = (numberOfInputPoints-1.0)/(numberOfOutputPoints-1.0)*i;
		points->InsertPoint(i, aSplineX->Evaluate(t), aSplineY->Evaluate(t),
						   aSplineZ->Evaluate(t));
		printf(" point:%f, %f, %f; \n",points->GetPoint(i)[0],
									   points->GetPoint(i)[1],points->GetPoint(i)[2]);
	}

	vtkCellArray *lines = vtkCellArray::New();
		int a=lines->InsertNextCell(numberOfOutputPoints);
		for(i=0;i<numberOfOutputPoints;i++)
		{
			lines->InsertCellPoint(i);
		}

		vtkPolyData *profileData = vtkPolyData::New();
		  profileData->SetPoints(points);
		  profileData->SetLines(lines);

	   int N= profileData->GetNumberOfPoints();
  
	  vtkFloatArray *Scalar=vtkFloatArray::New();
	   Scalar-> SetNumberOfTuples(N);
	   Scalar-> SetNumberOfComponents (1);
	  for(i=0;i<N;i++)
	  {
	   Scalar-> SetValue (i,i/400.0);
	  }
	//   ${cell}Scalar SetValue 0 4

	  profileData->GetPointData()-> SetScalars (Scalar);



	// Add thickness to the resulting line.
	vtkTubeFilter *profileTubes = vtkTubeFilter::New();
	profileTubes->SetNumberOfSides(8);
	profileTubes->SetInput(profileData);
	profileTubes->SetRadius(0.005);

	vtkLookupTable *lut=vtkLookupTable::New();
		lut-> SetNumberOfColors (256);
		lut-> Build();
		for (i= 0;i<128;i++) 
		{
			lut-> SetTableValue(i, i/128.0, (128.0-i)/128.0, (64.0-i)/128.0, 1);
		}
		for (i= 128;i<256;i++) 
		{
			lut-> SetTableValue (i, (i-128.0)/128.0, (i-128.0)/128.0, (256.0-i)/128.0, 1);
		}

	vtkPolyDataMapper *profileMapper = vtkPolyDataMapper::New();
	profileMapper->SetInputConnection(profileTubes->GetOutputPort());
	profileMapper->SetLookupTable(lut); 

	vtkActor *profile = vtkActor::New();
	profile->SetMapper(profileMapper);
	profile->GetProperty()->SetDiffuseColor(1,1,0);
	profile->GetProperty()->SetSpecular(0.3);
	profile->GetProperty()->SetSpecularPower(30);


	//////////////


	ren->AddActor(glyph);
	ren->AddActor(profile);


	iren->Initialize();
	renWindow->Render();

	iren->Start();
}


