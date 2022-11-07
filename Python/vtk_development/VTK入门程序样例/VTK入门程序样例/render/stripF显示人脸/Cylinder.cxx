
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkPNGReader.h"
#include "vtkTexture.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkTextProperty.h"
#include "vtkMaskPolyData.h"
#include "vtkPolyDataReader.h"
#include "vtkPolyDataMapper.h"

#include "vtkCastToConcrete.h"
#include "vtkProgrammableAttributeDataFilter.h"
#include "vtkMath.h"
#include "vtkRendererSource.h"
#include "vtkGlyph3D.h"
#include "vtkProperty.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkTransform.h"
#include "vtkMaskPoints.h"
#include "vtkStripper.h"

#include "vtkWindowToImageFilter.h"
#include "vtkImageMapper.h"
#include "vtkActor2D.h"
#include "vtkScalarBarActor.h"
#include "vtkPolyDataNormals.h"
int main()
{
	vtkRenderer *ren1= vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
        renWin->AddRenderer( ren1 );

	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
        iren->SetRenderWindow(renWin);

	vtkPNGReader *pnm1=vtkPNGReader::New();
		pnm1-> SetFileName("fran_cut.png");

	vtkTexture *atext=vtkTexture::New();
	    atext-> SetInputConnection(pnm1->GetOutputPort());
	    atext-> InterpolateOn();

	vtkPolyDataReader *fran=vtkPolyDataReader::New();
		fran-> SetFileName("fran_cut.vtk");

	vtkPolyDataNormals *normals=vtkPolyDataNormals::New();
		normals-> SetInputConnection (fran->GetOutputPort());
		normals-> FlipNormalsOn();

	vtkStripper *stripper=vtkStripper::New();
		stripper-> SetInputConnection (fran->GetOutputPort());

	vtkMaskPolyData *mask=vtkMaskPolyData::New();
		mask->  SetInputConnection (stripper ->GetOutputPort());
		mask->  SetOnRatio( 2);

    vtkPolyDataMapper *franMapper=vtkPolyDataMapper::New();
        franMapper-> SetInputConnection(mask-> GetOutputPort());

    vtkActor *franActor =vtkActor::New();
        franActor -> SetMapper (franMapper);
        franActor -> SetTexture (atext);

ren1-> AddActor (franActor); 

ren1-> SetBackground(1, 1, 1);

vtkCamera *camera=vtkCamera::New();
ren1-> SetActiveCamera( camera);


ren1-> GetActiveCamera()-> SetPosition(0.314753, -0.0699988, -0.264225 );
ren1-> GetActiveCamera()-> SetFocalPoint(0.00188636, -0.136847, -5.84226e-09 );
ren1-> GetActiveCamera()-> SetViewAngle(30);
ren1-> GetActiveCamera()-> SetViewUp( 0, 1, 0);

ren1-> ResetCameraClippingRange();


renWin-> SetSize( 600, 600);
renWin-> Render();


	iren->Initialize();
    iren->Start(); 

	ren1->Delete();
    renWin->Delete();
	iren->Delete();
    
	return 0;
}


	
	
