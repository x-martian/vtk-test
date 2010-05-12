#pragma once

#include "vtkProperty.h"
#include "vtkCursor3D.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"

template<typename T> class vtkPipelineTemplate
{
public:
	vtkPipelineTemplate(T& _t) : t(_t)
	{
		typedef T::SourceType SourceType;
		typedef T::MapperType MapperTyper;

		// create sphere geometry
		T::SourceType *source = T::SourceType::New();

		// map to graphics library
		T::MapperType *mapper = T::MapperType::New();
		mapper->SetInput(source->GetOutput());

		// actor coordinates geometry, properties, transformation
		vtkActor *actor = vtkActor::New();
		actor->SetMapper(mapper);
		actor->GetProperty()->SetColor(0,0,1); // sphere color blue

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
		renB->AddActor(actor);

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
		renA->RemoveAllLights();
		renB->RemoveAllLights();

		// render an image (lights and cameras are created automatically)
		win->Render();
	}

	~vtkPipelineTemplate(void)
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