#include "vtkContourFilter.h" 
#include "vtkHedgeHog.h" 
#include "vtkPLOT3DReader.h" 
#include "vtkProbeFilter.h" 
#include "vtkRenderWindow.h" 
#include "vtkRenderWindowInteractor.h" 
#include "vtkRenderer.h" 
#include "vtkActor.h" 
#include "vtkLODActor.h" 
#include "vtkPLOT3DReader.h" 
#include "vtkPolyDataMapper.h" 
#include "vtkProgrammableAttributeDataFilter.h" 
#include "vtkStructuredGridOutlineFilter.h" 


#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkDataSetCollection.h"
#include "vtkDataSet.h"
#include "vtkPointData.h"
#include "vtkFloatArray.h"

vtkProgrammableAttributeDataFilter *dotProduct;

int main()
{


	void ExecuteDot(void *);

// Create the RenderWindow, Renderer and interactor
//
vtkRenderer *ren1 = vtkRenderer::New();
vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer(ren1);

vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);

// create pipeline
//

// get the pressure gradient vector field
vtkPLOT3DReader *pl3d_gradient = vtkPLOT3DReader::New();
	pl3d_gradient->SetXYZFileName("combxyz.bin");
	pl3d_gradient->SetQFileName("combq.bin");
	pl3d_gradient->SetScalarFunctionNumber(100);
	pl3d_gradient->SetVectorFunctionNumber(210);
	pl3d_gradient->Update();

// get the velocity vector field
vtkPLOT3DReader *pl3d_velocity = vtkPLOT3DReader::New();
	pl3d_velocity->SetXYZFileName("combxyz.bin");
	pl3d_velocity->SetQFileName("combq.bin");
	pl3d_velocity->SetScalarFunctionNumber(100);
	pl3d_velocity->SetVectorFunctionNumber(200);
	pl3d_velocity->Update();


// contour the scalar fields
vtkContourFilter *contour = vtkContourFilter::New();
	contour->SetInputConnection(pl3d_gradient->GetOutputPort());
	contour->SetValue(0, 0.225);

// probe the vector fields to get data at the contour surface
vtkProbeFilter *probe_gradient = vtkProbeFilter::New();
	probe_gradient->SetInputConnection(contour->GetOutputPort());
	probe_gradient->SetSource((vtkDataSet *)pl3d_gradient->GetOutput());

vtkProbeFilter *probe_velocity = vtkProbeFilter::New();
	probe_velocity->SetInputConnection(contour->GetOutputPort());
	probe_velocity->SetSource((vtkDataSet  *)pl3d_velocity->GetOutput());



vtkHedgeHog *velocity = vtkHedgeHog::New();
	velocity->SetInputConnection(probe_velocity->GetOutputPort());
	velocity->SetScaleFactor(0.0015);

vtkHedgeHog *pressureGradient = vtkHedgeHog::New();
	pressureGradient->SetInputConnection(probe_gradient->GetOutputPort());
	pressureGradient->SetScaleFactor(0.00002);


	dotProduct = vtkProgrammableAttributeDataFilter::New();
	
	dotProduct->SetInputConnection(probe_velocity->GetOutputPort());
	dotProduct->AddInput(probe_velocity->GetOutput());
	dotProduct->AddInput(probe_gradient->GetOutput());
	dotProduct->SetExecuteMethod(ExecuteDot,NULL);


vtkPolyDataMapper *velocityMapper = vtkPolyDataMapper::New();
	velocityMapper->SetInputConnection(velocity->GetOutputPort());
	velocityMapper->ScalarVisibilityOff();

vtkLODActor *velocityActor = vtkLODActor::New();
	velocityActor->SetMapper(velocityMapper);
	velocityActor->SetNumberOfCloudPoints(1000);
	velocityActor->GetProperty()->SetColor(1, 0, 0);

vtkPolyDataMapper *pressureGradientMapper = vtkPolyDataMapper::New();
	pressureGradientMapper->SetInputConnection(pressureGradient->GetOutputPort());
	pressureGradientMapper->ScalarVisibilityOff();

