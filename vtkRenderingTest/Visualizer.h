#pragma once

class vtkActor;
class vtkRenderer;
class vtkRenderWindow;

/** Help visualize the scene. */
class Visualizer
{
public:
	Visualizer(void);
	~Visualizer(void);

	void AddActorToViewPortA(vtkActor* actor, bool reset);
	void AddActorToViewPortB(vtkActor* actor, bool reset);

	vtkRenderer& GetViewPort(int viewPort);

	void StartInteraction(void);

private:

	vtkRenderWindow* win;

	void Visualizer::AddActorToViewPort(vtkActor* actor, int viewPort, bool reset);
};
