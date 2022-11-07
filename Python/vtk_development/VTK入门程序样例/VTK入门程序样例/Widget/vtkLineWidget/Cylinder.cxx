/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: TestLineWidget.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkActor.h"
#include "vtkCommand.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkLineWidget.h"
#include "vtkPLOT3DReader.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkRibbonFilter.h"
#include "vtkRungeKutta4.h"
#include "vtkStreamLine.h"
#include "vtkStructuredGrid.h"
#include "vtkStructuredGridOutlineFilter.h"

#include "vtkTestUtilities.h"
#include "vtkRegressionTestImage.h"
#include "vtkDebugLeaks.h"

class vtkLWCallback : public vtkCommand
{
public:
  static vtkLWCallback *New() 
    { return new vtkLWCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkLineWidget *lineWidget = reinterpret_cast<vtkLineWidget*>(caller);
      lineWidget->GetPolyData(this->PolyData);
      this->Actor->VisibilityOn();
    }
  vtkLWCallback():PolyData(0),Actor(0) {}
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

  vtkPolyData *seeds = vtkPolyData::New();

  // Create streamtues
  vtkRungeKutta4 *rk4 = vtkRungeKutta4::New();

  vtkStreamLine *streamer = vtkStreamLine::New();
	streamer->SetInputConnection(pl3d->GetOutputPort());
	streamer->SetSource(seeds);
	streamer->SetMaximumPropagationTime(100);
	streamer->SetIntegrationStepLength(.2);
	streamer->SetStepLength(.001);
	streamer->SetNumberOfThreads(1);
	streamer->SetIntegrationDirectionToForward();
	streamer->VorticityOn();
	streamer->SetIntegrator(rk4);

  vtkRibbonFilter *rf = vtkRibbonFilter::New();
	rf->SetInputConnection(streamer->GetOutputPort());
	rf->SetWidth(0.1);
	rf->SetWidthFactor(5);

  vtkPolyDataMapper *streamMapper = vtkPolyDataMapper::New();
	streamMapper->SetInputConnection(rf->GetOutputPort());
	double tmp[2];
	pl3d->GetOutput()->GetScalarRange(tmp);
	streamMapper->SetScalarRange(tmp[0], tmp[1]);

  vtkActor *streamline =vtkActor::New();
	streamline->SetMapper(streamMapper);
	streamline->VisibilityOff();

  // An outline is shown for context.
  vtkStructuredGridOutlineFilter *outline = 
    vtkStructuredGridOutlineFilter::New();
  outline->SetInputConnection(pl3d->GetOutputPort());

  vtkPolyDataMapper *outlineMapper = vtkPolyDataMapper::New();
    outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkActor *outlineActor = vtkActor::New();
    outlineActor->SetMapper(outlineMapper);

  vtkRenderer *ren1 = vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkLWCallback *myCallback = vtkLWCallback::New();
    myCallback->PolyData = seeds;
    myCallback->Actor = streamline;

  vtkLineWidget *lineWidget = vtkLineWidget::New();
	lineWidget->SetInteractor(iren);
	lineWidget->SetInput(pl3d->GetOutput());
	lineWidget->SetAlignToYAxis();
	lineWidget->PlaceWidget();
	lineWidget->GetPolyData(seeds);
	lineWidget->AddObserver(vtkCommand::InteractionEvent,myCallback);

  ren1->AddActor(streamline);
  ren1->AddActor(outlineActor);

  // Add the actors to the renderer, set the background and size
  //
  ren1->SetBackground(0.1, 0.2, 0.4);
  renWin->SetSize(300, 300);

  iren->Initialize();
  renWin->Render();

  iren->SetKeyCode('i');
  iren->InvokeEvent(vtkCommand::CharEvent,NULL);
  // Remove the observers so we can go interactive. Without this the "-I"
  // testing option fails.
  iren->Start();


  myCallback->Delete();
  seeds->Delete();
  lineWidget->Delete();
  pl3d->Delete();
  rk4->Delete();
  streamer->Delete();
  rf->Delete();
  streamMapper->Delete();
  streamline->Delete();
  outline->Delete();
  outlineMapper->Delete();
  outlineActor->Delete();
  iren->Delete();
  renWin->Delete();
  ren1->Delete();
  
  return 0;
}
