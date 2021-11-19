#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkUnstructuredGrid.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkHexahedron.h"
#include "vtkFloatArray.h"
#include "vtkProperty.h"
#include "vtkPoints.h"
#include "vtkContourFilter.h"
#include "vtkPointData.h"

void main( )
{
  vtkRenderer *aren = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(aren);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

	// Hexahedron

	vtkPoints *hexahedronPoints=vtkPoints::New();
	  hexahedronPoints-> SetNumberOfPoints (16);
	  hexahedronPoints-> InsertPoint (0, 0, 0 ,0);
	  hexahedronPoints-> InsertPoint (1, 1, 0 ,0);
	  hexahedronPoints-> InsertPoint (2, 1, 1 ,0);
	  hexahedronPoints-> InsertPoint (3, 0, 1 ,0);
	  hexahedronPoints-> InsertPoint (4, 0, 0 ,1);
	  hexahedronPoints-> InsertPoint (5, 1, 0, 1);
	  hexahedronPoints-> InsertPoint (6, 1, 1 ,1);
	  hexahedronPoints-> InsertPoint (7, 0, 1 ,1);

	  hexahedronPoints-> InsertPoint (8, 0.5, 0 ,0);
	  hexahedronPoints-> InsertPoint (9, 1, 0.5 ,0);
	  hexahedronPoints-> InsertPoint (10, .5, 1 ,0);
	  hexahedronPoints-> InsertPoint (11, 0, 0.5 ,0);
	  hexahedronPoints-> InsertPoint (12, 0.5,0 ,1);
	  hexahedronPoints-> InsertPoint (13, 1, 0.5, 1);
	  hexahedronPoints-> InsertPoint (14, .5, 1 ,1);
	  hexahedronPoints-> InsertPoint (15, 0, .5 ,1); 
	  
	vtkFloatArray *hexahedronScalars=vtkFloatArray::New();
	  hexahedronScalars-> SetNumberOfTuples (16);
	  hexahedronScalars-> InsertValue (0, 1);
	  hexahedronScalars-> InsertValue (1, 1);
	  hexahedronScalars-> InsertValue (2, 1);
	  hexahedronScalars-> InsertValue (3, 1);
	  hexahedronScalars-> InsertValue (4, 1);
	  hexahedronScalars-> InsertValue (5, 1);
	  hexahedronScalars-> InsertValue (6, 1);
	  hexahedronScalars-> InsertValue (7, 1);
	  hexahedronScalars-> InsertValue (8, 1);
	  hexahedronScalars-> InsertValue (9, 1);
	  hexahedronScalars-> InsertValue (10, 1);
	  hexahedronScalars-> InsertValue (11, 1);
	  hexahedronScalars-> InsertValue (12, 1);
	  hexahedronScalars-> InsertValue (13, 1);
	  hexahedronScalars-> InsertValue (14, 1);
	  hexahedronScalars-> InsertValue (15, 1);

	vtkHexahedron *aHexahedron=vtkHexahedron::New();
	  aHexahedron-> GetPointIds() ->SetId (0 ,0);
	  aHexahedron-> GetPointIds() ->SetId (1 ,1);
	  aHexahedron-> GetPointIds() ->SetId (2 ,2);
	  aHexahedron-> GetPointIds() ->SetId (3 ,3);
	  aHexahedron-> GetPointIds() ->SetId (4 ,4);
	  aHexahedron-> GetPointIds() ->SetId (5 ,5);
	  aHexahedron-> GetPointIds() ->SetId (6 ,6);
	  aHexahedron-> GetPointIds() ->SetId (7 ,7);
	  aHexahedron-> GetPointIds() ->SetId (8 ,8);
	  aHexahedron-> GetPointIds() ->SetId (9 ,9);
	  aHexahedron-> GetPointIds() ->SetId (12 ,12);
	  aHexahedron-> GetPointIds() ->SetId (13 ,13);
	  aHexahedron-> GetPointIds() ->SetId (14 ,14);
	  aHexahedron-> GetPointIds() ->SetId (15 ,15);
	  aHexahedron-> GetPointIds() ->SetId (10 ,10);
	  aHexahedron-> GetPointIds() ->SetId (11 ,11);  


	vtkUnstructuredGrid *aHexahedronGrid=vtkUnstructuredGrid::New();
	  aHexahedronGrid-> Allocate (5 ,5);
	  aHexahedronGrid-> InsertNextCell 
		  (aHexahedron-> GetCellType(), aHexahedron-> GetPointIds());
	  aHexahedronGrid-> SetPoints (hexahedronPoints);
	  aHexahedronGrid-> GetPointData() ->SetScalars (hexahedronScalars);

	vtkDataSetMapper *aHexahedronMapper=vtkDataSetMapper::New();
	  aHexahedronMapper-> SetInput (aHexahedronGrid);
	  aHexahedronMapper-> ScalarVisibilityOff();

	vtkActor *aHexahedronActor=vtkActor::New();
	  aHexahedronActor-> SetMapper (aHexahedronMapper);
	  aHexahedronActor-> GetProperty()-> BackfaceCullingOn();
//	  aHexahedronActor-> GetProperty() ->SetRepresentationToWireframe();

  aren->AddActor(aHexahedronActor);
  aren->SetBackground (1,1,0);


  renWin->SetSize(600,600);

  renWin->Render();

  iren->Start();

  aren->Delete();
  renWin->Delete();
  iren->Delete();

}
