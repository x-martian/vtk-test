#include "SpherePipeline.h"

#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"

SpherePipeline::SpherePipeline(void)
{
}

SpherePipeline::~SpherePipeline(void)
{
}

vtkActor* SpherePipeline::GetActor() const
{
	// create sphere geometry
	vtkSphereSource *sphere = vtkSphereSource::New();
	sphere->SetCenter(0.0, 0.0, 0.0);
	sphere->SetRadius(1.0);
	sphere->SetThetaResolution(18);
	sphere->SetPhiResolution(18);

	// map to graphics library
	vtkPolyDataMapper *map = vtkPolyDataMapper::New();
	map->SetInput(sphere->GetOutput());

	// actor coordinates geometry, properties, transformation
	vtkActor *actor = vtkActor::New();
	actor->SetMapper(map);
	actor->GetProperty()->SetColor(0,0,1); // sphere color blue

	return actor;
}