


#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphere.h"
#include "vtkTexturedSphereSource.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkEarthSource.h"
#include "vtkPNMReader.h"
#include "vtkProperty.h"
#include "vtkPolyData.h"
#include "vtkSampleFunction.h"
#include "vtkTexture.h"
#include "vtkContourFilter.h"
#include "vtkPolyDataNormals.h"
#include "vtkPolyDataMapper.h"

void main()
{
	vtkRenderer *ren1 = vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
      renWin->AddRenderer(ren1);
    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
      iren->SetRenderWindow(renWin);

	vtkTexturedSphereSource *tss=vtkTexturedSphereSource::New();
	  tss-> SetThetaResolution (40);
	  tss-> SetPhiResolution (40);
	vtkPolyDataMapper   *earthMapper=vtkPolyDataMapper::New();
	  earthMapper-> SetInputConnection (tss->GetOutputPort());
	vtkActor *earthActor=vtkActor::New();
	  earthActor-> SetMapper (earthMapper);

	vtkTexture *atext=vtkTexture::New();
	vtkPNMReader *pnmReader=vtkPNMReader::New();
	  pnmReader-> SetFileName ("earth.ppm");
	  atext-> SetInputConnection (pnmReader-> GetOutputPort());
	  atext-> InterpolateOn();

	  earthActor->SetTexture (atext);

	vtkEarthSource *es=vtkEarthSource::New();
	  es-> SetRadius (0.501);
	  es-> SetOnRatio (2);
	vtkPolyDataMapper   *earth2Mapper=vtkPolyDataMapper::New();
	  earth2Mapper-> SetInputConnection (es-> GetOutputPort());
	vtkActor *earth2Actor=vtkActor::New();
	  earth2Actor-> SetMapper (earth2Mapper);

	  ren1-> AddActor (earthActor);
	  ren1-> AddActor (earth2Actor);
	  ren1-> SetBackground (1, 1, 1);
	  renWin-> SetSize (600,500);

	  ren1-> ResetCamera();
	  ren1-> GetActiveCamera()->Zoom( 1.4);

	  renWin->Render();
	  iren->Start();
}
