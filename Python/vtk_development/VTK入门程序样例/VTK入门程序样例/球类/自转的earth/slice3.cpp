


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

vtkTransform *aTransform;
vtkInteractorStyleTrackballCamera *style;
vtkRenderWindowInteractor *iren;
vtkCamera *aCamera;
vtkRenderWindow *renWin;
double angle=360;
double pi=3.1415926/180;

void left(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
	aTransform->RotateWXYZ(1, 0,0,1);   
	style->OnLeftButtonDown();
}

void keypress(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
	char key=iren->GetKeyCode();
	switch (key)
    {
      case 'm'://图形旋转
           aTransform->RotateWXYZ(1, 0,0,1);
		   break;
      case 'n'://视点变化使其旋转(不成)
		  double position[3]; 
		  aCamera->GetPosition(position);
/*
		  if(position[3]<0.01)
		  {
			aCamera->SetPosition(2.5,2.5,0);
			aCamera->SetFocalPoint(0,0,0);
//			aCamera->Roll(90);
		  }
		  else
			aCamera->Elevation(-1);
*/

//		  double xnew,ynew;
//		  xnew=cos(1)*position[0]-sin(1)*position[1];    
//		  ynew=sin(1)*position[0]+cos(1)*position[2]; 

//		  aCamera->SetPosition(xnew,ynew,position[3]);
		  angle=angle-2;
		  if (angle==0)
			angle=360;
		  position[0]=3*cos(angle*pi);
		  position[1]=3*sin(angle*pi);
		  position[2]=0;

		  aCamera->SetPosition(position);
		  aCamera->SetFocalPoint(0,0,0);

		  renWin->Render();
		  break;
	}
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

    aTransform = vtkTransform::New();
      aTransform->Scale(1,1,1);

    vtkTransformFilter *transFilter = vtkTransformFilter::New();
      transFilter->SetInput(tss->GetOutput());
      transFilter->SetTransform(aTransform); 
	  
	vtkPolyDataMapper   *earthMapper=vtkPolyDataMapper::New();
	  earthMapper-> SetInputConnection (transFilter->GetOutputPort());

	vtkActor *earthActor=vtkActor::New();
	  earthActor-> SetMapper (earthMapper);

	vtkTexture *atext=vtkTexture::New();
	vtkPNMReader *pnmReader=vtkPNMReader::New();
	  pnmReader-> SetFileName ("earth.ppm");
	  atext-> SetInputConnection (pnmReader-> GetOutputPort());
	  atext-> InterpolateOn();

	  earthActor->SetTexture (atext);

	  ren1-> AddActor (earthActor);
	  ren1-> SetBackground (1, 1, 1);
	  renWin-> SetSize (600,600);

  vtkCallbackCommand * cmd = vtkCallbackCommand::New();
	cmd->SetCallback(left);
  vtkCallbackCommand * cmd1 = vtkCallbackCommand::New();
	cmd1->SetCallback(keypress);

  style-> AddObserver (vtkCommand::KeyPressEvent,cmd1);
  style-> AddObserver (vtkCommand::LeftButtonPressEvent,cmd);

	aCamera = vtkCamera::New();
	  ren1->SetActiveCamera(aCamera);
	  ren1-> ResetCamera();
	  ren1-> GetActiveCamera()->Zoom( 1.2);
	  ren1->GetActiveCamera()->Roll(30);
	  ren1->GetActiveCamera()->Elevation (-30);

  vtkLight *light = vtkLight::New();
    light->SetFocalPoint(0,0,0);
    light->SetPosition(100,-100,0);
    ren1->AddLight(light);

  for (int i = 0; i < 360; ++i)
    {
    // Render the image and rotate the active camera by one degree
    renWin->Render();
	aTransform->RotateWXYZ(1, 0,0,1);
    }

	  renWin->Render();
	  iren->Start();
}
