
#include <iostream>
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkDICOMImageReader.h"
#include "vtkSphereSource.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkImageCast.h"
#include "vtkCallbackCommand.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkImageDataGeometryFilter.h" 
#include "vtkWarpScalar.h" 
#include "vtkWindowLevelLookupTable.h" 
#include "vtkImageMapToWindowLevelColors.h" 
#include "vtkInteractorStyleTrackballCamera.h" 
#include "vtkInteractorStyle.h" 
#include "vtkInteractorEventRecorder.h" 
#include "vtkTextActor.h" 
#include "vtkSphereSource.h" 
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include "vtkTextProperty.h" 
#include "vtkOrientationMarkerWidget.h"
#include "vtkAxesActor.h"
#include "vtkCaptionActor2D.h"
#include <math.h>
#include <vtkJPEGReader.h>
#include <vtkTexture.h>
#include "vtkSphereSource.h" 
#include "vtkPlane.h"
#include "vtkClipPolyData.h"
#include "vtkTextureMapToCylinder.h"
#include "vtkPolyDataNormals.h" 
#include "vtkTextureMapToCylinder.h"
#include "vtkTransformTextureCoords.h"
#include "vtkDataSetMapper.h"
#include "vtk3DSImporter.h"
#include "vtkCubeAxesActor2D.h"
#include "vtkTextProperty.h"

vtkRenderWindowInteractor *iren;
vtkCamera *aCamera;
vtkRenderer *ren1;
vtkRenderWindow *renWin;
vtkTextActor *txt;
vtkActor *feidie;
vtkInteractorEventRecorder *recorder;

int pos;
float dis;

char BoxWidgetEventLog[] =
	"LeftButtonPressEvent 153 253 0 0 0 0 i\n"
	"MouseMoveEvent 153 252 0 0 0 0 i\n"
	"LeftButtonReleaseEvent 153 252 0 0 0 0 i\n"
	;

void keypress(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata);

