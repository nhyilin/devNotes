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

#include "vtkAngleWidget.h"


int main()
{
  vtkCylinderSource *cylinder = vtkCylinderSource::New();
  cylinder->SetResolution(8);
  cylinder->SetRadius  (  20);
  cylinder->SetHeight(20);

  vtkPolyDataMapper *cylinderMapper = vtkPolyDataMapper::New();
  cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

  vtkActor *cylinderActor = vtkActor::New();
  cylinderActor->SetMapper(cylinderMapper);
  cylinderActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);

  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer(ren1);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow(renWin);

  ren1->AddActor(cylinderActor);
  ren1->SetBackground(0.1, 0.2, 0.4);
  renWin->SetSize(200, 200);

  ren1->ResetCamera();
  ren1->GetActiveCamera()->Zoom(1.5);

  vtkOrientationMarkerWidget* widget = vtkOrientationMarkerWidget::New();
	widget->SetOutlineColor( 0.9300, 0.5700, 0.1300 );
//	widget->SetOrientationMarker( axes2 );
	widget->SetInteractor( iren );
	widget->SetViewport( 0.0, 0.0, 0.4, 0.4 );
	widget->SetEnabled( 1 );
	widget->InteractiveOff();
	widget->InteractiveOn();


  renWin->Render();
  
  iren->Start();

  cylinder->Delete();
  cylinderMapper->Delete();
  cylinderActor->Delete();
  ren1->Delete();
  renWin->Delete();
  iren->Delete();

  return 0;
}




