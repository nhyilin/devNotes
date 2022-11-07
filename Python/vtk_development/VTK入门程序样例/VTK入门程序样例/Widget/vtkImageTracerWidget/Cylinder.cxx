/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: TestImageTracerWidget.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkCamera.h"
#include "vtkCommand.h"
#include "vtkExtractVOI.h"
#include "vtkGlyphSource2D.h"
#include "vtkImageActor.h"
#include "vtkImageData.h"
#include "vtkImageShiftScale.h"
#include "vtkImageStencil.h"
#include "vtkImageTracerWidget.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkInteractorStyleImage.h"
#include "vtkLinearExtrusionFilter.h"
#include "vtkMapper.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataToImageStencil.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSplineWidget.h"
#include "vtkVolume16Reader.h"

#include "vtkTestUtilities.h"
#include "vtkRegressionTestImage.h"
#include "vtkDebugLeaks.h"

// Callback for the tracer interaction
class vtkITWCallback : public vtkCommand
{
public:
  static vtkITWCallback *New()
    { return new vtkITWCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkImageTracerWidget *tracerWidget =
        reinterpret_cast<vtkImageTracerWidget*>(caller);
      if(!tracerWidget) { return; }

      int closed = tracerWidget->IsClosed();
      SplineWidget->SetClosed(closed);

      if (!closed)
        {
        Actor->SetInput(Extract->GetOutput());
        }

      int npts = tracerWidget->GetNumberOfHandles();
      if (npts < 2) { return; }

      tracerWidget->GetPath(PathPoly);
      vtkPoints* points = PathPoly->GetPoints();
      if (!points){ return; }

      SplineWidget->InitializeHandles(points);

      if (closed)
        {
        SplineWidget->GetPolyData(SplinePoly);
        Stencil->Update();  
        Actor->SetInput(Stencil->GetOutput());        
        }
    }

  vtkITWCallback():SplineWidget(0),Actor(0),Stencil(0),Extract(0),
                   PathPoly(0),SplinePoly(0){}

  vtkSplineWidget *SplineWidget;
  vtkImageActor   *Actor;
  vtkImageStencil *Stencil;
  vtkExtractVOI   *Extract;
  vtkPolyData     *PathPoly;
  vtkPolyData     *SplinePoly;
};

// Callback for the spline interaction.
// Note: this callback has to have a name different from that already
// used in another test: see TestSplineWidget.cxx!
class vtkSW2Callback : public vtkCommand
{
public:
  static vtkSW2Callback *New()
    { return new vtkSW2Callback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkSplineWidget *splineWidget =
        reinterpret_cast<vtkSplineWidget*>(caller);
      if(!splineWidget) { return; }

      int npts = splineWidget->GetNumberOfHandles();
      int closed = splineWidget->IsClosed();

      Points->Reset();
      for (int i = 0; i < npts; ++i)
        {
        Points->InsertNextPoint(splineWidget->GetHandlePosition(i));
        }

      if (closed)
        {
        if (TracerWidget->GetAutoClose())
          { 
          Points->InsertNextPoint(splineWidget->GetHandlePosition(0));
          }
         splineWidget->GetPolyData(SplinePoly);
         Stencil->Update();
         Actor->SetInput(Stencil->GetOutput());        
        }

      TracerWidget->InitializeHandles(Points);
    }

  vtkSW2Callback():Points(0),TracerWidget(0),Actor(0),Stencil(0),SplinePoly(0){}

  vtkPoints            *Points;
  vtkImageTracerWidget *TracerWidget;
  vtkImageActor        *Actor;
  vtkImageStencil      *Stencil;
  vtkPolyData          *SplinePoly;
};

