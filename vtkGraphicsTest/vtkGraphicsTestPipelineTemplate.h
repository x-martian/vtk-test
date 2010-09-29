#pragma once
#include <windows.h>

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
#include <sstream>

template<typename T, typename I=vtkInteractorStyle> class vtkGraphicsTestPipelineTemplate
{
public:
	vtkGraphicsTestPipelineTemplate(T& _t) : t(_t)
	{
		typedef T::DataType DataType;
		typedef T::FilterType FilterType;
		typedef T::MapperType MapperTyper;

		// get the filter
		T::FilterType *filter = t.GetFilter();

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
		/*
		vtkCursor2D* cursor = vtkCursor2D::New();
		cursor->SetFocalPoint(0.0, 0.0, 0.0);
		cursor->SetModelBounds(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5);
		cursor->AllOff();
		cursor->AxesOn();
		*/
		vtkPolyDataMapper* cursorMapper = vtkPolyDataMapper::New();
		cursorMapper->SetInput(cursor->GetOutput());
		vtkActor* actor = vtkActor::New();
		actor->SetMapper(cursorMapper);
		actor->GetProperty()->SetColor(1.0, 0.0, 0.0);

//		renA->AddActor(actor);
		renB->AddActor(actor);

		// an interactor
		vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
		I* style = I::New();
		//iren->SetInteractorStyle(style);
		iren->SetRenderWindow(win);

		// render an image (lights and cameras are created automatically)
		win->Render();
	}

	~vtkGraphicsTestPipelineTemplate(void)
	{
	}

	void StartInteraction(void)
	{
		std::stringstream text;
		win->GetInteractor()->GetInteractorStyle()->PrintSelf(text, vtkIndent());
		const char* buffer = text.str().c_str();
		win->GetInteractor()->Start();
	}

	COLORREF GetDisplayColor(int x, int y)
	{
		HWND hWnd = (HWND)win->GetGenericWindowId();

		RECT rect;
		GetClientRect(hWnd, &rect);
		y = rect.bottom - y;

		HDC hdc = GetDC(NULL);
		COLORREF color = GetPixel(hdc, x, y);

		for (int i=30; i<rect.right; ++i)
			for (int j=30; j<rect.bottom; ++j)
			{
				color = GetPixel(hdc, i, j);
				if (color == RGB(255,255,255)) {
					MessageBeep(1);
				}
			}

		ReleaseDC(hWnd, hdc);

		return color;
	}

private:
	T& t;

	vtkRenderWindow* win;
};