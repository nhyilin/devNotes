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
#include "vtkImageSinusoidSource.h"
#include "vtkImageGradient.h"
#include "vtkImageNormalize.h"
#include "vtkImageViewer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"

int main()
{
	vtkImageSinusoidSource *wSP=vtkImageSinusoidSource::New();
			wSP->SetWholeExtent(0,255,0,255,0,20);
			wSP->SetAmplitude(63);
			wSP->SetDirection(1,1,1);
			wSP->SetPeriod  (1) ; 
			//wSP->ReleaseDataFlagOff();


	vtkImageGradient *gradient=vtkImageGradient::New();
     gradient->SetInputConnection(wSP-> GetOutputPort());
     gradient-> SetDimensionality(3);

	vtkImageNormalize *norm=vtkImageNormalize::New();
     norm-> SetInputConnection (gradient->GetOutputPort());

	vtkImageViewer *viewer=vtkImageViewer::New();
//viewer DebugOn
viewer-> SetInputConnection (norm-> GetOutputPort());
viewer-> SetZSlice (10);
viewer-> SetColorWindow( 2.0);
viewer-> SetColorLevel( 0);

viewer-> Render();

    vtkRenderWindowInteractor *viewerinter = vtkRenderWindowInteractor::New();
	  viewer->SetupInteractor(viewerinter);

	   
	viewerinter->Initialize();
    viewerinter->Start(); 
  
  return 0;
}




