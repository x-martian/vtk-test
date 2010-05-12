#pragma once

class vtkPolyData;
class vtkImageReslice;
class vtkPolyDataMapper;

class vtkImageResliceDriver
{
public:
	typedef vtkPolyData DataType;
	typedef vtkImageReslice FilterType;
	typedef vtkPolyDataMapper MapperType;

	vtkImageResliceDriver(void);
	~vtkImageResliceDriver(void);

	FilterType* GetFilter();
};

bool vtkImageResliceTest(bool on);