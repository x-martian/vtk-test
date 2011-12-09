#pragma once
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyle.h"

template<typename T, typename I=vtkInteractorStyle>
class vtkHybridTestPipelineTemplate
{
    typedef typename T::PropType PropType;

public:

    vtkHybridTestPipelineTemplate(T& _t) : t(_t)
    {
        PropType* prop = t.GetProp();
		vtkRenderer *ren = vtkRenderer::New();
		ren->SetViewport(0.0, 0.0, 1.0, 1.0);
        ren->SetBackground(0.1, 0.2, 0.3);
        ren->AddActor(prop);
        prop->Delete();

		vtkRenderWindow* win = vtkRenderWindow::New();
        win->LineSmoothingOn();
        win->PolygonSmoothingOn();
		win->SetSize(300,300);
		win->AddRenderer(ren);
        ren->Delete();

		interactor = vtkRenderWindowInteractor::New();
		interactor->SetRenderWindow(win);
        win->Delete();

        win->Render();
    }

    ~vtkHybridTestPipelineTemplate(void)
    {
    }

    void StartInteractor(void) {
        if (interactor)
            interactor->Start();
    };

    static bool Run(bool on) {
        if (on) {
            T test;
            vtkHybridTestPipelineTemplate pipe(test);
            pipe.StartInteractor();
        }
        return true;
    }

private:
	T& t;

    vtkRenderWindowInteractor* interactor;
};
