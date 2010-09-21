#pragma once

class vtkPolyData;
class vtkImageReslice;
class vtkPolyDataMapper;

class vtkImageResliceDriver
{
public:
	typedef vtkImageReslice FilterType;

	vtkImageResliceDriver(void);
	~vtkImageResliceDriver(void);

	FilterType* GetFilter();
};

bool vtkImageResliceTest(bool on);