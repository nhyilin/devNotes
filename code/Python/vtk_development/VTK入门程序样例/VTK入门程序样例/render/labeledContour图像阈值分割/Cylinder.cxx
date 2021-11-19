
// 本例子可用于读取单幅CT图像并显示相应DICOM文件中头信息。

// First include the required header files for the VTK classes we are using.

#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkDICOMImageReader.h"
#include "vtkMaskPoints.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkTextProperty.h"

#include "vtkActor2D.h"
#include "vtkContourFilter.h"
#include "vtkLabeledDataMapper.h"
#include "vtkSelectVisiblePoints.h"


#include "vtkRenderWindowInteractor.h"


int main()
{
	vtkRenderer *ren1= vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
      renWin->AddRenderer( ren1 );
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
      iren->SetRenderWindow(renWin);


    vtkDICOMImageReader   *dr =  vtkDICOMImageReader::New();
	  dr->SetDataByteOrderToLittleEndian();
	  dr->SetFileName("E://CT/100098.dcm");
	  dr->SetDataOrigin(0.0,0.0,0.0);

	vtkContourFilter *skinext= vtkContourFilter::New();
      skinext->SetInputConnection(dr->GetOutputPort());
//    skinext->SetValue(0,200);
	  skinext->GenerateValues( 6, -600, 1150);
	  skinext->Update();

	int numpts= skinext->GetOutput()->GetNumberOfPoints();

	vtkPolyDataMapper *skinMapper = vtkPolyDataMapper::New();
      skinMapper->SetInputConnection(skinext->GetOutputPort());
	  skinMapper->ScalarVisibilityOn();
	  skinMapper->SetScalarRange(skinext->GetOutput()->GetScalarRange());

    vtkActor *skin = vtkActor::New();
      skin->SetMapper(skinMapper);
	  skin->GetProperty();
	  
// Subsample the points and label them
vtkMaskPoints *mask=vtkMaskPoints::New();
    mask-> SetInputConnection (skinext ->GetOutputPort());
    mask-> SetOnRatio(numpts / 50);
    mask-> SetMaximumNumberOfPoints(50);
    mask-> RandomModeOn();

// Create labels for points - only show visible points
vtkSelectVisiblePoints *visPts=vtkSelectVisiblePoints::New();
    visPts-> SetInputConnection(mask-> GetOutputPort());
    visPts-> SetRenderer (ren1);

vtkLabeledDataMapper *ldm=vtkLabeledDataMapper::New();
    ldm ->SetInputConnection (mask-> GetOutputPort());
//	char a='g';
//    ldm-> SetLabelFormat(&a);
    ldm-> SetLabelModeToLabelScalars();

    ldm-> GetLabelTextProperty()->SetFontFamilyToArial();
	ldm-> GetLabelTextProperty()->SetFontSize (10);
	ldm-> GetLabelTextProperty()->SetColor (1 ,0 ,0);

vtkActor2D *contourLabels=vtkActor2D::New();
    contourLabels-> SetMapper (ldm);

	  ren1->AddActor2D(skin);
	  ren1->AddActor2D(contourLabels);
	  ren1->SetBackground( 1.0, 1.0, 1 );

	//调整视窗大小
    renWin->SetSize( 600, 600 );

//	ren1-> GetActiveCamera()-> Zoom (1.5);

	iren->Initialize();
    iren->Start(); 

/*
	cout<<endl;
	cout<<"****************************************************************************"<<endl;
	cout<<"*******              The Information of This DICOM File              *******"<<endl;
	cout<<"****************************************************************************"<<endl;
	cout<<"The Patient's Name is :"<<dr->GetPatientName()<<endl;
	cout<<"The Height is :"<<dr->GetHeight()<<endl;
	cout<<"The weith  is :"<<dr->GetWidth()<<endl;
	cout<<"Study ID : "<<dr->GetStudyID()<<endl;
	cout<<"Study UID :"<<dr->GetStudyUID()<<endl;
	cout<<dr->GetDataByteOrderAsString()<<endl;
	cout<<"Header Size :"<<dr->GetHeaderSize()<<endl;
	cout<<"Pixel Spacing :"<<dr->GetPixelSpacing()<<endl;
	cout<<"***************************************************************************"<<endl;
	cout<<endl<<endl<<endl;
*/

	dr->Delete();
	ren1->Delete();
    renWin->Delete();
	iren->Delete();
    
	return 0;
}


	
	
