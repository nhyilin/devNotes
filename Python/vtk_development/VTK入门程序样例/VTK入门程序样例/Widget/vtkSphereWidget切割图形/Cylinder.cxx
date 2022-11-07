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
#include "vtkSphereWidget.h"
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
#include "vtkSphere.h"

// Callback for the interaction
class vtkBWCallback : public vtkCommand
{
public:
  static vtkBWCallback *New() 
    { return new vtkBWCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkSphereWidget *sphereWidget = reinterpret_cast<vtkSphereWidget*>(caller);
      sphereWidget->GetSphere(this->Sphere);
      this->Actor->VisibilityOn();
    }
  vtkBWCallback():Sphere(0),Actor(0) {}
  vtkSphere  *Sphere;
  vtkActor     *Actor;
};

#include "vtkDebugLeaks.h"


int main( int argc, char *argv[] )
{
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkSphereWidget *sphereWidget = vtkSphereWidget::New();
    sphereWidget->SetInteractor( iren );
    sphereWidget->SetPlaceFactor( 1.25 );

  vtkConeSource *cone = vtkConeSource::New();
    cone->SetResolution(6);
  vtkSphereSource *spheres = vtkSphereSource::New();
    spheres->SetThetaResolution(8); 
	spheres->SetPhiResolution(8);
  vtkGlyph3D *glyph = vtkGlyph3D::New();
    glyph->SetInputConnection(spheres->GetOutputPort());
    glyph->SetSource(cone->GetOutput());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleModeToScaleByVector();
    glyph->SetScaleFactor(0.25);
                                                        
  vtkAppendPolyData *append = vtkAppendPolyData::New();
    append->AddInput(glyph->GetOutput());
    append->AddInput(spheres->GetOutput());
  
  vtkPolyDataMapper *maceMapper = vtkPolyDataMapper::New();
    maceMapper->SetInputConnection(append->GetOutputPort());

  vtkActor *maceActor = vtkActor::New();
    maceActor->SetMapper(maceMapper);

//  renderer->AddActor(maceActor);
  renderer->SetBackground(0,0,0);
  renWin->SetSize(300,300);


vtkSphere *sphere=vtkSphere::New();

vtkClipPolyData *clipper=vtkClipPolyData::New();
    clipper-> SetInputConnection(append->GetOutputPort());
    clipper-> SetClipFunction(sphere);
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
  sphereWidget->SetProp3D(selectActor);
  sphereWidget->SetThetaResolution(100); 
  sphereWidget->SetPhiResolution(100);
  sphereWidget->PlaceWidget();
  sphereWidget->GetSphere(sphere);
  sphereWidget->GetSphereProperty()-> SetColor( 0 ,0 ,1);
  sphereWidget->GetSelectedSphereProperty()-> SetColor( 1,0,0);

  vtkBWCallback *myCallback = vtkBWCallback::New();
  myCallback->Sphere = sphere;
  myCallback->Actor = selectActor;
  sphereWidget->AddObserver(vtkCommand::InteractionEvent,myCallback);

  iren->Initialize();
  renWin->Render();

  iren->Start();

  //vtkCallbackCommand* callback = vtkCallbackCommand::New();
  //callback->SetClientData((void *)renWin);

  // Clean up
  myCallback->Delete();
  sphereWidget->Delete();
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