vtkLODActor *pressureGradientActor = vtkLODActor::New();
	pressureGradientActor->SetMapper(pressureGradientMapper);
	pressureGradientActor->SetNumberOfCloudPoints(1000);
	pressureGradientActor->GetProperty()->SetColor(0, 1, 0);

vtkPolyDataMapper *dotMapper = vtkPolyDataMapper::New();
	dotMapper->SetInput(dotProduct->GetPolyDataOutput());
	dotMapper->SetScalarRange(-1, 1);

vtkLODActor *dotActor = vtkLODActor::New();
	dotActor->SetMapper(dotMapper);
	dotActor->SetNumberOfCloudPoints(1000);


vtkPLOT3DReader *pl3d = vtkPLOT3DReader::New();
	pl3d->SetXYZFileName("combxyz.bin");

vtkStructuredGridOutlineFilter *outline = vtkStructuredGridOutlineFilter::New();
	outline->SetInputConnection(pl3d->GetOutputPort());

vtkPolyDataMapper *outlineMapper = vtkPolyDataMapper::New();
	outlineMapper->SetInputConnection(outline->GetOutputPort());

vtkActor *outlineActor = vtkActor::New();
	outlineActor->SetMapper(outlineMapper);
	outlineActor->GetProperty()->SetColor(0, 0, 0);

	ren1->AddActor(outlineActor);
	ren1->AddActor(velocityActor);
	ren1->AddActor(pressureGradientActor);
	ren1->AddActor(dotActor);
	ren1->SetBackground(1, 1, 1);
	renWin->SetSize(500, 500);
	//ren1 SetBackground 0.1 0.2 0.4


	ren1->GetActiveCamera()->SetClippingRange(3.95297, 50);
	ren1->GetActiveCamera()->SetFocalPoint(9.71821, 0.458166, 29.3999);
	ren1->GetActiveCamera()->SetPosition(-21.6807, -22.6387, 35.9759);
	ren1->GetActiveCamera()->SetViewUp(-0.0158865, 0.293715, 0.955761);

	renWin->Render();
	renWin->SetWindowName("Multidimensional Visualization Exercise");
	
	iren->Initialize();
	iren->Start();
// prevent the tk window from showing up then start the event loop
	

	return 0;
}

void ExecuteDot(void *)
{
	vtkDataSetCollection *inputs;
	vtkDataSet *input[2];
	int numPts;
	inputs = dotProduct->GetInputList();
	input[0] = inputs->GetDataSet(0);
	input[1] = inputs->GetDataSet(1);
	numPts = input[0]->GetNumberOfPoints();
	
	vtkDataArray *vectors[2];
	vectors[0] = input[0]->GetPointData()->GetVectors();
	vectors[1] = input[1]->GetPointData()->GetVectors();
	
	vtkFloatArray *scalars = vtkFloatArray::New();
	
	double *v[2];
	double v0x,v0y,v0z,v1x,v1y,v1z;
	for(int i = 0; i < numPts;  i++)
	{
		v[0] = vectors[0]->GetTuple3(i);
		v[1] = vectors[1]->GetTuple3(i);
		
		v0x = * v[0];
		v[0]++;
		v0y = * v[0];
		v[0]++;
		v0z = * v[0];
		
		v1x = * v[1];
		v[1]++;
		v1y = * v[1];
		v[1]++;
		v1z = * v[1];
		
		double l[2],d;

		l[0] = (double)(v0x) * (double)(v0x) + (double)(v0y) * (double)(v0y) + (double)(v0z) * (double)(v0z);
		l[1] = (double)(v1x) * (double)(v1x) + (double)(v1y) * (double)(v1y) + (double)(v1z) * (double)(v1z);
		
		l[0] = sqrt((double)(l[0]));
		l[1] = sqrt((double)(l[1]));
		
		if((l[0] > 0.0) && (l[1] > 0.0) )
			d = ((double)(v0x) * (double)(v1x) + (double)(v0y) * (double)(v1y) + (double)(v0z) * (double)(v1z))/(l[0] * l[1]);
		else{
			d = 0.0;
		}
		
		scalars->InsertValue(i, d);
	}
	
	dotProduct->GetOutput()->GetPointData()->SetScalars(scalars);
	
	scalars->Delete();
}
