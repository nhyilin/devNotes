


#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphere.h"
#include "vtkTexturedSphereSource.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkEarthSource.h"
#include "vtkPNMReader.h"
#include "vtkProperty.h"
#include "vtkPolyData.h"
#include "vtkTexture.h"
#include "vtkPolyDataNormals.h"
#include "vtkPolyDataMapper.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkTransform.h"
#include "vtkTransformFilter.h"
#include "vtkOrientationMarkerWidget.h"
#include "vtkTextProperty.h"
#include "vtkAxesActor.h"
#include "vtkCaptionActor2D.h"
#include "vtkCallbackCommand.h"
#include "math.h"
#include "vtkLight.h"
#include "vtkSphereSource.h"
#include "vtkCardinalSpline.h"
#include "vtkPoints.h"
#include <vtkGlyph3D.h>
#include <vtkProperty.h>
#include <vtkCellArray.h>
#include <vtkTubeFilter.h>
#include <vtkPolyLine.h>

vtkTransform *aTransform;
vtkInteractorStyleTrackballCamera *style;
vtkRenderWindowInteractor *iren;
vtkCamera *aCamera;
vtkRenderWindow *renWin;
vtkActor *earthActor;
vtkActor *moonActor;

double angle=360;
double pi=3.1415926/180;

void keypress(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
	char key=iren->GetKeyCode();		  
	double position[3];
	double mposition[3]; 
	switch (key)
    {
      case 'm':
      case 'M':
		  angle=angle-2;
		  if (angle==0)
			angle=360;
		  position[0]=12*cos(angle*pi);
		  position[1]=7*sin(angle*pi);
		  position[2]=0;

		  earthActor->SetPosition(position);

		   mposition[0]=position[0]-2*cos(3*angle*pi);
		   mposition[1]=position[1]+2*sin(3*angle*pi);
		   mposition[2]=0;

		   moonActor->SetPosition(mposition);
		  break;
      case 'n':
      case 'N':
		  angle=angle+2;
		  if (angle==360)
			angle=0;
		  position[0]=12*cos(angle*pi);
		  position[1]=7*sin(angle*pi);
		  position[2]=0;

		  earthActor->SetPosition(position);

		   mposition[0]=position[0]-2*cos(3*angle*pi);
		   mposition[1]=position[1]+2*sin(3*angle*pi);
		   mposition[2]=0;

		   moonActor->SetPosition(mposition);
		  break;

	}
	printf(" point:%f, %f, %f; \n",position[0],
								   position[1],position[2]);
	renWin->Render();
}

