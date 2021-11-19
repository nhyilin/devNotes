
#include "vtkDICOMImageReader.h"
#include "vtkImageCast.h"
#include "vtkRenderWindow.h"
#include "vtkImageReslice.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkProperty.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkActor2D.h"
#include "vtkImageMapper.h"

int main()
{
    vtkDICOMImageReader *readerDcm=vtkDICOMImageReader::New();
	  readerDcm->SetDataByteOrderToLittleEndian();
	  readerDcm->SetDirectoryName("E://CT/head30/");
	  readerDcm->SetDataOrigin(-100,-100,-41);
	  readerDcm->Update();

    vtkImageCast *readerImageCast = vtkImageCast::New();
	  readerImageCast->SetInputConnection(readerDcm->GetOutputPort());
	  readerImageCast->SetOutputScalarTypeToUnsignedShort();
	  readerImageCast->ClampOverflowOn();

	vtkImageReslice *reslice1=vtkImageReslice::New();
	  reslice1-> SetInputConnection (readerImageCast-> GetOutputPort());
	  reslice1-> SetInterpolationModeToCubic();
  	  reslice1-> SetOutputSpacing( 0.65 ,0.65 ,1.5);
	  reslice1-> SetOutputOrigin( 80, 120, 40 );
	  reslice1-> SetOutputExtent( 0 ,300 ,0, 300 ,0, 0);

	vtkImageReslice *reslice2=vtkImageReslice::New();
	  reslice2-> SetInputConnection (readerImageCast-> GetOutputPort());
	  reslice2-> SetInterpolationModeToLinear();
	  reslice2-> SetOutputSpacing (0.65, 0.65, 1.5);
	  reslice2-> SetOutputOrigin (80, 120, 40 );
	  reslice2-> SetOutputExtent( 0, 300, 0, 300, 0, 0);

	vtkImageReslice *reslice3=vtkImageReslice::New();
	  reslice3-> SetInputConnection (readerImageCast-> GetOutputPort());
	  reslice3-> SetInterpolationModeToNearestNeighbor();
	  reslice3-> SetOutputSpacing (0.65 ,0.65 ,1.5);
	  reslice3-> SetOutputOrigin (80 ,120 ,40 );
	  reslice3-> SetOutputExtent (0 ,300 ,0 ,300 ,0 ,0);

	vtkImageReslice *reslice4=vtkImageReslice::New();
	  reslice4-> SetInputConnection (readerImageCast-> GetOutputPort());
	  reslice4-> SetInterpolationModeToLinear();
	  reslice4-> SetOutputSpacing (3.2 ,3.2 ,1.5);
	  reslice4-> SetOutputOrigin (0 ,0,40 );
	  reslice4-> SetOutputExtent (0 ,300 ,0,300 ,0 ,0);

	vtkImageMapper *mapper1=vtkImageMapper::New();
	  mapper1-> SetInputConnection (reslice1->GetOutputPort());
//	  mapper1-> SetColorWindow (1000);
//	  mapper1-> SetColorLevel (0000);
	  mapper1-> SetZSlice (0);

	vtkImageMapper *mapper2=vtkImageMapper::New();
	  mapper2-> SetInputConnection (reslice2->GetOutputPort());
//	  mapper2-> SetColorWindow (1000);
//	  mapper2-> SetColorLevel (0);
	  mapper2-> SetZSlice (0 );

	vtkImageMapper *mapper3=vtkImageMapper::New();
	  mapper3-> SetInputConnection (reslice3->GetOutputPort());
//	  mapper3-> SetColorWindow (1000);
//	  mapper3-> SetColorLevel (0);
	  mapper3-> SetZSlice (0 );

	vtkImageMapper *mapper4=vtkImageMapper::New();
	  mapper4-> SetInputConnection (reslice4->GetOutputPort());
//	  mapper4-> SetColorWindow (1000);
//	  mapper4-> SetColorLevel (0);
	  mapper4-> SetZSlice (0 );

	vtkActor2D *actor1=vtkActor2D::New();
	  actor1-> SetMapper (mapper1);

	vtkActor2D *actor2=vtkActor2D::New();
	  actor2-> SetMapper (mapper2);

	vtkActor2D *actor3=vtkActor2D::New();
	  actor3-> SetMapper (mapper3);

	vtkActor2D *actor4=vtkActor2D::New();
	  actor4-> SetMapper (mapper4);

	vtkRenderer *imager1=vtkRenderer::New();
	  imager1-> AddActor2D (actor1);
	  imager1-> SetViewport( 0.5, 0.0, 1.0, 0.5);

	vtkRenderer *imager2=vtkRenderer::New();
	  imager2-> AddActor2D( actor2);
	  imager2-> SetViewport( 0.0, 0.0, 0.5, 0.5);

	vtkRenderer *imager3=vtkRenderer::New();
	  imager3-> AddActor2D (actor3);
	  imager3-> SetViewport( 0.5, 0.5, 1.0 ,1.0);

	vtkRenderer *imager4=vtkRenderer::New();
	  imager4-> AddActor2D (actor4);
	  imager4-> SetViewport( 0.0, 0.5, 0.5, 1.0);

	vtkRenderWindow *imgWin=vtkRenderWindow::New();
	  imgWin-> AddRenderer (imager1);
	  imgWin-> AddRenderer (imager2);
	  imgWin-> AddRenderer (imager3);
	  imgWin-> AddRenderer (imager4);
	  imgWin-> SetSize (600, 600);

    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
      iren->SetRenderWindow(imgWin);
    
	imgWin-> Render();
	iren->Start();

  return 0;
}


