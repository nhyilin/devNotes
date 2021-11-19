// Compiling and linking successfully in Microsoft Visual Studio 6.0
// This example demonstrates how to use a constraint polygon in Delaunay 
// triangulation.
#include "vtkActor.h"
#include "vtkCellArray.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkTubeFilter.h"
#include "vtkDelaunay2D.h"
#include "vtkExtractEdges.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#define  NUM_INPUT    14
#define  NUM_CONSTRAIN1 16
#define  NUM_CONSTRAIN2  3
#define  NUM_TOTAL (NUM_INPUT + NUM_CONSTRAIN1 + NUM_CONSTRAIN2)
int main( int argc, char *argv[] )
{
    // Generate the input points and constrained edges/polygons.
    float input[NUM_TOTAL][3] = {{0, 100, 0}, {0, 50, 0}, {0, 0, 0}, {50, 0, 0}, {100, 0, 0}, {150, 0, 0}, 
                                              {200, 0, 0}, {200, 50, 0}, {200, 100, 0}, {200, 150, 0}, {150, 150, 0},
                                              {100, 150, 0}, {50, 150, 0}, {0, 150, 0}, {154, 29, 0}, {167, 29, 0},
                                              {167, 20, 0}, {120, 20, 0}, {120, 29, 0}, {138, 29, 0}, {121, 63, 0}, 
                                              {74, 63, 0}, {58, 29, 0}, {78, 29, 0}, {78, 20, 0}, {38, 20, 0},
                                              {38, 29, 0}, {50, 29, 0}, {95, 130, 0}, {110, 135, 0}, {76,70, 0}, 
                                              {120, 70, 0}, {99, 121, 0}};
    vtkPoints *points = vtkPoints::New();
    for (int i = 0; i < NUM_TOTAL; ++i)
    {
        points->InsertPoint(i, input[i]);
    } 

    vtkCellArray *polys = vtkCellArray::New();
    polys->InsertNextCell(NUM_INPUT);
    for (i = 0; i < NUM_INPUT; ++i)
    {
        polys->InsertCellPoint(i );
    }
    polys->InsertNextCell(NUM_CONSTRAIN1);
    for (i = 0; i < NUM_CONSTRAIN1; ++i)
    {
        polys->InsertCellPoint(i + NUM_INPUT);
    }
    polys->InsertNextCell(NUM_CONSTRAIN2);
    for (i = 0; i < NUM_CONSTRAIN2; ++i)
    {
        polys->InsertCellPoint(i + NUM_INPUT + NUM_CONSTRAIN1);
    } 

    vtkPolyData *polyData = vtkPolyData::New();
    polyData->SetPoints(points);
    polyData->SetPolys(polys); 

    vtkDelaunay2D *del = vtkDelaunay2D::New();
    del->SetInput(polyData);
    del->SetSource(polyData); 

    vtkPolyDataMapper *mapMesh = vtkPolyDataMapper::New();
    mapMesh->SetInput(del->GetOutput()); 

    vtkActor *meshActor = vtkActor::New();
    meshActor->SetMapper(mapMesh);
    meshActor->GetProperty()->SetColor(0.4, 1.0, 0.4);
    meshActor->GetProperty()->SetOpacity(0.4); 

    vtkExtractEdges *extract = vtkExtractEdges::New();
    extract->SetInput(del->GetOutput());
    vtkTubeFilter *tubes = vtkTubeFilter::New();
    tubes->SetInput(extract->GetOutput());
    tubes->SetRadius(1.4);
    tubes->SetNumberOfSides(5); 

    vtkPolyDataMapper *mapEdges = vtkPolyDataMapper::New();
    mapEdges->SetInput(tubes->GetOutput()); 

    vtkActor *edgeActor = vtkActor::New();
    edgeActor->SetMapper(mapEdges);
    edgeActor->GetProperty()->SetColor(1, 1, 0); 

    // Create the rendering window, renderer, and interactive renderer
    vtkRenderer *ren1 = vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1); 

// Add the actors to the renderer, set the background and size
    ren1->AddActor(meshActor);
    ren1->AddActor(edgeActor);
    ren1->SetBackground(0.0, 0.0, 0.2);
    ren1->GetActiveCamera()->Zoom(1.8);
    renWin->SetSize(500, 400); 

    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin); 

    vtkInteractorStyleTrackballCamera *style = vtkInteractorStyleTrackballCamera::New();
    iren->SetInteractorStyle(style);
    iren->Initialize();
    iren->Start(); 

    // Free up any objects we created. All instances in VTK are deleted by
    // using the Delete() method.
    points->Delete();
    polys->Delete();
    polyData->Delete();
    del->Delete();
    mapMesh->Delete();
    meshActor->Delete();
    extract->Delete();
    tubes->Delete();
    mapEdges->Delete();
    edgeActor->Delete();
    ren1->Delete();
    renWin->Delete();
    iren->Delete();
    style->Delete();
    return 0;
} 

