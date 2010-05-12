#pragma once

class vtkTransformPolyDataFilter;
class vtkPolyDataMapper;
class vtkPolyData;
class vtkActor;

class vtkVoxelContoursToSurfaceFilterDriver
{
public:
	typedef vtkPolyData DataType;
	typedef vtkTransformPolyDataFilter FilterType;
	typedef vtkPolyDataMapper MapperType;
	typedef vtkActor PropType;

	vtkVoxelContoursToSurfaceFilterDriver(void);
	~vtkVoxelContoursToSurfaceFilterDriver(void);

	FilterType* GetFilter();
	PropType* GetProp();
};

bool vtkVoxelContourToSurfaceFilterTest(bool on);
