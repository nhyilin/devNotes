
#include "vtkPolyDataMapper.h" 
#include "vtkRenderer.h" 
#include "vtkRenderWindow.h" 
#include "vtkWin32RenderWindowInteractor.h" 
#include "vtkActor.h" 
#include "vtkPointPicker.h" 
#include "vtkSphereSource.h" 
#include "vtkGlyph3D.h" 
#include "vtkSelectPolyData.h" 
#include "vtkClipPolyData.h" 
#include  <stdio.h> 
#include  <ctype.h> 
#include  <iostream.h> 
#include  <vtkConeSource.h> 
#include  <vtkPolyDataNormals.h> 
#include  <vtkProperty.h> 
#include  <vtkSphereSource.h> 
#include  <vtkGlyph3D.h> 
#include  <vtkRenderWindowInteractor.h> 
#include  <vtkCallbackCommand.h> 
#include "vtkCamera.h"
#include "vtkPolyDataReader.h"
#include "vtkPolyDataNormals.h"

static void pickControl(void *); 
static vtkRenderer *ren1; 
static vtkRenderer *ren2; 
static vtkRenderWindow *renWin; 
static vtkPoints *points; 
static int n, p; 

vtkPolyDataReader *sphere=vtkPolyDataReader::New();
vtkRenderWindowInteractor  *iren;
vtkPoints *selectionPoints=vtkPoints::New(); 

void pickControl(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata);

void main( int argc, char *argv[] ) 
{ 
	ren1 = vtkRenderer::New(); 
	ren2 = vtkRenderer::New(); 
	renWin = vtkRenderWindow::New(); 
	renWin->AddRenderer(ren1);
	renWin->AddRenderer(ren2);	
	iren = vtkRenderWindowInteractor::New(); 

	n=0; 
	p=0; 

  vtkPointPicker *pointpicker = vtkPointPicker::New(); 



    sphere->SetFileName("E://CT/tooth.vtk");
	sphere->Update();

  vtkPolyDataNormals *normals = vtkPolyDataNormals::New();
    normals->SetInputConnection(sphere->GetOutputPort());
    normals->SetFeatureAngle(60);

  vtkPolyDataMapper *sphereMapper = vtkPolyDataMapper::New();
    sphereMapper->SetInput(normals->GetOutput());
  vtkActor *sphereActor = vtkActor::New();
    sphereActor->SetMapper(sphereMapper);
    sphereActor->GetProperty()->SetColor(0,0,0.8);


	iren->SetRenderWindow(renWin); 
	iren->SetPicker(pointpicker); 
//	iren->SetUserMethod(vtkCommand::pickControl, (void *)iren); 

  vtkCallbackCommand * cmd = vtkCallbackCommand::New();
	cmd->SetCallback(pickControl);
	pointpicker->AddObserver(vtkCommand::EndPickEvent, cmd);

	ren1->AddActor(sphereActor);
//	ren2->AddActor(sphereActor);

	ren1->SetBackground(0, 0, 0);
    ren1->SetViewport(0,0,0.5,1);
    ren2->SetBackground(0.2,0.3,0.5);
    ren2->SetViewport(0.5,0,1,1);

	ren2-> SetActiveCamera( ren1-> GetActiveCamera());

	renWin->SetSize(1000,500);
	ren1->ResetCamera ();

	iren->Initialize(); 
	renWin->Render(); 
	iren->Start(); 

	ren1->Delete(); 
	renWin->Delete(); 
	iren->Delete(); 
	pointpicker->Delete(); 
} 


