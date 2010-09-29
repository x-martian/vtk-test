#pragma once

class vtkImageData;
class vtkAlgorithm;
class vtkPolyDataMapper;

class vtkImageDataTest
{
public:
	typedef vtkImageData DataType;
	typedef vtkAlgorithm FilterType;
	typedef vtkPolyDataMapper MapperType;

	vtkImageDataTest(void);
	~vtkImageDataTest(void);

	static vtkImageData* MakeImageData(unsigned w, unsigned h, unsigned l);

	static bool Run(bool on);

	static const double X0, Y0, Z0;
	static const double DX, DY, DZ;
};

