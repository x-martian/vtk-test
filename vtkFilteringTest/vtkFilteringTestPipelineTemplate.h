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
    typedef typename T::DataType DataType;
    typedef typename T::FilterType FilterType;
    typedef typename T::MapperType MapperType;
    typedef typename T::PropType PropType;

    vtkFilteringTestPipelineTemplate(T& test) : t(test)
        , win(0)
    {
        FilterType* filter = t.GetFilter();
        MapperType *mapper = t.GetMapper();
        mapper->SetInputConnection(filter->GetOutputPort());
        filter->Delete();

        // actor coordinates geometry, properties, transformation
        PropType* prop = t.GetProp();
        prop->SetMapper(mapper);
        mapper->Delete();

        // renderers and render window
        vtkRenderer *renA = vtkRenderer::New();
        renA->AddActor(prop);
        prop->Delete();
        renA->SetViewport(0.0, 0.0, 0.5, 1.0);
        renA->SetBackground(0.1, 0.2, 0.4);
        renA->ResetCamera();
        vtkRenderer *renB = vtkRenderer::New();
        renB->SetViewport(0.5, 0.0, 1.0, 1.0);

        win = vtkRenderWindow::New();
        win->SetSize(600,300);
        win->AddRenderer(renA);
        renA->Delete();
        win->AddRenderer(renB);
        renB->Delete();

        // an interactor
        vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
        //I* style = I::New();
        iren->SetRenderWindow(win);
        iren->Delete();

        win->Render();
    }

    ~vtkFilteringTestPipelineTemplate(void)
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

