#pragma once

class vtkPolyData;
class vtkCutter;
class vtkAppendPolyData;
class vtkPolyDataMapper2D;
class vtkActor2D;

class vtkCutterDriver
{
public:
	typedef vtkPolyData DataType;
//	typedef vtkCutter FilterType;
	typedef vtkAppendPolyData FilterType;
	typedef vtkPolyDataMapper2D MapperType;
	typedef vtkActor2D PropType;

	vtkCutterDriver(void);
	~vtkCutterDriver(void);

	FilterType* GetFilter();
	PropType* GetProp();
};

bool vtkCutterTest(bool on);