int main()
{
    ren1= vtkRenderer::New();
    renWin = vtkRenderWindow::New();
      renWin->AddRenderer( ren1 );
    iren = vtkRenderWindowInteractor::New();
      iren->SetRenderWindow(renWin);
    vtkInteractorStyleTrackballCamera *style=vtkInteractorStyleTrackballCamera::New();

	pos=3000;
	dis=0.7;
///////////////////////////

	vtk3DSImporter *importer=vtk3DSImporter::New();
	  importer-> ComputeNormalsOn();
	  importer-> SetFileName ("aa.3ds");
	  importer-> Read();

	int numOfActors = importer-> GetRenderer()->GetActors()->GetNumberOfItems();  

	for(int i = 0 ; i < numOfActors-1 ; i++)
	{
		vtkActor *actor = (vtkActor *)importer-> GetRenderer()->GetActors()->GetItemAsObject(i);		
		ren1->AddActor(actor);
	}

////////////////////////////////////
	txt = vtkTextActor::New();
    txt->SetDisplayPosition(0, 0);
    txt->SetInput("Information Shown!");
    txt->GetTextProperty()->SetFontSize(18);
    txt->GetTextProperty()->SetFontFamilyToArial();
    txt->GetTextProperty()->BoldOff();
    txt->GetTextProperty()->ItalicOn();
    txt->GetTextProperty()->ShadowOn();
    txt->GetTextProperty()->SetColor(0, 0, 1);
/*飞碟
  vtkSphereSource *sphere = vtkSphereSource::New();
    sphere->SetThetaResolution(10); 
	sphere->SetPhiResolution(10);
	sphere->SetRadius(100);

  vtkTransform *aTransform = vtkTransform::New();
    aTransform->Scale(1,1,0.2);

  vtkTransformFilter *transFilter = vtkTransformFilter::New();
    transFilter->SetInput(sphere->GetOutput());
    transFilter->SetTransform(aTransform); 

  vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
	mapper->SetInputConnection(transFilter->GetOutputPort());

  feidie = vtkActor::New();
    feidie->SetMapper(mapper);
*/
	//人
	vtk3DSImporter *importer2=vtk3DSImporter::New();
	  importer2-> ComputeNormalsOn();
	  importer2-> SetFileName ("workman.3ds");
	  importer2-> Read();
	
	feidie = importer2-> GetRenderer()->GetActors()->GetLastActor();


/////////////////////////
  vtkCallbackCommand * cmd1 = vtkCallbackCommand::New();
	cmd1->SetCallback(keypress);

	style-> AddObserver (vtkCommand::KeyPressEvent,cmd1);
/////////////////////////


////////////////////////
//方向
  vtkAxesActor* axes2 = vtkAxesActor::New();
	  axes2->SetShaftTypeToCylinder();
	  axes2->SetXAxisLabelText( "X" );
	  axes2->SetYAxisLabelText( "Y" );
	  axes2->SetZAxisLabelText( "Z" );

	  axes2->SetTotalLength( 1.5, 1.5, 1.5 );
	  axes2->SetCylinderRadius( 0.500 * axes2->GetCylinderRadius() );
	  axes2->SetConeRadius    ( 1.025 * axes2->GetConeRadius() );
	  axes2->SetSphereRadius  ( 1.500 * axes2->GetSphereRadius() );

  vtkTextProperty* tprop2 = axes2->GetXAxisCaptionActor2D()->GetCaptionTextProperty();
	  tprop2->ItalicOn();
	  tprop2->ShadowOn();
	  tprop2->SetFontFamilyToTimes();

	  axes2->GetYAxisCaptionActor2D()->GetCaptionTextProperty()->ShallowCopy( tprop2 );
	  axes2->GetZAxisCaptionActor2D()->GetCaptionTextProperty()->ShallowCopy( tprop2 );

  vtkOrientationMarkerWidget *widget = vtkOrientationMarkerWidget::New();
	widget->SetOutlineColor( 0.9300, 0.5700, 0.1300 );
	widget->SetOrientationMarker( axes2 );
	widget->SetInteractor( iren );
	widget->SetViewport( 0.85, 0.0, 1, 0.2 );
	widget->SetEnabled( 1 );
	widget->InteractiveOff();
	widget->InteractiveOn();

////////////////////////	
/*
  vtkTextProperty *tprop=vtkTextProperty::New();
    tprop-> SetColor(0, 0, 1);
    tprop-> ShadowOn();

  vtkCubeAxesActor2D *axes=vtkCubeAxesActor2D::New();
    axes-> SetInput ((vtkDataSet *)importer-> GetRenderer()->GetActors()->GetLastActor()->GetMapper()->GetInput());
    axes-> SetCamera (ren1-> GetActiveCamera());
    axes-> SetFlyModeToOuterEdges();
    axes-> SetFontFactor(0.8);
    axes-> SetAxisTitleTextProperty(tprop);
    axes-> SetAxisLabelTextProperty(tprop);
	axes->SetFontFactor (8);

    ren1->AddViewProp(axes);
*/

	ren1->AddActor(txt);
	ren1->AddActor(feidie);

	ren1->SetBackground( 0.0, 0.6, 1.0 );

  aCamera = vtkCamera::New();
	ren1->SetActiveCamera(aCamera);
	ren1->ResetCamera();
	aCamera->SetPosition(100,100,5);
	aCamera->SetFocalPoint(3100,100,5);
	aCamera->SetViewUp(0,0,1);
	feidie->SetPosition(1100,100,5);

  // record events
  recorder = vtkInteractorEventRecorder::New();
	  recorder->SetInteractor(iren);
	  recorder->ReadFromInputStringOn();
	  recorder->SetInputString(BoxWidgetEventLog);


	//调整视窗大小
    renWin->SetSize( 800, 600 );

	iren-> SetInteractorStyle(style);
	iren->Initialize();

	renWin->Render();

    recorder->Play();
    recorder->Off();

    iren->Start(); 

//	dr->Delete();
	ren1->Delete();
    renWin->Delete();
	iren->Delete();
    
	return 0;
}
void keypress(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
	char key=iren->GetKeyCode();
    double normal[3];			
	double focal[3];	
	double position[3]; 
	double view[3]; 
	
	switch (key)
    {
      case '8':
				aCamera->GetViewPlaneNormal (normal); 	
				aCamera->GetFocalPoint(focal);				   
				aCamera->GetPosition(position);

				position[0]=position[0]-pos*normal[0];
				position[1]=position[1]-pos*normal[1];
				//position[2]=position[2]-pos*normal[2];

				focal[0]=focal[0]-pos*normal[0];
				focal[1]=focal[1]-pos*normal[1];
				//focal[2]=focal[2]-pos*normal[2];

				aCamera->SetPosition(position);
				aCamera->SetFocalPoint(focal);

                break;
	  case '5':
				aCamera->GetViewPlaneNormal (normal); 
				aCamera->GetFocalPoint(focal);   
				aCamera->GetPosition(position);

				position[0]=position[0]+pos*normal[0];
				position[1]=position[1]+pos*normal[1];
				//position[2]=position[2]+pos*normal[2];

				focal[0]=focal[0]+pos*normal[0];
				focal[1]=focal[1]+pos*normal[1];
				//focal[2]=focal[2]+pos*normal[2];

				aCamera->SetPosition(position);
				aCamera->SetFocalPoint(focal);

                break;
	  case '6':		  		
				aCamera->Yaw (-3);
                break;
	  case '4':
				aCamera->Yaw (3);
                break;
	  case 'n':		  		
				aCamera->Pitch(-3);
                break;
	  case 'm':
				aCamera->Pitch(3);
                break;
	  case '+':
				pos=pos+1;
				printf("%d\n",pos);
				break;
	  case '-':
				pos=pos-1;
				printf("%d\n",pos);
				break;
	  case '.':
				aCamera->GetViewPlaneNormal (normal); 
				aCamera->GetFocalPoint(focal);				   

				focal[0]=focal[0]+normal[0];
				focal[1]=focal[1]+normal[1];
				focal[2]=focal[2]+normal[2];

				aCamera->SetFocalPoint(focal);	
				break;
	  case ',':
				aCamera->GetViewPlaneNormal (normal); 
				aCamera->GetFocalPoint(focal);				   

				focal[0]=focal[0]-normal[0];
				focal[1]=focal[1]-normal[1];
				focal[2]=focal[2]-normal[2];

				aCamera->SetFocalPoint(focal);
				break;				
	  case 'v':
				aCamera->SetViewUp(0,0,1);
				break;
	  case 'c':
	  case '0':
				aCamera->SetPosition(100,100,5);
				aCamera->SetFocalPoint(110,100,5);
				aCamera->SetViewUp(0,0,1);
				recorder->Play();
				recorder->Off();
				break;
	  case 'b':
				if (feidie->GetVisibility())
					feidie->VisibilityOff();
				else 
					feidie->VisibilityOn();
				break;
	  case '*'://上
		  
				aCamera->GetFocalPoint(focal);				   
				aCamera->GetPosition(position);

				position[2]=position[2]-pos/3.0;
				focal[2]=focal[2]-pos/3.0;

				aCamera->SetPosition(position);
				aCamera->SetFocalPoint(focal);

                break;
	  case '/'://下 
				aCamera->GetFocalPoint(focal);   
				aCamera->GetPosition(position);

				position[2]=position[2]+pos/3.0;
				focal[2]=focal[2]+pos/3.0;

				aCamera->SetPosition(position);
				aCamera->SetFocalPoint(focal);

                break;
	}

	aCamera->GetViewPlaneNormal (normal); 	
	aCamera->GetFocalPoint(focal);				   
	aCamera->GetPosition(position);
	aCamera->GetViewUp(view);
    double length;
	length=sqrt((focal[0]-position[0])*(focal[0]-position[0])+
		        (focal[1]-position[1])*(focal[1]-position[1])+
		        (focal[2]-position[2])*(focal[2]-position[2]));


	char text[300];
	sprintf(text," Distance of focus: %f\n normal: %f,%f,%f\n position: %f,%f,%f\n focal: %f,%f,%f\n viewup: %f,%f,%f\n",
		length,
		normal[0],normal[1],normal[2],
		position[0],position[1],position[2],
		focal[0],focal[1],focal[2],
		view[0],view[1],view[2]);
	txt->SetInput(text);

	if (feidie->GetVisibility())
	{
		double dp[3];
		dp[0]=position[0]*dis+focal[0]*(1-dis);
	 	dp[1]=position[1]*dis+focal[1]*(1-dis);		
		dp[2]=position[2]*dis+focal[2]*(1-dis);
		feidie->SetPosition(dp);
	}

	renWin->Render();
}


	
