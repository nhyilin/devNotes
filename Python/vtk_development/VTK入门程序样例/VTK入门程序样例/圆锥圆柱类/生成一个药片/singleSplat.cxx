#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPoints.h"
#include "vtkCellArray.h"
#include "vtkFloatArray.h"
#include "vtkPolyData.h"
#include "vtkGaussianSplatter.h"
#include "vtkContourFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkOutlineFilter.h"
#include "vtkConeSource.h"
#include "vtkPointData.h"
#include "vtkProperty.h"


// Includes and a macro necessary for saving the image produced by a cxx 
// example program. This capability is critical for regression testing.

#include <stdio.h>
#include <string.h>
#include "vtkWindowToImageFilter.h"
#include "vtkTIFFWriter.h"
#define SAVEIMAGE( rw ) \
  if( (argc >= 2) && (strcmp("-S", argv[argc-1]) == 0) ) \
    { \
    char save_filename[1024]; \
    vtkWindowToImageFilter *w2if = vtkWindowToImageFilter::New(); \
    vtkTIFFWriter *rttiffw = vtkTIFFWriter::New(); \
    sprintf( save_filename, "%s.cxx.tif", argv[0] ); \
    w2if->SetInput(rw);\
    rttiffw->SetInput(w2if->GetOutput());\
    rttiffw->SetFileName(save_filename); \
    rttiffw->Write(); \
    exit( 1 ); \
    }
#include "SaveImage.h"

void main( int argc, char *argv[] )
{
  float x[3], n[3];

  vtkRenderer *aren = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(aren);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  // Create single splat point
  vtkPoints *pts = vtkPoints::New();
  vtkCellArray *verts = vtkCellArray::New();
  vtkFloatArray *norms = vtkFloatArray::New();
	norms->SetNumberOfComponents(3);
  vtkFloatArray *scalars = vtkFloatArray::New();

  x[0] = x[1] = x[2] = 0.0;
  pts->InsertNextPoint(x);
  n[0] = 0.707; n[1] = 0.707; n[2] = 0.0;
  norms->InsertNextTuple(n);
  scalars->InsertNextValue(2.5);
  verts->InsertNextCell(1);
  verts->InsertCellPoint(0);
  vtkPolyData *pData = vtkPolyData::New();
    pData->SetPoints(pts);
    pData->SetVerts(verts);
    pData->GetPointData()->SetNormals(norms);
    pData->GetPointData()->SetScalars(scalars);

  // Splat point and generate isosurface
  vtkGaussianSplatter *splat = vtkGaussianSplatter::New();
      splat->SetInput(pData);
      splat->SetModelBounds(-1.0,1.0, -1.0,1.0, -1.0,1.0);
      splat->SetSampleDimensions(75,75,75);
      splat->SetRadius(0.20);
      splat->SetEccentricity(5.0);

  vtkContourFilter *contour = vtkContourFilter::New();
      contour->SetInput((vtkDataSet *)splat->GetOutput());
      contour->SetValue(0, 0.9);
  vtkPolyDataMapper *splatMapper = vtkPolyDataMapper::New();
      splatMapper->SetInput(contour->GetOutput());
  vtkActor *splatActor = vtkActor::New();
      splatActor->SetMapper(splatMapper);

  // Create outline
  vtkOutlineFilter *outline = vtkOutlineFilter::New();
      outline->SetInput((vtkDataSet *)splat->GetOutput());
  vtkPolyDataMapper *outlineMapper = vtkPolyDataMapper::New();
      outlineMapper->SetInput(outline->GetOutput());
  vtkActor *outlineActor = vtkActor::New();
      outlineActor->SetMapper(outlineMapper);
      outlineActor->GetProperty()->SetColor(0,0,0);

  // Create cone to indicate direction
  vtkConeSource *cone = vtkConeSource::New();
      cone->SetResolution(24);
  vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
      coneMapper->SetInput(cone->GetOutput());
  vtkActor *coneActor = vtkActor::New();
      coneActor->SetMapper(coneMapper);
      coneActor->SetScale(0.75,0.75,0.75);
      coneActor->RotateZ(45.0);
      coneActor->AddPosition(0.50,0.50,0.0);
      coneActor->GetProperty()->SetColor(1.0000, 0.4118, 0.7059);
//
// Rendering stuff
//
  aren->SetBackground(0.6,0.4,0.3);
      aren->AddActor(splatActor);
     // aren->AddActor(outlineActor);
      aren->AddActor(coneActor);

  renWin->SetSize(300,300);
  renWin->Render();

  SAVEIMAGE( renWin );

  // interact with data
  iren->Start();

  // Clean up
  aren->Delete();
  renWin->Delete();
  iren->Delete();
  pts->Delete();
  verts->Delete();
  norms->Delete();
  scalars->Delete();
  pData->Delete();
  splat->Delete();
  contour->Delete();
  splatMapper->Delete();
  splatActor->Delete();
  outline->Delete();
  outlineMapper->Delete();
  outlineActor->Delete();
  cone->Delete();
  coneMapper->Delete();
  coneActor->Delete();
}