// Define picking method 
void pickControl(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata) 
{ 
	double *selPt; 
	double *pickpos; 
	double *pc; 
	int i; 

//	vtkRenderWindowInteractor *iren = (vtkRenderWindowInteractor *)arg; 
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

		selectionPoints-> InsertPoint( p-1,pointpicker->GetPickPosition()[0],
								  pointpicker->GetPickPosition()[1],
							      pointpicker->GetPickPosition()[2]);
		points->Modified(); 

		vtkPolyData *profile=vtkPolyData::New(); 
		profile->SetPoints(points); 

		vtkSphereSource *sphere=vtkSphereSource::New(); 
		sphere->SetRadius(1); 

		vtkGlyph3D *glyph=vtkGlyph3D::New(); 
		glyph->SetInput(profile); 
		glyph->SetSource(sphere->GetOutput()); 

		vtkPolyDataMapper *glyphMapper=vtkPolyDataMapper::New(); 
		glyphMapper->SetInput(glyph->GetOutput()); 


		vtkActor *glyphActor=vtkActor::New(); 
		glyphActor->SetMapper(glyphMapper); 
		glyphActor->GetProperty()->SetColor(0, 1, 0); //Set colour to red 

		ren1-> AddActor(glyphActor); 

		renWin->Render(); 

//		points-> Delete(); 
		profile->  Delete(); 
		sphere->  Delete(); 
		glyph->  Delete(); 
		glyphMapper->  Delete(); 
		glyphActor->  Delete(); 

	} 
	else if( pointpicker->GetPointId() < 0 ) 
	{ 
		cout<<"No point picked here!"<<"\n"; 
		//n=n+1; 
		//cout<<"n" <<n<<"\n"; 

		if (p >=3) 
		{
			cout<<"Selection completed!"<<"\n"; 

			// check the picked points, stored in vtkPoints 
			for (i=0; i<p; i++) 
			{ 
				pc = selectionPoints->GetPoint(i); 
				cout<<"point:"<<pc[0]<<" "<<pc[1]<<" "<<pc[2]<<"\n";//See components points 
				//selectionPoints->InsertPoint (i,pc[0],pc[1],pc[2]);
			} 

			vtkSelectPolyData *loop = vtkSelectPolyData::New(); 
			  loop->SetInput(sphere->GetOutput());
			  loop->SetLoop(selectionPoints); 
			  loop->GenerateSelectionScalarsOn(); 
			  loop->SetSelectionModeToSmallestRegion(); //negative scalars inside 
			vtkClipPolyData *clip = vtkClipPolyData::New(); //clips out positive region 
			  clip->SetInput(loop->GetOutput()); 
			vtkPolyDataMapper *clipMapper = vtkPolyDataMapper::New(); 
			  clipMapper->SetInput(clip->GetOutput()); 
			vtkActor *clipActor = vtkActor::New(); 
			  clipActor->SetMapper(clipMapper); 
//			  clipActor->AddPosition(1, 0, 0); 
			  clipActor->GetProperty()->SetColor(1, 1, 0); //Set colour blue 
/*
			vtkPolyData *profile=vtkPolyData::New(); 
			  profile->SetPoints(selectionPoints); 

			vtkSphereSource *sphere=vtkSphereSource::New(); 
			  sphere->SetRadius(1); 

			vtkGlyph3D *glyph=vtkGlyph3D::New(); 
			  glyph->SetInput(profile); 
			  glyph->SetSource(sphere->GetOutput()); 

			vtkPolyDataMapper *glyphMapper=vtkPolyDataMapper::New(); 
			  glyphMapper->SetInput(glyph->GetOutput()); 


			vtkActor *glyphActor=vtkActor::New(); 
			  glyphActor->SetMapper(glyphMapper); 
			  glyphActor->GetProperty()->SetColor(1, 0, 0); //Set colour to red 
*/
//			ren2-> AddActor(glyphActor); 
			ren2->AddActor(clipActor); 
			p=0;
			renWin->Render(); 

			loop->Delete(); 
			clip->Delete(); 
			clipMapper->Delete(); 
			clipActor->Delete();
/*			
			profile->  Delete(); 
			sphere->  Delete(); 
			glyph->  Delete(); 
			glyphMapper->  Delete(); 
			glyphActor->  Delete(); 
*/
       } 
	   else
	   {
			ren1->RemoveAllProps();

			vtkPolyDataMapper *sphereMapper = vtkPolyDataMapper::New();
			  sphereMapper->SetInput(sphere->GetOutput());
			vtkActor *sphereActor = vtkActor::New();
			  sphereActor->SetMapper(sphereMapper);
			  sphereActor->GetProperty()->SetColor(0.8,0.1,0.8);

			ren1->AddActor(sphereActor);
            renWin->Render(); 

			sphereMapper->  Delete(); 
			sphereActor->  Delete(); 
	   }

	} 

}  
