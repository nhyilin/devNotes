/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: TestPlaneWidget.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkActor.h"
#include "vtkCommand.h"
#include "vtkConeSource.h"
#include "vtkGlyph3D.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkPLOT3DReader.h"
#include "vtkPlaneWidget.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkProbeFilter.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkStructuredGrid.h"
#include "vtkStructuredGridOutlineFilter.h"

#include "vtkTestUtilities.h"
#include "vtkRegressionTestImage.h"
#include "vtkDebugLeaks.h"

// This does the actual work: updates the probe.
// Callback for the interaction
class vtkTPWCallback : public vtkCommand
{
public:
  static vtkTPWCallback *New() 
    { return new vtkTPWCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkPlaneWidget *planeWidget = reinterpret_cast<vtkPlaneWidget*>(caller);
      planeWidget->GetPolyData(this->PolyData);
      this->Actor->VisibilityOn();
    }
  vtkTPWCallback():PolyData(0),Actor(0) {}
  vtkPolyData *PolyData;
  vtkActor *Actor;
};

int main( int argc, char *argv[] )
{

  vtkPLOT3DReader *pl3d = vtkPLOT3DReader::New();
  pl3d->SetXYZFileName("combxyz.bin");
  pl3d->SetQFileName("combq.bin");
  pl3d->SetScalarFunctionNumber(100);
  pl3d->SetVectorFunctionNumber(202);
  pl3d->Update();


  vtkPolyData *plane = vtkPolyData::New();

  vtkProbeFilter *probe = vtkProbeFilter::New();
  probe->SetInput(plane);
  probe->SetSource(pl3d->GetOutput());

  vtkPolyDataMapper *probeMapper = vtkPolyDataMapper::New();
  probeMapper->SetInput(probe->GetPolyDataOutput());
  double tmp[2];
  pl3d->GetOutput()->GetScalarRange(tmp);
  probeMapper->SetScalarRange(tmp[0], tmp[1]);
  
  vtkActor *probeActor = vtkActor::New();
  probeActor->SetMapper(probeMapper);
  probeActor->VisibilityOff();

  // An outline is shown for context.
  vtkStructuredGridOutlineFilter *outline = 
    vtkStructuredGridOutlineFilter::New();
  outline->SetInputConnection(pl3d->GetOutputPort());

  vtkPolyDataMapper *outlineMapper = vtkPolyDataMapper::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkActor *outlineActor = vtkActor::New();
  outlineActor->SetMapper(outlineMapper);

  // Create the RenderWindow, Renderer and both Actors
  //
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer(ren1);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow(renWin);

  // The SetInteractor method is how 3D widgets are associated with the render
  // window interactor. Internally, SetInteractor sets up a bunch of callbacks
  // using the Command/Observer mechanism (AddObserver()).
  vtkTPWCallback *myCallback = vtkTPWCallback::New();
  myCallback->PolyData = plane;
  myCallback->Actor = probeActor;

  // The plane widget is used probe the dataset.
  //
  vtkPlaneWidget *planeWidget = vtkPlaneWidget::New();
  planeWidget->SetInteractor(iren);
  planeWidget->SetInput(pl3d->GetOutput());
  planeWidget->NormalToXAxisOn();
  planeWidget->SetResolution(20);
  planeWidget->SetRepresentationToOutline();
  planeWidget->PlaceWidget();
  planeWidget->AddObserver(vtkCommand::InteractionEvent,myCallback);

  ren1->AddActor(probeActor);
  ren1->AddActor(outlineActor);

  // Add the actors to the renderer, set the background and size
  //
  ren1->SetBackground(0.1, 0.2, 0.4);
  renWin->SetSize(300, 300);

  // render the image
  //
  iren->Initialize();
  renWin->Render();

  iren->Start();

  myCallback->Delete();
  planeWidget->Delete();
  pl3d->Delete();
  plane->Delete();
  probe->Delete();
  probeMapper->Delete();
  probeActor->Delete();
  outline->Delete();
  outlineMapper->Delete();
  outlineActor->Delete();
  iren->Delete();
  renWin->Delete();
  ren1->Delete();
  
  return 0;
}
