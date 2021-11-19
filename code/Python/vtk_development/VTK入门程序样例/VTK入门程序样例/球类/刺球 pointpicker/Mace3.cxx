

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
#include "vtkPointPicker.h"
#include "vtkCallbackCommand.h"

vtkRenderWindow *renWin;
vtkPointPicker *picker;
vtkTextMapper *textActor;

void MyExecute(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata);

void main( int argc, char *argv[] )
{
  vtkRenderer *ren1 = vtkRenderer::New();
  renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
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

  picker=vtkPointPicker::New();

  vtkCallbackCommand * cmd = vtkCallbackCommand::New();
	cmd->SetCallback(MyExecute);
	picker->AddObserver(vtkCommand::EndPickEvent, cmd);

	iren->SetPicker(picker);


  textActor=vtkTextMapper::New();
    textActor->SetInput ("This is a sphere");

  vtkScaledTextActor *mmm=vtkScaledTextActor::New();
	mmm->SetMapper(textActor);
	mmm->SetDisplayPosition(90, 50 );

  ren1->AddActor(sphereActor);
  ren1->AddActor(spikeActor);
  ren1->AddActor2D(mmm);
  ren1->SetBackground(0,0,0);
  renWin->SetSize(300,300);

  renWin->Render();
  ren1->GetActiveCamera()->Zoom(1.4);
  renWin->Render();
  
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

  if (picker->GetPointId() < 0 )
  {
    textActor->SetInput ("OUT");
	picker->GetPickPosition(globalCoordinate);	//得到全局坐标
    printf("The point you picked is: %f, %f, %f, \n",
		globalCoordinate[0],globalCoordinate[1],globalCoordinate[2]);
  }
  else 
  {
    textActor->SetInput ("IN");	
    picker->GetPickPosition(globalCoordinate);	//得到全局坐标
    printf("The point you picked is: %f, %f, %f, \n",
		globalCoordinate[0],globalCoordinate[1],globalCoordinate[2]);	
  }
  renWin->Render();
}
