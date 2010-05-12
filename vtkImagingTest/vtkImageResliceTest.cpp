#include "vtkImageResliceTest.h"
#include "vtkSphereSource.h"
#include "vtkImageReslice.h"
#include "vtkPolyDataMapper.h"
#include "vtkMatrix4x4.h"

#include "vtkImagingTestPipelineTemplate.h"
#include "../lemon.h"

vtkImageResliceDriver::vtkImageResliceDriver(void)
{
}

vtkImageResliceDriver::~vtkImageResliceDriver(void)
{
}

vtkImageResliceDriver::FilterType* vtkImageResliceDriver::GetFilter()
{
	// create sphere geometry
	vtkSphereSource *sphere = vtkSphereSource::New();
	sphere->SetCenter(0.0, 0.0, 0.0);
	sphere->SetRadius(1.0);
	sphere->SetThetaResolution(18);
	sphere->SetPhiResolution(18);

	vtkImageReslice* reslice = vtkImageReslice::New();

	static double axes[16] = {
		         1, 0, 0, 0,
			     0, 1, 0, 0,
				 0, 0, 1, 0,
				0, 0, 0, 1 };

	vtkMatrix4x4* matrix = vtkMatrix4x4::New();
	matrix->DeepCopy(axes);
	reslice->SetResliceAxes(matrix);
	reslice->SetInputConnection(sphere->GetOutputPort());
	reslice->Update();

	return reslice;
}

bool vtkImageResliceTest(bool on)
{
	lemon::test<> t;

	vtkImageResliceDriver driver;
	vtkImagingTestPipelineTemplate<vtkImageResliceDriver> pipeline(driver);

	pipeline.StartInteraction();

	return t.done();
}