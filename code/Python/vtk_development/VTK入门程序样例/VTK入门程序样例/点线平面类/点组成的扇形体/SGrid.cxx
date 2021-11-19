#include "vtkMath.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkStructuredGrid.h"
#include "vtkFloatArray.h"
#include "vtkPoints.h"
#include "vtkHedgeHog.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkPointData.h"
#include "vtkProperty.h"
#include "vtkCamera.h"


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
  int i, j, k, kOffset, jOffset, offset;
  float x[3], v[3], rMin=0.5, rMax=1.0, deltaRad, deltaZ;
  float radius, theta;
  static int dims[3]={13,11,11};
  
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkStructuredGrid *sgrid = vtkStructuredGrid::New();
  //vtkStructuredGrid 表现 topologically 点的一般的排列的几何学的结构
      sgrid->SetDimensions(dims);

  vtkFloatArray *vectors = vtkFloatArray::New();
    vectors->Allocate(dims[0]*dims[1]*dims[2]);
	vectors->SetNumberOfComponents(3);
	vectors->SetNumberOfTuples(dims[0]*dims[1]*dims[2]);

  vtkPoints *points = vtkPoints::New();
    points->Allocate(dims[0]*dims[1]*dims[2]);//点数
  
  deltaZ = 2.0 / (dims[2]-1);
  deltaRad = (rMax-rMin) / (dims[1]-1);
  v[2]=0.0;
  for ( k=0; k<dims[2]; k++)
    {
    x[2] = -1.0 + k*deltaZ;
    kOffset = k * dims[0] * dims[1];
    for (j=0; j<dims[1]; j++) 
      {
      radius = rMin + j*deltaRad;
      jOffset = j * dims[0];
      for (i=0; i<dims[0]; i++) 
        {
        theta = i * 15.0 * vtkMath::DegreesToRadians();
        x[0] = radius * cos(theta);
        x[1] = radius * sin(theta);
        v[0] = -x[1];
        v[1] = x[0];
        offset = i + jOffset + kOffset;
        points->InsertPoint(offset,x);
        vectors->InsertTuple(offset,v);
        }
      }
    }
  sgrid->SetPoints(points);
  points->Delete();
  sgrid->GetPointData()->SetVectors(vectors);
  vectors->Delete();

  vtkHedgeHog *hedgehog = vtkHedgeHog::New();
      hedgehog->SetInput(sgrid);
      hedgehog->SetScaleFactor(0.1);

  vtkPolyDataMapper *sgridMapper = vtkPolyDataMapper::New();
      sgridMapper->SetInput(hedgehog->GetOutput());
  vtkActor *sgridActor = vtkActor::New();
      sgridActor->SetMapper(sgridMapper);
      sgridActor->GetProperty()->SetColor(0,0,0);

  renderer->AddActor(sgridActor);
  renderer->SetBackground(1,1,1);
  renderer->GetActiveCamera()->Elevation(60.0);
  renderer->GetActiveCamera()->Azimuth(30.0);
  renderer->GetActiveCamera()->Zoom(1.25);
  renWin->SetSize(300,300);

  // interact with data
  renWin->Render();

  SAVEIMAGE( renWin );

  iren->Start();

  renderer->Delete();
  renWin->Delete();
  iren->Delete();
  sgrid->Delete();
  hedgehog->Delete();
  sgridMapper->Delete();
  sgridActor->Delete();
}
