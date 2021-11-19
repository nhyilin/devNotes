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

#include "vtkRenderer.h"   //着色,光照等
#include "vtkRenderWindow.h"//用于指定动作描述窗口
#include "vtkRenderWindowInteractor.h"//提供独立的平台,交互机制来实现鼠标键盘事件
#include "vtkVolume16Reader.h"//读取16位图像文件
#include "vtkPolyDataMapper.h"//将多边形数据转换为图形
#include "vtkActor.h"//描绘实现
#include "vtkOutlineFilter.h"//场景的外围边缘的立方体
#include "vtkCamera.h"//虚拟照像机来实现3D;
#include "vtkProperty.h"//描绘几何实体的光照度等表面信息
#include "vtkPolyDataNormals.h"//计算多边形网格的法线
#include "vtkContourFilter.h"//从标量值得到等值面,等值线.
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
  startall=clock();//用于计算处理时间

  vtkRenderer *aRenderer = vtkRenderer::New();//创建一个vtkRender,黑背景,白色光照,两侧光照开启
  vtkRenderWindow *renWin = vtkRenderWindow::New();//创建一个vtkRenderWindow,屏幕大小为300*300
                                                   //边缘开启,定位为(0,0),双缓冲开启
    renWin->AddRenderer(aRenderer);//将aRenderer加到renWin中来
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
                                  //物体的行为调试开启,时间置0;
    iren->SetRenderWindow(renWin);//设置renWin为可控制窗体

  cout<<"创建一个renderer对象"<< endl; 
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
                                     //初始化16位图像类型,前缀等
    v16->SetDataDimensions (64,64);//设数据范围大小
    v16->SetImageRange (1,93);//读取图像的文件名 *.1--*.123
    v16->SetDataByteOrderToLittleEndian();//字节格式(字节顺序),如果是littleEndian要倒过来
    v16->SetFilePrefix ("E://CT/headsq/quarter");//设置文件目录
    v16->SetDataSpacing (3.2, 3.2, 1.5);//像素间的间隔
  cout<<"创建一个16位图像的读取器对象"<< endl;

  end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK);  

  // An isosurface, or contour(轮廓) value of 500 is known to correspond to the
  // skin of the patient. Once generated, a vtkPolyDataNormals filter is
  // is used to create normals(法线) for smooth surface shading during rendering.
  start = clock(); 
  vtkContourFilter *skinExtractor = vtkContourFilter::New();
    skinExtractor->SetInputConnection(v16->GetOutputPort());//将V16与skinextractor连接上
	                                  //v16->GetOutputPort()为源头对象的输出
    skinExtractor->SetValue(0, 500);//设置轮廓值(0到1500范围内)

  vtkPolyDataNormals *skinNormals = vtkPolyDataNormals::New();
    skinNormals->SetInputConnection(skinExtractor->GetOutputPort());
    skinNormals->SetFeatureAngle(60.0);//多边形联结的角度范围,如果高于该值就将其改为该值

  vtkPolyDataMapper *skinMapper = vtkPolyDataMapper::New();
    skinMapper->SetInputConnection(skinNormals->GetOutputPort());
    skinMapper->ScalarVisibilityOff();//标量数据是否是有颜色的

  vtkActor *skin = vtkActor::New();//描绘实体
    skin->SetMapper(skinMapper);//连接最后的可视化操作

 cout<<"创建面绘制器对象"<< endl;
   end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  // An outline provides context around the data.
  // 提供边缘框架立方体
  start = clock(); 
  vtkOutlineFilter *outlineData = vtkOutlineFilter::New();
    outlineData->SetInputConnection(v16->GetOutputPort());////将V16与框架连接上
  vtkPolyDataMapper *mapOutline = vtkPolyDataMapper::New();
    mapOutline->SetInputConnection(outlineData->GetOutputPort());
  vtkActor *outline = vtkActor::New();
    outline->SetMapper(mapOutline);
    outline->GetProperty()->SetColor(1,1,1);//(1,1,1)表白色
	cout<<"创建边缘框架"<< endl;
	  end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  // It is convenient to create an initial view of the data. The FocalPoint
  // and Position form a vector direction. Later on (ResetCamera() method)
  // this vector is used to position the camera to look at the data in
  // this direction.
  start = clock(); 
  vtkCamera *aCamera = vtkCamera::New();
    aCamera->SetViewUp (0, 0, -1);//设视角位置
    aCamera->SetPosition (0, 1, 0);//设观察对象位置
    aCamera->SetFocalPoint (0, 0, 0);//设焦点
    aCamera->ComputeViewPlaneNormal();//自动
	cout<<"创建Camera(视点)对象,并设定."<< endl;
	  end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  // Actors are added to the renderer. An initial camera view is created.
  // The Dolly() method moves the camera towards the FocalPoint,
  // thereby enlarging the image.

  start = clock(); 
  //将图像读取对象与框架对象,轮廓描绘对象,视点对象相关联
  aRenderer->AddActor(outline);
  cout<<"为图像读取对象添加框架"<< endl;
  end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  start = clock();
  aRenderer->AddActor(skin); 
  cout<<"将图像读取对象与轮廓描绘对象相关联"<< endl;
  end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  start = clock(); 
  aRenderer->SetActiveCamera(aCamera);
  end = clock(); 
  cout<<"视点对象激活SetActiveCamera(aCamera)"<< endl;
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  start = clock();
  aRenderer->ResetCamera ();//自动设置CAMERA对照可见的动作
  end = clock(); 
  cout<<"自动设置视点ResetCamera ()"<< endl;
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  start = clock();
  aCamera->Dolly(1.5);
  cout<<"aCamera->Dolly(1.5);"<< endl;
  end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  // Set a background color for the renderer and set the size of the
  // render window (expressed in pixels).
  aRenderer->SetBackground(1,1,1);//设背景色
  renWin->SetSize(640, 480);//设窗体初始大小
  cout<<"设置窗体大小,背景"<< endl;

  // Note that when camera movement occurs (as it does in the Dolly()
  // method), the clipping planes often need adjusting. Clipping planes
  // consist of two planes: near and far along the view direction. The 
  // near plane clips out objects in front of the plane; the far plane
  // clips out objects behind the plane. This way only what is drawn
  // between the planes is actually rendered.
  start = clock(); 
  aRenderer->ResetCameraClippingRange ();
  cout<<"运动事件处理"<< endl;

    end = clock(); 
  printf("The time was: %f\n", (double)(end - start) / CLK_TCK); 

  // Initialize the event loop and then start it.
  cout<<"开始之前"<< endl;
  iren->Initialize();
  iren->Start(); 
  cout<<"开始"<< endl;

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
 printf("总时间为: %f\n", (double)(end - startall) / CLK_TCK); 
 int ww;
	 cin>>ww;
  return 0;
}
