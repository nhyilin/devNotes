/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: volProt.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkCamera.h"
#include "vtkFiniteDifferenceGradientEstimator.h"
#include "vtkPiecewiseFunction.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkStructuredPoints.h"
#include "vtkStructuredPointsReader.h"
#include "vtkVolume.h"
#include "vtkVolumeProperty.h"
#include "vtkVolumeRayCastCompositeFunction.h"
#include "vtkVolumeRayCastIsosurfaceFunction.h"
#include "vtkVolumeRayCastMIPFunction.h"
#include "vtkVolumeRayCastMapper.h"
#include "vtkVolumeTextureMapper2D.h"
#include "vtkColorTransferFunction.h"

#include "vtkTestUtilities.h"
#include "vtkRegressionTestImage.h"
#include "vtkDebugLeaks.h"

// Create an 8x7 grid of render windows in a renderer and render a volume
// using various techniques for testing purposes
int main( int argc, char *argv[] )
{
  int i, j;
  
  // Create the renderers, render window, and interactor
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow(renWin);
  vtkRenderer *ren = vtkRenderer::New();
  renWin->AddRenderer(ren);
  
  // Read the data from a vtk file
  vtkStructuredPointsReader *reader = vtkStructuredPointsReader::New();
  reader->SetFileName("ironProt.vtk");
  reader->Update();
  
  // Create a transfer function mapping scalar value to opacity
  vtkPiecewiseFunction *oTFun = vtkPiecewiseFunction::New();
  oTFun->AddSegment(10, 0.0, 255, 0.3);

  vtkPiecewiseFunction *oTFun2 = vtkPiecewiseFunction::New();
  oTFun2->AddSegment(  0, 0.0, 128, 1.0);
  oTFun2->AddSegment(128, 1.0, 255, 0.0);

  // Create a transfer function mapping scalar value to color (grey)
  vtkPiecewiseFunction *gTFun = vtkPiecewiseFunction::New();
  gTFun->AddSegment(0, 1.0, 255, 1.0);
    
  // Create a transfer function mapping scalar value to color (color)
  vtkColorTransferFunction *cTFun = vtkColorTransferFunction::New();
  cTFun->AddRGBPoint(   0, 1.0, 0.0, 0.0 );
  cTFun->AddRGBPoint(  64, 1.0, 1.0, 0.0 );
  cTFun->AddRGBPoint( 128, 0.0, 1.0, 0.0 );
  cTFun->AddRGBPoint( 192, 0.0, 1.0, 1.0 );
  cTFun->AddRGBPoint( 255, 0.0, 0.0, 1.0 );

  // Create a transfer function mapping magnitude of gradient to opacity
  vtkPiecewiseFunction *goTFun = vtkPiecewiseFunction::New();
  goTFun->AddPoint(   0, 0.0 );
  goTFun->AddPoint(  30, 0.0 );
  goTFun->AddPoint(  40, 1.0 );
  goTFun->AddPoint( 255, 1.0 );

  // Create a set of properties for mip
  vtkVolumeProperty *mipprop[4];
  int  index = 0;
  for ( j = 0; j < 2; j++ )
    {
    for ( i = 0; i < 2; i++ )
      {
      mipprop[index] = vtkVolumeProperty::New();
      mipprop[index]->SetScalarOpacity(oTFun2);          
          
      if ( j )
        {
        mipprop[index]->SetColor( cTFun );
        }
      else
        {
        mipprop[index]->SetColor( gTFun );
        }
      
      if ( i )
        {
        mipprop[index]->SetInterpolationTypeToNearest();
        }
      else
        {
        mipprop[index]->SetInterpolationTypeToLinear();
        }
          
      index++;
      }
    }

 
  
  // Create mip ray functions
  vtkVolumeRayCastMIPFunction *MIPFunction1 = 
    vtkVolumeRayCastMIPFunction::New();
  MIPFunction1->SetMaximizeMethodToScalarValue();

  vtkVolumeRayCastMIPFunction *MIPFunction2 = 
    vtkVolumeRayCastMIPFunction::New();
  MIPFunction2->SetMaximizeMethodToOpacity();

  vtkFiniteDifferenceGradientEstimator *gradest = 
    vtkFiniteDifferenceGradientEstimator::New();
  
  // Create 56 volumes
  vtkVolume *volume[8];
  index = 0;

    for ( i = 0; i < 8; i++ )
      {
      volume[index] = vtkVolume::New();
      volume[index]->AddPosition( i*70, 70, 0 );
      ren->AddViewProp(volume[index]);
      index++;
      }
    
  // Create 48 ray cast mappers - 32 composite, 8 mip, 8 isosurface
  vtkVolumeRayCastMapper *raycastMapper[48];
  for ( i = 0; i < 8; i++ )
    {
    raycastMapper[i] = vtkVolumeRayCastMapper::New();
    raycastMapper[i]->SetInputConnection(reader->GetOutputPort());
    raycastMapper[i]->SetGradientEstimator(gradest);
    volume[i]->SetMapper( raycastMapper[i] );

      if ( i < 4 )
        {
        raycastMapper[i]->SetVolumeRayCastFunction( MIPFunction1 );  
        volume[i]->SetProperty( mipprop[i] );
        }
      else
        {
        raycastMapper[i]->SetVolumeRayCastFunction( MIPFunction2 );  
        volume[i]->SetProperty( mipprop[i-4] );
        }
    }

  renWin->SetSize(400,350);

  ren->ResetCamera();
  ren->GetActiveCamera()->Zoom(1.5);
  
  renWin->Render();

  int retVal = vtkRegressionTestImageThreshold( renWin, 70 );

  // Interact with the data at 3 frames per second
  iren->SetDesiredUpdateRate(3.0);
  iren->SetStillUpdateRate(0.001);


  iren->Start();

  
  // Clean up
  reader->Delete();
  oTFun->Delete();
  oTFun2->Delete();
  gTFun->Delete();
  cTFun->Delete();
  goTFun->Delete();
  for ( i = 0; i < 4; i++ )
    {
    mipprop[i]->Delete();
    }
  MIPFunction1->Delete();
  MIPFunction2->Delete();
  for ( i = 0; i < 8; i++ )
    {
    volume[i]->Delete();
    }
  gradest->Delete();
  ren->Delete();
  iren->Delete();
  renWin->Delete();
  
  return !retVal;
}



