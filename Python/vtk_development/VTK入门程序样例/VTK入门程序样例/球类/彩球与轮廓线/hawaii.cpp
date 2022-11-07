#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyDataReader.h"
#include "vtkElevationFilter.h"
#include "vtkLookupTable.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkSphereSource.h"
#include "vtkTexture.h"
#include "vtkJPEGReader.h"
#include "vtkProperty.h"
#include "vtkStripper.h"
#include "vtkPolyData.h"
#include "vtkShrinkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkPolyDataNormals.h"
#include "vtkExtractEdges.h"

int main()
{
	//Create the RenderWindow, Renderer and both Actors
	vtkRenderer *ren1 = vtkRenderer::New();
	vtkRenderer *ren2= vtkRenderer::New();
	vtkRenderWindow *renWin = vtkRenderWindow::New();
    	renWin->AddRenderer(ren1);
    	renWin->AddRenderer(ren2);
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    	iren->SetRenderWindow(renWin);
/*
	//read a vtk file
	char *path = getenv("VTK_DATA_ROOT");
	strcat(path, "/data/honolulu.vtk");
	vtkPolyDataReader *hawaii = vtkPolyDataReader::New();
    	hawaii->SetFileName(path);
    	//hawaii->Update();

*/
	vtkSphereSource *hawaii = vtkSphereSource::New();
      hawaii->SetPhiResolution(8); 
	//Set the number of points in the latitude direction
	  hawaii->SetThetaResolution(80);
	//Set the number of points in the longitude direction
	  hawaii->Update();

vtkPolyDataNormals *cowNormals=vtkPolyDataNormals::New();
  cowNormals->SetInputConnection (hawaii->GetOutputPort());

vtkStripper *cutStrips=vtkStripper::New(); 
  cutStrips-> SetInputConnection (cowNormals-> GetOutputPort());
  cutStrips-> Update();

vtkExtractEdges *extract=vtkExtractEdges::New();
  extract-> SetInputConnection (cowNormals ->GetOutputPort());

vtkPolyDataMapper *cutMapper=vtkPolyDataMapper::New(); 
  cutMapper-> SetInput ((vtkPolyData *)extract->GetOutput()); 

vtkActor *cutActor=vtkActor::New(); 
  cutActor-> SetMapper( cutMapper);
  cutActor-> GetProperty() ->SetColor (0,0,1);


    vtkShrinkPolyData *shrink2=vtkShrinkPolyData::New();
		shrink2-> SetInputConnection (cowNormals ->GetOutputPort());
		shrink2-> SetShrinkFactor( 0.90);

	vtkElevationFilter *elevation = vtkElevationFilter::New();
    	elevation->SetInput((vtkDataSet *)shrink2->GetOutput());
//    	elevation->SetLowPoint(0, 0, -1);
//    	elevation->SetHighPoint(0, 0, 1);
    //	elevation->SetScalarRange(0, 1);
	vtkLookupTable *lut = vtkLookupTable::New();
		lut->SetHueRange(0.7, 0);
		lut->SetSaturationRange(1.0, 0);
		lut->SetValueRange(0.5, 1.0);
    	lut->SetNumberOfColors(8);
    	lut->Build();
    	lut->SetTableValue(0, 0.0000, 0.7800, 0.5500, 1);
		lut->SetTableValue(1, 0.2353, 0.7020, 0.4431, 1);
		lut->SetTableValue(2, 0.5608, 0.7373, 0.5608, 1);
		lut->SetTableValue(3, 0.3333, 0.4196, 0.1843, 1);
		lut->SetTableValue(4, 0.5000, 0.1647, 0.1647, 1);
		lut->SetTableValue(5, 0.6400, 0.5800, 0.5000, 1);
		lut->SetTableValue(6, 0.9608, 0.9608, 0.8627, 1);
		lut->SetTableValue(7, 1.0000, 0.8941, 0.7686, 1);

	vtkDataSetMapper *hawaiiMapper = vtkDataSetMapper::New();
    	hawaiiMapper->SetInput(elevation->GetOutput());
//    	hawaiiMapper->SetScalarRange(0, 1000);
//    	hawaiiMapper->SetLookupTable(lut);
//    	hawaiiMapper->ImmediateModeRenderingOn();

	vtkJPEGReader *texture_reader=vtkJPEGReader::New();
	  texture_reader->SetFileName("beach.jpg");
	
		
	vtkTexture *texture=vtkTexture::New();
	  texture->SetInputConnection(texture_reader->GetOutputPort());
	  texture->InterpolateOn();
	

	vtkActor *hawaiiActor = vtkActor::New();
    	hawaiiActor->SetMapper(hawaiiMapper);
		hawaiiActor->SetTexture(texture);

	//Add the actors to the renderer, set the background and size
	ren1->AddActor(hawaiiActor);
	ren1->AddActor(cutActor);
	renWin->SetSize(1000, 500);
	renWin->DoubleBufferOff();
	ren1->SetBackground(0.4,0.4,0.0);

	//render the image
//	ren1->GetActiveCamera()->Zoom(1.0);

  ren1->SetViewport(0,0,0.5,1.0);

  ren2->AddActor(cutActor);
  ren2->SetBackground(0.4,0.4,0.0);
  ren2->SetViewport(0.5,0,1.0,1.0);


	renWin->Render();



	iren->Initialize();
	iren->Start();

	//clean up
	iren->Delete();
	renWin->Delete();
	ren1->Delete();
	hawaiiActor->Delete();
	hawaiiMapper->Delete();
	lut->Delete();
	elevation->Delete();
	hawaii->Delete();

	return 0;
}