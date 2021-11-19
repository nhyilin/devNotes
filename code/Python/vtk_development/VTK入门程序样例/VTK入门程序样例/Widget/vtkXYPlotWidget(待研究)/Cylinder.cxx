
#include "vtkProbeFilter.h"
#include "vtkXYPlotWidget.h"
#include "vtkStructuredGridGeometryFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkScalarBarActor.h"
#include "vtkStructuredGrid.h"

#include "vtkTestUtilities.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkXYPlotActor.h"

#include "vtkDICOMImageReader.h"
#include <vtkImageMapper.h>
#include <vtkProperty2D.h>
#include <vtkDICOMImageReader.h>
#include <vtkActor2D.h>
#include <vtkLookupTable.h>
#include <vtkTextProperty.h>

int main( int argc, char *argv[] )
{
 
  // Start by loading some data.
	vtkDICOMImageReader* reader = vtkDICOMImageReader::New();	
	  reader->SetFileName("E://CT/100098.dcm");
	  reader->SetDataByteOrderToLittleEndian();
	  reader->Update();

  vtkPolyData* poly = vtkPolyData::New();

  vtkProbeFilter* probe = vtkProbeFilter::New();
    probe->SetInput(poly);
    probe->SetSource(reader->GetOutput());

  vtkImageData* data = reader->GetOutput();
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

  // Create the RenderWindow, Renderer and both Actors
  //
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer(ren1);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow(renWin);

  vtkXYPlotWidget *XYPlotWidget = vtkXYPlotWidget::New();
  XYPlotWidget->SetInteractor(iren);
  XYPlotWidget->SetXYPlotActor(profile);
//  XYPlotWidget->GetXYPlotActor()->SetTitle("Temperature");
//  XYPlotWidget->GetXYPlotActor()->SetLookupTable(outlineMapper->GetLookupTable());
  
  ren1->AddActor(profile);

  ren1->SetBackground(0.1, 0.2, 0.4);
  renWin->SetSize(300, 300);

  iren->Initialize();
  renWin->Render();

    iren->Start();
  
  return 0;
}
