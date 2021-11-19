//
// cut an outer sphere to reveal an inner sphere
//

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkPlanes.h"
#include "vtkPoints.h"
#include "vtkLineSource.h"
#include "vtkImplicitTextureCoords.h"
#include "vtkDataSetMapper.h"
#include "vtkStructuredPointsReader.h"
#include "vtkTexture.h"
#include "vtkProperty.h"
#include "vtkPolyDataMapper.h"
#include "vtkVectorText.h"
#include "vtkFollower.h"
#include "vtkCamera.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkCallbackCommand.h"
#include "vtkTextProperty.h" 
#include "vtkOrientationMarkerWidget.h"
#include "vtkAxesActor.h"
#include "vtkCaptionActor2D.h"

vtkLineSource *linex;
vtkLineSource *liney;
vtkLineSource *linez;
vtkActor *innerSphere;
vtkRenderWindowInteractor *iren;
vtkRenderWindow *renWin;
vtkVectorText *Text;
vtkFollower *TextActor;
double position[3];
char textshow[40];

void keypress(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata);

void main( )
{
  vtkRenderer *aren = vtkRenderer::New();
  renWin = vtkRenderWindow::New();
    renWin->AddRenderer(aren);
  iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);
  vtkInteractorStyleTrackballCamera *style=vtkInteractorStyleTrackballCamera::New();
    iren-> SetInteractorStyle(style);

  // hidden sphere
  vtkSphereSource *sphere = vtkSphereSource::New();
    sphere->SetThetaResolution(12); 
	sphere->SetPhiResolution(12);
    sphere->SetRadius(0.5);

  vtkPolyDataMapper *innerMapper = vtkPolyDataMapper::New();
    innerMapper->SetInput(sphere->GetOutput());

  innerSphere = vtkActor::New();
    innerSphere->SetMapper(innerMapper);
    innerSphere->GetProperty()->SetColor (1,1,1);

////////////////////////

    innerSphere-> GetPosition(position);

//x
    linex=vtkLineSource::New(); 
	  linex->SetResolution(20);
	  linex->SetPoint1 (position[0]+5, position[1], position[2]);
	  linex->SetPoint2 (position[0]-5, position[1], position[2]);

	vtkPolyDataMapper *lineMapperx = vtkPolyDataMapper::New();
	  lineMapperx->SetInput(linex->GetOutput());
	
	vtkActor *lineActorx = vtkActor::New();
	  lineActorx->SetMapper(lineMapperx); 
 	  lineActorx->GetProperty()->SetDiffuseColor(1,0,0);
//y
    liney=vtkLineSource::New(); 
	  liney->SetResolution(20);
	  liney->SetPoint1 (position[0], position[1]+5, position[2]);
	  liney->SetPoint2 (position[0], position[1]-5, position[2]);

	vtkPolyDataMapper *lineMappery = vtkPolyDataMapper::New();
	  lineMappery->SetInput(liney->GetOutput());
	
	vtkActor *lineActory = vtkActor::New();
	  lineActory->SetMapper(lineMappery); 
 	  lineActory->GetProperty()->SetDiffuseColor(0,1,0);
//z
    linez=vtkLineSource::New(); 
	  linez->SetResolution(20);
	  linez->SetPoint1 (position[0], position[1], position[2]+5);
	  linez->SetPoint2 (position[0], position[1], position[2]-5);

	vtkPolyDataMapper *lineMapperz = vtkPolyDataMapper::New();
	  lineMapperz->SetInput(linez->GetOutput());
	
	vtkActor *lineActorz = vtkActor::New();
	  lineActorz->SetMapper(lineMapperz); 
 	  lineActorz->GetProperty()->SetDiffuseColor(0,0,1);

	sprintf(textshow,"     X:%.2f,Y:%.2f,Z:%.2f",position[0], position[1], position[2]);

    Text=vtkVectorText::New();
      Text-> SetText(textshow);

    vtkPolyDataMapper *TextMapper=vtkPolyDataMapper::New();
      TextMapper-> SetInputConnection (Text-> GetOutputPort());

    TextActor=vtkFollower::New();
      TextActor-> SetMapper (TextMapper);
      TextActor-> SetScale (0.3, .3, .3);
      TextActor-> SetPosition (position);
      TextActor-> GetProperty()-> SetColor (1, 1, 0);

////////////////////////
//·½Ïò
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
	widget->SetViewport( 0.75, 0.0, 1, 0.25 );
	widget->SetEnabled( 1 );
	widget->InteractiveOff();
	widget->InteractiveOn();

////////////////////////


  aren->AddActor(innerSphere);
  aren->AddActor(lineActorx);
  aren->AddActor(lineActory);
  aren->AddActor(lineActorz);
  aren->AddActor(TextActor);
  aren->SetBackground (0,0,0);
  renWin->SetSize(600,600);

//////////½»»¥
  vtkCallbackCommand * cmd = vtkCallbackCommand::New();
	cmd->SetCallback(keypress);
	style-> AddObserver (vtkCommand::KeyPressEvent,cmd);

  aren->ResetCamera();
  // interact with data
  renWin->Render();

  TextActor->SetCamera(aren->GetActiveCamera());


  iren->Start();

  // Clean up
  aren->Delete();
  renWin->Delete();
  iren->Delete();
  sphere->Delete();
  innerMapper->Delete();
  innerSphere->Delete();
  TextActor->Delete();
  Text->Delete();
  TextMapper->Delete();
  linex->Delete();
  liney->Delete();
  linez->Delete();
  lineActorx->Delete();
  lineActory->Delete();
  lineActorz->Delete();
  lineMapperx->Delete();
  lineMappery->Delete();
  lineMapperz->Delete();

}

void keypress(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{	
//	double position[3]; 
	char key=iren->GetKeyCode();
	innerSphere-> GetPosition(position);
	switch (key)
    {
      case '1':
				position[0]=position[0]+0.5;
                break;
      case '2':
				position[0]=position[0]-0.5;
                break;
      case '4':
				position[1]=position[1]+0.5;
                break;
      case '5':
				position[1]=position[1]-0.5;
                break;
      case '7':
				position[2]=position[2]+0.5;
                break;
      case '8':
				position[2]=position[2]-0.5;
                break;
	}

	switch (key)
    {
      case '1':
      case '2':
      case '4':
      case '5':
      case '7':
      case '8':
		    innerSphere-> SetPosition(position);

			linex->SetPoint1 (position[0]+5, position[1], position[2]);
			linex->SetPoint2 (position[0]-5, position[1], position[2]);

			liney->SetPoint1 (position[0], position[1]+5, position[2]);
			liney->SetPoint2 (position[0], position[1]-5, position[2]);


			linez->SetPoint1 (position[0], position[1], position[2]+5);
			linez->SetPoint2 (position[0], position[1], position[2]-5);

			sprintf(textshow,"     X:%.2f,Y:%.2f,Z:%.2f",position[0], position[1], position[2]);
			Text-> SetText(textshow);
			TextActor-> SetPosition (position);

			renWin->Render();
			break;
	}
}