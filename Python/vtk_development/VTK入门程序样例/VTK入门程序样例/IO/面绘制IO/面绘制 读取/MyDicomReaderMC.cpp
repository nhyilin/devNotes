

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkPolyDataMapper.h"
#include "vtkPolyDataNormals.h"
#include "vtkPolyDataReader.h"
#include <vtkDICOMImageReader.h>
#include "vtkImageShrink3D.h"
#include "vtkCubeAxesActor2D.h"
#include "vtkTextProperty.h"
#include "vtkDecimatePro.h"
#include "vtkSmoothPolyDataFilter.h" 

#include "vtkPolyDataReader.h"
#include <vtkBYUReader.h> 
#include "vtkXMLPolyDataReader.h"
#include "vtkDataSetReader.h"
#include <vtkMCubesReader.h> 
#include "vtkSTLReader.h"
//#include <vtkCGMReader.h> 

#pragma comment (lib, "vtkGraphics.lib")
#pragma comment (lib, "vtkFiltering.lib")
#pragma comment (lib, "vtkIO.lib")
#pragma comment (lib, "vtkRendering.lib")


int main (int argc, char **argv)
{
  vtkRenderer *aRenderer = vtkRenderer::New();
	vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(aRenderer);
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);
/*
  vtkPolyDataReader *polyReader=vtkPolyDataReader::New();
    polyReader->SetFileName("E://CT/PolyDataWriter.vtk");
	polyReader->Update();

  vtkSTLReader *polyReader=vtkSTLReader::New();
    polyReader->SetFileName("E://CT/STLWriter.stl");
	polyReader->Update();

  vtkXMLPolyDataReader *polyReader=vtkXMLPolyDataReader::New();
    polyReader->SetFileName("E://CT/XMLPolyDataWriter.xpd");
	polyReader->Update();

  vtkMCubesReader *polyReader=vtkMCubesReader::New();
    polyReader->SetFileName("E://CT/MCubesWriter.tri");
    polyReader->SetLimitsFileName("E://CT/MCubesWriter.lim");
	polyReader->Update();

  vtkBYUReader *polyReader=vtkBYUReader::New();
    polyReader->SetGeometryFileName("E://CT/BYUWriter.g");
    polyReader->SetScalarFileName("E://CT/BYUWriter.s");
    polyReader->SetDisplacementFileName ("E://CT/BYUWriter.d");
//	polyReader->SetPartNumber(1);
	polyReader->Update();
*/
  vtkDataSetReader *polyReader=vtkDataSetReader::New();
    polyReader->SetFileName("E://CT/vtkDataSetWriter.dsw");
	polyReader->Update();

  vtkPolyDataMapper *Mapper = vtkPolyDataMapper::New();
    Mapper->SetInputConnection(polyReader->GetOutputPort());
    Mapper->ScalarVisibilityOff();

  vtkActor *Actor = vtkActor::New();
    Actor->SetMapper(Mapper);
//    Actor->GetProperty()->SetDiffuse(.8);
//    Actor->GetProperty()->SetSpecular(.5);
//    Actor->GetProperty()->SetSpecularPower(30);
	
	aRenderer->AddActor(Actor);
	aRenderer->SetBackground(1,1,1);
	renWin->SetSize(600,600);
	aRenderer->ResetCameraClippingRange();

  vtkTextProperty *tprop=vtkTextProperty::New();
    tprop-> SetColor(0, 0, 1);
    tprop-> ShadowOn();

  vtkCubeAxesActor2D *axes=vtkCubeAxesActor2D::New();
    axes-> SetInput (polyReader-> GetOutput());
    axes-> SetCamera (aRenderer-> GetActiveCamera());
    axes-> SetFlyModeToOuterEdges();
    axes-> SetFontFactor(0.8);
    axes-> SetAxisTitleTextProperty(tprop);
    axes-> SetAxisLabelTextProperty(tprop);
//	axes->GetProperty()->SetDiffuseColor(1, 0, 0.25);
	axes->SetFontFactor (8);

  aRenderer->AddViewProp(axes);
  aRenderer->SetBackground(0,0,0);

	iren->Initialize();
	iren->Start(); 

	aRenderer->Delete();
	renWin->Delete();
	iren->Delete();
	
	return 0;
}