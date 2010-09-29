#pragma once

#include "vtkImageActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleImage.h"

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
		imgMap->SetWindow(1600.0);
		imgMap->SetLevel(800.0);

		// actor coordinates geometry, properties, transformation
		vtkImageActor* actor = vtkImageActor::New();
		actor->InterpolateOff();
		actor->SetInput(imgMap->GetOutput());

		// renderers and render window
		vtkRenderer *renA = vtkRenderer::New();
		renA->SetViewport(0.0, 0.0, 0.5, 1.0);
//		vtkRenderer *renB = vtkRenderer::New();
//		renB->SetViewport(0.5, 0.0, 1.0, 1.0);

		win = vtkRenderWindow::New();
		win->SetSize(600,300);
		win->AddRenderer(renA);
//		win->AddRenderer(renB);

		// add the actors to the renders
		renA->AddActor(actor);

//		renB->ResetCamera();

		// an interactor
		vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
		iren->SetRenderWindow(win);

		vtkInteractorStyleImage* imgStyle = vtkInteractorStyleImage::New();
		iren->SetInteractorStyle(imgStyle);
		imgStyle->Delete();

		renA->SetBackground(1,1,1); // Background color white
//		renB->SetBackground(1,1,1);

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