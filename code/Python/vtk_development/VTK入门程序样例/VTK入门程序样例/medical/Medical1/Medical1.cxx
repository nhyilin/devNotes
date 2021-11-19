/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: Medical1.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//
// This example reads a volume dataset, extracts an isosurface that
// represents the skin and displays it.
//

#include "vtkRenderer.h"   //��ɫ,���յ�
#include "vtkRenderWindow.h"//����ָ��������������
#include "vtkRenderWindowInteractor.h"//�ṩ������ƽ̨,����������ʵ���������¼�
#include "vtkVolume16Reader.h"//��ȡ16λͼ���ļ�
#include "vtkPolyDataMapper.h"//�����������ת��Ϊͼ��
#include "vtkActor.h"//���ʵ��
#include "vtkOutlineFilter.h"//��������Χ��Ե��������
#include "vtkCamera.h"//�����������ʵ��3D;
#include "vtkProperty.h"//��漸��ʵ��Ĺ��նȵȱ�����Ϣ
#include "vtkPolyDataNormals.h"//������������ķ���
#include "vtkContourFilter.h"//�ӱ���ֵ�õ���ֵ��,��ֵ��.
#include <time.h> 

int main (/*int argc, char **argv*/)
{ 
  //if (argc < 2)
  //  {
   //   cout << "Usage: " << argv[0] << " DATADIR/headsq/quarter" << endl;
   // return 1;
   // }

  // Create the renderer, the render window, and the interactor. The renderer
  // draws into the render window, the interactor enables mouse- and 
  // keyboard-based interaction with the data within the render window.
  //
  clock_t start,startall, end; 
  start = clock(); 
  startall=clock();//���ڼ��㴦��ʱ��

  vtkRenderer *aRenderer = vtkRenderer::New();//����һ��vtkRender,�ڱ���,��ɫ����,������տ���
  vtkRenderWindow *renWin = vtkRenderWindow::New();//����һ��vtkRenderWindow,��Ļ��СΪ300*300
                                                   //��Ե����,��λΪ(0,0),˫���忪��
    renWin->AddRenderer(aRenderer);//��aRenderer�ӵ�renWin����
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
                                  //�������Ϊ���Կ���,ʱ����0;
    iren->SetRenderWindow(renWin);//����renWinΪ�ɿ��ƴ���

  cout<<"����һ��renderer����"<< endl; 
  end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  
  // The following reader is used to read a series of 2D slices (images)
  // that compose the volume. The slice dimensions are set, and the
  // pixel spacing. The data Endianness must also be specified. The reader
  // usese the FilePrefix in combination with the slice number to construct
  // filenames using the format FilePrefix.%d. (In this case the FilePrefix
  // is the root name of the file: quarter.)
  start = clock(); 

  vtkVolume16Reader *v16 = vtkVolume16Reader::New();
                                     //��ʼ��16λͼ������,ǰ׺��
    v16->SetDataDimensions (64,64);//�����ݷ�Χ��С
    v16->SetImageRange (1,93);//��ȡͼ����ļ��� *.1--*.123
    v16->SetDataByteOrderToLittleEndian();//�ֽڸ�ʽ(�ֽ�˳��),�����littleEndianҪ������
    v16->SetFilePrefix ("E://CT/headsq/quarter");//�����ļ�Ŀ¼
    v16->SetDataSpacing (3.2, 3.2, 1.5);//���ؼ�ļ��
  cout<<"����һ��16λͼ��Ķ�ȡ������"<< endl;

  end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK);  

  // An isosurface, or contour(����) value of 500 is known to correspond to the
  // skin of the patient. Once generated, a vtkPolyDataNormals filter is
  // is used to create normals(����) for smooth surface shading during rendering.
  start = clock(); 
  vtkContourFilter *skinExtractor = vtkContourFilter::New();
    skinExtractor->SetInputConnection(v16->GetOutputPort());//��V16��skinextractor������
	                                  //v16->GetOutputPort()ΪԴͷ��������
    skinExtractor->SetValue(0, 500);//��������ֵ(0��1500��Χ��)

  vtkPolyDataNormals *skinNormals = vtkPolyDataNormals::New();
    skinNormals->SetInputConnection(skinExtractor->GetOutputPort());
    skinNormals->SetFeatureAngle(60.0);//���������ĽǶȷ�Χ,������ڸ�ֵ�ͽ����Ϊ��ֵ

  vtkPolyDataMapper *skinMapper = vtkPolyDataMapper::New();
    skinMapper->SetInputConnection(skinNormals->GetOutputPort());
    skinMapper->ScalarVisibilityOff();//���������Ƿ�������ɫ��

  vtkActor *skin = vtkActor::New();//���ʵ��
    skin->SetMapper(skinMapper);//�������Ŀ��ӻ�����

 cout<<"���������������"<< endl;
   end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  // An outline provides context around the data.
  // �ṩ��Ե���������
  start = clock(); 
  vtkOutlineFilter *outlineData = vtkOutlineFilter::New();
    outlineData->SetInputConnection(v16->GetOutputPort());////��V16����������
  vtkPolyDataMapper *mapOutline = vtkPolyDataMapper::New();
    mapOutline->SetInputConnection(outlineData->GetOutputPort());
  vtkActor *outline = vtkActor::New();
    outline->SetMapper(mapOutline);
    outline->GetProperty()->SetColor(1,1,1);//(1,1,1)���ɫ
	cout<<"������Ե���"<< endl;
	  end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  // It is convenient to create an initial view of the data. The FocalPoint
  // and Position form a vector direction. Later on (ResetCamera() method)
  // this vector is used to position the camera to look at the data in
  // this direction.
  start = clock(); 
  vtkCamera *aCamera = vtkCamera::New();
    aCamera->SetViewUp (0, 0, -1);//���ӽ�λ��
    aCamera->SetPosition (0, 1, 0);//��۲����λ��
    aCamera->SetFocalPoint (0, 0, 0);//�轹��
    aCamera->ComputeViewPlaneNormal();//�Զ�
	cout<<"����Camera(�ӵ�)����,���趨."<< endl;
	  end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  // Actors are added to the renderer. An initial camera view is created.
  // The Dolly() method moves the camera towards the FocalPoint,
  // thereby enlarging the image.

  start = clock(); 
  //��ͼ���ȡ�������ܶ���,����������,�ӵ���������
  aRenderer->AddActor(outline);
  cout<<"Ϊͼ���ȡ������ӿ��"<< endl;
  end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  start = clock();
  aRenderer->AddActor(skin); 
  cout<<"��ͼ���ȡ���������������������"<< endl;
  end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  start = clock(); 
  aRenderer->SetActiveCamera(aCamera);
  end = clock(); 
  cout<<"�ӵ���󼤻�SetActiveCamera(aCamera)"<< endl;
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  start = clock();
  aRenderer->ResetCamera ();//�Զ�����CAMERA���տɼ��Ķ���
  end = clock(); 
  cout<<"�Զ������ӵ�ResetCamera ()"<< endl;
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  start = clock();
  aCamera->Dolly(1.5);
  cout<<"aCamera->Dolly(1.5);"<< endl;
  end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  // Set a background color for the renderer and set the size of the
  // render window (expressed in pixels).
  aRenderer->SetBackground(1,1,1);//�豳��ɫ
  renWin->SetSize(640, 480);//�贰���ʼ��С
  cout<<"���ô����С,����"<< endl;

  // Note that when camera movement occurs (as it does in the Dolly()
  // method), the clipping planes often need adjusting. Clipping planes
  // consist of two planes: near and far along the view direction. The 
  // near plane clips out objects in front of the plane; the far plane
  // clips out objects behind the plane. This way only what is drawn
  // between the planes is actually rendered.
  start = clock(); 
  aRenderer->ResetCameraClippingRange ();
  cout<<"�˶��¼�����"<< endl;

    end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  // Initialize the event loop and then start it.
  cout<<"��ʼ֮ǰ"<< endl;
  iren->Initialize();
  iren->Start(); 
  cout<<"��ʼ"<< endl;

  // It is important to delete all objects created previously to prevent
  // memory leaks. In this case, since the program is on its way to
  // exiting, it is not so important. But in applications it is
  // essential.
  v16->Delete();
  skinExtractor->Delete();
  skinNormals->Delete();
  skinMapper->Delete();
  skin->Delete();
  outlineData->Delete();
  mapOutline->Delete();
  outline->Delete();
  aCamera->Delete();
  iren->Delete();
  renWin->Delete();
  aRenderer->Delete();
 printf("��ʱ��Ϊ: %f\n", (double)(end - startall) / CLK_TCK); 
 int ww;
	 cin>>ww;
  return 0;
}
