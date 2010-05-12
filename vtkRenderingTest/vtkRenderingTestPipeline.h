#pragma once

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyDataMapper.h"
#include "vtkCursor3D.h"
#include "vtkProperty.h"

template<typename T, typename I> class vtkRenderingTestPipeline
{
public:
	vtkRenderingTestPipeline(T& _t) : t(_t)
	{
		// renderers and render window
		vtkRenderer *renA = vtkRenderer::New();
		renA->SetViewport(0.0, 0.0, 0.5, 1.0);
		vtkRenderer *renB = vtkRenderer::New();
		renB->SetViewport(0.5, 0.0, 1.0, 1.0);

		win = vtkRenderWindow::New();
		win->SetSize(600,300);
		win->AddRenderer(renA);
		win->AddRenderer(renB);

		typedef T::DataType DataType;
		typedef T::FilterType FilterType;
		typedef T::MapperType MapperType;
		typedef T::PropType PropType;

		FilterType* filter = 0;
		MapperType* mapper = 0;
		PropType* prop = 0;

		// get the filter
		filter = t.GetFilter(0);

		// map to graphics library
		mapper = MapperType::New();
		mapper->SetInputConnection(filter->GetOutputPort());
		mapper->ScalarVisibilityOff();

		// actor coordinates geometry, properties, transformation
		prop = t.GetProp();
		prop->SetMapper(mapper);
		mapper->Delete();

		// add the actors to the renders
		renA->AddActor(prop);

		// get the filter
		filter = t.GetFilter(1);

		// map to graphics library
		mapper = MapperType::New();
		mapper->SetInputConnection(filter->GetOutputPort());
		mapper->ScalarVisibilityOff();

		// actor coordinates geometry, properties, transformation
		prop = t.GetProp();
		prop->SetMapper(mapper);
		mapper->Delete();

		// add the actors to the renders
		renB->AddActor(prop);

		/*
		mapper = T::MapperType::New();
		T::DataType* data = T::DataType::SafeDownCast(filter->GetInput());
		mapper->ScalarVisibilityOff();
		prop = t.GetProp();
		prop->SetMapper(mapper);
		renB->AddActor(prop);
		renB->ResetCamera();
		*/
		renA->SetBackground(1,1,1); // Background color white
		renB->SetBackground(1,1,1);

		// an interactor
		vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
		I* style = I::New();
		iren->SetInteractorStyle(style);
		iren->SetRenderWindow(win);

		// render an image (lights and cameras are created automatically)
		win->Render();

		prop->Delete();
	}

	~vtkRenderingTestPipeline(void)
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

