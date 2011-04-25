#pragma once

class vtkPolyData;
class vtkPolyDataAlgorithm;
class vtkPolyDataMapper2D;
class vtkActor2D;

class vtkImageActorDriver
{
public:
	typedef vtkPolyData DataType;
	typedef vtkPolyDataAlgorithm FilterType;
	typedef vtkPolyDataMapper2D MapperType;
	typedef vtkActor2D PropType;

	vtkImageActorDriver(void);

	~vtkImageActorDriver(void);
};

