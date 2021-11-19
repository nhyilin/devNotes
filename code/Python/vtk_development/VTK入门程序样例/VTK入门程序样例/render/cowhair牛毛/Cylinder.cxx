
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkPLOT3DReader.h"
#include "vtkPolyDataNormals.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkTextProperty.h"
#include "vtkTexture.h"
#include "vtkFloatArray.h"
#include "vtkContourFilter.h"
#include "vtkCastToConcrete.h"
#include "vtkProgrammableAttributeDataFilter.h"
#include "vtkMath.h"
#include "vtkRendererSource.h"
#include "vtkProgrammableAttributeDataFilter.h"
#include "vtkProperty.h"
#include "vtkSphereSource.h"
#include "vtkPointData.h"
#include "vtkHedgeHog.h"
#include "vtkCleanPolyData.h"

#include "vtkTransformPolyDataFilter.h"
#include "vtkTransform.h"
#include "vtkConeSource.h"
#include "vtkOBJReader.h"

int main()
{
	vtkRenderer *ren1= vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
      renWin->AddRenderer( ren1 );
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
      iren->SetRenderWindow(renWin);

vtkOBJReader *wavefront=vtkOBJReader::New();
  wavefront-> SetFileName ("cow.obj");
  wavefront-> Update();

vtkConeSource *cone=vtkConeSource::New();
    cone-> SetResolution( 6);
    cone-> SetRadius (.1);

vtkTransform *transform=vtkTransform::New();
    transform-> Translate (0.5 ,0.0 ,0.0);

vtkTransformPolyDataFilter *transformF=vtkTransformPolyDataFilter::New();
    transformF-> SetInputConnection(cone-> GetOutputPort());
    transformF-> SetTransform(transform);

// we just clean the normals for efficiency (keep down number of cones)
vtkCleanPolyData *clean=vtkCleanPolyData::New();
  clean-> SetInputConnection(wavefront-> GetOutputPort());

vtkHedgeHog *glyph=vtkHedgeHog::New();
  glyph-> SetInputConnection(clean-> GetOutputPort());
  glyph-> SetVectorModeToUseNormal();
  glyph-> SetScaleFactor (0.4);

vtkPolyDataMapper *hairMapper=vtkPolyDataMapper::New();
  hairMapper-> SetInputConnection (glyph-> GetOutputPort());

vtkActor *hair=vtkActor::New();
  hair-> SetMapper (hairMapper);

vtkPolyDataMapper *cowMapper=vtkPolyDataMapper::New();
  cowMapper-> SetInputConnection (wavefront-> GetOutputPort());

vtkActor *cow=vtkActor::New();
  cow-> SetMapper (cowMapper);

hair-> GetProperty()-> SetDiffuseColor (1,0.2,0.6);
hair-> GetProperty()->  SetAmbientColor(0,0.8,0.1);
hair-> GetProperty()->  SetAmbient( .3);
cow-> GetProperty()->  SetDiffuseColor(1,0.8,0.1);

	  ren1->AddActor(cow);
	  ren1->AddActor(hair);
	  ren1->SetBackground( 1, 1, 1 );
	  ren1-> ResetCamera();

    renWin->SetSize( 600, 600 );
	renWin-> Render();

	iren->Initialize();
    iren->Start(); 

	ren1->Delete();
    renWin->Delete();
	iren->Delete();
    
	return 0;
}


	
	
