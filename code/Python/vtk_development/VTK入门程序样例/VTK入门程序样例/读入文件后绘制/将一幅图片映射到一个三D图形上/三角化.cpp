#include "vtkPolyDataMapper.h"
#include "vtkPolyDataReader.h"
#include "vtkRenderer.h"
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkWin32RenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkTexture.h"
#include "vtkTextureMapToCylinder.h"
#include "vtkPointSource.h"
#include "vtkTransformTextureCoords.h"
#include "vtkDelaunay3D.h"
#include "vtkPolyData.h"
#include "vtkDataSetMapper.h"
#include "vtkBMPReader.h"
#include "vtkUnstructuredGrid.h"
#include "vtkBYUReader.h"
#include "vtkPolyDataNormals.h"
#include "vtkTriangleFilter.h"
#include "vtkFeatureEdges.h"
#include "vtkJPEGReader.h"

void main()
{
//Compute normals, in case they are not provided with the model.
	
	vtkBYUReader *model_reader=vtkBYUReader::New();
	model_reader->SetGeometryFileName("teapot.g");
	
	vtkPolyDataNormals *model_normals=vtkPolyDataNormals::New();
	model_normals->SetInput(model_reader->GetOutput());
	
	vtkTextureMapToCylinder *tmapper=vtkTextureMapToCylinder::New();
	tmapper->SetInput(model_normals->GetOutput());
	tmapper->PreventSeamOn();
	
	vtkTransformTextureCoords *transform_texture=vtkTransformTextureCoords::New();
	transform_texture->SetInput(tmapper->GetOutput());
		
	vtkDataSetMapper *mapper=vtkDataSetMapper::New();
	mapper->SetInput(transform_texture->GetOutput());
	
	
	vtkJPEGReader *texture_reader=vtkJPEGReader::New();
	texture_reader->SetFileName("beach.jpg");
	
	
	/*vtkImageReader2Factory *create_reader=vtkImageReader2Factory::New();
	texture_reader->create_reader(CreateImageReader2());
	texture_reader->SetFileName();*/
		
	vtkTexture *texture=vtkTexture::New();
	texture->SetInputConnection(texture_reader->GetOutputPort());
	texture->InterpolateOn();
	
	vtkActor *actor=vtkActor::New();
	actor->SetMapper(mapper);
	actor->SetTexture(texture);
	
	
	/*Create a triangle filter that will feed the model geometry to
	the feature edge extractor. Create the corresponding mapper 
	and actor.*/
	
	vtkTriangleFilter *triangle_filter=vtkTriangleFilter::New();
	triangle_filter->SetInput(model_normals->GetOutput());
	
	vtkFeatureEdges *edges_extractor=vtkFeatureEdges::New();
	edges_extractor->SetInput(triangle_filter->GetOutput());
	edges_extractor->ColoringOff();
	edges_extractor->BoundaryEdgesOn();
	edges_extractor->ManifoldEdgesOn();
	edges_extractor->NonManifoldEdgesOn();
	
	vtkPolyDataMapper *edges_mapper=vtkPolyDataMapper::New();
	edges_mapper->SetInput(edges_extractor->GetOutput());
	edges_mapper->SetResolveCoincidentTopologyToPolygonOffset();
	
	vtkActor *edges_actor=vtkActor::New();
	edges_actor->SetMapper(edges_mapper);
	edges_actor->GetProperty()->SetColor(0,0,0);
	edges_actor->GetProperty()->SetLineStipplePattern(4369);
	edges_actor->VisibilityOff();
	
	vtkRenderer *ren=vtkRenderer::New();
	ren->AddActor(actor);
    ren->AddActor(edges_actor);
    
	ren->ResetCamera();
	ren->SetBackground(1,1,1);
	vtkWin32OpenGLRenderWindow *renWin=vtkWin32OpenGLRenderWindow::New();
	renWin->AddRenderer(ren);
	vtkWin32RenderWindowInteractor *iren=vtkWin32RenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);
	renWin->SetSize(300,300);
	renWin->Render();
	iren->Start();
	ren->Delete();
	iren->Delete();
	renWin->Delete();
}






