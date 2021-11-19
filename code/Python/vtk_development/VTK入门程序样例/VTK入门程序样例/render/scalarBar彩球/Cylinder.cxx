
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkPLOT3DReader.h"
#include "vtkPolyDataNormals.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkTextProperty.h"
#include "vtkTexture.h"
#include "vtkFloatArray.h"
#include "vtkContourFilter.h"
#include "vtkCastToConcrete.h"
#include "vtkProgrammableAttributeDataFilter.h"
#include "vtkMath.h"
#include "vtkRendererSource.h"
#include "vtkProgrammableAttributeDataFilter.h"
#include "vtkProperty.h"
#include "vtkSphereSource.h"
#include "vtkPointData.h"
#include "vtkCellData.h"
#include "vtkScalarBarActor.h"

int main()
{
	vtkRenderer *ren1= vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
      renWin->AddRenderer( ren1 );
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
      iren->SetRenderWindow(renWin);

vtkSphereSource *sphere=vtkSphereSource::New();
    sphere-> SetThetaResolution( 40);
    sphere-> SetPhiResolution( 20);
    sphere-> Update();

vtkProgrammableAttributeDataFilter *randomColors=vtkProgrammableAttributeDataFilter::New();
    randomColors-> SetInputConnection (sphere-> GetOutputPort());
    vtkMath *randomColorGenerator=vtkMath::New();
//      int input=randomColors-> GetInput();
//      int output=randomColors-> GetOutput();

    int numCells=((vtkPolyData *)randomColors-> GetInput())-> GetNumberOfCells();

	printf("numCells : %d\n",numCells);

    vtkFloatArray *colors=vtkFloatArray::New();
	  colors->SetNumberOfTuples(numCells);
	int i;
	double f;
	for (i=0;i<numCells;i++)
	{
		f=randomColorGenerator->Random (0, 1);
		colors-> SetValue(i,f);
		printf("i : %d color : %f\n",i,f);
	}

    randomColors->GetOutput()->GetCellData()->CopyScalarsOff();
    randomColors->GetOutput()->GetCellData()->
		PassData(((vtkPolyData *)randomColors-> GetInput())-> GetCellData());
	randomColors->Update();
    randomColors->GetOutput()->GetCellData()->SetScalars(colors);

//    colors-> Delete(); 
    randomColorGenerator-> Delete();

randomColors->Update();

vtkPolyDataMapper *mapper=vtkPolyDataMapper::New();
    mapper ->SetInput(randomColors-> GetPolyDataOutput());
	mapper-> SetScalarRange(randomColors->GetPolyDataOutput()-> GetScalarRange());
//    mapper ->ScalarVisibilityOn();


    vtkActor *sphereActor  = vtkActor::New();
      sphereActor->SetMapper(mapper);


vtkScalarBarActor *scalarBar=vtkScalarBarActor::New();
    scalarBar-> SetLookupTable(mapper-> GetLookupTable());
    scalarBar-> SetTitle ("Color Table");
    scalarBar-> GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
    scalarBar-> GetPositionCoordinate()-> SetValue(0.1, 0.01);  
//    scalarBar-> GetPositionCoordinate()->
	scalarBar->SetNumberOfLabels(6);  
    scalarBar-> SetOrientationToHorizontal();
    scalarBar-> SetWidth (0.8);
    scalarBar-> SetHeight (0.17);

	scalarBar-> SetPosition (scalarBar-> GetPosition());
	scalarBar-> SetNumberOfLabels(8);

	  ren1->AddActor(sphereActor);
	  ren1->AddActor2D(scalarBar);
	  ren1->SetBackground( 1, 1, 1 );
	  ren1-> ResetCamera();


    renWin->SetSize( 600, 600 );
	renWin-> Render();

	iren->Initialize();
    iren->Start(); 


	ren1->Delete();
    renWin->Delete();
	iren->Delete();
    
	return 0;
}


	
	
