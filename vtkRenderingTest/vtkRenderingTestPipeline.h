#pragma once

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyDataMapper.h"
#include "vtkCamera.h"
#include "vtkProperty.h"

class StdCamera
{
public:

	StdCamera(void)
	{
	}

	~StdCamera(void)
	{
	}

	static vtkCamera* Camera(unsigned int i) {
		vtkCamera* camera = vtkCamera::New();
		camera->SetViewUp(0.0, 1.0, 0.0);
		camera->SetPosition(45.410005000000403, 82.031335999999996, 100.000000000000000);
		camera->SetFocalPoint(45.410005000000403, 82.031335999999996, 0.000000000000000);
		camera->SetPosition(0.0, 0.0, 40.0);
		camera->SetFocalPoint(0.0, 0.0, 0.0);
		camera->SetDistance(40.0);
		return camera;
	}
};


template<typename T, typename I, typename C=StdCamera> class vtkRenderingTestPipeline
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
		mapper = t.GetMapper();
		mapper->SetInputConnection(filter->GetOutputPort());

		// actor coordinates geometry, properties, transformation
		prop = t.GetProp();
		prop->SetMapper(mapper);
		mapper->Delete();

		vtkCamera* camera = C::Camera(0);

		// add the actors to the renders
		renA->AddActor(prop);
		renA->SetActiveCamera(camera);
		camera->Delete();

		// get the filter
		filter = t.GetFilter(1);

		// map to graphics library
		mapper = t.GetMapper();
		mapper->SetInputConnection(filter->GetOutputPort());

		// actor coordinates geometry, properties, transformation
		prop = t.GetProp();
		prop->SetMapper(mapper);
		mapper->Delete();

		// add the actors to the renders
		renB->AddActor(prop);
		camera = C::Camera(1);
		renB->SetActiveCamera(camera);
		camera->Delete();

		/*
		mapper = T::MapperType::New();
		T::DataType* data = T::DataType::SafeDownCast(filter->GetInput());
		mapper->ScalarVisibilityOff();
		prop = t.GetProp();
		prop->SetMapper(mapper);
		renB->AddActor(prop);
		renB->ResetCamera();
		*/
		renA->SetBackground(0.2,0.2,0.2);
		renB->SetBackground(0.2,0.2,0.2);

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
		if (win)
			win->Delete();
	}

	void StartInteraction(void)
	{
		win->GetInteractor()->Start();
	}

private:
	T& t;

	vtkRenderWindow* win;
};

