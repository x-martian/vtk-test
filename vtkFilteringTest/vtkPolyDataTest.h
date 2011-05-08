#pragma once
class vtkPolyData;
class vtkAlgorithm;
class vtkPolyDataSource;    // not in use
class vtkPolyDataMapper;
class vtkActor;

class vtkPolyDataTest
{
public:
    typedef vtkPolyData DataType;
    typedef vtkAlgorithm FilterType;
    typedef vtkPolyDataMapper MapperType;
    typedef vtkActor PropType;

    vtkPolyDataTest(void);
    ~vtkPolyDataTest(void);

    MapperType* GetMapper();
    FilterType* GetFilter();
    PropType* GetProp();

    /** make a poly data object of a box. */
	static vtkPolyData* MakeBox(double a, double b, double c, double w, double h, double l);

	static bool Run(bool on);
};

