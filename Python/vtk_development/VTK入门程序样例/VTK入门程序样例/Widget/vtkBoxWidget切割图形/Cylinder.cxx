/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: BoxWidget.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkAppendPolyData.h"
#include "vtkBoxWidget.h"
#include "vtkCommand.h"
#include "vtkConeSource.h"
#include "vtkGlyph3D.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkRenderer.h"
#include "vtkSphereSource.h"
#include "vtkTransform.h"
#include "vtkCallbackCommand.h"
#include "vtkRegressionTestImage.h"
#include "vtkDebugLeaks.h"

#include "vtkPlanes.h"
#include "vtkClipPolyData.h"
#include "vtkLODActor.h"
#include "vtkRegressionTestImage.h"
#include "vtkDebugLeaks.h"
#include "vtkProperty.h"
// Callback for the interaction
class vtkBWCallback : public vtkCommand
{
public:
  static vtkBWCallback *New() 
    { return new vtkBWCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkBoxWidget *boxWidget = reinterpret_cast<vtkBoxWidget*>(caller);
      boxWidget->GetPlanes(this->Planes);
      this->Actor->VisibilityOn();
    }
  vtkBWCallback():Planes(0),Actor(0) {}
  vtkPlanes  *Planes;
  vtkActor     *Actor;
};

#include "vtkRegressionTestImage.h"
#include "vtkDebugLeaks.h"


int main( int argc, char *argv[] )
{
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkBoxWidget *boxWidget = vtkBoxWidget::New();
    boxWidget->SetInteractor( iren );
    boxWidget->SetPlaceFactor( 1.25 );

  vtkConeSource *cone = vtkConeSource::New();
    cone->SetResolution(6);
  vtkSphereSource *sphere = vtkSphereSource::New();
    sphere->SetThetaResolution(8); sphere->SetPhiResolution(8);
  vtkGlyph3D *glyph = vtkGlyph3D::New();
    glyph->SetInputConnection(sphere->GetOutputPort());
    glyph->SetSource(cone->GetOutput());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleModeToScaleByVector();
    glyph->SetScaleFactor(0.25);
                                                        
  vtkAppendPolyData *append = vtkAppendPolyData::New();
    append->AddInput(glyph->GetOutput());
    append->AddInput(sphere->GetOutput());
  
  vtkPolyDataMapper *maceMapper = vtkPolyDataMapper::New();
    maceMapper->SetInputConnection(append->GetOutputPort());

  vtkActor *maceActor = vtkActor::New();
    maceActor->SetMapper(maceMapper);

//  renderer->AddActor(maceActor);
  renderer->SetBackground(0,0,0);
  renWin->SetSize(300,300);


vtkPlanes *planes=vtkPlanes::New();
  double ped[24];
  int i;
  for (i = 0; i < 6; ++i)
    {
    ped[i] = 0;
    }
  planes->SetFrustumPlanes(ped);


vtkClipPolyData *clipper=vtkClipPolyData::New();
    clipper-> SetInputConnection(append->GetOutputPort());
    clipper-> SetClipFunction(planes);
    clipper-> InsideOutOn();
vtkPolyDataMapper *selectMapper=vtkPolyDataMapper::New();
    selectMapper-> SetInputConnection(clipper-> GetOutputPort());
vtkLODActor *selectActor=vtkLODActor::New();
    selectActor-> SetMapper(selectMapper);
    selectActor-> GetProperty()-> SetColor( 1 ,1 ,0);
    selectActor-> VisibilityOff();
    selectActor-> SetScale(1.01,1.01,1.01);

renderer->AddActor(selectActor);

  // Configure the box widget including callbacks
  boxWidget->SetProp3D(selectActor);
  boxWidget->PlaceWidget();
  boxWidget-> GetPlanes(planes);

  vtkBWCallback *myCallback = vtkBWCallback::New();
  myCallback->Planes = planes;
  myCallback->Actor = selectActor;
  boxWidget->AddObserver(vtkCommand::InteractionEvent,myCallback);

  iren->Initialize();
  renWin->Render();

  iren->Start();

  //vtkCallbackCommand* callback = vtkCallbackCommand::New();
  //callback->SetClientData((void *)renWin);

  // Clean up
  myCallback->Delete();
  boxWidget->Delete();
  sphere->Delete();
  cone->Delete();
  glyph->Delete();
  append->Delete();
  maceMapper->Delete();
  maceActor->Delete();
  renderer->Delete();
  renWin->Delete();
  iren->Delete();

  return 0;
}
