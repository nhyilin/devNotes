
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkPolyData.h"
#include "vtkBoxWidget.h"
#include "vtkCardinalSpline.h"
#include "vtkPoints.h"
#include "stdio.h"
#include <time.h>
#include <vtkGlyph3D.h>
#include <vtkProperty.h>
#include <vtkCellArray.h>
#include <vtkPointDataToCellData.h>
#include <vtkPolyLine.h>

void main()
{

  srand(time(NULL)) ;

//	rand()/RAND_MAX;//	0 - RAND_MAX
  vtkRenderer *ren = vtkRenderer::New();
  vtkRenderWindow *renWindow = vtkRenderWindow::New();
    renWindow->AddRenderer(ren);
  renWindow->SetSize( 600, 600 );

    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWindow);

  int numberOfInputPoints = 30;

	vtkCardinalSpline *aSplineX = vtkCardinalSpline::New();
	vtkCardinalSpline *aSplineY = vtkCardinalSpline::New();
	vtkCardinalSpline *aSplineZ = vtkCardinalSpline::New();

vtkPoints *inputPoints = vtkPoints::New();

double x,y,z;
int i;
for(i=0;i<numberOfInputPoints;i++)
{
	x = (float)rand()/(float)RAND_MAX;
    y = (float)rand()/(float)RAND_MAX;
    z = (float)rand()/(float)RAND_MAX;
	printf(" x:%f,y:%f,z:%f\n",x,y,z);
    aSplineX->AddPoint(i, x);
    aSplineY->AddPoint(i, y);
    aSplineZ->AddPoint(i, z);
    inputPoints->InsertPoint(i, x, y, z);
}


vtkPolyData *inputData =vtkPolyData::New();
inputData->SetPoints(inputPoints);

vtkSphereSource *balls =vtkSphereSource::New();
balls->SetRadius(.01);
balls->SetPhiResolution(10);
balls->SetThetaResolution(10);

vtkGlyph3D *glyphPoints =vtkGlyph3D::New();
glyphPoints->SetInput(inputData);
glyphPoints->SetSource(balls->GetOutput());

vtkPolyDataMapper *glyphMapper = vtkPolyDataMapper::New();
glyphMapper->SetInputConnection(glyphPoints->GetOutputPort());

vtkActor *glyph = vtkActor::New();
glyph->SetMapper(glyphMapper);
glyph->GetProperty()->SetDiffuseColor(1,0,0);
glyph->GetProperty()->SetSpecular(.3);
glyph->GetProperty()->SetSpecularPower(30);

///////////////
vtkPointDataToCellData *pointDataToCellData = vtkPointDataToCellData::New();
	pointDataToCellData->SetInputConnection((vtkAlgorithmOutput *)inputPoints);
	pointDataToCellData->PassPointDataOn();

vtkPolyDataMapper *plyMapper=vtkPolyDataMapper::New();
   plyMapper-> SetInputConnection (pointDataToCellData-> GetOutputPort());
vtkActor *plyActor=vtkActor::New();
   plyActor-> SetMapper(plyMapper);




//////////////
//ren->AddActor(glyph);
ren->AddActor(plyActor);

iren->Initialize();
renWindow->Render();

iren->Start();
}


