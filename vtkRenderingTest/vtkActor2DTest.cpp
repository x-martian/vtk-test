#include "vtkActor2DTest.h"

#include "vtkPolyDataMapper2D.h"
#include "vtkActor2D.h"
#include "vtkProperty2D.h"
#include "vtkPolyData.h"
#include "vtkPoints.h"
#include "vtkCellArray.h"
#include "vtkInteractorStyleImage.h"
#include "vtkTriangleFilter.h"
#include "vtkAppendPolyData.h"

#include "vtkRenderingTestPipeline.h"

class vtkActor2DDriver
{
public:
	typedef vtkPolyData DataType;
	typedef vtkPolyDataAlgorithm FilterType;
	typedef vtkPolyDataMapper2D MapperType;
	typedef vtkActor2D PropType;

	vtkActor2DDriver(void)
	{
	}
	~vtkActor2DDriver(void)
	{
	}

	vtkPoints* GetPoints()
	{
		vtkPoints* points = vtkPoints::New();
		points->SetNumberOfPoints(4);
		points->SetPoint(0, 10.0, 10.0, 0.0);
		points->SetPoint(1, 110.0, 183.2, 0.0);
		points->SetPoint(2, 210.0, 10.0, 0.0);
		points->SetPoint(3, 110.0, 80.7, 0.0);

		return points;
	}

	FilterType* GetFilter(unsigned int id)
	{
		vtkTriangleFilter* filter = vtkTriangleFilter::New();
		vtkCellArray* cells = vtkCellArray::New();

		// create a concave polygon (equilateral with a cutout at the bottom)
		vtkPoints* points = GetPoints();

		cells->Allocate(1, 5);
		cells->InsertNextCell(5);
		cells->InsertCellPoint(0);
		cells->InsertCellPoint(1);
		cells->InsertCellPoint(2);
		cells->InsertCellPoint(3);
		cells->InsertCellPoint(0);

		vtkPolyData* poly = vtkPolyData::New();
		poly->Initialize();
		poly->SetGlobalWarningDisplay(1);
		poly->SetPoints(points);
		poly->SetPolys(cells);

		points->Delete();
		cells->Delete();

		//return poly;
		filter->AddInput(poly);
		return filter;
	}

	PropType* GetProp()
	{
		PropType* actor = PropType::New();
		actor->GetProperty()->SetColor(0, 1.0, 0.0);
		actor->GetProperty()->SetLineWidth(1.6);
		actor->GetProperty()->SetOpacity(0.333);
		return actor;
	}
};

bool vtkActor2DTest(bool on)
{
	vtkActor2DDriver driver;
	vtkRenderingTestPipeline<vtkActor2DDriver, vtkInteractorStyleImage> pipeline(driver);

	pipeline.StartInteraction();

	return true;
}
