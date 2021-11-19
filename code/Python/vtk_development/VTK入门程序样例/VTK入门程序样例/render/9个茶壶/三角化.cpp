#include "vtkPolyDataMapper.h"
#include "vtkPolyDataReader.h"
#include "vtkRenderer.h"
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkWin32RenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkTexture.h"
#include "vtkTextureMapToCylinder.h"
#include "vtkPointSource.h"
#include "vtkTransformTextureCoords.h"
#include "vtkDelaunay3D.h"
#include "vtkPolyData.h"
#include "vtkDataSetMapper.h"
#include "vtkBMPReader.h"
#include "vtkHull.h"
#include "vtkBYUReader.h"
#include "vtkPolyDataNormals.h"
#include "vtkTriangleFilter.h"
#include "vtkFeatureEdges.h"
#include "vtkPolyDataMapper.h"

void main()
{
//Compute normals, in case they are not provided with the model.
	vtkRenderer *ren=vtkRenderer::New();
	vtkWin32OpenGLRenderWindow *renWin=vtkWin32OpenGLRenderWindow::New();
  	  renWin->AddRenderer(ren);
	vtkWin32RenderWindowInteractor *iren=vtkWin32RenderWindowInteractor::New();
	  iren->SetRenderWindow(renWin);	

	vtkBYUReader *byuReader=vtkBYUReader::New();
	  byuReader->SetGeometryFileName("teapot.g");
	
	vtkPolyDataMapper  *byuMapper=vtkPolyDataMapper::New();
      byuMapper-> SetInputConnection (byuReader-> GetOutputPort());

	double diagonal;
	  
////////////////////0
    vtkActor *byuActor0=vtkActor::New();
      byuActor0-> SetMapper (byuMapper);
    ren-> AddActor (byuActor0);

    vtkHull *hull0=vtkHull::New();
    hull0-> SetInputConnection (byuReader-> GetOutputPort());

    vtkPolyDataMapper *hullMapper0=vtkPolyDataMapper::New();
    hullMapper0-> SetInputConnection (hull0-> GetOutputPort());
    
    vtkActor *hullActor0=vtkActor::New();
    hullActor0-> SetMapper (hullMapper0);
    hullActor0-> GetProperty()-> SetColor (1 ,0, 0);
    hullActor0-> GetProperty()-> SetAmbient (0.2);
    hullActor0-> GetProperty()-> SetDiffuse (0.8);
    hullActor0-> GetProperty()-> SetRepresentationToWireframe();

    ren->AddActor(hullActor0);


	diagonal =byuActor0-> GetLength();


	byuActor0->AddPosition ( -diagonal,-diagonal, 0);
	hullActor0->AddPosition( -diagonal,-diagonal, 0);

	  
////////////////////1
    vtkActor *byuActor1=vtkActor::New();
      byuActor1-> SetMapper (byuMapper);
    ren-> AddActor (byuActor1);

    vtkHull *hull1=vtkHull::New();
    hull1-> SetInputConnection (byuReader-> GetOutputPort());

    vtkPolyDataMapper *hullMapper1=vtkPolyDataMapper::New();
    hullMapper1-> SetInputConnection (hull1-> GetOutputPort());
    
    vtkActor *hullActor1=vtkActor::New();
    hullActor1-> SetMapper (hullMapper1);
    hullActor1-> GetProperty()-> SetColor (1 ,0, 0);
    hullActor1-> GetProperty()-> SetAmbient (0.2);
    hullActor1-> GetProperty()-> SetDiffuse (0.8);
    hullActor1-> GetProperty()-> SetRepresentationToWireframe();

    ren->AddActor(hullActor1);


	diagonal =byuActor1-> GetLength();


	byuActor1->AddPosition ( - diagonal,  0, 0);
	hullActor1->AddPosition( - diagonal,  0, 0);

	  
////////////////////2
    vtkActor *byuActor2=vtkActor::New();
      byuActor2-> SetMapper (byuMapper);
    ren-> AddActor (byuActor2);

    vtkHull *hull2=vtkHull::New();
    hull2-> SetInputConnection (byuReader-> GetOutputPort());

    vtkPolyDataMapper *hullMapper2=vtkPolyDataMapper::New();
    hullMapper2-> SetInputConnection (hull2-> GetOutputPort());
    
    vtkActor *hullActor2=vtkActor::New();
    hullActor2-> SetMapper (hullMapper2);
    hullActor2-> GetProperty()-> SetColor (1 ,0, 0);
    hullActor2-> GetProperty()-> SetAmbient (0.2);
    hullActor2-> GetProperty()-> SetDiffuse (0.8);
    hullActor2-> GetProperty()-> SetRepresentationToWireframe();

    ren->AddActor(hullActor2);

	diagonal =byuActor2-> GetLength();


	byuActor2->AddPosition (-diagonal, diagonal, 0);
	hullActor2->AddPosition(-diagonal, diagonal, 0);

	  
////////////////////3
    vtkActor *byuActor3=vtkActor::New();
      byuActor3-> SetMapper (byuMapper);
    ren-> AddActor (byuActor3);

    vtkHull *hull3=vtkHull::New();
    hull3-> SetInputConnection (byuReader-> GetOutputPort());

    vtkPolyDataMapper *hullMapper3=vtkPolyDataMapper::New();
    hullMapper3-> SetInputConnection (hull3-> GetOutputPort());
    
    vtkActor *hullActor3=vtkActor::New();
    hullActor3-> SetMapper (hullMapper3);
    hullActor3-> GetProperty()-> SetColor (1 ,0, 0);
    hullActor3-> GetProperty()-> SetAmbient (0.2);
    hullActor3-> GetProperty()-> SetDiffuse (0.8);
    hullActor3-> GetProperty()-> SetRepresentationToWireframe();

    ren->AddActor(hullActor3);


	diagonal =byuActor3-> GetLength();


	byuActor3->AddPosition ( 0, -diagonal, 0);
	hullActor3->AddPosition( 0, - diagonal, 0);

	  
////////////////////4
    vtkActor *byuActor4=vtkActor::New();
      byuActor4-> SetMapper (byuMapper);
    ren-> AddActor (byuActor4);

    vtkHull *hull4=vtkHull::New();
    hull4-> SetInputConnection (byuReader-> GetOutputPort());

    vtkPolyDataMapper *hullMapper4=vtkPolyDataMapper::New();
    hullMapper4-> SetInputConnection (hull4-> GetOutputPort());
    
    vtkActor *hullActor4=vtkActor::New();
    hullActor4-> SetMapper (hullMapper4);
    hullActor4-> GetProperty()-> SetColor (1 ,0, 0);
    hullActor4-> GetProperty()-> SetAmbient (0.2);
    hullActor4-> GetProperty()-> SetDiffuse (0.8);
    hullActor4-> GetProperty()-> SetRepresentationToWireframe();

    ren->AddActor(hullActor4);


	diagonal =byuActor4-> GetLength();


		byuActor4->AddPosition ( 0, 0, 0);
		hullActor4->AddPosition( 0, 0, 0);

////////////////////5
    vtkActor *byuActor5=vtkActor::New();
      byuActor5-> SetMapper (byuMapper);
    ren-> AddActor (byuActor5);

    vtkHull *hull5=vtkHull::New();
    hull5-> SetInputConnection (byuReader-> GetOutputPort());

    vtkPolyDataMapper *hullMapper5=vtkPolyDataMapper::New();
    hullMapper5-> SetInputConnection (hull5-> GetOutputPort());
    
    vtkActor *hullActor5=vtkActor::New();
    hullActor5-> SetMapper (hullMapper5);
    hullActor5-> GetProperty()-> SetColor (1 ,0, 0);
    hullActor5-> GetProperty()-> SetAmbient (0.2);
    hullActor5-> GetProperty()-> SetDiffuse (0.8);
    hullActor5-> GetProperty()-> SetRepresentationToWireframe();

    ren->AddActor(hullActor5);


	diagonal =byuActor5-> GetLength();

		byuActor5->AddPosition ( 0, diagonal, 0);
		hullActor5->AddPosition( 0, diagonal, 0);

////////////////////6
    vtkActor *byuActor6=vtkActor::New();
      byuActor6-> SetMapper (byuMapper);
    ren-> AddActor (byuActor6);

    vtkHull *hull6=vtkHull::New();
    hull6-> SetInputConnection (byuReader-> GetOutputPort());

    vtkPolyDataMapper *hullMapper6=vtkPolyDataMapper::New();
    hullMapper6-> SetInputConnection (hull6-> GetOutputPort());
    
    vtkActor *hullActor6=vtkActor::New();
    hullActor6-> SetMapper (hullMapper6);
    hullActor6-> GetProperty()-> SetColor (1 ,0, 0);
    hullActor6-> GetProperty()-> SetAmbient (0.2);
    hullActor6-> GetProperty()-> SetDiffuse (0.8);
    hullActor6-> GetProperty()-> SetRepresentationToWireframe();

    ren->AddActor(hullActor6);


	diagonal =byuActor6-> GetLength();


	byuActor6->AddPosition ( diagonal, -diagonal, 0);
	hullActor6->AddPosition( diagonal, -diagonal, 0);
////////////////////7
    vtkActor *byuActor7=vtkActor::New();
      byuActor7-> SetMapper (byuMapper);
    ren-> AddActor (byuActor7);

    vtkHull *hull7=vtkHull::New();
    hull7-> SetInputConnection (byuReader-> GetOutputPort());

    vtkPolyDataMapper *hullMapper7=vtkPolyDataMapper::New();
    hullMapper7-> SetInputConnection (hull7-> GetOutputPort());
    
    vtkActor *hullActor7=vtkActor::New();
    hullActor7-> SetMapper (hullMapper7);
    hullActor7-> GetProperty()-> SetColor (1 ,0, 0);
    hullActor7-> GetProperty()-> SetAmbient (0.2);
    hullActor7-> GetProperty()-> SetDiffuse (0.8);
    hullActor7-> GetProperty()-> SetRepresentationToWireframe();

    ren->AddActor(hullActor7);


	diagonal =byuActor7-> GetLength();


		byuActor7->AddPosition (diagonal, 0, 0);
		hullActor7->AddPosition(diagonal, 0, 0);

////////////////////8
    vtkActor *byuActor8=vtkActor::New();
      byuActor8-> SetMapper (byuMapper);
    ren-> AddActor (byuActor8);

    vtkHull *hull8=vtkHull::New();
    hull8-> SetInputConnection (byuReader-> GetOutputPort());

    vtkPolyDataMapper *hullMapper8=vtkPolyDataMapper::New();
    hullMapper8-> SetInputConnection (hull8-> GetOutputPort());
    
    vtkActor *hullActor8=vtkActor::New();
    hullActor8-> SetMapper (hullMapper8);
    hullActor8-> GetProperty()-> SetColor (1 ,0, 0);
    hullActor8-> GetProperty()-> SetAmbient (0.2);
    hullActor8-> GetProperty()-> SetDiffuse (0.8);
    hullActor8-> GetProperty()-> SetRepresentationToWireframe();

    ren->AddActor(hullActor8);


	diagonal =byuActor8-> GetLength();

	byuActor8->AddPosition ( diagonal, diagonal, 0);
	hullActor8->AddPosition( diagonal, diagonal, 0);
	
////////////////////


hull0-> AddCubeFacePlanes();   
hull1-> AddCubeEdgePlanes(); 
hull2-> AddCubeVertexPlanes(); 
hull3-> AddCubeFacePlanes(); 
hull3-> AddCubeEdgePlanes(); 
hull3-> AddCubeVertexPlanes(); 
hull4-> AddRecursiveSpherePlanes (0); 
hull5-> AddRecursiveSpherePlanes (1);
hull6-> AddRecursiveSpherePlanes (2);
hull7-> AddRecursiveSpherePlanes (3);
hull8-> AddRecursiveSpherePlanes (4);
 
	ren->ResetCamera();
	ren->SetBackground(1,1,1);

	renWin->SetSize(300,300);
	renWin->Render();
	iren->Start();

	ren->Delete();
	iren->Delete();
	renWin->Delete();
}






