#include "vtkActor.h" 
#include "vtkBYUReader.h" 
#include "vtkClipPolyData.h" 
#include "vtkCutter.h" 
#include "vtkPlane.h" 
#include "vtkPolyData.h" 
#include "vtkPolyDataMapper.h" 
#include "vtkPolyDataNormals.h" 
#include "vtkProperty.h" 
#include "vtkRenderWindow.h" 
#include "vtkRenderWindowInteractor.h" 
#include "vtkRenderer.h" 
#include "vtkStripper.h" 
#include "vtkTriangleFilter.h"

#include "vtkCamera.h" 
#include "vtkVolume16Reader.h"
#include "vtkContourFilter.h"
#include "vtkCommand.h"
#include "vtkCallbackCommand.h"
#include "vtkPlaneWidget.h"


vtkRenderWindow *renWin;
vtkPlane *plane;
vtkClipPolyData *clipper;
vtkPolyDataMapper *clipMapper;
vtkStripper *cutStrips;
vtkCutter *cutEdges;
vtkPolyData *cutPoly;
vtkPolyDataMapper *cutMapper;

void *m_viewer;

class vtkTPWCallback : public vtkCommand
{
public:
  static vtkTPWCallback *New() 
    { return new vtkTPWCallback; }

  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkPlaneWidget *planeWidget = reinterpret_cast<vtkPlaneWidget*>(caller);
      planeWidget->GetPolyData(this->PolyData);
	  planeWidget->GetPlane(Plane);   
    }

  vtkTPWCallback():PolyData(0),Plane(0) {}
  vtkPolyData *PolyData;
  vtkPlane *Plane;
};



void Test_vtkCutter()
{

	void Cut(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata);

	vtkBYUReader *cow = vtkBYUReader::New();
	cow->SetGeometryFileName("cow.g");

	vtkPolyDataNormals *cowNormals = vtkPolyDataNormals::New();
		cowNormals->SetInputConnection(cow->GetOutputPort());


	plane = vtkPlane::New();
      plane->SetOrigin(100, 100, 100);

	cutEdges = vtkCutter::New();
		cutEdges->SetInputConnection(cowNormals->GetOutputPort());
		cutEdges->SetCutFunction(plane);
		cutEdges->GenerateCutScalarsOn();
		cutEdges->SetValue(0, 0.5); 

	cutStrips = vtkStripper::New();
		cutStrips->SetInputConnection(cutEdges->GetOutputPort());
		cutStrips->Update();

	vtkPolyData *cutPoly = vtkPolyData::New();
		cutPoly->SetPoints(cutStrips->GetOutput()->GetPoints());
		cutPoly->SetPolys(cutStrips->GetOutput()->GetLines());

	vtkTriangleFilter *cutTriangles = vtkTriangleFilter::New();
		cutTriangles->SetInput(cutPoly);

	cutMapper = vtkPolyDataMapper::New();
		cutMapper->SetInput(cutPoly);
		cutMapper->SetInputConnection(cutTriangles->GetOutputPort());

	vtkActor *cutActor = vtkActor::New();
		cutActor->SetMapper(cutMapper);
		cutActor->GetProperty()->SetColor(0.0, 0.0, 1.0);//切割平面
		cutActor->GetProperty()->SetOpacity  (0.5)  ;

	clipper = vtkClipPolyData::New();
		clipper->SetInputConnection(cowNormals->GetOutputPort());
		clipper->SetClipFunction(plane);
		clipper->GenerateClipScalarsOn();
		clipper->GenerateClippedOutputOn();
//		clipper->SetValue(0.5);

	clipMapper = vtkPolyDataMapper::New();
		clipMapper->SetInputConnection(clipper->GetOutputPort());
		clipMapper->ScalarVisibilityOff();

	vtkProperty *backProp = vtkProperty::New();
		backProp->SetDiffuseColor(1.0, 0.0, 0.0);

	vtkActor *clipActor = vtkActor::New();
		clipActor->SetMapper(clipMapper);//切割后的图形
		clipActor->GetProperty()->SetColor(1.0, 0.6, 0.1);
		clipActor->SetBackfaceProperty(backProp);


	vtkPolyDataMapper *restMapper = vtkPolyDataMapper::New();
		restMapper->SetInput(clipper->GetClippedOutput());
		restMapper->ScalarVisibilityOff();

	vtkActor *restActor = vtkActor::New();
		restActor->SetMapper(restMapper);//原始图形
		restActor->GetProperty()->SetOpacity  (0.2)  ;


	vtkRenderer *ren1 = vtkRenderer::New();

	renWin = vtkRenderWindow::New();
		renWin->AddRenderer(ren1);

    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	    iren->SetRenderWindow(renWin);


    vtkTPWCallback *myCallback = vtkTPWCallback::New();
	    myCallback->PolyData = cutPoly;
	    myCallback->Plane = plane;


	vtkPlaneWidget *planeWidget = vtkPlaneWidget::New();
		planeWidget->SetInteractor(iren);
		planeWidget->SetInput(cowNormals->GetOutput());
		planeWidget->SetPlaceFactor(1.25);
		planeWidget->SetRepresentationToOutline();
		planeWidget->PlaceWidget();
		planeWidget->AddObserver(vtkCommand::InteractionEvent,myCallback);

planeWidget->On();

	ren1->AddActor(clipActor);
	ren1->AddActor(cutActor);
	ren1->AddActor(restActor);
	ren1->SetBackground(1, 1, 1);
	ren1->ResetCamera();
	ren1->GetActiveCamera()->Azimuth(30);
	ren1->GetActiveCamera()->Elevation(30);
	ren1->GetActiveCamera()->Dolly(1.5);
	ren1->ResetCameraClippingRange();


	renWin->SetSize(600, 600);

	renWin->Render();
iren->SetKeyCode('i');
	iren->Initialize();
	iren->SetKeyCode('i');
	iren->Start();

}

int main()
{
	Test_vtkCutter();
	return 0;
}