/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: otherCoordinate.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// .NAME 
// .SECTION Description
// this program tests vtkCoordinate

#include "vtkCoordinate.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkCamera.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkDebugLeaks.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"

void ToAll (vtkCoordinate *c1, vtkViewport *ren1, 
            double *from)
{
  double *value;
  int *ivalue;
  const char *whichCoord = c1->GetCoordinateSystemAsString();

  c1->SetValue (from);

  cout << endl << "========" << endl;
  cout << *c1;
  value = c1->GetComputedWorldValue (ren1);
  cout << whichCoord <<"(" << from[0] << ", " << from[1] << ", " << from[2]
       << ") -> World(" << value[0] << ", " << value[1] << ", " << value[2] 
       << ")" << endl;
  ivalue = c1->GetComputedDisplayValue (ren1);
  cout << whichCoord << "(" << from[0] << ", " << from[1] << ", " << from[2]
       << ") -> Display(" << ivalue[0] << ", " << ivalue[1] << ")" << endl;
  ivalue = c1->GetComputedLocalDisplayValue (ren1);
  cout << whichCoord << "(" << from[0] << ", " << from[1] << ", " << from[2]
       << ") -> LocalDisplay(" << ivalue[0] << ", " << ivalue[1] 
       << ")" << endl;
  ivalue = c1->GetComputedViewportValue (ren1);
  cout << whichCoord << "(" << from[0] << ", " << from[1] << ", " << from[2]
       << ") -> Viewport(" << ivalue[0] << ", " << ivalue[1] << ")" << endl;


}
int main()
{
  // actual test
  cout << "Testing vtkCoordinate" << endl;
  vtkCoordinate *c1 = vtkCoordinate::New();
  vtkCoordinate *c2 = vtkCoordinate::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  vtkRenderer *ren1 = vtkRenderer::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

	vtkSphereSource *sphere=vtkSphereSource::New();
		sphere-> SetThetaResolution( 20);
		sphere-> SetPhiResolution( 20);
	vtkPolyDataMapper *sphereMapper=vtkPolyDataMapper::New();
		sphereMapper-> SetInputConnection (sphere-> GetOutputPort());
	vtkActor *sphereActor=vtkActor::New();
		sphereActor-> SetMapper (sphereMapper);

    ren1-> AddActor (sphereActor);

  vtkCamera *camera = vtkCamera::New();
  double from[3];
  
  ren1->SetActiveCamera (camera);
  renWin->AddRenderer (ren1);
  renWin->SetSize (500, 500);
  
  cout << "Origin: (" << ren1->GetOrigin()[0] << ", " << ren1->GetOrigin()[1] << ")" << endl;
  cout << "Center: (" << ren1->GetCenter()[0] << ", " << ren1->GetOrigin()[1] << ")" << endl;

  cout << endl << "********** A NULL Viewport **********" << endl;
  
  c1->SetCoordinateSystemToWorld();
  from[0] = 0.0; from[1] = 0.0; from[2] = 0.0;
  ToAll ( c1, ren1, from);  
  
  renWin->Render();
  iren->Start();

  c1->SetCoordinateSystemToDisplay();
  from[0] = 50; from[1] = 50; from[2] = 0;
  ToAll (c1, ren1, from);
   
  renWin->Render();
  iren->Start();
 
  c1->SetCoordinateSystemToNormalizedDisplay();
  from[0] = .5; from[1] = .5; from[2] = 0.0;
  ToAll ( c1, ren1, from); 
   
  renWin->Render();
  iren->Start();
 
  c1->SetCoordinateSystemToViewport();
  from[0] = 50; from[1] = 50; from[2] = 0;
  ToAll ( c1, ren1, from); 
   
  renWin->Render();
  iren->Start();
 
  c1->SetCoordinateSystemToNormalizedViewport();
  from[0] = .5; from[1] = .5; from[2] = 0;
  ToAll ( c1, ren1, from); 
  
  c1->SetCoordinateSystemToView();
  from[0] = 0.0; from[1] = 0.0; from[2] = 0.0;
  ToAll ( c1, ren1, from); 
  
  cout << endl << "********** A specified Viewport **********" << endl;
  c1->SetViewport (ren1);
  
  c1->SetCoordinateSystemToWorld();
  from[0] = 0.0; from[1] = 0.0; from[2] = 0.0;
  ToAll ( c1, ren1, from);   

  c1->SetCoordinateSystemToDisplay();
  from[0] = 50; from[1] = 50; from[2] = 0;
  ToAll  (c1, ren1, from);
  
  c1->SetCoordinateSystemToNormalizedDisplay();
  from[0] = .5; from[1] = .5; from[2] = 0.0;
  ToAll ( c1, ren1, from); 
  
  c1->SetCoordinateSystemToViewport();
  from[0] = 50; from[1] = 50; from[2] = 0;
  ToAll ( c1, ren1, from); 
  
  c1->SetCoordinateSystemToNormalizedViewport();
  from[0] = .5; from[1] = .5; from[2] = 0;
  ToAll ( c1, ren1, from); 
  
  c1->SetCoordinateSystemToView();
  from[0] = 0.0; from[1] = 0.0; from[2] = 0.0;
  ToAll ( c1, ren1, from); 
  
  cout << endl << "********** With a Reference Coordinate **********" << endl;

  c2->SetCoordinateSystemToNormalizedDisplay();
  c2->SetCoordinateSystemToWorld();
  c2->SetValue (0.0, 0.0, 0.0);
  c1->SetReferenceCoordinate (c2);
  
  cout << *c2;
  
  c1->SetCoordinateSystemToWorld();
  from[0] = 0.0; from[1] = 0.0; from[2] = 0.0;
  ToAll ( c1, ren1, from);   

  c1->SetCoordinateSystemToDisplay();
  from[0] = 50; from[1] = 50; from[2] = 0;
  ToAll (c1, ren1, from);
  
  c1->SetCoordinateSystemToNormalizedDisplay();
  from[0] = .5; from[1] = .5; from[2] = 0.0;
  ToAll ( c1, ren1, from); 
  
  c1->SetCoordinateSystemToViewport();
  from[0] = 50; from[1] = 50; from[2] = 0;
  ToAll ( c1, ren1, from); 
  
  c1->SetCoordinateSystemToNormalizedViewport();
  from[0] = .5; from[1] = .5; from[2] = 0;
  ToAll (c1, ren1, from);
  
  c1->SetCoordinateSystemToView();
  from[0] = 0.0; from[1] = 0.0; from[2] = 0.0;
  ToAll (c1, ren1, from);
  
  c1->Delete ();
  c2->Delete ();
  renWin->Delete ();
  ren1->Delete ();
  camera->Delete ();

  cout << "Testing completed" << endl;
  return 0;
}


