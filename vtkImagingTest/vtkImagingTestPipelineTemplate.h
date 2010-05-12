#pragma once

#include "vtkActor.h"
#include "vtkCursor3D.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"

template<typename T> class vtkImagingTestPipelineTemplate
{
public:
	vtkImagingTestPipelineTemplate(T& _t) : t(_t)
	{
		typedef T::DataType DataType;
		typedef T::FilterType FilterType;
		typedef T::MapperType MapperTyper;

		// create sphere geometry
		T::FilterType *filter = t.GetFilter();

		// map to graphics library
		T::MapperType *mapper = T::MapperType::New();
		mapper->SetInputConnection(filter->GetOutputPort());
		mapper->ScalarVisibilityOff();

		// actor coordinates geometry, properties, transformation
		vtkActor *actor = vtkActor::New();
		actor->SetMapper(mapper);
		actor->GetProperty()->SetColor(0,0,1); // sphere color blue
		actor->GetProperty()->SetRepresentationToWireframe();
		actor->GetProperty()->ShadingOff();

		// renderers and render window
		vtkRenderer *renA = vtkRenderer::New();
		renA->SetViewport(0.0, 0.0, 0.5, 1.0);
		vtkRenderer *renB = vtkRenderer::New();
		renB->SetViewport(0.5, 0.0, 1.0, 1.0);

		win = vtkRenderWindow::New();
		win->SetSize(600,300);
		win->AddRenderer(renA);
		win->AddRenderer(renB);

		// add the actors to the renders
		renA->AddActor(actor);

		mapper = T::MapperType::New();
		T::DataType* data = T::DataType::SafeDownCast(filter->GetInput());
		mapper->ScalarVisibilityOff();
		actor = vtkActor::New();
		actor->SetMapper(mapper);
		actor->GetProperty()->SetRepresentationToWireframe();
		actor->GetProperty()->ShadingOff();
		renB->AddActor(actor);
		renB->ResetCamera();

		// an interactor
		vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
		iren->SetRenderWindow(win);

		renA->SetBackground(1,1,1); // Background color white
		renB->SetBackground(1,1,1);

		// add a 3D cursor to each Renderer
		vtkCursor3D* cursor = vtkCursor3D::New();
		cursor->SetFocalPoint(0.0, 0.0, 0.0);
		cursor->AllOff();
		cursor->XShadowsOn();
		cursor->YShadowsOn();
		cursor->ZShadowsOn();
		/*
		vtkCursor2D* cursor = vtkCursor2D::New();
		cursor->SetFocalPoint(0.0, 0.0, 0.0);
		cursor->SetModelBounds(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5);
		cursor->AllOff();
		cursor->AxesOn();
		*/
		mapper = vtkPolyDataMapper::New();
		mapper->SetInput(cursor->GetOutput());
		actor = vtkActor::New();
		actor->SetMapper(mapper);
		actor->GetProperty()->SetColor(1.0, 0.0, 0.0);

		renA->AddActor(actor);
		renB->AddActor(actor);

		// render an image (lights and cameras are created automatically)
		win->Render();
	}

	~vtkImagingTestPipelineTemplate(void)
	{
	}

	void StartInteraction(void)
	{
		win->GetInteractor()->Start();
	}

private:
	T& t;

	vtkRenderWindow* win;
};