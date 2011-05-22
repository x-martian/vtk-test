#pragma once

class vtkCursor2D;
class vtkPolyDataMapper;
class vtkActor;
class vtkPolyData;

class vtkCursor2DDriver
{
public:
	vtkCursor2DDriver();
	~vtkCursor2DDriver(void);

	typedef vtkPolyData DataType;
	typedef vtkCursor2D FilterType;
	typedef vtkPolyDataMapper MapperType;
	typedef vtkActor PropType;

	FilterType* GetFilter();
	PropType* GetProp();
};

bool vtkCursor2DTest(bool on);