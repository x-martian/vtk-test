#pragma once

class vtkPolyData;
class vtkCutter;
class vtkPolyDataMapper;
class vtkActor;

class vtkCutterDriver
{
public:
	typedef vtkPolyData DataType;
	typedef vtkCutter FilterType;
	typedef vtkPolyDataMapper MapperType;
	typedef vtkActor PropType;

	vtkCutterDriver(void);
	~vtkCutterDriver(void);

	FilterType* GetFilter();
	PropType* GetProp();
};

bool vtkCutterTest(bool on);