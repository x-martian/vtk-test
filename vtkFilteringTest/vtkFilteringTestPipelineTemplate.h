#pragma once

#ifdef GetProp
#undef GetProp
#endif

#include "vtkActor.h"
#include "vtkCursor3D.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyle.h"

template<typename T, typename typename I=vtkInteractorStyle> class vtkFilteringTestPipelineTemplate
{
public:

	vtkFilteringTestPipelineTemplate(T& test) : t(test)
	{
		typedef T::DataType DataType;
		typedef T::FilterType FilterType;
		typedef T::MapperType MapperTyper;
		
		// get the filter
//		T::FilterType *filter = t.GetFilter();

		// map to graphics library
		T::MapperType *mapper = T::MapperType::New();
		vtkPolyData* polyData = filter->GetOutput();
		mapper->SetInput(polyData);
		mapper->ScalarVisibilityOff();

		// actor coordinates geometry, properties, transformation
		T::PropType* prop = t.GetProp();
		prop->SetMapper(mapper);

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
		renA->AddActor(prop);

		mapper = T::MapperType::New();
		T::DataType* data = T::DataType::SafeDownCast(filter->GetInput());
		mapper->ScalarVisibilityOff();
		prop = t.GetProp();
		prop->SetMapper(mapper);
		renB->AddActor(prop);
		renB->ResetCamera();

		renA->SetBackground(1,1,1); // Background color white
		renB->SetBackground(1,1,1);

		// add a 3D cursor to each Renderer
		vtkCursor3D* cursor = vtkCursor3D::New();
		cursor->SetFocalPoint(0.0, 0.0, 0.0);
		cursor->AllOff();
		cursor->XShadowsOn();
		cursor->YShadowsOn();
		cursor->ZShadowsOn();

		vtkPolyDataMapper* cursorMapper = vtkPolyDataMapper::New();
		cursorMapper->SetInput(cursor->GetOutput());
		vtkActor* actor = vtkActor::New();
		actor->SetMapper(cursorMapper);
		actor->GetProperty()->SetColor(1.0, 0.0, 0.0);

		renA->AddActor(actor);
		renB->AddActor(actor);

		// an interactor
		vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
		I* style = I::New();
		//iren->SetInteractorStyle(style);
		iren->SetRenderWindow(win);

		// render an image (lights and cameras are created automatically)
		win->Render();
	}

	~vtkFilteringTestPipelineTemplate(void)
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

