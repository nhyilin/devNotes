/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: TestScalarBarWidget.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkPLOT3DReader.h"
#include "vtkScalarBarWidget.h"
#include "vtkStructuredGridGeometryFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkScalarBarActor.h"
#include "vtkStructuredGrid.h"

#include "vtkTestUtilities.h"
#include "vtkRegressionTestImage.h"
#include "vtkDebugLeaks.h"

int main( int argc, char *argv[] )
{
 
  // Start by loading some data.
  vtkPLOT3DReader *pl3d = vtkPLOT3DReader::New();
  pl3d->SetXYZFileName("combxyz.bin");
  pl3d->SetQFileName("combq.bin");
  pl3d->SetScalarFunctionNumber(100);
  pl3d->SetVectorFunctionNumber(202);
  pl3d->Update();
  
  // An outline is shown for context.
  vtkStructuredGridGeometryFilter *outline = 
    vtkStructuredGridGeometryFilter::New();
  outline->SetInputConnection(pl3d->GetOutputPort());
  outline->SetExtent(0,100,0,100,9,9);
  
  vtkPolyDataMapper *outlineMapper = vtkPolyDataMapper::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkActor *outlineActor = vtkActor::New();
  outlineActor->SetMapper(outlineMapper);

  // Create the RenderWindow, Renderer and both Actors
  //
  vtkRenderer *ren1 = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer(ren1);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow(renWin);

  vtkScalarBarWidget *scalarWidget = vtkScalarBarWidget::New();
  scalarWidget->SetInteractor(iren);
  scalarWidget->GetScalarBarActor()->SetTitle("Temperature");
  scalarWidget->GetScalarBarActor()->SetLookupTable(outlineMapper->GetLookupTable());
  
  ren1->AddActor(outlineActor);

  // Add the actors to the renderer, set the background and size
  //
  ren1->SetBackground(0.1, 0.2, 0.4);
  renWin->SetSize(300, 300);

  iren->Initialize();
  renWin->Render();

    iren->Start();

  scalarWidget->Delete();
  pl3d->Delete();
  outline->Delete();
  outlineMapper->Delete();
  outlineActor->Delete();
  iren->Delete();
  renWin->Delete();
  ren1->Delete();
  
  return 0;
}
