#include "Visualizer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRendererCollection.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCursor3D.h"
#include "vtkCursor2D.h"
#include "vtkProperty.h"
#include "vtkPolyDataMapper.h"

Visualizer::Visualizer(void)
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
	vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
	mapper->SetInput(cursor->GetOutput());
	vtkActor* actor = vtkActor::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(1.0, 0.0, 0.0);

	renA->AddActor(actor);
	renB->AddActor(actor);
	renA->RemoveAllLights();
	renB->RemoveAllLights();

	// render an image (lights and cameras are created automatically)
	win->Render();
}

Visualizer::~Visualizer(void)
{
}

void Visualizer::AddActorToViewPortA(vtkActor* actor, bool reset)
{
	AddActorToViewPort(actor, 0, reset);
}

void Visualizer::AddActorToViewPortB(vtkActor* actor, bool reset)
{
	AddActorToViewPort(actor, 1, reset);
}

void Visualizer::AddActorToViewPort(vtkActor* actor, int viewPort, bool reset)
{
	vtkRendererCollection* c = win->GetRenderers();
	vtkRenderer& renderer = *vtkRenderer::SafeDownCast(c->GetItemAsObject(viewPort));
	renderer.AddActor(actor);

	if (reset) renderer.ResetCamera();
}

vtkRenderer& Visualizer::GetViewPort(int viewPort)
{
	vtkRendererCollection* c = win->GetRenderers();
	return *vtkRenderer::SafeDownCast(c->GetItemAsObject(viewPort));
}

void Visualizer::StartInteraction(void)
{
	win->GetInteractor()->Start();
}