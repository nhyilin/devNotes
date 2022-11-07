/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: TimeRenderer2.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkCullerCollection.h"
#include "vtkPlaneSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkStripper.h"
#include "vtkCellArray.h"
#include "vtkTriangleFilter.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCylinderSource.h"
#include "vtkProperty.h"
#include "vtkCylinder.h"
#include "vtkTransform.h"
#include "vtkClipPolyData.h"
#include "vtkPlane.h"

int main( int argc, char *argv[] )
{
  vtkRenderer *m_pvtkRenderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(m_pvtkRenderer);
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

	vtkPoints * pvtkPoints = vtkPoints::New();
		pvtkPoints->SetNumberOfPoints(4);
		pvtkPoints->InsertPoint(0, 0.0, 0.0, 0.0);
		pvtkPoints->InsertPoint(1, 10.0, 0.0, 0.0);
		pvtkPoints->InsertPoint(2, 10.0, 10.0, 0.0);
		pvtkPoints->InsertPoint(3, 0.0, 10.0, 0.0);

	vtkCellArray * pvtkCellArray = vtkCellArray::New();
		pvtkCellArray->InsertNextCell(4);
	for(int pi = 0; pi < 4; pi++)
	{
		pvtkCellArray->InsertCellPoint(pi);
	}
	vtkPolyData * pvtkPolyData = vtkPolyData::New();
		pvtkPolyData->SetPoints(pvtkPoints);
		pvtkPolyData->SetPolys(pvtkCellArray);

	vtkPolyDataMapper * pvtkPolyDataMapper = vtkPolyDataMapper::New();
		pvtkPolyDataMapper->SetInput(pvtkPolyData);

	vtkActor * pvtkActor = vtkActor::New();
		pvtkActor->SetMapper(pvtkPolyDataMapper);
		pvtkActor->GetProperty()->SetColor(255.0, 0.0, 0.0);

//以下是我的裁剪代码
    double dblExt[6];
    m_pvtkRenderer->ComputeVisiblePropBounds(dblExt);
    double coCenter[3];
		coCenter[0] = (dblExt[0] + dblExt[1]) / 2.0;
		coCenter[1] = (dblExt[2] + dblExt[3]) / 2.0;
		coCenter[2] = (dblExt[4] + dblExt[5]) / 2.0;

    vtkCylinder * pCylinder = vtkCylinder::New();
		pCylinder->SetRadius(2.5);
		pCylinder->SetCenter(5, 5, 0);

    vtkPlane * plane = vtkPlane::New();

    vtkCylinderSource * cylinder = vtkCylinderSource::New();
		cylinder->SetRadius(2.5);
		cylinder->SetCenter(5, 5, 0);

    vtkPolyDataMapper *spikeMapper = vtkPolyDataMapper::New();
        spikeMapper->SetInput(cylinder->GetOutput());

    vtkActor *spikeActor = vtkActor::New();
		spikeActor->SetMapper(spikeMapper);


    vtkTransform * pTransform = vtkTransform::New();
	    pTransform->Identity();
		pTransform->Translate(coCenter[0], coCenter[1], coCenter[2]);
		pTransform->RotateY(90);
		pTransform->Translate(-coCenter[0], -coCenter[1], -coCenter[2]);

    pCylinder->SetTransform(pTransform);


	vtkClipPolyData * pClipPolyData = vtkClipPolyData::New();
		pClipPolyData->SetInput(cylinder->GetOutput());
		pClipPolyData->SetClipFunction(pCylinder);
		pClipPolyData->InsideOutOn();//打开的话，场景中看不到实体了；关掉的话，没有变化

	vtkPolyDataMapper * pClipPolyDataMapper = vtkPolyDataMapper::New();
		pClipPolyDataMapper->SetInput(pClipPolyData->GetOutput());

    vtkActor * pActor = vtkActor::New();
		pActor->SetMapper(pClipPolyDataMapper);


	m_pvtkRenderer->SetBackground(0.0, 0.0, 0.4);
	m_pvtkRenderer->AddActor(pActor);
//	m_pvtkRenderer->AddActor(spikeActor);
	m_pvtkRenderer->ResetCamera();

	renWin->SetSize(600,600);
	renWin->Render();

	iren->Start();

	pvtkPoints->Delete();
	pvtkCellArray->Delete();
	pvtkPolyData->Delete();
	pvtkPolyDataMapper->Delete();
	pvtkActor->Delete();
    pCylinder->Delete();
//    pTransform->Delete();
  return 1;
}