int main( int argc, char *argv[] )
{
  char* fname = vtkTestUtilities::ExpandDataFileName(argc, argv, "Data/headsq/quarter");

 // Increase polygon offsets to support some OpenGL drivers
  vtkMapper::SetResolveCoincidentTopologyToPolygonOffset();
  vtkMapper::SetResolveCoincidentTopologyPolygonOffsetParameters(10,10);

// Start by loading some data.
//
  vtkVolume16Reader* v16 = vtkVolume16Reader::New();
    v16->SetDataDimensions(64, 64);
    v16->SetDataByteOrderToLittleEndian();
    v16->SetImageRange(1, 93);
    v16->SetDataSpacing(3.2, 3.2, 1.5);
    v16->SetFilePrefix("e://ct/headsq/quarter");
    v16->ReleaseDataFlagOn();
    v16->SetDataMask(0x7fff);
    v16->Update();

  delete[] fname;

  vtkRenderer* ren1 = vtkRenderer::New();
  vtkRenderer* ren2 = vtkRenderer::New();

  vtkRenderWindow* renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
    renWin->AddRenderer(ren2);

  vtkInteractorStyleImage* interactorStyle = vtkInteractorStyleImage::New();

  vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::New();
    iren->SetInteractorStyle(interactorStyle);
    iren->SetRenderWindow(renWin);

  double range[2];
  v16->GetOutput()->GetScalarRange(range);

  vtkImageShiftScale* shifter = vtkImageShiftScale::New();
    shifter->SetShift(-1.0*range[0]);
    shifter->SetScale(255.0/(range[1]-range[0]));
    shifter->SetOutputScalarTypeToUnsignedChar();
    shifter->SetInputConnection(v16->GetOutputPort());
    shifter->ReleaseDataFlagOff();
    shifter->Update();

// Display a y-z plane.
//
  vtkImageActor* imageActor1 = vtkImageActor::New();
    imageActor1->SetInput(shifter->GetOutput());
    imageActor1->VisibilityOn();
    imageActor1->SetDisplayExtent(31, 31, 0, 63, 0, 92);
    imageActor1->InterpolateOff();

  vtkExtractVOI* extract = vtkExtractVOI::New();
    extract->SetVOI(imageActor1->GetDisplayExtent());
    extract->SetSampleRate(1, 1, 1);
    extract->SetInputConnection(shifter->GetOutputPort());
    extract->ReleaseDataFlagOff();

  vtkImageActor* imageActor2 = vtkImageActor::New();
    imageActor2->SetInput(extract->GetOutput());
    imageActor2->VisibilityOn();
    imageActor2->SetDisplayExtent(extract->GetVOI());
    imageActor2->InterpolateOff();

// Set up the image tracer widget
//
  vtkImageTracerWidget* imageTracerWidget = vtkImageTracerWidget::New();
    imageTracerWidget->SetDefaultRenderer(ren1);
    imageTracerWidget->SetCaptureRadius(1.5);
    imageTracerWidget->GetGlyphSource()->SetColor(1, 0, 0);
    imageTracerWidget->GetGlyphSource()->SetScale(3.0);
    imageTracerWidget->GetGlyphSource()->SetRotationAngle(45.0);
    imageTracerWidget->GetGlyphSource()->Modified();
    imageTracerWidget->ProjectToPlaneOn();
    imageTracerWidget->SetProjectionNormalToXAxes();
    imageTracerWidget->SetProjectionPosition(imageActor1->GetBounds()[0]);
    imageTracerWidget->SetViewProp(imageActor1);
    imageTracerWidget->SetInput(shifter->GetOutput());
    imageTracerWidget->SetInteractor(iren);
    imageTracerWidget->PlaceWidget();
    imageTracerWidget->SnapToImageOff();
    imageTracerWidget->AutoCloseOn();

// Set up a vtkSplineWidget in the second renderer and have
// its handles set by the tracer widget.
//
  vtkSplineWidget* splineWidget = vtkSplineWidget::New();
    splineWidget->SetCurrentRenderer(ren2);
    splineWidget->SetDefaultRenderer(ren2);
    splineWidget->SetInput(extract->GetOutput());
    splineWidget->SetInteractor(iren);
    splineWidget->PlaceWidget(imageActor2->GetBounds());
    splineWidget->ProjectToPlaneOn();
    splineWidget->SetProjectionNormalToXAxes();
    splineWidget->SetProjectionPosition(imageActor2->GetBounds()[0]);

  vtkPolyData* pathPoly = vtkPolyData::New();
  vtkPoints* points = vtkPoints::New();
  vtkPolyData* splinePoly = vtkPolyData::New();

// Set up a pipleline to demonstrate extraction of a 2D
// region of interest.
//
  vtkLinearExtrusionFilter* extrude = vtkLinearExtrusionFilter::New();
    extrude->SetInput(splinePoly);
    extrude->SetScaleFactor(1);
    extrude->SetExtrusionTypeToNormalExtrusion();
    extrude->SetVector(1, 0, 0);

  vtkPolyDataToImageStencil* dataToStencil = vtkPolyDataToImageStencil::New();
    dataToStencil->SetInputConnection(extrude->GetOutputPort());

  vtkImageStencil* stencil = vtkImageStencil::New();
    stencil->SetInputConnection(extract->GetOutputPort());
    stencil->SetStencil(dataToStencil->GetOutput());
    stencil->ReverseStencilOff();
    stencil->SetBackgroundValue(128);

// Set up callbacks for widget interactions.
//
  vtkITWCallback* itwCallback = vtkITWCallback::New();
    itwCallback->SplineWidget = splineWidget;
    itwCallback->Actor = imageActor2;
    itwCallback->Stencil = stencil;
    itwCallback->Extract = extract;
    itwCallback->PathPoly = pathPoly;
    itwCallback->SplinePoly = splinePoly;

  imageTracerWidget->AddObserver(vtkCommand::EndInteractionEvent,itwCallback);

  vtkSW2Callback* swCallback = vtkSW2Callback::New();
    swCallback->Points = points;
    swCallback->TracerWidget = imageTracerWidget;
    swCallback->Actor = imageActor2;
    swCallback->Stencil = stencil;
    swCallback->SplinePoly = splinePoly;

  splineWidget->AddObserver(vtkCommand::EndInteractionEvent,swCallback);

  ren1->SetBackground(0.4, 0.4, 0.5);
  ren1->SetViewport(0, 0, 0.5, 1);
  ren1->AddViewProp(imageActor1);
  ren2->SetBackground(0.5, 0.4, 0.4);
  ren2->SetViewport(0.5, 0, 1, 1);
  ren2->AddViewProp(imageActor2);

  ren1->ResetCamera();
  ren2->ResetCamera();
  renWin->SetSize(480, 240);

  imageTracerWidget->On();
  splineWidget->On();

  vtkCamera* cam = ren1->GetActiveCamera();
  cam->SetViewUp(0, 1, 0);
  cam->Azimuth(270);
  cam->Roll(270);
  cam->Dolly(1.7);
  ren1->ResetCameraClippingRange();

  cam = ren2->GetActiveCamera();
  cam->SetViewUp(0, 1, 0);
  cam->Azimuth(270);
  cam->Roll(270);
  cam->Dolly(1.7);
  ren2->ResetCameraClippingRange();

  iren->Initialize();

  renWin->Render();
    
  iren->Start();

  v16->Delete();
  shifter->Delete();
  extract->Delete();
  extrude->Delete();
  dataToStencil->Delete();
  stencil->Delete();
  imageActor1->Delete();
  imageActor2->Delete();
  pathPoly->Delete();
  points->Delete();
  splinePoly->Delete();
  imageTracerWidget->RemoveObserver(itwCallback);
  imageTracerWidget->Delete();
  itwCallback->Delete();
  splineWidget->RemoveObserver(swCallback);
  splineWidget->Delete();
  swCallback->Delete();
  interactorStyle->Delete();
  iren->Delete();
  renWin->Delete();
  ren1->Delete();
  ren2->Delete();

  return 0;
}
