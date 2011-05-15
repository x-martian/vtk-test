#pragma once

#include "vtkImageActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkCamera.h"

template<typename T> class vtkImagingTestPipelineTemplate
{
public:
	vtkImagingTestPipelineTemplate(T& _t) : t(_t)
	{
		typedef T::FilterType FilterType;

		T::FilterType *filter = t.GetFilter();

		vtkImageMapToWindowLevelColors* imgMap = vtkImageMapToWindowLevelColors::New();
		imgMap->SetOutputFormatToLuminance();
		imgMap->SetInputConnection(filter->GetOutputPort());
        filter->Delete();
		imgMap->SetWindow(1600.0);
		imgMap->SetLevel(800.0);

		// actor coordinates geometry, properties, transformation
		vtkImageActor* actor = vtkImageActor::New();
		actor->InterpolateOff();
		actor->SetInput(imgMap->GetOutput());
        imgMap->Delete();

		// renderers and render window
		vtkRenderer *renA = vtkRenderer::New();
		renA->SetViewport(0.0, 0.0, 0.5, 1.0);
//		vtkCamera* camera = renA->GetActiveCameraAndResetIfCreated();
//		camera->SetParallelProjection(1);

		win = vtkRenderWindow::New();
		win->SetSize(600,300);
		win->AddRenderer(renA);
        renA->Delete();
//		win->AddRenderer(renB);

		// add the actors to the renders
		renA->AddActor(actor);
        actor->Delete();

//		renB->ResetCamera();

		// an interactor
		vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
		iren->SetRenderWindow(win);
        iren->Delete();

		vtkInteractorStyleImage* imgStyle = vtkInteractorStyleImage::New();
		iren->SetInteractorStyle(imgStyle);
		imgStyle->Delete();

		renA->SetBackground(1,1,1); // Background color white
//		renB->SetBackground(1,1,1);

		// render an image (lights and cameras are created automatically)
		win->Start();
		std::string windowName("vtkImaging Test - ");
		windowName.append(t.Name());
		win->SetWindowName(windowName.c_str());
		win->Render();
	}

	~vtkImagingTestPipelineTemplate(void)
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