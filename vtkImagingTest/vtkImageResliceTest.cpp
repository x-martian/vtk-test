#include "vtkImageResliceTest.h"
#include "vtkSphereSource.h"
#include "vtkImageReslice.h"
#include "vtkPolyDataMapper.h"
#include "vtkMatrix4x4.h"
#include "vtkImageData.h"
#include "vtkImageMapToWindowLevelColors.h"

#include "../vtkFilteringTest/vtkImageDataTest.h"

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
	vtkImageData* img3D = vtkImageDataTest::MakeImageData(8, 8, 8);

	vtkImageReslice* reslice = vtkImageReslice::New();

	static double axes[16] = {
		         1, 0, 0, 0,
			     0, 1, 0, 0,
				 0, 0, 1, 0,
				0, 0, 0, 1 };

	vtkMatrix4x4* matrix = vtkMatrix4x4::New();
	matrix->DeepCopy(axes);
	reslice->SetResliceAxes(matrix);
	reslice->SetInput(img3D);
	reslice->Update();

	return reslice;
}

bool vtkImageResliceTest(bool on)
{
	lemon::test<> t;

	vtkImageData* img3D = vtkImageDataTest::MakeImageData(16, 8, 4);
	double d = vtkImageDataTest::Y0;
	static double axes[16] = {
		1, 0, 0, 0,
	    0, 0, 1, d,
	    0, 1, 0, 0,
	    0, 0, 0, 1 };
	vtkMatrix4x4* resliceAxes = vtkMatrix4x4::New();
	resliceAxes->DeepCopy(axes);
	vtkImageReslice* reslice = vtkImageReslice::New();
	reslice->SetOutputDimensionality(2);
	reslice->SetResliceAxes(resliceAxes);
	reslice->SetInterpolationModeToLinear();
	reslice->InterpolateOff();
	reslice->SetInput(img3D);

	t.diag("The colums corresponding to the direction cosines of the slice plan");
	t.is(reslice->GetResliceAxesDirectionCosines()[0], 1, "column 1");
	t.is(reslice->GetResliceAxesDirectionCosines()[5], 1, "column 2");
	t.is(reslice->GetResliceAxesDirectionCosines()[7], 1, "column 3");

	vtkImageData* img2D = reslice->GetOutput();
	t.is(img2D->GetDataDimension(), 0, "Output data is invalid before Update");

	reslice->Update();

	t.diag("This creates a \"coronal\" cut from an axel source.");

	t.diag("First verify the demensionality:");
	t.is(img2D->GetDataDimension(), 2, "Output Data Dimension");
	t.is(img2D->GetDimensions()[2], 1, "the size of the third dimension is one");
	t.is(img2D->GetDimensions()[0], 16, "the size of the first dimension");
	t.is(img2D->GetDimensions()[1], 4, "the size of the second dimension");

	t.diag("second, verify the origin");
	t.is(img2D->GetOrigin()[0], vtkImageDataTest::X0, "The x-coordinate");
	t.is(img2D->GetOrigin()[1], vtkImageDataTest::Z0, "the y-coordinate");
	t.is(img2D->GetOrigin()[2], 0.0, "the z-coordinate is zero for a 2-D output");

	t.diag("finally, verify the data type and values");
	t.is(img2D->GetScalarType(), img3D->GetScalarType(), "scalar type agree with that of the input");
	t.is(img2D->GetScalarSize(), img3D->GetScalarSize(), "scalar size agree with that of the input");
	vtkIdType inc[3];
	img2D->GetIncrements(inc);
	t.is(inc[0], img2D->GetNumberOfScalarComponents(), "get the data increment");
	unsigned long* data = static_cast<unsigned long*>(img2D->GetScalarPointer());
	t.is(data[0], 0, "the value of first voxel");
	t.is(data[inc[0]], /*(i+j+k) of the img3D*/(1+0+0)*100, "the value of voxel incremented in x-direction of the output image");
	t.is(data[inc[1]], /*(i+j+k) of the img3D*/(0+1+0)*100, "the value of voxel incremented in y-direction of the output image");

	vtkImageResliceDriver driver;
	vtkImagingTestPipelineTemplate<vtkImageResliceDriver> pipeline(driver);

	pipeline.StartInteraction();

	return t.done();
}