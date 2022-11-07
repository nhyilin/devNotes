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

// Callback for the interaction
class vtkBWCallback : public vtkCommand
{
public:
  static vtkBWCallback *New() 
    { return new vtkBWCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkBoxWidget *boxWidget = reinterpret_cast<vtkBoxWidget*>(caller);
      boxWidget->GetTransform(this->Transform);
      this->Actor->SetUserTransform(this->Transform);
    }
  vtkBWCallback():Transform(0),Actor(0) {}
  vtkTransform *Transform;
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

  renderer->AddActor(maceActor);
  renderer->SetBackground(0,0,0);
  renWin->SetSize(300,300);

  // Configure the box widget including callbacks
  vtkTransform *t = vtkTransform::New();
  boxWidget->SetProp3D(maceActor);
  boxWidget->PlaceWidget();

  vtkBWCallback *myCallback = vtkBWCallback::New();
  myCallback->Transform = t;
  myCallback->Actor = maceActor;
  boxWidget->AddObserver(vtkCommand::InteractionEvent,myCallback);

  iren->Initialize();
  renWin->Render();

  iren->Start();

  //vtkCallbackCommand* callback = vtkCallbackCommand::New();
  //callback->SetClientData((void *)renWin);

  // Clean up
  t->Delete();
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
