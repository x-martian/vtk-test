#pragma once

class vtkCursor2D;
class vtkPolyDataMapper2D;
class vtkActor2D;
class vtkPolyData;

class vtkCursor2DDriver
{
public:
	vtkCursor2DDriver();
	~vtkCursor2DDriver(void);

	typedef vtkPolyData DataType;
	typedef vtkCursor2D FilterType;
	typedef vtkPolyDataMapper2D MapperType;
	typedef vtkActor2D PropType;

	FilterType* GetFilter();
	PropType* GetProp();
};

bool vtkCursor2DTest(bool on);