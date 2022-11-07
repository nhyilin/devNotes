/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: TestOrientationMarkerWidget.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkActor.h"
#include "vtkAnnotatedCubeActor.h"
#include "vtkAppendPolyData.h"
#include "vtkAxesActor.h"
#include "vtkCamera.h"
#include "vtkCaptionActor2D.h"
#include "vtkCellArray.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkMath.h"
#include "vtkOrientationMarkerWidget.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkPropAssembly.h"
#include "vtkPropCollection.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkTextProperty.h"
#include "vtkTransform.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkTubeFilter.h"

#include "vtkRegressionTestImage.h"
#include "vtkDebugLeaks.h"

int main( int argc, char *argv[] )
{
  // create an actor out of parts of vtkAxesActor and vtkAnnotatedCubeActor
  // to have the widget follow.
  // part 1 is a helical spring to test vtkAxesActor SetUserDefinedShaft
  //
  double dt = vtkMath::DoublePi() / 20.0;
  double t = 0.0;
  double x = 0.0;
  int nPoints = 120;
  double dx = 0.8 / nPoints;

  vtkPoints* points  = vtkPoints::New(VTK_DOUBLE);
  vtkCellArray* line = vtkCellArray::New();
  line->InsertNextCell( nPoints + 80 );

  int i = 0;
  do
    {
    points->InsertPoint( i, 0.1*cos(t), x, 0.1*sin(t) );
    line->InsertCellPoint( i );
    t += dt;
    }while( ++i < 40 );

  do
    {
    points->InsertPoint( i, 0.1*cos(t), x, 0.1*sin(t) );
    line->InsertCellPoint(i);
    t += dt;
    x += dx;
    }while( ++i < nPoints + 40 );

  do
    {
    points->InsertPoint( i, 0.1*cos(t), x, 0.1*sin(t) );
    line->InsertCellPoint( i );
    t += dt;
    }while( ++i < nPoints + 80 );

  vtkPolyData* wiggle =  vtkPolyData::New();
  wiggle->SetPoints( points );
  wiggle->SetLines( line );

  vtkTubeFilter* tube = vtkTubeFilter::New();
  tube->SetInput( wiggle );
  tube->SetGenerateTCoordsToOff();
  tube->CappingOff();
  tube->SetVaryRadiusToVaryRadiusOff();
  tube->SetRadius( 0.02 );
  tube->SetNumberOfSides( 5 );

  // part 2 is generated from vtkAnnotatedCubeActor to test
  // vtkAxesActor SetUserDefinedTip
  //
  vtkAnnotatedCubeActor* cube = vtkAnnotatedCubeActor::New();
  cube->SetXPlusFaceText ( "V" );
  cube->SetXMinusFaceText( "K" );
  cube->SetYPlusFaceText ( "T" );
  cube->SetZPlusFaceText ( "" );
  cube->SetZMinusFaceText( "" );
  cube->SetYMinusFaceText( "" );
  cube->SetFaceTextScale( 0.666667 );

  vtkPropCollection* props = vtkPropCollection::New();
  cube->GetActors( props );

  vtkAppendPolyData* append = vtkAppendPolyData::New();

  vtkTransformPolyDataFilter* transformFilter = vtkTransformPolyDataFilter::New();
  vtkTransform* transform = vtkTransform::New();
  transformFilter->SetTransform( transform );

  vtkCollectionSimpleIterator sit;
  props->InitTraversal( sit );
  int nprops = props->GetNumberOfItems();

  for ( i = 0; i < nprops; i++ )
    {
    vtkActor *node = vtkActor::SafeDownCast( props->GetNextProp( sit ) );

    // the first prop in the collection will be the cube outline, the last
    // will be the text outlines
    //
    if ( node && i == 0 || i == (nprops - 1) )
      {
      vtkPolyData* poly = vtkPolyData::SafeDownCast(node->GetMapper()->GetInput());
      if ( poly )
        {
        transformFilter->SetInput( poly );
        transform->Identity();
        transform->SetMatrix( node->GetMatrix() );
        transform->Scale( 2.0, 2.0, 2.0 );
        transformFilter->Update();

        vtkPolyData* newpoly = vtkPolyData::New();
        newpoly->DeepCopy( transformFilter->GetOutput() );
        append->AddInput( newpoly );
        newpoly->Delete();
        }
      }
    }

  // the final actor the widget will follow
  //
  vtkAxesActor* axes = vtkAxesActor::New();

  axes->SetTotalLength( 1.2, 1.2 , 1.2 );
  axes->SetUserDefinedTip( append->GetOutput() );
  axes->SetTipTypeToUserDefined();
  axes->SetNormalizedShaftLength( 0.85, 0.85, 0.85 );
  axes->SetNormalizedTipLength( 0.15, 0.15, 0.15 );
  axes->AxisLabelsOff();
  axes->SetUserDefinedShaft( tube->GetOutput() );
  axes->SetShaftTypeToUserDefined();

  vtkProperty* property = axes->GetXAxisTipProperty();
  property->SetRepresentationToWireframe();
  property->SetDiffuse(0);
  property->SetAmbient(1);
  property->SetColor( 1, 0, 1 );

  property = axes->GetYAxisTipProperty();
  property->SetRepresentationToWireframe();
  property->SetDiffuse(0);
  property->SetAmbient(1);
  property->SetColor( 1, 1, 0 );

  property = axes->GetZAxisTipProperty();
  property->SetRepresentationToWireframe();
  property->SetDiffuse(0);
  property->SetAmbient(1);
  property->SetColor( 0, 1, 1 );

  // set up the renderer, window, and interactor
  //
  vtkRenderer* renderer = vtkRenderer::New();
  renderer->SetBackground( 0.0980, 0.0980, 0.4392 );

  vtkRenderWindow* renWin = vtkRenderWindow::New();
  renWin->AddRenderer( renderer );
  renWin->SetSize( 400, 400 );

  vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow( renWin );

  renderer->AddViewProp( axes );

  // set up an interesting view
  //
  vtkCamera* camera = renderer->GetActiveCamera();
  camera->SetViewUp( 0, 0, 1 );
  camera->SetFocalPoint( 0, 0, 0 );
  camera->SetPosition( 4.5, 4.5, 2.5 );
  renderer->ResetCameraClippingRange();

  // the orientation marker passed to the widget will be composed of two
  // actors: vtkAxesActor and a vtkAnnotatedCubeActor
  //
  cube->SetFaceTextScale( 0.65 );
  property = cube->GetCubeProperty();
  property->SetColor( 0.5, 1, 1 );

  property = cube->GetTextEdgesProperty();
  property->SetLineWidth( 1 );
  property->SetDiffuse( 0 );
  property->SetAmbient( 1 );
  property->SetColor( 0.1800, 0.2800, 0.2300 );

  // this static function improves the appearance of the text edges
  // since they are overlaid on a surface rendering of the cube's faces
  //
  vtkMapper::SetResolveCoincidentTopologyToPolygonOffset();

  // just for coverage
  //
  cube->TextEdgesOff();
  cube->TextEdgesOn();
  cube->CubeOff();
  cube->CubeOn();
  cube->FaceTextOff();
  cube->FaceTextOn();

  // anatomic labelling
  //
  cube->SetXPlusFaceText ( "A" );
  cube->SetXMinusFaceText( "P" );
  cube->SetYPlusFaceText ( "L" );
  cube->SetYMinusFaceText( "R" );
  cube->SetZPlusFaceText ( "S" );
  cube->SetZMinusFaceText( "I" );

  // change the vector text colors
  //
  property = cube->GetXPlusFaceProperty();
  property->SetColor(0, 0, 1);
  property->SetInterpolationToFlat();
  property = cube->GetXMinusFaceProperty();
  property->SetColor(0, 0, 1);
  property->SetInterpolationToFlat();
  property = cube->GetYPlusFaceProperty();
  property->SetColor(0, 1, 0);
  property->SetInterpolationToFlat();
  property = cube->GetYMinusFaceProperty();
  property->SetColor(0, 1, 0);
  property->SetInterpolationToFlat();
  property = cube->GetZPlusFaceProperty();
  property->SetColor(1, 0, 0);
  property->SetInterpolationToFlat();
  property = cube->GetZMinusFaceProperty();
  property->SetColor(1, 0, 0);
  property->SetInterpolationToFlat();

  vtkAxesActor* axes2 = vtkAxesActor::New();

  // simulate a left-handed coordinate system
  //
  transform->Identity();
  transform->RotateY(90);
  axes2->SetShaftTypeToCylinder();
  axes2->SetUserTransform( transform );
  axes2->SetXAxisLabelText( "w" );
  axes2->SetYAxisLabelText( "v" );
  axes2->SetZAxisLabelText( "u" );

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

  // combine orientation markers into one with an assembly
  //
  vtkPropAssembly* assembly = vtkPropAssembly::New();
  assembly->AddPart( axes2 );
  assembly->AddPart( cube );

  // set up the widget
  //
  vtkOrientationMarkerWidget* widget = vtkOrientationMarkerWidget::New();
  widget->SetOutlineColor( 0.9300, 0.5700, 0.1300 );
  widget->SetOrientationMarker( assembly );
  widget->SetInteractor( iren );
  widget->SetViewport( 0.0, 0.0, 0.4, 0.4 );
  widget->SetEnabled( 1 );
  widget->InteractiveOff();
  widget->InteractiveOn();

  iren->Initialize();
  renWin->Render();
  iren->Start();

  renderer->Delete();
  renWin->Delete();
  iren->Delete();
  props->Delete();
  transformFilter->Delete();
  transform->Delete();
  points->Delete();
  line->Delete();
  wiggle->Delete();
  tube->Delete();
  append->Delete();
  axes->Delete();
  cube->Delete();
  axes2->Delete();
  assembly->Delete();
  widget->Delete();

  return 0;
}
