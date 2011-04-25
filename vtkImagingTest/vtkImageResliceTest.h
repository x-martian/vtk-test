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

	const char* Name() const {return "vtkImageReslice";}
};

bool vtkImageResliceTest(bool on);