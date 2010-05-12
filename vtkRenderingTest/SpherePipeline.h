#pragma once

class vtkSphereSource;
class vtkActor;

class SpherePipeline
{
public:
	SpherePipeline(void);
	~SpherePipeline(void);

	vtkActor* GetActor() const;
private:
	vtkSphereSource* source;
};