void main()
{
	vtkRenderer *ren1 = vtkRenderer::New();
    renWin = vtkRenderWindow::New();
      renWin->AddRenderer(ren1);
    iren = vtkRenderWindowInteractor::New();
      iren->SetRenderWindow(renWin);
	style=vtkInteractorStyleTrackballCamera::New();
	  iren-> SetInteractorStyle(style);

	vtkTexturedSphereSource *tss=vtkTexturedSphereSource::New();
	  tss-> SetThetaResolution (40);
	  tss-> SetPhiResolution (40);
	  tss-> SetRadius(1);
	  
	vtkPolyDataMapper  *earthMapper=vtkPolyDataMapper::New();
	  earthMapper-> SetInputConnection (tss->GetOutputPort());

	earthActor=vtkActor::New();
	  earthActor-> SetMapper (earthMapper);

	vtkTexture *atext=vtkTexture::New();
	vtkPNMReader *pnmReader=vtkPNMReader::New();
	  pnmReader-> SetFileName ("earth.ppm");
	  atext-> SetInputConnection (pnmReader-> GetOutputPort());
	  atext-> InterpolateOn();

	  earthActor->SetPosition(8,0,0);
	  earthActor->SetTexture (atext);

   vtkSphereSource *sphereSource = vtkSphereSource::New();
      sphereSource->SetThetaResolution(40);
      sphereSource->SetPhiResolution(40);
      sphereSource->SetRadius(2);
   vtkPolyDataMapper *SunMapper = vtkPolyDataMapper::New();
      SunMapper->SetInput(sphereSource->GetOutput());
   vtkActor *SunActor = vtkActor::New();
      SunActor->SetMapper(SunMapper);
      SunActor->GetProperty()->SetColor(1, 1, 1);
	  SunActor->SetPosition(-3,0,0);
	  SunActor->GetProperty()->SetOpacity  (0.3)  ; 

   vtkSphereSource *moonSource = vtkSphereSource::New();
      moonSource->SetThetaResolution(40);
      moonSource->SetPhiResolution(40);
      moonSource->SetRadius(0.5);
   vtkPolyDataMapper *moonMapper = vtkPolyDataMapper::New();
      moonMapper->SetInput(moonSource->GetOutput());
   moonActor = vtkActor::New();
      moonActor->SetMapper(moonMapper);
      moonActor->GetProperty()->SetColor(1, 1, 0);
	  moonActor->SetPosition(6,0,0);
	  moonActor->GetProperty()->SetOpacity  (0.3)  ; 


////////////////
    int numberOfInputPoints = 37;

	vtkCardinalSpline *aSplineX = vtkCardinalSpline::New();
	vtkCardinalSpline *aSplineY = vtkCardinalSpline::New();
	vtkCardinalSpline *aSplineZ = vtkCardinalSpline::New();

	vtkPoints *inputPoints = vtkPoints::New();

	double x,y,z;
	int i;
	for(i=0;i<numberOfInputPoints;i++)
	{
		x = 12*cos(i*10*pi);
		y = 7*sin(i*10*pi);
		z = 0;

		aSplineX->AddPoint(i, x);
		aSplineY->AddPoint(i, y);
		aSplineZ->AddPoint(i, z);
		inputPoints->InsertPoint(i, x, y, z);
	}

	vtkPoints *points = vtkPoints::New();

	// Number of points on the spline
	int numberOfOutputPoints = 400;
	float t;

	for(i=0;i<numberOfOutputPoints;i++)
	{
		t = (numberOfInputPoints-1.0)/(numberOfOutputPoints-1.0)*i;
		points->InsertPoint(i, aSplineX->Evaluate(t), aSplineY->Evaluate(t),
						   aSplineZ->Evaluate(t));
//		printf(" point:%f, %f, %f; \n",points->GetPoint(i)[0],
//									   points->GetPoint(i)[1],points->GetPoint(i)[2]);
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

	// Add thickness to the resulting line.
	vtkTubeFilter *profileTubes = vtkTubeFilter::New();
		profileTubes->SetNumberOfSides(8);
		profileTubes->SetInput(profileData);
		profileTubes->SetRadius(0.05);

	vtkPolyDataMapper *profileMapper = vtkPolyDataMapper::New();
		profileMapper->SetInputConnection(profileTubes->GetOutputPort());

	vtkActor *profile = vtkActor::New();
		profile->SetMapper(profileMapper);
		profile->GetProperty()->SetDiffuseColor(0.2,0,0);
		profile->GetProperty()->SetSpecular(0.3);
		profile->GetProperty()->SetSpecularPower(30);

////////////////


	  ren1-> AddActor (earthActor);
	  ren1-> AddActor(SunActor);
	  ren1-> AddActor(moonActor);
	  ren1-> AddActor(profile);
	  ren1-> SetBackground (0, 0, 0.2);
	  renWin-> SetSize (1000,600);

  vtkCallbackCommand * cmd1 = vtkCallbackCommand::New();
	cmd1->SetCallback(keypress);

  style-> AddObserver (vtkCommand::KeyPressEvent,cmd1);

	aCamera = vtkCamera::New();
	  ren1->SetActiveCamera(aCamera);
	  ren1-> ResetCamera();

  vtkLight *light = vtkLight::New();
    light->SetPosition(0,0,0);
	light->LightTypeIsHeadlight ();
//  ren1->AddLight(light);

  for (i = 360; i >0; --i)
    {
       renWin->Render();
	   double position[3]; 

	   position[0]=12*cos(i*pi);
	   position[1]=7*sin(i*pi);
	   position[2]=0;

	   earthActor->SetPosition(position);

	   double mposition[3]; 

	   mposition[0]=position[0]-2*cos(3*i*pi);
	   mposition[1]=position[1]+2*sin(3*i*pi);
	   mposition[2]=0;

	   moonActor->SetPosition(mposition);

    }

	  renWin->Render();
	  iren->Start();
}
