#pragma once

class vtkSphereSource;
class vtkActor;

class SpherePipeline
{
public:
	SpherePipeline(void);
	~SpherePipeline(void);

	static vtkActor* GetActor();
private:
	vtkSphereSource* source;
};
