//
// Brute force computation of Bessel functions. Might be better to create a
// filter (or source) object. Might also consider vtkSampleFunction.

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPlaneSource.h"
#include "vtkTransform.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkPoints.h"
#include "vtkDoubleArray.h"
#include "vtkWarpScalar.h"
#include "vtkDataSetMapper.h"
#include "vtkPolyData.h"
#include "vtkActor.h"
#include "vtkPointData.h"

//#include "SaveImage.h"

void main( int argc, char *argv[] )
{
  int i, numPts;
  double x[3];
  double r, deriv;

  vtkRenderer *ren = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);
  
  // create plane to warp
  vtkPlaneSource *plane = vtkPlaneSource::New();
    plane->SetResolution (300,300);
	//定义一个平面

  vtkTransform *transform = vtkTransform::New();
     transform->Scale(10.0,10.0,1.0);

  vtkTransformPolyDataFilter *transF = vtkTransformPolyDataFilter::New();
     transF->SetInput(plane->GetOutput());
     transF->SetTransform(transform);
     transF->Update();

  // compute Bessel function and derivatives. This portion could be 
  // encapsulated into source or filter object.
  //

//vtkPolyData *input = plane->GetOutput();
  vtkPolyData *input = transF->GetOutput();
  numPts = input->GetNumberOfPoints();
  vtkPoints *newPts = vtkPoints::New();
    newPts->SetNumberOfPoints(numPts);
  vtkDoubleArray *derivs = vtkDoubleArray::New();
    derivs->SetNumberOfTuples(numPts);
  vtkPolyData *bessel = vtkPolyData::New();
    bessel->CopyStructure(input);
    bessel->SetPoints(newPts);
    bessel->GetPointData()->SetScalars(derivs);

  for (i=0; i<numPts; i++)
    {
    input->GetPoint(i,x);
    r = sqrt(double(x[0]*x[0]) + double(x[1]*x[1]));
    x[2] = exp(-r) * cos (10.0L*r);
    newPts->SetPoint(i,x);
    deriv = -exp(-r) * (cos(10.0L*r) + 10.0L*sin(10.0L*r));
    derivs->SetTuple(i,&deriv);
    }
  newPts->Delete(); //reference counting - it's ok
  derivs->Delete();
  
  // warp plane
  vtkWarpScalar *warp = vtkWarpScalar::New();
    warp->SetInput(bessel);
    warp->XYPlaneOn();
    warp->SetScaleFactor(0.5);

  // mapper and actor
  vtkDataSetMapper *mapper = vtkDataSetMapper::New();
    mapper->SetInput(warp->GetOutput());
    mapper->SetScalarRange(bessel->GetScalarRange());

  vtkActor *carpet = vtkActor::New();
    carpet->SetMapper(mapper);

  // assign our actor to the renderer
  ren->AddActor(carpet);
  ren->SetBackground(1,1,1);
  renWin->SetSize(300,300);

  // draw the resulting scene
  renWin->Render();

//  SAVEIMAGE( renWin );

  // Begin mouse interaction
  iren->Start();
}
