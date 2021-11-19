//#include "stdafx.h"
#include "vtk.h"
#include "vtkPolyDataNormals.h"
#include "vtkClipVolume.h"
#include "vtkCylinder.h"
#include "vtkPolygon.h"
#include <vtkUnstructuredGrid.h>
#include <vtkPoints.h>
#include "vtkDataSetMapper.h"
#include "vtkDICOMImageReader.h"

CVTK::CVTK(int contourValue)

{
	//文件读取
	/*
	vtkVolume16Reader *v16=vtkVolume16Reader::New();
	v16->SetDataDimensions(64,64);
	v16->SetImageRange(1,93);
	v16->SetFilePrefix("./BMPData/quarter");
	v16->SetDataSpacing (3.2,3.2,1.5);//间距是否由拍摄片子而定
	*/

	vtkDICOMImageReader   *reader =  vtkDICOMImageReader::New();
	reader->SetDataByteOrderToLittleEndian();
	reader->SetDirectoryName("E://CT/head30/");
	reader->SetDataSpacing(3.2, 3.2, 1.5);
	reader->SetDataOrigin(0.0, 0.0, 0.0);

	//构造表面提取器,及其参数
	skinExtractor=vtkContourFilter::New();
	skinExtractor->SetInput((vtkDataObject *)reader->GetOutput());
     skinExtractor->SetValue(0,800);
//   skinExtractor->SetValue(0,500);

	reader->Delete();	
	//对表面进行平滑处理
	vtkPolyDataNormals * normal=vtkPolyDataNormals::New();
	normal->SetInput(skinExtractor->GetOutput());

	//裁切
    vtkPoints *polypoint=vtkPoints::New();
	polypoint->SetNumberOfPoints(4);
	polypoint->InsertPoint(0,0,0,0);
	polypoint->InsertPoint(1,1,0,0);
	polypoint->InsertPoint(2,1,1,0);
	polypoint->InsertPoint(3,0,1,0);

    vtkPolygon *polycell=vtkPolygon::New();
	//polycell->GetPointIds().SetNumberOfIds(4);
	//polycell->GetPointIds().SetId(0,0); 
	//polycell->GetPointIds().SetId(1,1);
	//polycell->GetPointIds().SetId(2,2);
	//polycell->GetPointIds().SetId(3,3);
	
	vtkUnstructuredGrid *polygrid=vtkUnstructuredGrid::New();
    polygrid->Allocate(1,1);
	polygrid->InsertNextCell(polycell->GetCellType(),polycell->GetPointIds()); 
	polygrid->SetPoints(polypoint);



	
	//图象映射器，根据数据形成图象
//	vtkPolyDataMapper *Mapper= vtkPolyDataMapper::New();
	Mapper= vtkPolyDataMapper::New();
//	Mapper->SetInput(normal->GetOutput());

    Mapper->SetInput(normal->GetOutput());

	normal->Delete();
	//表示行为者，表示物体
	Actor = vtkActor::New();
	// Actor = vtkActor::New();
	Actor->SetMapper(Mapper);
	Actor->GetProperty()->SetColor(0.6,0.6,0.6);
	
	
	//绘制器
 	renderer = vtkRenderer::New();
//	vtkRenderer *renderer = vtkRenderer::New();
	renderer->AddActor(Actor);
	renderer->SetBackground(0.5,0.5,0.5);
	
	//绘制窗
 	renWin = vtkRenderWindow::New();
//	vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer(renderer);
	
	//交互器
 	iren = vtkRenderWindowInteractor::New();
//	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);
	
	//轨迹器交互风格
	//vtkInteractorStyleTrackballActor * interactorStyle=vtkInteractorStyleTrackballActor::New();
	//iren->SetInteractorStyle(interactorStyle);
	//interactorStyle->Delete();
}


CVTK::~CVTK()
{
	iren->Delete();
	renWin->Delete();
	renderer->Delete();
	Actor->Delete();
	Mapper->Delete();
	skinExtractor->Delete();
}


void CVTK::BeginRenderOn(CStatic* aStatic)
{
	CRect rect;
	aStatic->GetClientRect(&rect);
	renWin->SetSize(rect.Width(),rect.Height());
	renWin->SetParentId(aStatic->m_hWnd);			
	renWin->Render();   
}
