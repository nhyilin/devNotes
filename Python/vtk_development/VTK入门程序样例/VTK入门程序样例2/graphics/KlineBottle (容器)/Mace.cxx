
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkCellArray.h"
#include "vtkDebugLeaks.h"
#include "vtkPlanes.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRegressionTestImage.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkPoints.h"
#include "vtkSphereSource.h"

#include "vtkLoopSubdivisionFilter.h"
#include "vtkDataSetMapper.h"
#include "vtkLODActor.h"
#include "vtkProperty.h"
#include "vtkFeatureEdges.h"

void main(  )
{
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

	vtkPoints *points=vtkPoints::New();
		points->InsertNextPoint( 0 ,-16, 0 );
		points->InsertNextPoint( 0, 0 ,-14 );
		points->InsertNextPoint( 0, 0 ,14 );
		points->InsertNextPoint( 14, 0 ,0 );
		points->InsertNextPoint( 10, 20 ,-10 );
		points->InsertNextPoint( 10, 20 ,10 );
		points->InsertNextPoint( 10, -20 ,-10 );
		points->InsertNextPoint( 10 ,-20 ,10 );
		points->InsertNextPoint( -10, -20 ,-10 );
		points->InsertNextPoint( -10, -20, 10 );
		points->InsertNextPoint( -10, 20, -10 );
		points->InsertNextPoint( -10, 20, 10 );
		points->InsertNextPoint( -2, 27, 0 );
		points->InsertNextPoint( 0, 27, 2 );
		points->InsertNextPoint( 0, 27, -2 );
		points->InsertNextPoint( 2,27, 0 );
		points->InsertNextPoint( -14 ,4, -1 );
		points->InsertNextPoint( -14 ,3, 0 );
		points->InsertNextPoint( -14 ,5, 0 );
		points->InsertNextPoint( -14 ,4, 1 );
		points->InsertNextPoint( -1 ,38, -2 );
		points->InsertNextPoint( -1 ,38, 2 );
		points->InsertNextPoint( 2 ,35 ,-2 );
		points->InsertNextPoint( 2 ,35, 2 );
		points->InsertNextPoint( 17, 42 ,0 );
		points->InsertNextPoint( 15 ,40, 2 );
		points->InsertNextPoint( 15 ,39, -2 );
		points->InsertNextPoint( 13 ,37, 0 );
		points->InsertNextPoint( 19 ,-2, -2 );
		points->InsertNextPoint( 19, -2, 2 );
		points->InsertNextPoint( 15, 2 ,-2 );
		points->InsertNextPoint( 15 ,2, 2 );

	vtkCellArray *faces=vtkCellArray::New();
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 3);
		faces->InsertCellPoint( 4);
		faces->InsertCellPoint( 5);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 3);
		faces->InsertCellPoint( 5);
		faces->InsertCellPoint( 7);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 3);
		faces->InsertCellPoint( 7);
		faces->InsertCellPoint( 6);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 3);
		faces->InsertCellPoint( 6);
		faces->InsertCellPoint( 4);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 0);
		faces->InsertCellPoint( 6);
		faces->InsertCellPoint( 7);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 0);
		faces->InsertCellPoint( 7);
		faces->InsertCellPoint( 9);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 0);
		faces->InsertCellPoint( 9);
		faces->InsertCellPoint( 8);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 0);
		faces->InsertCellPoint( 8);
		faces->InsertCellPoint( 6);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 1);
		faces->InsertCellPoint( 4);
		faces->InsertCellPoint( 6);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 1);
		faces->InsertCellPoint( 6);
		faces->InsertCellPoint( 8);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 1);
		faces->InsertCellPoint( 8);
		faces->InsertCellPoint( 10);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 1);
		faces->InsertCellPoint( 10);
		faces->InsertCellPoint( 4);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 2);
		faces->InsertCellPoint( 11);
		faces->InsertCellPoint( 9);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 2);
		faces->InsertCellPoint( 9);
		faces->InsertCellPoint( 7);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 2);
		faces->InsertCellPoint( 7);
		faces->InsertCellPoint( 5);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 2);
		faces->InsertCellPoint( 5);
		faces->InsertCellPoint( 11);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 4);
		faces->InsertCellPoint( 15);
		faces->InsertCellPoint( 5);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 4);
		faces->InsertCellPoint( 14);
		faces->InsertCellPoint( 15);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 5);
		faces->InsertCellPoint( 13);
		faces->InsertCellPoint( 11);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 5);
		faces->InsertCellPoint( 15);
		faces->InsertCellPoint( 13);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 11);
		faces->InsertCellPoint( 12);
		faces->InsertCellPoint( 10);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 11);
		faces->InsertCellPoint( 13);
		faces->InsertCellPoint( 12);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 10);
		faces->InsertCellPoint( 14);
		faces->InsertCellPoint( 4);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 10);
		faces->InsertCellPoint( 12);
		faces->InsertCellPoint( 14);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 8);
		faces->InsertCellPoint( 17);
		faces->InsertCellPoint( 16);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 8);
		faces->InsertCellPoint( 9);
		faces->InsertCellPoint( 17);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 9);
		faces->InsertCellPoint( 19);
		faces->InsertCellPoint( 17);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 9);
		faces->InsertCellPoint( 11);
		faces->InsertCellPoint( 19);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 11);
		faces->InsertCellPoint( 18);
		faces->InsertCellPoint( 19);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 11);
		faces->InsertCellPoint( 10);
		faces->InsertCellPoint( 18);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 10);
		faces->InsertCellPoint( 16);
		faces->InsertCellPoint( 18);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 10);
		faces->InsertCellPoint( 8);
		faces->InsertCellPoint( 16);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 13);
		faces->InsertCellPoint( 21);
		faces->InsertCellPoint( 12);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 12);
		faces->InsertCellPoint( 21);
		faces->InsertCellPoint( 20);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 12);
		faces->InsertCellPoint( 20);
		faces->InsertCellPoint( 14);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 14);
		faces->InsertCellPoint( 20);
		faces->InsertCellPoint( 22);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 14);
		faces->InsertCellPoint( 22);
		faces->InsertCellPoint( 15);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 15);
		faces->InsertCellPoint( 22);
		faces->InsertCellPoint( 23);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 15);
		faces->InsertCellPoint( 23);
		faces->InsertCellPoint( 13);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 13);
		faces->InsertCellPoint( 23);
		faces->InsertCellPoint( 21);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 21);
		faces->InsertCellPoint( 25);
		faces->InsertCellPoint( 24);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 21);
		faces->InsertCellPoint( 24);
		faces->InsertCellPoint( 20);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 20);
		faces->InsertCellPoint( 24);
		faces->InsertCellPoint( 26);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 20);
		faces->InsertCellPoint( 26);
		faces->InsertCellPoint( 22);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 22);
		faces->InsertCellPoint( 26);
		faces->InsertCellPoint( 27);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 22);
		faces->InsertCellPoint( 27);
		faces->InsertCellPoint( 23);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 23);
		faces->InsertCellPoint( 27);
		faces->InsertCellPoint( 25);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 23);
		faces->InsertCellPoint( 25);
		faces->InsertCellPoint( 21);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 25);
		faces->InsertCellPoint( 29);
		faces->InsertCellPoint( 24);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 24);
		faces->InsertCellPoint( 29);
		faces->InsertCellPoint( 28);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 24);
		faces->InsertCellPoint( 28);
		faces->InsertCellPoint( 26);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 26);
		faces->InsertCellPoint( 28);
		faces->InsertCellPoint( 30);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 26);
		faces->InsertCellPoint( 30);
		faces->InsertCellPoint( 27);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 27);
		faces->InsertCellPoint( 30);
		faces->InsertCellPoint( 31);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 27);
		faces->InsertCellPoint( 31);
		faces->InsertCellPoint( 25);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 25);
		faces->InsertCellPoint( 31);
		faces->InsertCellPoint( 29);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 29);
		faces->InsertCellPoint( 19);
		faces->InsertCellPoint( 17);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 29);
		faces->InsertCellPoint( 17);
		faces->InsertCellPoint( 28);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 28);
		faces->InsertCellPoint( 17);
		faces->InsertCellPoint( 16);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 28);
		faces->InsertCellPoint( 16);
		faces->InsertCellPoint( 30);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 30);
		faces->InsertCellPoint( 16);
		faces->InsertCellPoint( 18);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 30);
		faces->InsertCellPoint( 18);
		faces->InsertCellPoint( 31);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 31);
		faces->InsertCellPoint( 18);
		faces->InsertCellPoint( 19);
		faces->InsertNextCell(3);
		faces->InsertCellPoint( 31);
		faces->InsertCellPoint( 19);
		faces->InsertCellPoint( 29);


	vtkPolyData *model=vtkPolyData::New();
	  model-> SetPolys( faces);
	  model-> SetPoints( points);


	//vtkButterflySubdivisionFilter subdivide
	vtkLoopSubdivisionFilter *subdivide=vtkLoopSubdivisionFilter::New();
	  subdivide-> SetInput( model);
	  subdivide-> SetNumberOfSubdivisions( 4);

	vtkDataSetMapper *mapper=vtkDataSetMapper::New();
	   mapper-> SetInputConnection (subdivide ->GetOutputPort());

	vtkLODActor *rose=vtkLODActor::New();
		rose-> SetMapper( mapper);
		vtkProperty *backP=vtkProperty::New();
		  backP-> SetDiffuseColor (1 ,1 ,.3);
		rose-> SetBackfaceProperty( backP);
		rose-> GetProperty() ->SetDiffuseColor( 1 ,.4 ,.3);
		rose-> GetProperty() ->SetSpecular( .4);
		rose-> GetProperty() ->SetDiffuse( .8);
		rose-> GetProperty() ->SetSpecularPower( 40);

	vtkFeatureEdges *fe=vtkFeatureEdges::New();
	  fe-> SetInputConnection (subdivide-> GetOutputPort());
	  fe-> SetFeatureAngle( 100);

	vtkPolyDataMapper *feMapper=vtkPolyDataMapper::New();
	  feMapper-> SetInputConnection (fe ->GetOutputPort());

	vtkActor *edges=vtkActor::New();
	  edges-> SetMapper( feMapper);

	ren1-> AddActor( rose);
	ren1-> AddActor (edges);

	ren1-> SetBackground (0.1, 0.2, 0.4);
	renWin-> SetSize (600, 600);

	ren1->ResetCamera();
	ren1->GetActiveCamera()->Zoom (4.5);
	ren1->GetActiveCamera()->Azimuth( -90);
	ren1-> ResetCameraClippingRange();
	iren-> Initialize();

  renWin->Render();
  iren->Start();
  // Clean up
  renWin->Delete();
  iren->Delete();


}
