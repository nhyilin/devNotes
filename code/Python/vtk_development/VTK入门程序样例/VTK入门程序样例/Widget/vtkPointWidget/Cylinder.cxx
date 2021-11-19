/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: TestPointWidget.cxx,v $

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
#include "vtkPointWidget.h"
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
class vtkmyPWCallback : public vtkCommand
{
public:
  static vtkmyPWCallback *New() 
    { return new vtkmyPWCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkPointWidget *pointWidget = reinterpret_cast<vtkPointWidget*>(caller);
          pointWidget->GetPolyData(this->PolyData);
      pointWidget->GetPolyData(this->PolyData);
      this->Actor->VisibilityOn();
    }
  vtkmyPWCallback():PolyData(0),Actor(0) {}
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

  vtkPolyData *point = vtkPolyData::New();

  vtkProbeFilter *probe = vtkProbeFilter::New();
  probe->SetInput(point);
  probe->SetSource(pl3d->GetOutput());

  // create glyph
  vtkConeSource *cone = vtkConeSource::New();
  cone->SetResolution(16);

  vtkGlyph3D *glyph = vtkGlyph3D::New();
  glyph->SetInputConnection(probe->GetOutputPort());
  glyph->SetSource(cone->GetOutput());
  glyph->SetVectorModeToUseVector();
  glyph->SetScaleModeToDataScalingOff();
  glyph->SetScaleFactor(pl3d->GetOutput()->GetLength() * 0.1);

  vtkPolyDataMapper *glyphMapper = vtkPolyDataMapper::New();
  glyphMapper->SetInputConnection(glyph->GetOutputPort());

  vtkActor *glyphActor = vtkActor::New();
  glyphActor->SetMapper(glyphMapper);
  glyphActor->VisibilityOff();

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
  vtkmyPWCallback *myCallback = vtkmyPWCallback::New();
  myCallback->PolyData = point;
  myCallback->Actor = glyphActor;

  // The plane widget is used probe the dataset.
  //
  vtkPointWidget *pointWidget = vtkPointWidget::New();
  pointWidget->SetInteractor(iren);
  pointWidget->SetInput(pl3d->GetOutput());
  pointWidget->AllOff();
  pointWidget->PlaceWidget();
  pointWidget->AddObserver(vtkCommand::InteractionEvent,myCallback);

  ren1->AddActor(outlineActor);
  ren1->AddActor(glyphActor);

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
  pointWidget->Delete();
  pl3d->Delete();
  point->Delete();
  probe->Delete();
  cone->Delete();
  glyph->Delete();
  glyphMapper->Delete();
  glyphActor->Delete();
  outline->Delete();
  outlineMapper->Delete();
  outlineActor->Delete();
  iren->Delete();
  renWin->Delete();
  ren1->Delete();
  
  return 0;
}
