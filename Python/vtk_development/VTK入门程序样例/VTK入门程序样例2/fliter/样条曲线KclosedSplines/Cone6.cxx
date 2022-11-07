
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkPolyData.h"
#include "vtkBoxWidget.h"
#include "vtkKochanekSpline.h"
#include "vtkCardinalSpline.h"
#include "vtkPoints.h"
#include "stdio.h"
#include <time.h>
#include <vtkGlyph3D.h>
#include <vtkProperty.h>
#include <vtkCellArray.h>
#include <vtkTubeFilter.h>
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

vtkKochanekSpline *aKSplineX=vtkKochanekSpline::New();
 aKSplineX-> ClosedOn();
vtkKochanekSpline *aKSplineY=vtkKochanekSpline::New();
 aKSplineY-> ClosedOn();
vtkKochanekSpline *aKSplineZ=vtkKochanekSpline::New();
 aKSplineZ-> ClosedOn();

vtkCardinalSpline *aCSplineX=vtkCardinalSpline::New();
 aCSplineX-> ClosedOn();
vtkCardinalSpline *aCSplineY=vtkCardinalSpline::New();
 aCSplineY-> ClosedOn();
vtkCardinalSpline *aCSplineZ=vtkCardinalSpline::New();
 aCSplineZ-> ClosedOn();

//# add some points
vtkPoints *inputPoints=vtkPoints::New();
//float x -1.0; set y -1.0; set z 0.0
aKSplineX-> AddPoint (0 ,-1.0);
aKSplineY-> AddPoint (0 ,-1.0);
aKSplineZ-> AddPoint (0 ,0.0);
aCSplineX-> AddPoint (0 ,-1.0);
aCSplineY-> AddPoint (0 ,-1.0);
aCSplineZ-> AddPoint (0 ,0.0);
inputPoints-> InsertPoint (0, -1.0,-1.0,0);

//set x 1.0; set y -1.0; set z 0.0
aKSplineX-> AddPoint (1 ,1.0);
aKSplineY-> AddPoint (1 ,-1.0);
aKSplineZ-> AddPoint (1 ,0.0);
aCSplineX-> AddPoint (1 ,1.0);
aCSplineY-> AddPoint (1 ,-1.0);
aCSplineZ-> AddPoint (1 ,0.0);
inputPoints-> InsertPoint (1, 1.0,-1.0,0);

//set x 1.0; set y 1.0; set z 0.0
aKSplineX-> AddPoint (2 ,1.0);
aKSplineY-> AddPoint (2 ,1.0);
aKSplineZ-> AddPoint (2 ,0.0);
aCSplineX-> AddPoint (2 ,1.0);
aCSplineY-> AddPoint (2 ,1.0);
aCSplineZ-> AddPoint (2 ,0.0);
inputPoints-> InsertPoint (2, 1.0,1.0,0);

//set x -1.0; set y 1.0; set z 0.0
aKSplineX-> AddPoint (3 ,-1.0);
aKSplineY-> AddPoint (3 ,1.0);
aKSplineZ-> AddPoint (3 ,0.0);
aCSplineX-> AddPoint (3 ,-1.0);
aCSplineY-> AddPoint (3 ,1.0);
aCSplineZ-> AddPoint (3 ,0.0);
inputPoints-> InsertPoint (3, -1.0,1.0,0);

vtkPolyData *inputData =vtkPolyData::New();
inputData->SetPoints(inputPoints);

vtkSphereSource *balls =vtkSphereSource::New();
balls->SetRadius(.04);
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
vtkPoints *Kpoints = vtkPoints::New();
vtkPoints *Cpoints = vtkPoints::New();

Kpoints ->Reset();
Cpoints ->Reset();

vtkPolyData *profileKData=vtkPolyData::New();
vtkPolyData *profileCData=vtkPolyData::New(); 

numberOfInputPoints=5;
int numberOfOutputPoints=100;

float t;
int i;
for(i=0;i<numberOfOutputPoints;i++)
{
    t = (numberOfInputPoints-1.0)/(numberOfOutputPoints-1.0)*i;
    Kpoints->InsertPoint(i, aKSplineX->Evaluate(t), aKSplineY->Evaluate(t),
                       aKSplineZ->Evaluate(t));
	Cpoints->InsertPoint(i, aCSplineX->Evaluate(t), aCSplineY->Evaluate(t),
                       aCSplineZ->Evaluate(t));


}

vtkCellArray *lines = vtkCellArray::New();
	int a=lines->InsertNextCell(numberOfOutputPoints);
	for(i=0;i<numberOfOutputPoints;i++)
	{
		lines->InsertCellPoint(i);
	}

profileKData->SetPoints(Kpoints);
profileKData->SetLines(lines);

profileCData->SetPoints(Cpoints);
profileCData->SetLines(lines);

// Add thickness to the resulting line.
vtkTubeFilter *profileKTubes = vtkTubeFilter::New();
profileKTubes->SetNumberOfSides(8);
profileKTubes->SetInput(profileKData);
profileKTubes->SetRadius(0.01);

vtkTubeFilter *profileCTubes = vtkTubeFilter::New();
profileCTubes->SetNumberOfSides(8);
profileCTubes->SetInput(profileCData);
profileCTubes->SetRadius(0.01);

vtkPolyDataMapper *profileKMapper = vtkPolyDataMapper::New();
profileKMapper->SetInputConnection(profileKTubes->GetOutputPort());

vtkActor *profileK = vtkActor::New();
profileK->SetMapper(profileKMapper);
profileK->GetProperty()->SetDiffuseColor(1,1,0);
profileK->GetProperty()->SetSpecular(0.3);
profileK->GetProperty()->SetSpecularPower(30);

vtkPolyDataMapper *profileCMapper = vtkPolyDataMapper::New();
profileCMapper->SetInputConnection(profileCTubes->GetOutputPort());

vtkActor *profileC = vtkActor::New();
profileC->SetMapper(profileCMapper);
profileC->GetProperty()->SetDiffuseColor(0,0,1);
profileC->GetProperty()->SetSpecular(0.3);
profileC->GetProperty()->SetSpecularPower(30);

//////////////


ren->AddActor(glyph);
ren->AddActor(profileC);
ren->AddActor(profileK);

iren->Initialize();
renWindow->Render();

iren->Start();
}


