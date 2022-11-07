#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkCommand.h"
#include "vtkImageData.h"
#include "vtkImagePlaneWidget.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkKochanekSpline.h"
#include "vtkOutlineFilter.h"
#include "vtkParametricSpline.h"
#include "vtkPlaneSource.h"
#include "vtkPointData.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkProbeFilter.h"
#include "vtkProperty.h"
#include "vtkProperty2D.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkSplineWidget.h"
#include "vtkTextProperty.h"
#include "vtkVolume16Reader.h"
#include "vtkXYPlotActor.h"

#include "vtkTestUtilities.h"
#include "vtkRegressionTestImage.h"
#include "vtkDebugLeaks.h"

// Callback for the image plane widget interaction
class vtkIPWCallback : public vtkCommand
{
public:
  static vtkIPWCallback *New()
    { return new vtkIPWCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkImagePlaneWidget *planeWidget = reinterpret_cast<vtkImagePlaneWidget*>(caller);
      if(planeWidget->GetPlaneOrientation() == 3)
        {
        Spline->SetProjectionPosition(0);
        }
      else
        {
        Spline->SetProjectionPosition(planeWidget->GetSlicePosition());
        }
      Spline->GetPolyData(Poly);
    }
  vtkIPWCallback():Spline(0),Poly(0){};
  vtkSplineWidget* Spline;
  vtkPolyData* Poly;
};

// Callback for the spline widget interaction
class vtkSWCallback : public vtkCommand
{
public:
  static vtkSWCallback *New()
    { return new vtkSWCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkSplineWidget *spline = reinterpret_cast<vtkSplineWidget*>(caller);
      spline->GetPolyData(Poly);
    }
  vtkSWCallback():Poly(0){};
  vtkPolyData* Poly;
};

