#include "vtkPolyDataMapper.h"
#include "vtkPolyDataReader.h"
#include "vtkRenderer.h"
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkWin32RenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkTexture.h"
#include "vtkTextureMapToCylinder.h"
#include "vtkParametricSuperEllipsoid.h"
#include "vtkParametricSuperToroid.h"
#include "vtkParametricMobius.h"
#include "vtkPolyData.h"
#include "vtkDataSetMapper.h"
#include "vtkParametricFigure8Klein.h"
#include "vtkActor2D.h"
#include "vtkParametricKlein.h"
#include "vtkTextMapper.h"
#include "vtkParametricFunctionSource.h"
#include "vtkParametricTorus.h"
#include "vtkJPEGReader.h"

#include "vtkPoints.h"
#include "vtkParametricSpline.h"
#include "vtkParametricConicSpiral.h"
#include "vtkParametricBoy.h"
#include "vtkParametricRoman.h"
#include "vtkParametricRandomHills.h"
#include "vtkParametricEllipsoid.h"
#include "vtkParametricDini.h"
#include "vtkParametricEnneper.h"
#include "vtkParametricCrossCap.h"
#include "vtkParametricEnneper.h"
#include "vtkTextProperty.h"
#include "vtkMath.h"

void main()
{
//Compute normals, in case they are not provided with the model.
	vtkRenderer *ren1=vtkRenderer::New();
	vtkWin32OpenGLRenderWindow *renWin=vtkWin32OpenGLRenderWindow::New();
  	  renWin->AddRenderer(ren1);
	vtkWin32RenderWindowInteractor *iren=vtkWin32RenderWindowInteractor::New();
	  iren->SetRenderWindow(renWin);	

vtkJPEGReader *textureReader=vtkJPEGReader::New();
  textureReader-> SetFileName ("beach.jpg");
vtkTexture *texture=vtkTexture::New();
  texture ->SetInputConnection (textureReader ->GetOutputPort());
int i;
/*
# ------------------------------------------------------------
# For each parametric surface:
# 1) Create it
# 2) Assign mappers and actors
# 3) Position ths object
# 5) Add a label
# ------------------------------------------------------------

# ------------------------------------------------------------
# Create a torus
# ------------------------------------------------------------
*/
vtkParametricTorus *torus=vtkParametricTorus::New();
vtkParametricFunctionSource *torusSource=vtkParametricFunctionSource::New();
  torusSource-> SetParametricFunction (torus);
  torusSource-> SetScalarModeToPhase();

vtkPolyDataMapper *torusMapper=vtkPolyDataMapper::New();
  torusMapper-> SetInputConnection (torusSource-> GetOutputPort());
  torusMapper-> SetScalarRange( 0 ,360);

vtkActor *torusActor=vtkActor::New();
  torusActor-> SetMapper (torusMapper);
  torusActor-> SetPosition( 0 ,12, 0);

vtkTextMapper *torusTextMapper=vtkTextMapper::New();
    torusTextMapper-> SetInput ("Torus");
    torusTextMapper-> GetTextProperty()-> SetJustificationToCentered();
    torusTextMapper-> GetTextProperty()-> SetVerticalJustificationToCentered();
    torusTextMapper-> GetTextProperty()-> SetColor( 1 ,0 ,0);
    torusTextMapper-> GetTextProperty()-> SetFontSize (14);

vtkActor2D *torusTextActor =vtkActor2D::New();
    torusTextActor-> SetMapper (torusTextMapper );   
    torusTextActor-> GetPositionCoordinate()-> SetCoordinateSystemToWorld();
    torusTextActor-> GetPositionCoordinate()-> SetValue (0, 9.5 ,0);

//# ------------------------------------------------------------
//# Create a klein bottle
//# ------------------------------------------------------------
vtkParametricKlein *klein=vtkParametricKlein::New();
vtkParametricFunctionSource *kleinSource=vtkParametricFunctionSource::New();
  kleinSource-> SetParametricFunction (klein);
  kleinSource-> SetScalarModeToU0V0();

vtkPolyDataMapper *kleinMapper=vtkPolyDataMapper::New();
  kleinMapper-> SetInputConnection (kleinSource->GetOutputPort());
  kleinMapper-> SetScalarRange (0, 3);

vtkActor *kleinActor=vtkActor::New();
  kleinActor-> SetMapper(kleinMapper);
  kleinActor-> SetPosition (8 ,10.5 ,0);

vtkTextMapper *kleinTextMapper=vtkTextMapper::New();
    kleinTextMapper-> SetInput ("Klein");
    kleinTextMapper-> GetTextProperty() ->SetJustificationToCentered();
    kleinTextMapper-> GetTextProperty() ->SetVerticalJustificationToCentered();
    kleinTextMapper-> GetTextProperty()-> SetColor( 1, 0 ,0);
    kleinTextMapper-> GetTextProperty()-> SetFontSize (14);
vtkActor2D *kleinTextActor=vtkActor2D ::New();
    kleinTextActor-> SetMapper (kleinTextMapper );   
    kleinTextActor-> GetPositionCoordinate() ->SetCoordinateSystemToWorld();
    kleinTextActor-> GetPositionCoordinate() ->SetValue (8 ,9.5 ,0);

//------------------------------------------------------------
// Create a Figure-8 Klein
// ------------------------------------------------------------
vtkParametricFigure8Klein *klein2=vtkParametricFigure8Klein::New();
vtkParametricFunctionSource *klein2Source=vtkParametricFunctionSource::New();
  klein2Source-> SetParametricFunction (klein2);
  klein2Source ->GenerateTextureCoordinatesOn();

vtkPolyDataMapper *klein2Mapper=vtkPolyDataMapper::New();
  klein2Mapper-> SetInputConnection (klein2Source-> GetOutputPort());
  klein2Mapper-> SetScalarRange (0 ,3);

vtkActor *klein2Actor=vtkActor::New();
  klein2Actor-> SetMapper (klein2Mapper);
  klein2Actor-> SetPosition (16 ,12 ,0);
  klein2Actor-> SetTexture (texture);


vtkTextMapper *fig8KleinTextMapper=vtkTextMapper::New();
    fig8KleinTextMapper ->SetInput ("Fig-8 Klein");
    fig8KleinTextMapper-> GetTextProperty()-> SetJustificationToCentered();
    fig8KleinTextMapper-> GetTextProperty()-> SetVerticalJustificationToCentered();
    fig8KleinTextMapper-> GetTextProperty()-> SetColor (1 ,0 ,0);
    fig8KleinTextMapper-> GetTextProperty()-> SetFontSize (14);
vtkActor2D *fig8KleinTextActor=vtkActor2D::New();
    fig8KleinTextActor-> SetMapper (fig8KleinTextMapper);
    fig8KleinTextActor-> GetPositionCoordinate() ->SetCoordinateSystemToWorld();
    fig8KleinTextActor-> GetPositionCoordinate() ->SetValue( 16 ,9.5 ,0);

// ------------------------------------------------------------
// Create a mobius strip
// ------------------------------------------------------------
vtkParametricMobius *mobius=vtkParametricMobius::New();
vtkParametricFunctionSource *mobiusSource=vtkParametricFunctionSource::New();
  mobiusSource-> SetParametricFunction (mobius);
  mobiusSource-> GenerateTextureCoordinatesOn();

vtkPolyDataMapper *mobiusMapper=vtkPolyDataMapper::New();
  mobiusMapper ->SetInputConnection(mobiusSource ->GetOutputPort());

vtkActor *mobiusActor=vtkActor::New();
  mobiusActor-> SetMapper (mobiusMapper);
  mobiusActor-> RotateX (45);
  mobiusActor-> SetPosition (24 ,12 ,0);
  mobiusActor-> SetTexture (texture);

vtkTextMapper *mobiusTextMapper=vtkTextMapper::New();
    mobiusTextMapper-> SetInput ("Mobius");
    mobiusTextMapper-> GetTextProperty() ->SetJustificationToCentered();
    mobiusTextMapper-> GetTextProperty()-> SetVerticalJustificationToCentered();
    mobiusTextMapper-> GetTextProperty()-> SetColor (1, 0, 0);
    mobiusTextMapper-> GetTextProperty()-> SetFontSize (14);
vtkActor2D *mobiusTextActor=vtkActor2D::New();
    mobiusTextActor-> SetMapper (mobiusTextMapper);
    mobiusTextActor-> GetPositionCoordinate() ->SetCoordinateSystemToWorld();
    mobiusTextActor-> GetPositionCoordinate() ->SetValue (24 ,9.5 ,0);

//# ------------------------------------------------------------
//# Create a super toroid
//# ------------------------------------------------------------
vtkParametricSuperToroid *toroid=vtkParametricSuperToroid::New();
  toroid-> SetN1( 2);
  toroid-> SetN2( 3);
vtkParametricFunctionSource *toroidSource=vtkParametricFunctionSource::New();
  toroidSource-> SetParametricFunction (toroid);
  toroidSource-> SetScalarModeToU();

vtkPolyDataMapper *toroidMapper=vtkPolyDataMapper::New();
  toroidMapper-> SetInputConnection (toroidSource-> GetOutputPort());
  toroidMapper ->SetScalarRange (0 ,6.28);

vtkActor *toroidActor=vtkActor::New();
  toroidActor ->SetMapper (toroidMapper);
  toroidActor ->SetPosition( 0, 4, 0);

vtkTextMapper *superToroidTextMapper=vtkTextMapper::New();
    superToroidTextMapper-> SetInput ("Super Toroid");
    superToroidTextMapper-> GetTextProperty()-> SetJustificationToCentered();
    superToroidTextMapper-> GetTextProperty()-> SetVerticalJustificationToCentered();
    superToroidTextMapper-> GetTextProperty()-> SetColor (1,0 ,0);
    superToroidTextMapper-> GetTextProperty()-> SetFontSize (14);
vtkActor2D *superToroidTextActor=vtkActor2D::New();
    superToroidTextActor-> SetMapper(superToroidTextMapper);
    superToroidTextActor-> GetPositionCoordinate() ->SetCoordinateSystemToWorld();
    superToroidTextActor-> GetPositionCoordinate() ->SetValue (0 ,1.5 ,0);

//# ------------------------------------------------------------
//# Create a super ellipsoid
//# ------------------------------------------------------------
vtkParametricSuperEllipsoid *superEllipsoid=vtkParametricSuperEllipsoid::New();
superEllipsoid-> SetXRadius (1.25);
superEllipsoid-> SetYRadius (1.5);
superEllipsoid-> SetZRadius (1.0);
superEllipsoid ->SetN1 (1.1);
superEllipsoid-> SetN2 (1.75);
vtkParametricFunctionSource *superEllipsoidSource=vtkParametricFunctionSource::New();
  superEllipsoidSource ->SetParametricFunction (superEllipsoid);
  superEllipsoidSource ->SetScalarModeToV();

vtkPolyDataMapper *superEllipsoidMapper=vtkPolyDataMapper::New();
  superEllipsoidMapper ->SetInputConnection( superEllipsoidSource ->GetOutputPort());
  superEllipsoidMapper ->SetScalarRange (0 ,3.14);

vtkActor *superEllipsoidActor=vtkActor::New();
  superEllipsoidActor ->SetMapper (superEllipsoidMapper);
  superEllipsoidActor ->SetPosition (8,4 ,0);

vtkTextMapper *superEllipsoidTextMapper=vtkTextMapper::New();
    superEllipsoidTextMapper ->SetInput ("Super Ellipsoid");
    superEllipsoidTextMapper ->GetTextProperty() ->SetJustificationToCentered();
    superEllipsoidTextMapper-> GetTextProperty() ->SetVerticalJustificationToCentered();
    superEllipsoidTextMapper-> GetTextProperty() ->SetColor (1, 0, 0);
    superEllipsoidTextMapper-> GetTextProperty() ->SetFontSize (14);
vtkActor2D *superEllipsoidTextActor=vtkActor2D::New();
    superEllipsoidTextActor ->SetMapper (superEllipsoidTextMapper);
    superEllipsoidTextActor ->GetPositionCoordinate() ->SetCoordinateSystemToWorld();
    superEllipsoidTextActor-> GetPositionCoordinate() ->SetValue (8, 1.5, 0);

// ------------------------------------------------------------
// Create an open 1D spline
// ------------------------------------------------------------
vtkMath *math=vtkMath::New();
vtkPoints *inputPoints=vtkPoints::New();
for (i=0;i<10;i++)
{
    double x = math-> Random (-1 ,1);
    double y = math-> Random (-1 ,1);
    double z = math-> Random (-1 ,1);
    inputPoints ->InsertPoint (i ,x ,y ,z);
}
vtkParametricSpline *spline=vtkParametricSpline::New();
  spline ->SetPoints  (inputPoints);
  spline ->ClosedOff ();
vtkParametricFunctionSource *splineSource=vtkParametricFunctionSource::New();
  splineSource ->SetParametricFunction  (spline);

vtkPolyDataMapper *splineMapper=vtkPolyDataMapper::New();
  splineMapper ->SetInputConnection (splineSource ->GetOutputPort());

vtkActor *splineActor=vtkActor::New();
  splineActor ->SetMapper (splineMapper);
  splineActor ->SetPosition (16 ,4 ,0);
  splineActor ->GetProperty() ->SetColor (1 ,1 ,0);

vtkTextMapper *splineTextMapper=vtkTextMapper::New();
    splineTextMapper ->SetInput ("Open Spline");
    splineTextMapper ->GetTextProperty()-> SetJustificationToCentered();
    splineTextMapper-> GetTextProperty() ->SetVerticalJustificationToCentered();
    splineTextMapper ->GetTextProperty()-> SetColor (1 ,0 ,0);
    splineTextMapper ->GetTextProperty()-> SetFontSize (14);
vtkActor2D *splineTextActor=vtkActor2D::New();
    splineTextActor-> SetMapper (splineTextMapper);
    splineTextActor-> GetPositionCoordinate()-> SetCoordinateSystemToWorld();
    splineTextActor-> GetPositionCoordinate()-> SetValue (16 ,1.5 ,0);

//# ------------------------------------------------------------
//# Create a closed 1D spline
//# ------------------------------------------------------------
vtkParametricSpline *spline2=vtkParametricSpline::New();
  spline2 ->SetPoints( inputPoints);
  spline2 ->ClosedOn();
vtkParametricFunctionSource *spline2Source=vtkParametricFunctionSource::New();
  spline2Source ->SetParametricFunction( spline2);

vtkPolyDataMapper *spline2Mapper=vtkPolyDataMapper::New();
  spline2Mapper ->SetInputConnection (spline2Source ->GetOutputPort());

vtkActor *spline2Actor=vtkActor::New();
  spline2Actor ->SetMapper (spline2Mapper);
  spline2Actor ->SetPosition (24, 4 ,0);
  spline2Actor ->GetProperty() ->SetColor (1, 1 ,0);

vtkTextMapper *spline2TextMapper=vtkTextMapper::New();
    spline2TextMapper ->SetInput ("Closed Spline");
    spline2TextMapper ->GetTextProperty() ->SetJustificationToCentered();
    spline2TextMapper-> GetTextProperty() ->SetVerticalJustificationToCentered();
    spline2TextMapper-> GetTextProperty() ->SetColor (1, 0 ,0);
    spline2TextMapper-> GetTextProperty() ->SetFontSize (14);
vtkActor2D *spline2TextActor=vtkActor2D::New();
    spline2TextActor ->SetMapper (spline2TextMapper);
    spline2TextActor ->GetPositionCoordinate() ->SetCoordinateSystemToWorld();
    spline2TextActor ->GetPositionCoordinate() ->SetValue (24 ,1.5 ,0);

//# ------------------------------------------------------------
//# Create a spiral conic
//# ------------------------------------------------------------
vtkParametricConicSpiral *sconic=vtkParametricConicSpiral::New();
  sconic-> SetA (0.8);
  sconic-> SetB (2.5);
  sconic-> SetC (0.4);
vtkParametricFunctionSource *sconicSource=vtkParametricFunctionSource::New();
  sconicSource-> SetParametricFunction (sconic);
  sconicSource-> SetScalarModeToDistance();

vtkPolyDataMapper *sconicMapper=vtkPolyDataMapper::New();
sconicMapper-> SetInputConnection (sconicSource ->GetOutputPort());
vtkActor *sconicActor=vtkActor::New();
  sconicActor-> SetMapper (sconicMapper);
  sconicMapper-> SetScalarRange (0, 9);
  sconicActor-> SetPosition (0 ,-4, 0);
  sconicActor-> SetScale (1.2 ,1.2, 1.2);

vtkTextMapper *sconicTextMapper=vtkTextMapper::New();
    sconicTextMapper-> SetInput ("Spiral Conic");
    sconicTextMapper-> GetTextProperty()-> SetJustificationToCentered();
    sconicTextMapper-> GetTextProperty()-> SetVerticalJustificationToCentered();
    sconicTextMapper ->GetTextProperty()-> SetColor (1 ,0 ,0);
    sconicTextMapper-> GetTextProperty()-> SetFontSize (14);
vtkActor2D *sconicTextActor=vtkActor2D::New();
    sconicTextActor ->SetMapper (sconicTextMapper);
    sconicTextActor ->GetPositionCoordinate() ->SetCoordinateSystemToWorld();
    sconicTextActor ->GetPositionCoordinate() ->SetValue (0 ,-6.5 ,0);

//# ------------------------------------------------------------
//# Create Boy's surface
//# ------------------------------------------------------------
vtkParametricBoy *boy=vtkParametricBoy::New();
vtkParametricFunctionSource *boySource=vtkParametricFunctionSource::New();
  boySource ->SetParametricFunction (boy);
  boySource ->SetScalarModeToModulus();

vtkPolyDataMapper *boyMapper=vtkPolyDataMapper::New();
  boyMapper ->SetInputConnection( boySource ->GetOutputPort());
  boyMapper ->SetScalarRange( 0, 2);
vtkActor *boyActor=vtkActor::New();
  boyActor ->SetMapper (boyMapper);
  boyActor ->SetPosition( 8 ,-4 ,0);
  boyActor ->SetScale (1.5 ,1.5, 1.5);

vtkTextMapper *boyTextMapper=vtkTextMapper::New();
    boyTextMapper ->SetInput ("Boy");
    boyTextMapper ->GetTextProperty() ->SetJustificationToCentered();
    boyTextMapper ->GetTextProperty()-> SetVerticalJustificationToCentered();
    boyTextMapper ->GetTextProperty()-> SetColor (1 ,0 ,0);
    boyTextMapper ->GetTextProperty()-> SetFontSize (14);
vtkActor2D *boyTextActor=vtkActor2D::New();
    boyTextActor-> SetMapper (boyTextMapper);
    boyTextActor-> GetPositionCoordinate()-> SetCoordinateSystemToWorld();
    boyTextActor-> GetPositionCoordinate()-> SetValue (8 ,-6.5 ,0);

//# ------------------------------------------------------------
//# Create a cross cap
//# ------------------------------------------------------------
vtkParametricCrossCap *crossCap=vtkParametricCrossCap::New();
vtkParametricFunctionSource *crossCapSource=vtkParametricFunctionSource::New();
  crossCapSource ->SetParametricFunction (crossCap);
  crossCapSource ->SetScalarModeToY();

vtkPolyDataMapper *crossCapMapper=vtkPolyDataMapper::New();
  crossCapMapper ->SetInputConnection (crossCapSource ->GetOutputPort());
vtkActor *crossCapActor=vtkActor::New();
  crossCapActor ->SetMapper (crossCapMapper);
  crossCapActor ->RotateX (65);
  crossCapActor ->SetPosition (16, -4 ,0);
  crossCapActor ->SetScale (1.5 ,1.5 ,1.5);

vtkTextMapper *crossCapTextMapper=vtkTextMapper::New();
    crossCapTextMapper ->SetInput ("Cross Cap");
    crossCapTextMapper-> GetTextProperty() ->SetJustificationToCentered();
    crossCapTextMapper-> GetTextProperty() ->SetVerticalJustificationToCentered();
    crossCapTextMapper-> GetTextProperty() ->SetColor (1 ,0 ,0);
    crossCapTextMapper-> GetTextProperty() ->SetFontSize (14);
vtkActor2D *crossCapTextActor=vtkActor2D::New();
    crossCapTextActor ->SetMapper( crossCapTextMapper);
    crossCapTextActor ->GetPositionCoordinate() ->SetCoordinateSystemToWorld();
    crossCapTextActor ->GetPositionCoordinate() ->SetValue (16, -6.5, 0);

//# ------------------------------------------------------------
//# Create Dini's surface
//# ------------------------------------------------------------
vtkParametricDini *dini=vtkParametricDini::New();
vtkParametricFunctionSource *diniSource=vtkParametricFunctionSource::New();
  diniSource ->SetScalarModeToDistance();
  diniSource ->SetParametricFunction (dini);

vtkPolyDataMapper *diniMapper=vtkPolyDataMapper::New();
  diniMapper ->SetInputConnection (diniSource ->GetOutputPort());

vtkActor *diniActor=vtkActor::New();
  diniActor ->SetMapper (diniMapper);
  diniActor ->RotateX (-90);
  diniActor ->SetPosition (24 ,-3 ,0);
  diniActor ->SetScale (1.5 ,1.5 ,0.5);

vtkTextMapper *diniTextMapper=vtkTextMapper::New();
    diniTextMapper ->SetInput ("Dini");
    diniTextMapper ->GetTextProperty() ->SetJustificationToCentered();
    diniTextMapper ->GetTextProperty() ->SetVerticalJustificationToCentered();
    diniTextMapper-> GetTextProperty() ->SetColor (1 ,0, 0);
    diniTextMapper-> GetTextProperty() ->SetFontSize (14);
vtkActor2D *diniTextActor=vtkActor2D::New();
    diniTextActor ->SetMapper (diniTextMapper);
    diniTextActor ->GetPositionCoordinate() ->SetCoordinateSystemToWorld();
    diniTextActor ->GetPositionCoordinate() ->SetValue (24 ,-6.5 ,0);

//# ------------------------------------------------------------
//# Create Enneper's surface
//# ------------------------------------------------------------
vtkParametricEnneper *enneper=vtkParametricEnneper::New();
vtkParametricFunctionSource *enneperSource=vtkParametricFunctionSource::New();
  enneperSource ->SetParametricFunction (enneper);
  enneperSource ->SetScalarModeToQuadrant();

vtkPolyDataMapper *enneperMapper=vtkPolyDataMapper::New();
  enneperMapper ->SetInputConnection (enneperSource ->GetOutputPort());
  enneperMapper ->SetScalarRange (1 ,4);

vtkActor *enneperActor=vtkActor::New();
  enneperActor ->SetMapper (enneperMapper);
  enneperActor ->SetPosition( 0 ,-12 ,0);
  enneperActor ->SetScale (0.25 ,0.25 ,0.25);

vtkTextMapper *enneperTextMapper=vtkTextMapper::New();
    enneperTextMapper ->SetInput ("Enneper");
    enneperTextMapper ->GetTextProperty() ->SetJustificationToCentered();
    enneperTextMapper ->GetTextProperty() ->SetVerticalJustificationToCentered();
    enneperTextMapper ->GetTextProperty() ->SetColor (1 ,0 ,0);
    enneperTextMapper ->GetTextProperty() ->SetFontSize (14);
vtkActor2D *enneperTextActor =vtkActor2D::New();
    enneperTextActor-> SetMapper (enneperTextMapper    );
    enneperTextActor ->GetPositionCoordinate() ->SetCoordinateSystemToWorld();
    enneperTextActor ->GetPositionCoordinate() ->SetValue (0 ,-14.5 ,0);

//# ------------------------------------------------------------
//# Create an ellipsoidal surface
//# ------------------------------------------------------------
vtkParametricEllipsoid *ellipsoid=vtkParametricEllipsoid::New();
  ellipsoid ->SetXRadius (1);
  ellipsoid ->SetYRadius (0.75);
  ellipsoid ->SetZRadius (0.5);
vtkParametricFunctionSource *ellipsoidSource=vtkParametricFunctionSource::New();
  ellipsoidSource ->SetParametricFunction (ellipsoid);
  ellipsoidSource ->SetScalarModeToZ();

vtkPolyDataMapper *ellipsoidMapper=vtkPolyDataMapper::New();
  ellipsoidMapper ->SetInputConnection (ellipsoidSource ->GetOutputPort());
  ellipsoidMapper ->SetScalarRange (-0.5, 0.5);

vtkActor *ellipsoidActor=vtkActor::New();
  ellipsoidActor ->SetMapper (ellipsoidMapper);
  ellipsoidActor ->SetPosition (8 ,-12, 0);
  ellipsoidActor ->SetScale (1.5 ,1.5 ,1.5);

vtkTextMapper *ellipsoidTextMapper=vtkTextMapper::New();
    ellipsoidTextMapper ->SetInput ("Ellipsoid");
    ellipsoidTextMapper ->GetTextProperty() ->SetJustificationToCentered();
    ellipsoidTextMapper ->GetTextProperty() ->SetVerticalJustificationToCentered();
    ellipsoidTextMapper ->GetTextProperty() ->SetColor (1 ,0 ,0);
    ellipsoidTextMapper ->GetTextProperty() ->SetFontSize (14);
vtkActor2D *ellipsoidTextActor =vtkActor2D::New();
    ellipsoidTextActor ->SetMapper( ellipsoidTextMapper    );
    ellipsoidTextActor ->GetPositionCoordinate() ->SetCoordinateSystemToWorld();
    ellipsoidTextActor ->GetPositionCoordinate() ->SetValue (8 ,-14.5 ,0);
/*
# ------------------------------------------------------------
# Create an surface with random hills on it.
# Note that for testing, we will disable the
# random generation of the surfaces. This is
# because random number generators do not
# return the same result on different operating
# systems.
# ------------------------------------------------------------*/
vtkParametricRandomHills *randomHills=vtkParametricRandomHills::New();
  randomHills ->AllowRandomGenerationOff();
  randomHills ->GenerateTheHills();
vtkParametricFunctionSource *randomHillsSource=vtkParametricFunctionSource::New();
  randomHillsSource-> SetParametricFunction (randomHills);
  randomHillsSource-> GenerateTextureCoordinatesOn();

vtkPolyDataMapper *randomHillsMapper=vtkPolyDataMapper::New();
  randomHillsMapper-> SetInputConnection (randomHillsSource->GetOutputPort());

vtkActor *randomHillsActor=vtkActor::New();
  randomHillsActor ->SetMapper (randomHillsMapper);
  randomHillsActor ->SetPosition (16, -14 ,0);
  randomHillsActor ->SetScale (0.2 ,0.2 ,0.2);
  randomHillsActor ->SetTexture (texture);

vtkTextMapper *randomHillsTextMapper=vtkTextMapper::New();
    randomHillsTextMapper ->SetInput ("Random Hills");
    randomHillsTextMapper-> GetTextProperty()-> SetJustificationToCentered();
    randomHillsTextMapper-> GetTextProperty() ->SetVerticalJustificationToCentered();
    randomHillsTextMapper-> GetTextProperty() ->SetColor (1, 0 ,0);
    randomHillsTextMapper-> GetTextProperty() ->SetFontSize (14);
vtkActor2D *randomHillsTextActor =vtkActor2D::New();
    randomHillsTextActor ->SetMapper (randomHillsTextMapper    );
    randomHillsTextActor-> GetPositionCoordinate()-> SetCoordinateSystemToWorld();
    randomHillsTextActor-> GetPositionCoordinate() ->SetValue (16 ,-14.5, 0);

//# ------------------------------------------------------------
//# Create an Steiner's Roman Surface.
//# ------------------------------------------------------------
vtkParametricRoman *roman=vtkParametricRoman::New();
  roman ->SetRadius (1.5);
vtkParametricFunctionSource *romanSource=vtkParametricFunctionSource::New();
  romanSource ->SetParametricFunction( roman);
  romanSource ->SetScalarModeToX();

vtkPolyDataMapper *romanMapper=vtkPolyDataMapper::New();
  romanMapper ->SetInputConnection( romanSource ->GetOutputPort());

vtkActor *romanActor=vtkActor::New();
  romanActor-> SetMapper (romanMapper);
  romanActor-> SetPosition (24 ,-12, 0);

vtkTextMapper *romanTextMapper=vtkTextMapper::New();
    romanTextMapper-> SetInput( "Roman");
    romanTextMapper-> GetTextProperty()-> SetJustificationToCentered();
    romanTextMapper-> GetTextProperty()-> SetVerticalJustificationToCentered();
    romanTextMapper-> GetTextProperty()-> SetColor (1 ,0 ,0);
    romanTextMapper-> GetTextProperty()-> SetFontSize (14);
vtkActor2D *romanTextActor=vtkActor2D::New();
    romanTextActor-> SetMapper (romanTextMapper );
    romanTextActor-> GetPositionCoordinate()-> SetCoordinateSystemToWorld();
    romanTextActor-> GetPositionCoordinate()-> SetValue( 24 ,-14.5, 0);

//# ------------------------------------------------------------
//# Create the RenderWindow, Renderer and both Actors
//# ------------------------------------------------------------


// add actors
ren1->AddViewProp (torusActor);
ren1->AddViewProp (kleinActor);
ren1->AddViewProp (klein2Actor);
ren1->AddViewProp (toroidActor);
ren1->AddViewProp (superEllipsoidActor);
ren1->AddViewProp (mobiusActor);
ren1->AddViewProp (splineActor);
ren1->AddViewProp (spline2Actor);
ren1->AddViewProp (sconicActor);
ren1->AddViewProp (boyActor);
ren1->AddViewProp (crossCapActor);
ren1->AddViewProp (diniActor);
ren1->AddViewProp (enneperActor);
ren1->AddViewProp (ellipsoidActor);
ren1->AddViewProp (randomHillsActor);
ren1->AddViewProp (romanActor);
//add text actors
ren1->AddViewProp (torusTextActor);
ren1->AddViewProp (kleinTextActor);
ren1->AddViewProp (fig8KleinTextActor);
ren1->AddViewProp (mobiusTextActor);
ren1->AddViewProp (superToroidTextActor);
ren1->AddViewProp (superEllipsoidTextActor);
ren1->AddViewProp (splineTextActor);
ren1->AddViewProp (spline2TextActor);
ren1->AddViewProp (sconicTextActor);
ren1->AddViewProp (boyTextActor);
ren1->AddViewProp (crossCapTextActor);
ren1->AddViewProp (diniTextActor);
ren1->AddViewProp (enneperTextActor);
ren1->AddViewProp (ellipsoidTextActor);
ren1->AddViewProp (randomHillsTextActor);
ren1->AddViewProp (romanTextActor);


	ren1->ResetCamera();
	ren1->SetBackground(0.7, 0.8, 1);

	renWin->SetSize(700,700);
	renWin->Render();
	iren->Start();

	ren1->Delete();
	iren->Delete();
	renWin->Delete();
}






