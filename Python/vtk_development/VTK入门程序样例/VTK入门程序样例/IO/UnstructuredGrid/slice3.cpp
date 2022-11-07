#include "vtkQuadraticHexahedron.h"
#include "vtkUnstructuredGridReader.h"
#include "vtkMapper.h"
#include "vtkBMPReader.h"
#include  "vtkTexture.h"
#include  "vtkUnstructuredGridSource.h"
#include  "vtkUnstructuredGrid.h"
#include  "vtkProperty.h"
#include "vtkDataSetMapper.h"
#include "vtkLight.h"
#include "vtkCamera.h"
#include "vtkUnstructuredGridWriter.h"
#include "vtkPolyDataMapper.h" 
#include "vtkActor.h" 
#include "vtkRenderWindow.h" 
#include "vtkRenderer.h" 
#include "vtkRenderWindowInteractor.h" 
#include "vtkInteractorStyleTrackballCamera.h" 
#include "vtkCallbackCommand.h" 

int mode1=0;
int mode2=0;
vtkRenderWindow *renWin;
vtkRenderWindowInteractor *iren;
vtkDataSetMapper* elMapper;
void keypress(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata);

void main () 
{ 
vtkUnstructuredGrid *el= vtkUnstructuredGrid::New();
vtkUnstructuredGridReader *elReader= vtkUnstructuredGridReader::New();
elReader -> SetFileName("test1.vtk") ;
elReader -> OpenVTKFile();
el = elReader->GetOutput();
elReader -> CloseVTKFile();

elMapper= vtkDataSetMapper::New();
elMapper ->SetInputConnection(elReader->GetOutputPort());
//elMapper ->SetColorModeToMapScalars  (     ) ;

//elMapper ->SetScalarMode  (mode);  
//elMapper ->SetScalarModeToUseCellFieldData  (     );  
//elMapper ->SetScalarModeToUsePointFieldData  (     );  
//elMapper ->SetScalarModeToUseCellData  (     );  
//elMapper ->SetScalarModeToUsePointData  (     );  

vtkActor* elActor= vtkActor::New();
elActor ->SetMapper(elMapper);

vtkRenderer *ren=vtkRenderer::New();
renWin=vtkRenderWindow::New();
renWin->AddRenderer(ren);
iren = vtkRenderWindowInteractor::New();
iren->SetRenderWindow(renWin);
vtkInteractorStyleTrackballCamera *style=vtkInteractorStyleTrackballCamera::New();

ren->AddActor(elActor);


  vtkCallbackCommand * cmd1 = vtkCallbackCommand::New();
	cmd1->SetCallback(keypress);
	style-> AddObserver (vtkCommand::KeyPressEvent,cmd1);

iren-> SetInteractorStyle(style);
renWin->Render();
iren->Start();
}

void keypress(vtkObject *caller, unsigned long eid, void *clientdata, void *calldata)
{
	char key=iren->GetKeyCode();
	 
	switch (key)
    {
      case 'm':
		  mode1++;
		  if (mode1>2)
			  mode1=0;
		  elMapper ->SetColorMode  (mode1);  
		  renWin->Render();
		  break;
      case 'n':
		  mode2++;
		  if (mode2>5)
			  mode2=0;
		  elMapper ->SetScalarMode  (mode2);  
		  renWin->Render();
		  break;
	}
	printf("ColorMode :%d  ScalarMode %d\n",mode1,mode2);
}
