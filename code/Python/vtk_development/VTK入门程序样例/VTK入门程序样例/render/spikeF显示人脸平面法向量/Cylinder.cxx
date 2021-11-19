
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
#include "vtkGlyph3D.h"
#include "vtkProperty.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkTransform.h"
#include "vtkMaskPoints.h"
#include "vtkConeSource.h"

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

    vtkPolyDataMapper *franMapper=vtkPolyDataMapper::New();
        franMapper-> SetInputConnection(normals-> GetOutputPort());

    vtkActor *franActor =vtkActor::New();
        franActor -> SetMapper (franMapper);
        franActor -> SetTexture (atext);

vtkMaskPoints *ptMask=vtkMaskPoints::New();
    ptMask-> SetInputConnection (normals-> GetOutputPort());
    ptMask-> SetOnRatio( 10);
    ptMask-> RandomModeOn();

// In this case we are using a cone as a glyph. We transform the cone so
// its base is at 0,0,0. This is the point where glyph rotation occurs.
vtkConeSource *cone=vtkConeSource::New();
    cone-> SetResolution (6);

vtkTransform *transform=vtkTransform::New();
    transform-> Translate (0.5, 0.0 ,0.0);

vtkTransformPolyDataFilter *transformF=vtkTransformPolyDataFilter::New();
    transformF-> SetInputConnection (cone-> GetOutputPort());
    transformF-> SetTransform (transform);

// vtkGlyph3D takes two inputs: the input point set (SetInputConnection)
// which can be any vtkDataSet; and the glyph (SetSourceConnection) which
// must be a vtkPolyData.  We are interested in orienting the glyphs by the
// surface normals that we previosuly generated.
vtkGlyph3D *glyph=vtkGlyph3D::New();
    glyph-> SetInputConnection  (ptMask-> GetOutputPort());
    glyph-> SetSource (transformF-> GetOutput());
    glyph-> SetVectorModeToUseNormal();
    glyph-> SetScaleModeToScaleByVector();
    glyph-> SetScaleFactor (0.004);

vtkPolyDataMapper *spikeMapper=vtkPolyDataMapper::New();
    spikeMapper-> SetInputConnection (glyph-> GetOutputPort());

vtkActor *spikeActor=vtkActor::New();
    spikeActor-> SetMapper(spikeMapper);
    spikeActor-> GetProperty() ->SetColor(0.0 ,0.79 ,0.34);


ren1-> AddActor (franActor); 
ren1-> AddActor (spikeActor); 

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


	
	
