
#include  <stdio.h> 
#include  <ctype.h> 
#include  <iostream.h> 
#include "vtkPolyDataMapper.h" 
#include "vtkRenderer.h" 
#include "vtkRenderWindow.h" 
#include "vtkRenderWindowInteractor.h" 
#include "vtkActor.h" 
#include "vtkPointPicker.h" 
#include "vtkSphereSource.h" 
#include "vtkGlyph3D.h" 
#include "vtkSelectPolyData.h" 
#include "vtkClipPolyData.h" 
#include  <vtkCellArray.h> 
#include  <vtkProperty.h> 

static void pickControl(void *); 
static vtkRenderer *ren1; 
static vtkRenderWindow *renWin; 
static vtkPoints *points; 
static int n, p; 
vtkSphereSource *sphere = vtkSphereSource::New();

void main( int argc, char *argv[] ) 
{ 
  ren1 = vtkRenderer::New(); 
  renWin = vtkRenderWindow::New(); 
  renWin->AddRenderer(ren1); 
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New(); 
	iren->SetRenderWindow(renWin);

	n=0; 
	p=0; 

    sphere->SetThetaResolution(50); 
	sphere->SetPhiResolution(50);
  vtkPolyDataMapper *sphereMapper = vtkPolyDataMapper::New();
    sphereMapper->SetInput(sphere->GetOutput());
  vtkActor *sphereActor = vtkActor::New();
    sphereActor->SetMapper(sphereMapper);
    sphereActor->GetProperty()->SetColor(0.8,0.1,0.8);

	ren1->AddActor(sphereActor); 

  vtkPointPicker *pointpicker = vtkPointPicker::New(); 
	 
	iren->SetPicker(pointpicker); 
//	pointpicker->SetEndPickMethod(pickControl, (void *)iren); 
	iren->SetEndPickMethod(pickControl, (void *)iren); 

// render the image 
	ren1->SetBackground(0, 0, 0); 
	renWin->SetSize(500,500); 
	iren->Initialize(); 
	renWin->Render(); 
	iren->Start(); 

	ren1->Delete(); 
	renWin->Delete(); 
	iren->Delete(); 
	pointpicker->Delete(); 
} 


// Define picking method 
static void pickControl(void *arg) 
{ 
	double *selPt; 
	double *pickpos; 
	double *pc; 
	int i; 

	vtkRenderWindowInteractor *iren = (vtkRenderWindowInteractor *)arg; 
	vtkPointPicker *pointpicker = (vtkPointPicker *)iren->GetPicker(); 

	selPt = pointpicker->GetSelectionPoint(); 

	cout<<"Screen location:"<<selPt[0]<<" "<<selPt[1]<<"\n"; 



	if ( pointpicker->GetPointId() >= 0 ) 
	{ 
		p = p+1; //count number of points picked 
		pickpos = pointpicker->GetPickPosition(); 

		cout<<"Point location:"<<pickpos[0]<<" "<<pickpos[1]<<" "<<pickpos[2]<<"\n"; 

		//Define method for placing spheres 
		points=vtkPoints::New(); 
		points->InsertNextPoint(pickpos); 
		points->Modified(); 

		vtkPolyData *profile=vtkPolyData::New(); 
		profile->SetPoints(points); 

		vtkSphereSource *sphere=vtkSphereSource::New(); 
		sphere->SetRadius(0.02); 

		vtkGlyph3D *glyph=vtkGlyph3D::New(); 
		glyph->SetInput(profile); 
		glyph->SetSource(sphere->GetOutput()); 

		vtkPolyDataMapper *glyphMapper=vtkPolyDataMapper::New(); 
		glyphMapper->SetInput(glyph->GetOutput()); 


		vtkActor *glyphActor=vtkActor::New(); 
		glyphActor->SetMapper(glyphMapper); 
		glyphActor->GetProperty()->SetColor(1, 0, 0); //Set colour to red 

		ren1-> AddActor(glyphActor); 

		renWin->Render(); 


		//points-> Delete(); 
		profile->  Delete(); 
		sphere->  Delete(); 
		glyph->  Delete(); 
		glyphMapper->  Delete(); 
		glyphActor->  Delete(); 


	} 
	else if( pointpicker->GetPointId() < 0 ) 
	{ 
		cout<<"No point picked here!"<<"\n"; 
		n=n+1; 
		cout<<"n" <<n<<"\n"; 

		if (n >=3) 
		{ 
			cout<<"Selection completed!"<<"\n"; 

			// check the picked points, stored in vtkPoints 
			for (i=0; i<p; i++) 
			{ 
				pc = points->GetPoint(i); 
				cout<<"point:"<<pc[0]<<" "<<pc[1]<<" "<<pc[2]<<"\n";//See components points 
			} 

			vtkSelectPolyData *loop = vtkSelectPolyData::New(); 
//			loop->SetInput(reader->GetOutput()); 
			  loop->SetInput(sphere->GetOutput());
			  loop->SetLoop(points); 
			  loop->GenerateSelectionScalarsOn(); 
			  loop->SetSelectionModeToSmallestRegion(); //negative scalars inside 
			vtkClipPolyData *clip = vtkClipPolyData::New(); //clips out positive region 
			  clip->SetInput(loop->GetOutput()); 
			vtkPolyDataMapper *clipMapper = vtkPolyDataMapper::New(); 
			  clipMapper->SetInput(clip->GetOutput()); 
			vtkActor *clipActor = vtkActor::New(); 
			  clipActor->SetMapper(clipMapper); 
			  clipActor->AddPosition(1, 0, 0); 
			  clipActor->GetProperty()->SetColor(0, 0, 1); //Set colour blue 

			ren1->AddActor(clipActor); 
			renWin->Render(); 

			points-> Delete(); 
			loop->Delete(); 
			clip->Delete(); 
			clipMapper->Delete(); 
			clipActor->Delete(); 

       } 

	} 

} 