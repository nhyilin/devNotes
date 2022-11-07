

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkConeSource.h"
#include "vtkGlyph3D.h"
#include "vtkCamera.h"

#include "vtkTextMapper.h"
#include "vtkScaledTextActor.h"
#include "vtkProperty.h"
#include "vtkCellPicker.h"
#include "vtkCallbackCommand.h"
#include "vtkActor2D.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkTextProperty.h"

vtkRenderWindow *renWin;
vtkCellPicker *picker;
vtkInteractorStyleTrackballCamera *style;
vtkTextMapper *textMapper;
vtkActor2D *textActor;
vtkRenderer *ren1;
vtkRenderWindowInteractor *iren;
int MouseMotion;

void MyExecute(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata);
void cbLBR (vtkObject *caller, unsigned long eid, void *clientdata, void *calldata);
void left(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata);
void move(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata);

void main( int argc, char *argv[] )
{
  ren1 = vtkRenderer::New();
  renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkSphereSource *sphere = vtkSphereSource::New();
    sphere->SetThetaResolution(7); 
	sphere->SetPhiResolution(7);
  vtkPolyDataMapper *sphereMapper = vtkPolyDataMapper::New();
    sphereMapper->SetInput(sphere->GetOutput());
  vtkActor *sphereActor = vtkActor::New();
    sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetColor(0.8,0.1,0.8);

  vtkConeSource *cone = vtkConeSource::New();
    cone->SetResolution(20);
  vtkGlyph3D *glyph = vtkGlyph3D::New();
    glyph->SetInput((vtkDataSet *)sphere->GetOutput());
    glyph->SetSource(cone->GetOutput());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleModeToScaleByVector();
    glyph->SetScaleFactor(0.25);
  vtkPolyDataMapper *spikeMapper = vtkPolyDataMapper::New();
    spikeMapper->SetInput(glyph->GetOutput());
  vtkActor *spikeActor = vtkActor::New();
    spikeActor->SetMapper(spikeMapper);

  picker=vtkCellPicker::New();

  vtkCallbackCommand * cmd = vtkCallbackCommand::New();
	cmd->SetCallback(MyExecute);
	picker->AddObserver(vtkCommand::EndPickEvent, cmd);
	iren->SetPicker(picker);

  vtkCallbackCommand * cmd1 = vtkCallbackCommand::New();
	cmd1->SetCallback(cbLBR);

  vtkCallbackCommand * cmd2 = vtkCallbackCommand::New();
	cmd2->SetCallback(left);

  vtkCallbackCommand * cmd3 = vtkCallbackCommand::New();
	cmd3->SetCallback(move);

// Create a text mapper and actor to display the results of picking.
  textMapper=vtkTextMapper::New();
    textMapper->GetTextProperty()->SetFontFamilyToArial();
    textMapper->GetTextProperty()->SetFontSize( 10);
    textMapper->GetTextProperty()->BoldOn();
    textMapper->GetTextProperty()->ShadowOn();
    textMapper->GetTextProperty()->SetColor( 1 ,0 ,0 );

  textActor=vtkActor2D::New();
    textActor-> VisibilityOff();
    textActor-> SetMapper(textMapper);

  style=vtkInteractorStyleTrackballCamera::New();
   style-> AddObserver (vtkCommand::LeftButtonPressEvent,cmd2);
   style-> AddObserver (vtkCommand::MouseMoveEvent, cmd3);
   style-> AddObserver (vtkCommand::LeftButtonReleaseEvent,cmd1);
//    style-> AddObserver (vtkCommand::LeftButtonPressEvent, cmd);


  ren1->AddActor(sphereActor);
  ren1->AddActor(spikeActor);
  ren1->AddActor2D(textActor);
  ren1->SetBackground(0,0,0);
  renWin->SetSize(300,300);

  renWin->Render();
  ren1->GetActiveCamera()->Zoom(1.4);
  renWin->Render();
  
  iren-> SetInteractorStyle(style);
  iren->Start();

  ren1->Delete();
  renWin->Delete();
  iren->Delete();
  sphere->Delete();
  sphereMapper->Delete();
  sphereActor->Delete();
  cone->Delete();
  glyph->Delete();
  spikeMapper->Delete();
  spikeActor->Delete();
}

void MyExecute(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
  double globalCoordinate[3]; //拾取点的屏幕坐标和全局坐标
  double selPt[2];

  if (picker->GetCellId() < 0 )
  {
	picker->GetSelectionPoint(selPt);
    picker->GetPickPosition(globalCoordinate);	//得到全局坐标
	char str[50];
    sprintf(str,"Out: %f, %f, %f",
		globalCoordinate[0],globalCoordinate[1],globalCoordinate[2]);
	textMapper-> SetInput(str);
	textActor-> SetPosition(selPt[0],selPt[1]);
	textActor-> VisibilityOn();
  }
  else 
  {
	picker->GetSelectionPoint(selPt);
    picker->GetPickPosition(globalCoordinate);	//得到全局坐标
	char str[50];
    sprintf(str,"In: %f, %f, %f",
		globalCoordinate[0],globalCoordinate[1],globalCoordinate[2]);
	textMapper-> SetInput(str);
	textActor-> SetPosition(selPt[0],selPt[1]);
	textActor-> VisibilityOn();
  }
  renWin->Render();
}

void cbLBR (vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
 {
//  if (MouseMotion == 0)
  {
    picker->Pick(iren->GetEventPosition()[0],iren->GetEventPosition()[1],0, ren1);
  }
 // Do the default things for the trackball style
  style->OnLeftButtonUp ();
}

void left(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
	MouseMotion=0;
	style->OnLeftButtonDown();
}

void move(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
	MouseMotion=1;
	style->OnMouseMove();
}