
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkJPEGReader.h"
#include "vtkTexture.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkTextProperty.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkStripper.h"
#include "vtkWindowToImageFilter.h"
#include "vtkImageMapper.h"
#include "vtkPolyDataNormals.h"
#include "vtkPlane.h"
#include "vtkClipPolyData.h"
#include "vtkBMPReader.h"
#include "vtkTransformTextureCoords.h"
#include "vtkDataSetMapper.h"
#include "vtkTextureMapToCylinder.h"
#include "vtkPolyData.h"
#include "vtkCellArray.h"
#include "vtkPlaneSource.h"

int main()
{
	vtkRenderer *ren1= vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
        renWin->AddRenderer( ren1 );

	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
        iren->SetRenderWindow(renWin);

/////////////////////天空纹理
	vtkJPEGReader *pnm1=vtkJPEGReader::New();
		pnm1-> SetFileName("高山云海_04.jpg");
/*
	vtkBMPReader *pnm1=vtkBMPReader::New();
		pnm1-> SetFileName("ddd.bmp");
*/
	vtkTexture *atext=vtkTexture::New();
	    atext-> SetInputConnection(pnm1->GetOutputPort());
	    atext-> InterpolateOn();

///////////////////////绿地纹理
	vtkJPEGReader *pnm2=vtkJPEGReader::New();
		pnm2-> SetFileName("风景_18.jpg");
/*
	vtkBMPReader *pnm1=vtkBMPReader::New();
		pnm1-> SetFileName("ddd.bmp");
*/
	vtkTexture *datext=vtkTexture::New();
	    datext-> SetInputConnection(pnm2->GetOutputPort());
	    datext-> InterpolateOn();

////////////////////////天空actor
	vtkSphereSource *sphere = vtkSphereSource::New();
		sphere->SetThetaResolution(100); 
		sphere->SetPhiResolution(100);
		sphere->SetRadius(0.5);

    vtkPlane *plane1=vtkPlane::New();
	  plane1->SetNormal(0,0,1);//设置切平面的法向量
	  plane1->SetOrigin(1,0,0);

    vtkClipPolyData *clipper=vtkClipPolyData::New();
      clipper->SetInputConnection(sphere-> GetOutputPort());
      clipper->SetClipFunction(plane1);
      clipper->InsideOutOff();

	vtkPolyDataNormals *normals=vtkPolyDataNormals::New();
		normals-> SetInputConnection (clipper->GetOutputPort());
		normals-> FlipNormalsOn();

	vtkTextureMapToCylinder *tmapper=vtkTextureMapToCylinder::New();
	  tmapper->SetInput(normals->GetOutput());
	  tmapper->PreventSeamOn();

	vtkTransformTextureCoords *xform=vtkTransformTextureCoords::New();
	  xform-> SetInputConnection(tmapper-> GetOutputPort());
	  xform-> SetScale( 1, 1, 1);

    vtkDataSetMapper  *franMapper=vtkDataSetMapper::New();
        franMapper-> SetInputConnection(xform-> GetOutputPort());

    vtkActor *franActor =vtkActor::New();
        franActor -> SetMapper (franMapper);
        franActor -> SetTexture (atext);

////////////////////////////////绿地
    vtkPlaneSource *plane = vtkPlaneSource::New();
        plane->SetResolution(10,10);

	vtkPolyDataNormals *dnormals=vtkPolyDataNormals::New();
		dnormals-> SetInputConnection (plane-> GetOutputPort());
		dnormals-> FlipNormalsOn();

	vtkTextureMapToCylinder *dtmapper=vtkTextureMapToCylinder::New();
	  dtmapper->SetInput(dnormals->GetOutput());
	  dtmapper->PreventSeamOn();

	vtkTransformTextureCoords *dxform=vtkTransformTextureCoords::New();
	  dxform-> SetInputConnection(dtmapper-> GetOutputPort());
	  dxform-> SetScale( 4, 4, 1);

    vtkPolyDataMapper *dfranMapper=vtkPolyDataMapper::New();
        dfranMapper-> SetInputConnection(dxform-> GetOutputPort());

    vtkActor *dfranActor =vtkActor::New();
        dfranActor -> SetMapper (dfranMapper);
        dfranActor -> SetTexture (datext);


ren1-> AddActor (franActor); 
ren1-> AddActor (dfranActor);
ren1-> SetBackground(1, 1, 1);

vtkCamera *camera=vtkCamera::New();
ren1-> SetActiveCamera( camera);


ren1-> GetActiveCamera()-> SetPosition(0, 0, 0.02 );
ren1-> GetActiveCamera()-> SetFocalPoint(0.0, 0.05, 0.03 );
ren1-> GetActiveCamera()-> SetViewAngle(30);
ren1-> GetActiveCamera()-> SetViewUp( 0, 0, 1);

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


	
	
