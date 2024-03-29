#pragma once
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"

template<typename T> class vtkWidgetsTestPipelineTemplate
{
public:
    vtkWidgetsTestPipelineTemplate(T& _t) : t(_t)
	{
		// renderers and render window
		vtkRenderer *renA = vtkRenderer::New();
		renA->SetViewport(0.0, 0.0, 1.0, 1.0);
        renA->SetBackground(0.1, 0.2, 0.3);

		vtkRenderWindow* win = vtkRenderWindow::New();
        win->LineSmoothingOn();
        win->PolygonSmoothingOn();
		win->SetSize(300,300);
		win->AddRenderer(renA);
        renA->Delete();

		// create the interactor, widgets like interactors to be set early on
		interactor = vtkRenderWindowInteractor::New();
//		I* style = I::New();
//		iren->SetInteractorStyle(style);
		interactor->SetRenderWindow(win);
        win->Delete();

        widget = t.CreateScene(*renA);
        if (widget)
            widget->EnabledOn();

		win->Render();
	}

	~vtkWidgetsTestPipelineTemplate(void)
	{
        if (widget)
            widget->Delete();
        if (interactor)
            interactor->Delete();
    }

    void StartInteractor(void) {
        if (interactor)
            interactor->Start();
    };

    static bool Run(bool on) {
        if (on) {
            T test;
            vtkWidgetsTestPipelineTemplate pipe(test);
            pipe.StartInteractor();
        }
        return true;
    }

private:
	T& t;
    vtkRenderWindowInteractor* interactor;
    vtkInteractorObserver* widget;
};

