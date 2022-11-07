
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkPNGReader.h"
#include "vtkTexture.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkTextProperty.h"
#include "vtkPolyDataReader.h"
#include "vtkDecimatePro.h"
#include "vtkPolyDataMapper.h"

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

#include "vtkWindowToImageFilter.h"
#include "vtkImageMapper.h"
#include "vtkActor2D.h"
#include "vtkScalarBarActor.h"

int main()
{
	vtkRenderer *ren1= vtkRenderer::New();
	vtkRenderer *ren2= vtkRenderer::New();
	vtkRenderer *ren3= vtkRenderer::New();
	vtkRenderer *ren4= vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
      renWin->AddRenderer( ren1 );
	  renWin->AddRenderer( ren2 );
	  renWin->AddRenderer( ren3 );
	  renWin->AddRenderer( ren4 );
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
      iren->SetRenderWindow(renWin);

vtkPNGReader *pnm1=vtkPNGReader::New();
    pnm1-> SetFileName("fran_cut.png");

vtkTexture *atext=vtkTexture::New();
  atext-> SetInputConnection(pnm1->GetOutputPort());
  atext-> InterpolateOn();

vtkPolyDataReader *fran=vtkPolyDataReader::New();
    fran-> SetFileName("fran_cut.vtk");

    vtkDecimatePro *deci11=vtkDecimatePro::New();
      deci11-> SetInputConnection (fran-> GetOutputPort());
      deci11-> SetTargetReduction (0.95);
      deci11-> PreserveTopologyOn();
      deci11-> AccumulateErrorOn();
    vtkPolyDataMapper *mapper11=vtkPolyDataMapper::New();
      mapper11-> SetInputConnection(deci11-> GetOutputPort());
    vtkActor *fran11=vtkActor::New();
      fran11-> SetMapper (mapper11);
      fran11-> SetTexture (atext);

    vtkDecimatePro *deci10=vtkDecimatePro::New();
      deci10-> SetInputConnection (fran-> GetOutputPort());
      deci10-> SetTargetReduction (0.95);
      deci10-> PreserveTopologyOn();
      deci10-> AccumulateErrorOff();
    vtkPolyDataMapper *mapper10=vtkPolyDataMapper::New();
      mapper10-> SetInputConnection(deci10-> GetOutputPort());
    vtkActor *fran10=vtkActor::New();
      fran10-> SetMapper (mapper10);
      fran10-> SetTexture (atext);

    vtkDecimatePro *deci01=vtkDecimatePro::New();
      deci01-> SetInputConnection (fran-> GetOutputPort());
      deci01-> SetTargetReduction (0.95);
      deci01-> PreserveTopologyOff();
      deci01-> AccumulateErrorOn();
    vtkPolyDataMapper *mapper01=vtkPolyDataMapper::New();
      mapper01-> SetInputConnection(deci01-> GetOutputPort());
    vtkActor *fran01=vtkActor::New();
      fran01-> SetMapper (mapper01);
      fran01-> SetTexture (atext);

    vtkDecimatePro *deci00=vtkDecimatePro::New();
      deci00-> SetInputConnection (fran-> GetOutputPort());
      deci00-> SetTargetReduction (0.95);
      deci00-> PreserveTopologyOff();
      deci00-> AccumulateErrorOff();
    vtkPolyDataMapper *mapper00=vtkPolyDataMapper::New();
      mapper00-> SetInputConnection(deci00-> GetOutputPort());
    vtkActor *fran00=vtkActor::New();
      fran00-> SetMapper (mapper00);
      fran00-> SetTexture (atext);

ren1-> SetViewport( 0, .5, .5, 1);
ren2-> SetViewport( .5, .5, 1, 1);
ren3-> SetViewport( 0 ,0, .5, .5);
ren4-> SetViewport( .5, 0 ,1, .5);

ren1-> AddActor (fran11); 
ren2-> AddActor (fran10);
ren3-> AddActor (fran01);
ren4-> AddActor (fran00);

ren1-> SetBackground(1, 1, 1);
ren2-> SetBackground(1, 1, 1);
ren3-> SetBackground(1, 1, 1);
ren4-> SetBackground(1, 1, 1);

vtkCamera *camera=vtkCamera::New();
ren1-> SetActiveCamera( camera);
ren2-> SetActiveCamera( camera);
ren3-> SetActiveCamera( camera);
ren4-> SetActiveCamera( camera);

ren1-> GetActiveCamera()-> SetPosition(0.314753, -0.0699988, -0.264225 );
ren1-> GetActiveCamera()-> SetFocalPoint(0.00188636, -0.136847, -5.84226e-09 );
ren1-> GetActiveCamera()-> SetViewAngle(30);
ren1-> GetActiveCamera()-> SetViewUp( 0, 1, 0);

ren1-> ResetCameraClippingRange();
ren2-> ResetCameraClippingRange();
ren3-> ResetCameraClippingRange();
ren4-> ResetCameraClippingRange();

renWin-> SetSize( 780, 780);
renWin-> Render();


	iren->Initialize();
    iren->Start(); 

	ren1->Delete();
    renWin->Delete();
	iren->Delete();
    
	return 0;
}


	
	
