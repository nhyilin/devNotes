
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkLODActor.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkScaledTextActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkProperty2D.h>
#include <vtkTextActor.h>

void main()
{
	vtkSphereSource* sphere;
	vtkPolyDataMapper* sphereMapper;
	vtkLODActor* sphereActor;
	vtkTextMapper* textMapper;
	vtkScaledTextActor* text;
	vtkRenderer* renderer;
	vtkRenderWindowInteractor* iren;
	vtkRenderWindow* renWin;
	vtkTextActor* text2;

    sphere=vtkSphereSource::New();
		sphereMapper=vtkPolyDataMapper::New();
		sphereMapper->SetInput(sphere->GetOutput());
		sphereMapper->GlobalImmediateModeRenderingOn();
		sphereActor=vtkLODActor::New();
		sphereActor->SetMapper(sphereMapper);

    textMapper=vtkTextMapper::New();
		textMapper->SetInput("this is a \nsphere text!");
		textMapper->GetTextProperty()->ShadowOn();
		textMapper->GetTextProperty()->SetFontFamilyToArial();
		textMapper->GetTextProperty()->SetFontSize(10);
		textMapper->GetTextProperty()->BoldOn();
		textMapper->GetTextProperty()->ItalicOn();

    text=vtkScaledTextActor::New();
		text->SetMapper(textMapper);
		text->GetProperty()->SetColor(0,0,1);
		text->ScaledTextOff ();
		text->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
		text->GetPositionCoordinate()->SetValue(0.5,0.5);

    text2=vtkTextActor::New();
		text2->SetMapper(textMapper);
		text2->GetProperty()->SetColor(0,0,1);
		text2->ScaledTextOff();
//		text2->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
//		text2->GetPositionCoordinate()->SetValue(0.5,0.5);

    renderer=vtkRenderer::New();
    renWin=vtkRenderWindow::New();
    iren=vtkRenderWindowInteractor::New();
    renWin->AddRenderer(renderer);
    iren->SetRenderWindow(renWin);

    renderer->AddActor2D(text);
    renderer->AddActor2D(text2);
    renderer->AddActor(sphereActor);

//    renWin=vtkRenderWindow::New();

    renWin->SetSize(600,600);
    renWin->Render();

	iren->Initialize();
	iren->Start();
}
