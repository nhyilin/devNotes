#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkUnstructuredGrid.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkHexahedron.h"
#include "vtkIdList.h"
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

  //Hexahedron
  vtkHexahedron *hexahedron = vtkHexahedron::New();
  double hexahedronCoords[8][3];

  hexahedron->GetPointIds()->SetNumberOfIds(8);
  hexahedron->GetPointIds()->SetId(0,0);
  hexahedron->GetPointIds()->SetId(1,1);
  hexahedron->GetPointIds()->SetId(2,2);
  hexahedron->GetPointIds()->SetId(3,3);
  hexahedron->GetPointIds()->SetId(4,4);
  hexahedron->GetPointIds()->SetId(5,5);
  hexahedron->GetPointIds()->SetId(6,6);
  hexahedron->GetPointIds()->SetId(7,7);

  hexahedronCoords[0][0] = .5; hexahedronCoords[0][1] = 0.5; hexahedronCoords[0][2] = 0.1;
  hexahedronCoords[1][0] = .9; hexahedronCoords[1][1] = 0.9; hexahedronCoords[1][2] = 0.5;
  hexahedronCoords[2][0] = .5; hexahedronCoords[2][1] = 0.1; hexahedronCoords[2][2] = 0.5;
  hexahedronCoords[3][0] = .5; hexahedronCoords[3][1] = 0.5; hexahedronCoords[3][2] = 0.1;
  hexahedronCoords[4][0] = .5; hexahedronCoords[4][1] = 0.5; hexahedronCoords[4][2] = 0.9;
  hexahedronCoords[5][0] = .9; hexahedronCoords[5][1] = 0.9; hexahedronCoords[5][2] = 0.7;
  hexahedronCoords[6][0] = .5; hexahedronCoords[6][1] = 0.1; hexahedronCoords[6][2] = 0.7;
  hexahedronCoords[7][0] = .5; hexahedronCoords[7][1] = 0.5; hexahedronCoords[7][2] = 0.9;
  
  vtkIdList *ids = vtkIdList::New();
  
  for (int j = 0; j < 8; j++)
    {
    hexahedron->CellBoundary (0, hexahedronCoords[j], ids);
    }


	vtkUnstructuredGrid *aHexahedronGrid=vtkUnstructuredGrid::New();
	  aHexahedronGrid-> Allocate (1 ,1);
	  aHexahedronGrid-> InsertNextCell 
		  (hexahedron-> GetCellType(), hexahedron-> GetPointIds());
//	  aHexahedronGrid-> SetPoints (hexahedronCoords);
//	  aHexahedronGrid-> GetPointData() ->SetScalars (hexahedronScalars);

	vtkDataSetMapper *aHexahedronMapper=vtkDataSetMapper::New();
	  aHexahedronMapper-> SetInput ((vtkDataSet *)hexahedron);
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