int main( int argc, char *argv[] )
{
  vtkVolume16Reader* v16 = vtkVolume16Reader::New();
    v16->SetDataDimensions(64, 64);
    v16->SetDataByteOrderToLittleEndian();
    v16->SetImageRange(1, 93);
    v16->SetDataSpacing(3.2, 3.2, 1.5);
    v16->SetFilePrefix("e://ct/headsq/quarter");
    v16->ReleaseDataFlagOn();
    v16->SetDataMask(0x7fff);
    v16->Update();

  vtkRenderer* ren1 = vtkRenderer::New();
  vtkRenderer* ren2 = vtkRenderer::New();
  vtkRenderWindow* renWin = vtkRenderWindow::New();
    renWin->AddRenderer( ren1);
    renWin->AddRenderer( ren2);
  vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow( renWin);

  vtkOutlineFilter* outline = vtkOutlineFilter::New();
    outline->SetInputConnection(v16->GetOutputPort());

  vtkPolyDataMapper* outlineMapper = vtkPolyDataMapper::New();
    outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkActor* outlineActor =  vtkActor::New();
    outlineActor->SetMapper(outlineMapper);

  vtkImagePlaneWidget* ipw = vtkImagePlaneWidget::New();
    ipw->DisplayTextOn();
    ipw->TextureInterpolateOff();
    ipw->UserControlledLookupTableOff();
    ipw->SetInput(v16->GetOutput());
    ipw->KeyPressActivationOn();
    ipw->SetKeyPressActivationValue('x');
    ipw->SetResliceInterpolateToNearestNeighbour();
    ipw->SetInteractor(iren);
    ipw->SetPlaneOrientationToXAxes();
    ipw->SetSliceIndex(32);
    ipw->GetPlaneProperty()->SetColor(1,0,0);

  vtkSplineWidget* spline = vtkSplineWidget::New();
    spline->SetInteractor( iren);
    spline->SetInput(v16->GetOutput());
    spline->SetPriority(1.0);
    spline->KeyPressActivationOff();
    spline->PlaceWidget();
    spline->ProjectToPlaneOn();
    spline->SetProjectionNormal(0);
    spline->SetProjectionPosition(102.4);  //initial plane oriented position
    spline->SetProjectionNormal(3); //allow arbitrary oblique orientations
    spline->SetPlaneSource((vtkPlaneSource*)ipw->GetPolyDataAlgorithm());


  // Specify the type of spline (change from default vtkCardinalSpline)
  vtkKochanekSpline* xspline = vtkKochanekSpline::New();
  vtkKochanekSpline* yspline = vtkKochanekSpline::New();
  vtkKochanekSpline* zspline = vtkKochanekSpline::New();

  vtkParametricSpline* para = spline->GetParametricSpline();

  para->SetXSpline(xspline);
  para->SetYSpline(yspline);
  para->SetZSpline(zspline);

  xspline->Delete();
  yspline->Delete();
  zspline->Delete();

  vtkPolyData* poly = vtkPolyData::New();
    spline->GetPolyData(poly);

  vtkProbeFilter* probe = vtkProbeFilter::New();
    probe->SetInput(poly);
    probe->SetSource(v16->GetOutput());

  vtkIPWCallback* ipwcb = vtkIPWCallback::New();
    ipwcb->Spline = spline;
    ipwcb->Poly = poly;

  ipw->AddObserver(vtkCommand::InteractionEvent,ipwcb);

  vtkSWCallback* swcb = vtkSWCallback::New();
    swcb->Poly = poly;

  spline->AddObserver(vtkCommand::InteractionEvent,swcb);

  vtkImageData* data = v16->GetOutput();
  double* range = data->GetPointData()->GetScalars()->GetRange();

  vtkXYPlotActor* profile = vtkXYPlotActor::New();
    profile->AddInput(probe->GetOutput());
    profile->GetPositionCoordinate()->SetValue( 0.05, 0.05, 0);
    profile->GetPosition2Coordinate()->SetValue( 0.95, 0.95, 0);
    profile->SetXValuesToNormalizedArcLength();
    profile->SetNumberOfXLabels( 6);
    profile->SetTitle( "Profile Data ");
    profile->SetXTitle( "s");
    profile->SetYTitle( "I(s)");
    profile->SetXRange( 0, 1);
    profile->SetYRange( range[0], range[1]);
    profile->GetProperty()->SetColor( 0, 0, 0);
    profile->GetProperty()->SetLineWidth( 2);
    profile->SetLabelFormat("%g");
    vtkTextProperty* tprop = profile->GetTitleTextProperty();
    tprop->SetColor(0.02,0.06,0.62);
    tprop->SetFontFamilyToArial();
    profile->SetAxisTitleTextProperty(tprop);
    profile->SetAxisLabelTextProperty(tprop);
    profile->SetTitleTextProperty(tprop);

  ren1->SetBackground( 0.1, 0.2, 0.4);
  ren1->SetViewport( 0, 0, 0.5, 1);
  ren1->AddActor(outlineActor);

  ren2->SetBackground( 1, 1, 1);
  ren2->SetViewport( 0.5, 0, 1, 1);
  ren2->AddActor2D( profile);

  renWin->SetSize( 600, 300);

  ipw->On();
  ipw->SetInteraction(0);
  ipw->SetInteraction(1);
  spline->On();
  spline->SetNumberOfHandles(4);
  spline->SetNumberOfHandles(5);
  spline->SetResolution(399);

  // Set up an interesting viewpoint
  vtkCamera* camera = ren1->GetActiveCamera();
  camera->Elevation(110);
  camera->SetViewUp(0, 0, -1);
  camera->Azimuth(45);
  camera->SetFocalPoint(100.8,100.8,69);
  camera->SetPosition(560.949, 560.949, -167.853);
  ren1->ResetCameraClippingRange();

  // Position the actors
//  renWin->Render();
//  iren->SetEventPosition(200,200);
//  iren->SetKeyCode('r');
//  iren->InvokeEvent(vtkCommand::CharEvent,NULL);
//  ren1->ResetCameraClippingRange();
//  renWin->Render();
//  iren->SetKeyCode('t');
//  iren->InvokeEvent(vtkCommand::CharEvent,NULL);


  // Test On Off mechanism
  ipw->SetEnabled(0);
  spline->EnabledOff();
  ipw->SetEnabled(1);
  spline->EnabledOn();

  // Test Set Get handle positions
  double pos[3];
  int i;
  for(i=0;i<spline->GetNumberOfHandles();i++)
    {
    spline->GetHandlePosition(i,pos);
    spline->SetHandlePosition(i,pos);
    }

  // Test Closed On Off  
  spline->ClosedOn();
  spline->ClosedOff();

  // Render the image
  iren->Initialize();
  renWin->Render();


    iren->Start();


  outlineActor->Delete();
  outlineMapper->Delete();
  outline->Delete();
  renWin->Delete();
  ren1->Delete();
  ren2->Delete();
  iren->Delete();

  ipw->RemoveObserver(ipwcb);
  ipw->Delete();
  ipwcb->Delete();
  spline->RemoveObserver(swcb);
  spline->Delete();
  swcb->Delete();
  poly->Delete();
  probe->Delete();
  profile->Delete();
  v16->Delete();

  return 0;
}


