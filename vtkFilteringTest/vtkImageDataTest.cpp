#include "vtkImageDataTest.h"
#include "vtkFilteringTestPipelineTemplate.h"

#include "vtkImageData.h"
#include "vtkPointData.h"

#include "../lemon.h"

#define W 64
#define H 32
#define L 16

const double vtkImageDataTest::X0 = -25.003;
const double vtkImageDataTest::Y0 = -25.002;
const double vtkImageDataTest::Z0 = -15.006;
const double vtkImageDataTest::DX = 1.732;
const double vtkImageDataTest::DY = 3.464;
const double vtkImageDataTest::DZ = 6.928;

vtkImageDataTest::vtkImageDataTest(void)
{
}

vtkImageDataTest::~vtkImageDataTest(void)
{
}

vtkImageData* vtkImageDataTest::MakeImageData(unsigned w, unsigned h, unsigned l)
{
	vtkImageData* img = vtkImageData::New();

	// prepare
	double spacing[3] = {DX,DY,DZ}, origin[3] = {X0,Y0,Z0};
	int extend[6] = {0, w-1, 0, h-1, 0, l-1};
	img->SetSpacing(spacing);
	img->SetOrigin(origin);
	img->SetExtent(extend);
	img->SetScalarTypeToUnsignedLong();
	img->SetNumberOfScalarComponents(2);
	img->AllocateScalars();
	img->GetPointData()->GetScalars()->SetName("TestImage");

	// fill in the voxel data
	unsigned long* buffer = (unsigned long*)img->GetScalarPointer();
	for (unsigned int i = 0; i < l; ++i) {
		for (unsigned int j = 0; j < h; ++j)
			for (unsigned int k = 0; k < w; ++k) {
				*buffer = (i+j+k)*100;
				++buffer;
				*buffer = (i+j+k)*100+1;
				++buffer;
			}
	}

	return img;
}

bool vtkImageDataTest::Run(bool on)
{
	lemon::test<> t;

	vtkImageData* img = MakeImageData(W, H, L);

	int ijk[3] = {1, 1, 1};
	t.is(img->ComputePointId(ijk), vtkIdType(W*H+W+1), "Verify Point Id");
	t.is(img->ComputeCellId(ijk), vtkIdType((W-1)*(H-1)+W), "Verify Cell Id");
	t.is(img->FindPoint(X0+DX/3.0, Y0+DY/3.0, Z0+DZ/3.0), vtkIdType(0), "Verify FindPoint");
	t.is(img->GetActualMemorySize(), 4*2*W*H*L/1024, "Verify ActualMemorySize");
	t.is(img->GetBounds()[0], X0, "GetBounds()[0]");
	t.is(img->GetBounds()[5], Z0+DZ*(L-1), "GetBounds()[1]");
	t.is(img->GetDataDimension(), 3, "GetDataDimension");
	t.ok(img->GetDataReleased()==0, "GetDataReleased");	// "==0" used to remove warning
	t.is(img->GetDimensions()[2], L, "GetDimension");
	t.is(img->GetMaximumNumberOfPieces(), -1, "GetMaximumNumberOfPieces");
	t.is(img->GetOrigin()[0], X0, "GetOrigin");
	t.is(((unsigned long*)img->GetScalarPointer())[W*H*1+W*2+3], (1+2+3)*100, "verify stored data");
	t.is(img->GetScalarSize(), 4, "verify GetScalerSize is 4 byte (long)");
	t.is(img->GetSpacing()[0], DX, "verify get spacing");

	img->Initialize();
	t.is(img->GetDimensions()[0], 0, "dimension is reset after Initialize()");
	img->SetDimensions(W, H, L);
	t.is(img->GetExtent()[1], W-1, "equivalency of SetDimensions and SetExtend()");

	img->Delete();

	vtkImageDataTest test;
//	vtkFilteringTestPipelineTemplate<vtkImageDataTest> pipeline(test);
//	pipeline.StartInteraction();
	return true;
}
