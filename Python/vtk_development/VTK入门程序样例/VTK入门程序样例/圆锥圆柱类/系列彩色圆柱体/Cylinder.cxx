/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: Cylinder.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//
// This simple example shows how to do basic rendering and pipeline
// creation using C++.
//
#include "vtkCylinderSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkActor2D.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkOrientationMarkerWidget.h"
#include "vtkTextProperty.h"
#include "vtkAxesActor.h"
#include "vtkCaptionActor2D.h"
#include "math.h"
#include "stdio.h"
#include <time.h>

int main()
{
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  vtkCylinderSource *cylinder[100];
  vtkPolyDataMapper *cylinderMapper[100];
  vtkActor *cylinderActor[100];

  srand(time(NULL)) ;
  int i;
  for(i=0;i<100;i++)
  {
	  cylinder[i] = vtkCylinderSource::New();
	  cylinder[i]->SetResolution(20);
	  cylinder[i]->SetRadius  (20);
	  cylinder[i]->SetHeight(2);

	  cylinderMapper[i] = vtkPolyDataMapper::New();
	  cylinderMapper[i] ->SetInputConnection(cylinder[i] ->GetOutputPort());

	  cylinderActor[i] = vtkActor::New();
	  cylinderActor[i]->SetMapper(cylinderMapper[i] );
	  cylinderActor[i]->GetProperty()->SetColor(
		  (float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX);
	  cylinderActor[i]->SetPosition(0,2*i,0);

	  ren1->AddActor(cylinderActor[i]);
  }


  // Add the actors to the renderer, set the background and size
  //

  ren1->SetBackground(0, 0, 0);
  renWin->SetSize(500, 500);

  // We'll zoom in a little by accessing the camera and invoking a "Zoom"
  // method on it.
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Zoom(1.5);


  vtkAxesActor* axes2 = vtkAxesActor::New();

//  transform->Identity();
//  transform->RotateY(90);
  axes2->SetShaftTypeToCylinder();
//  axes2->SetUserTransform( transform );
  axes2->SetXAxisLabelText( "X" );
  axes2->SetYAxisLabelText( "Y" );
  axes2->SetZAxisLabelText( "Z" );

  axes2->SetTotalLength( 1.5, 1.5, 1.5 );
  axes2->SetCylinderRadius( 0.500 * axes2->GetCylinderRadius() );
  axes2->SetConeRadius    ( 1.025 * axes2->GetConeRadius() );
  axes2->SetSphereRadius  ( 1.500 * axes2->GetSphereRadius() );

  vtkTextProperty* tprop = axes2->GetXAxisCaptionActor2D()->
    GetCaptionTextProperty();
  tprop->ItalicOn();
  tprop->ShadowOn();
  tprop->SetFontFamilyToTimes();

  axes2->GetYAxisCaptionActor2D()->GetCaptionTextProperty()->ShallowCopy( tprop );
  axes2->GetZAxisCaptionActor2D()->GetCaptionTextProperty()->ShallowCopy( tprop );

  vtkOrientationMarkerWidget* widget = vtkOrientationMarkerWidget::New();
	widget->SetOutlineColor( 0.9300, 0.5700, 0.1300 );
	widget->SetOrientationMarker( axes2 );
	widget->SetInteractor( iren );
	widget->SetViewport( 0.0, 0.0, 0.4, 0.4 );
	widget->SetEnabled( 1 );
	widget->InteractiveOff();
	widget->InteractiveOn();


  renWin->Render();
  
  // This starts the event loop and as a side effect causes an initial render.
  iren->Start();

  // Exiting from here, we have to delete all the instances that
  // have been created.
//  cylinder->Delete();
//  cylinderMapper->Delete();
//  cylinderActor->Delete();
  ren1->Delete();
  renWin->Delete();
  iren->Delete();

  return 0;
}




