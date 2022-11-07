/*
This example demonstrates cell picking using vtkCellPicker.  It displays
the results of picking using a vtkTextMapper.

converted from TCL
*/
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkLODActor.h"
#include "vtkConeSource.h"
#include "vtkGlyph3D.h"
#include "vtkCellPicker.h"
#include "vtkTextMapper.h"
#include "vtkActor2D.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkTextProperty.h"
#include "vtkCallbackCommand.h"
#include "vtkCamera.h"

int MouseMotion;
vtkRenderer *ren1;
vtkRenderWindow *renWin;
vtkRenderWindowInteractor *iren;
vtkCellPicker *picker;
vtkActor2D *textActor;
vtkTextMapper *textMapper;

class PickCommand : public vtkCommand
{
public:

   static PickCommand *New() { return new PickCommand; }
   void Delete() { delete this; }

   virtual void Execute(vtkObject *caller, unsigned long l, void *callData)
   {

       if (picker->GetCellId() < 0 )
       {
           textActor->VisibilityOff();
       }
       else
       {

           double selpt[3];
           picker->GetSelectionPoint(selpt);
           double x = selpt[0];
           double y = selpt[1];
           double pickPos[3];
           picker->GetPickPosition( pickPos );
           double xp = pickPos[0];
           double yp = pickPos[1];
           double zp = pickPos[2];

           char text[120];
           sprintf( text, "(%5.5f,  %5.5f,  %5.5f)", xp, yp, zp );
           textMapper->SetInput( text );

           textActor->SetPosition(x, y);
           textActor->VisibilityOn();
       }

       renWin->Render();
   }
};


void PickerInteractionCallback( vtkObject* vtkNotUsed(object),
                                      unsigned long event,
                                      void* clientdata,
                                      void* vtkNotUsed(calldata) )
{
   vtkInteractorStyleTrackballCamera * style =
(vtkInteractorStyleTrackballCamera*)clientdata;
   switch( event )
   {
   case vtkCommand::LeftButtonPressEvent:
       MouseMotion = 0;
       style->OnLeftButtonDown();
       break;
   case vtkCommand::LeftButtonReleaseEvent:
       if (MouseMotion == 0)
       {
           int *pick = iren->GetEventPosition();
           picker->Pick((double)pick[0], (double)pick[1], 0.0, ren1);
       }
       style->OnLeftButtonUp();
       break;
   case vtkCommand::MouseMoveEvent:
       MouseMotion = 1;
       style->OnMouseMove();
       break;
   }
}


void main(int argc, char* argv)
{
   MouseMotion = 0;
   vtkSphereSource *sphere = vtkSphereSource::New();

   vtkPolyDataMapper *sphereMapper = vtkPolyDataMapper::New();

   sphereMapper->SetInput(sphere->GetOutput());
   sphereMapper->GlobalImmediateModeRenderingOn();

   vtkLODActor *sphereActor = vtkLODActor::New();
   sphereActor->SetMapper(sphereMapper);

// create the spikes by glyphing the sphere with a cone.  Create the mapper
// and actor for the glyphs.
   vtkConeSource *cone = vtkConeSource::New();
   vtkGlyph3D *glyph = vtkGlyph3D::New();

   glyph->SetInput(sphere->GetOutput());
   glyph->SetSource(cone->GetOutput());
   glyph->SetVectorModeToUseNormal();
   glyph->SetScaleModeToScaleByVector();
   glyph->SetScaleFactor(0.25);

   vtkPolyDataMapper *spikeMapper = vtkPolyDataMapper::New();
   spikeMapper->SetInput(glyph->GetOutput());
   vtkLODActor *spikeActor = vtkLODActor::New();
   spikeActor->SetMapper(spikeMapper);

// Create a cell picker.
   PickCommand* pickObserver = PickCommand::New();
   picker = vtkCellPicker::New();
   picker->AddObserver( vtkCommand::EndPickEvent, pickObserver );

// Create a text mapper and actor to display the results of picking.
   textMapper = vtkTextMapper::New();
   vtkTextProperty *tprop = textMapper->GetTextProperty();
   tprop->SetFontFamilyToArial();
   tprop->SetFontSize(12);
   tprop->BoldOn();
//    tprop->ShadowOn();
   tprop->SetColor(1, 0, 0);
   textActor = vtkActor2D::New();
   textActor->VisibilityOff();
   textActor->SetMapper(textMapper);


// Create the Renderer, RenderWindow, and RenderWindowInteractor


   vtkInteractorStyleTrackballCamera *style =
vtkInteractorStyleTrackballCamera::New();
   vtkCallbackCommand * pickerCommand = vtkCallbackCommand::New();
   pickerCommand->SetClientData(style);
   pickerCommand->SetCallback(PickerInteractionCallback);
   style->AddObserver(vtkCommand::LeftButtonPressEvent, pickerCommand);
   style->AddObserver(vtkCommand::MouseMoveEvent, pickerCommand);
   style->AddObserver(vtkCommand::LeftButtonReleaseEvent, pickerCommand);

   ren1 = vtkRenderer::New();
   renWin = vtkRenderWindow::New();
   renWin->AddRenderer(ren1);
   iren = vtkRenderWindowInteractor::New();
   iren->SetRenderWindow(renWin);
   iren->SetInteractorStyle(style);
   iren->SetPicker(picker);


// Add the actors to the renderer, set the background and size


   ren1->AddActor2D(textActor);
   ren1->AddActor(sphereActor);
   ren1->AddActor(spikeActor);
   ren1->SetBackground(1, 1, 1);

   renWin->SetSize(300, 300);

// Get the camera and zoom in closer to the image.
   vtkCamera *cam1 = ren1->GetActiveCamera();
   cam1->Zoom(1.4);

   iren->Initialize();
   iren->Start();

   picker->RemoveObserver( pickObserver );
   sphere->Delete();
   sphereMapper->Delete();
   sphereActor->Delete();
   cone->Delete();
   glyph->Delete();
   spikeMapper->Delete();
   spikeActor->Delete();
   picker->Delete();
   textMapper->Delete();
   textActor->Delete();
   pickerCommand->Delete();
   style->Delete();
   ren1->Delete();
   renWin->Delete();
   pickObserver->Delete();
//    iren->Delete();
}