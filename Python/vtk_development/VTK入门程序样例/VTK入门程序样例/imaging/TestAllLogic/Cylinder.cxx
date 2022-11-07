

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"

#include "vtkImageEllipsoidSource.h"
#include "vtkImageLogic.h"
#include "vtkImageMapper.h"
#include "vtkActor2D.h"

#include "vtkProperty.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkCommand.h"
#include "vtkCallbackCommand.h"


void main( )
{
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

    vtkImageEllipsoidSource *sphere1[6];
    vtkImageEllipsoidSource *sphere2[6];
    vtkImageLogic *logic[6];
    vtkImageMapper *mapper[6];
    vtkActor2D *actor[6];
    vtkRenderer *image[6];

	for(int i=0;i<6;i++)
	{
		sphere1[i]=vtkImageEllipsoidSource::New();
		  sphere1[i]-> SetCenter( 95, 100, 0);
		  sphere1[i]-> SetRadius( 70, 70, 70);
		  sphere1[i]-> SetOutputScalarTypeToUnsignedShort();

		sphere2[i]=vtkImageEllipsoidSource::New();
		  sphere2[i]-> SetCenter (161, 100, 0);
		  sphere2[i]-> SetRadius (70, 70, 70 );
		  sphere2[i]-> SetOutputScalarTypeToUnsignedShort();

		logic[i]=vtkImageLogic ::New();
		  logic[i]-> SetInput1 ((vtkDataObject *)sphere1[i]-> GetOutput());
		  logic[i]-> SetInput2 ((vtkDataObject *)sphere2[i]-> GetOutput());
		  logic[i]-> SetOutputTrueValue (150);
		  logic[i]-> SetOperation(i);//And, or, xor, nand, nor, not. 

		mapper[i]=vtkImageMapper::New();
		  mapper[i]-> SetInputConnection (logic[i]-> GetOutputPort());
		  mapper[i]-> SetColorWindow (255);
		  mapper[i]-> SetColorLevel (127.5);

		actor[i]=vtkActor2D::New();
		  actor[i]-> SetMapper (mapper[i]);

		image[i]=vtkRenderer::New();
		  image[i]-> AddActor2D (actor[i]);
		renWin-> AddRenderer (image[i]);
	}

  image[0]->SetViewport( 0, .5, .33, 1);
  image[1]->SetViewport( .33, .5, .66, 1);
  image[2]-> SetViewport( .66, .5, 1, 1);
  image[3]-> SetViewport( 0, 0, .33, .5);
  image[4]-> SetViewport( .33, 0, .66, .5);
  image[5]-> SetViewport( .66, 0, 1, .5);

  renWin->SetSize(768,512);

  renWin->Render();

  iren->Start();

  renWin->Delete();
  iren->Delete();
}