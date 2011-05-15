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
#include "vtkTransformPolyDataFilter.h"
#include "vtkMatrix4x4.h"
#include "vtkTransform.h"

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

	vtkPoints* GetROIPoints()
	{
		vtkPoints* points = vtkPoints::New();
		points->SetNumberOfPoints(60);
		points->SetPoint( 0, 45.410005000000403, -82.031335999999996, 75.000000000000000);
		points->SetPoint( 1, 47.363129000000399, -82.451385593886002, 75.000000000000000);
		points->SetPoint( 2, 49.316253000000401, -82.896442554347999, 75.000000000000000);
		points->SetPoint( 3, 51.269377000000397, -83.339630893130007, 75.000000000000000);
		points->SetPoint( 4, 53.222501000000399, -83.339630893130007, 75.000000000000000);
		points->SetPoint( 5, 55.175625000000402, -82.946862874999994, 75.000000000000000);
		points->SetPoint( 6, 57.128749000000397, -82.904816455554993, 75.000000000000000);
		points->SetPoint( 7, 59.081873000000400, -82.444816506383006, 75.000000000000000);
		points->SetPoint( 8, 61.034997000000402, -81.580615076922996, 75.000000000000000);
		points->SetPoint( 9, 61.178609058823902, -81.543054999999995, 75.000000000000000);
		points->SetPoint(10, 62.988121000000397, -81.127356310810995, 75.000000000000000);
		points->SetPoint(11, 64.941245000000393, -80.005874074074001, 75.000000000000000);
		points->SetPoint(12, 65.517166179487603, -79.589931000000007, 75.000000000000000);
		points->SetPoint(13, 66.894369000000395, -78.508503281879001, 75.000000000000000);
		points->SetPoint(14, 67.711241616352595, -77.636807000000005, 75.000000000000000);
		points->SetPoint(15, 68.847493000000398, -76.471232999999998, 75.000000000000000);
		points->SetPoint(16, 69.565553294118104, -75.683683000000002, 75.000000000000000);
		points->SetPoint(17, 70.777906255814401, -73.730559000000000, 75.000000000000000);
		points->SetPoint(18, 70.800617000000400, -73.707848255814000, 75.000000000000000);
		points->SetPoint(19, 72.132292454545905, -71.777434999999997, 75.000000000000000);
		points->SetPoint(20, 72.753741000000403, -70.855126444443997, 75.000000000000000);
		points->SetPoint(21, 73.565508162500393, -69.824310999999994, 75.000000000000000);
		points->SetPoint(22, 74.706865000000406, -67.902025800000004, 75.000000000000000);
		points->SetPoint(23, 74.730116476190901, -67.871187000000006, 75.000000000000000);
		points->SetPoint(24, 75.414872450000402, -65.918063000000004, 75.000000000000000);
		points->SetPoint(25, 74.706865000000406, -64.594684588785000, 75.000000000000000);
		points->SetPoint(26, 74.115788000000407, -63.964939000000001, 75.000000000000000);
		points->SetPoint(27, 72.753741000000403, -63.029557325300999, 75.000000000000000);
		points->SetPoint(28, 70.800617000000400, -63.188339695238000, 75.000000000000000);
		points->SetPoint(29, 68.881959894118097, -63.964939000000001, 75.000000000000000);
		points->SetPoint(30, 68.847493000000398, -63.987649744186001, 75.000000000000000);
		points->SetPoint(31, 66.894369000000395, -64.533220841808003, 75.000000000000000);
		points->SetPoint(32, 64.941245000000393, -65.429782000000003, 75.000000000000000);
		points->SetPoint(33, 62.988121000000397, -65.851479227273003, 75.000000000000000);
		points->SetPoint(34, 62.893615000000402, -65.918063000000004, 75.000000000000000);
		points->SetPoint(35, 61.034997000000402, -66.769548093596001, 75.000000000000000);
		points->SetPoint(36, 59.081873000000400, -66.774168013215998, 75.000000000000000);
		points->SetPoint(37, 57.128749000000397, -66.774168013215998, 75.000000000000000);
		points->SetPoint(38, 55.223495686274902, -65.918063000000004, 75.000000000000000);
		points->SetPoint(39, 55.175625000000402, -65.878685500000003, 75.000000000000000);
		points->SetPoint(40, 53.222501000000399, -65.423969130952003, 75.000000000000000);
		points->SetPoint(41, 51.269377000000397, -64.975031025750994, 75.000000000000000);
		points->SetPoint(42, 49.316253000000401, -64.530028247190998, 75.000000000000000);
		points->SetPoint(43, 47.363129000000399, -64.527029918604001, 75.000000000000000);
		points->SetPoint(44, 45.410005000000403, -65.836061610686997, 75.000000000000000);
		points->SetPoint(45, 45.328003610687396, -65.918063000000004, 75.000000000000000);
		points->SetPoint(46, 43.456881000000401, -67.228849427807006, 75.000000000000000);
		points->SetPoint(47, 42.661403344371202, -67.871187000000006, 75.000000000000000);
		points->SetPoint(48, 41.503757000000398, -69.535992695237994, 75.000000000000000);
		points->SetPoint(49, 41.292054748252099, -69.824310999999994, 75.000000000000000);
		points->SetPoint(50, 39.979528472973300, -71.777434999999997, 75.000000000000000);
		points->SetPoint(51, 39.550633000000403, -72.646976506849001, 75.000000000000000);
		points->SetPoint(52, 39.079790607143302, -73.730559000000000, 75.000000000000000);
		points->SetPoint(53, 39.092125231707698, -75.683683000000002, 75.000000000000000);
		points->SetPoint(54, 39.071019710059502, -77.636807000000005, 75.000000000000000);
		points->SetPoint(55, 39.550633000000403, -78.373667418181995, 75.000000000000000);
		points->SetPoint(56, 41.288152402597802, -79.589931000000007, 75.000000000000000);
		points->SetPoint(57, 41.503757000000398, -79.738159160714005, 75.000000000000000);
		points->SetPoint(58, 43.456881000000401, -81.044159195652000, 75.000000000000000);
		points->SetPoint(59, 44.152311515151901, -81.543054999999995, 75.000000000000000);

		return points;
	}

	FilterType* GetROIFilter(unsigned int id)
	{
		vtkTriangleFilter* filter = vtkTriangleFilter::New();
		vtkCellArray* cells = vtkCellArray::New();

		vtkPoints* points = GetROIPoints();

		cells->Allocate(1, 61);
		cells->InsertNextCell(61);
		cells->InsertCellPoint( 0);
		cells->InsertCellPoint( 1);
		cells->InsertCellPoint( 2);
		cells->InsertCellPoint( 3);
		cells->InsertCellPoint( 4);
		cells->InsertCellPoint( 5);
		cells->InsertCellPoint( 6);
		cells->InsertCellPoint( 7);
		cells->InsertCellPoint( 8);
		cells->InsertCellPoint( 9);
		cells->InsertCellPoint(10);
		cells->InsertCellPoint(11);
		cells->InsertCellPoint(12);
		cells->InsertCellPoint(13);
		cells->InsertCellPoint(14);
		cells->InsertCellPoint(15);
		cells->InsertCellPoint(16);
		cells->InsertCellPoint(17);
		cells->InsertCellPoint(18);
		cells->InsertCellPoint(19);
		cells->InsertCellPoint(20);
		cells->InsertCellPoint(21);
		cells->InsertCellPoint(22);
		cells->InsertCellPoint(23);
		cells->InsertCellPoint(24);
		cells->InsertCellPoint(25);
		cells->InsertCellPoint(26);
		cells->InsertCellPoint(27);
		cells->InsertCellPoint(28);
		cells->InsertCellPoint(29);
		cells->InsertCellPoint(30);
		cells->InsertCellPoint(31);
		cells->InsertCellPoint(32);
		cells->InsertCellPoint(33);
		cells->InsertCellPoint(34);
		cells->InsertCellPoint(35);
		cells->InsertCellPoint(36);
		cells->InsertCellPoint(37);
		cells->InsertCellPoint(38);
		cells->InsertCellPoint(39);
		cells->InsertCellPoint(40);
		cells->InsertCellPoint(41);
		cells->InsertCellPoint(42);
		cells->InsertCellPoint(43);
		cells->InsertCellPoint(44);
		cells->InsertCellPoint(45);
		cells->InsertCellPoint(46);
		cells->InsertCellPoint(47);
		cells->InsertCellPoint(48);
		cells->InsertCellPoint(49);
		cells->InsertCellPoint(50);
		cells->InsertCellPoint(51);
		cells->InsertCellPoint(52);
		cells->InsertCellPoint(53);
		cells->InsertCellPoint(54);
		cells->InsertCellPoint(55);
		cells->InsertCellPoint(56);
		cells->InsertCellPoint(57);
		cells->InsertCellPoint(58);
		cells->InsertCellPoint(59);
		cells->InsertCellPoint(0);

		vtkPolyData* poly = vtkPolyData::New();
		poly->Initialize();
		poly->SetGlobalWarningDisplay(1);
		poly->SetPoints(points);
		poly->SetPolys(cells);

		points->Delete();
		cells->Delete();

        filter->SetInput(poly); poly->Delete();

		vtkTransformPolyDataFilter* xformFilter = vtkTransformPolyDataFilter::New();
        xformFilter->SetInputConnection(filter->GetOutputPort()); filter->Delete();
		vtkMatrix4x4* matrix = vtkMatrix4x4::New();
		double elem[16] = {1.0, 0.0, 0.0, 0.0,  0.0, -1.0, 0.0, 0.0,  0.0, 0.0, -1.0, 75.0,  0.0, 0.0, 0.0, 1.0};
		matrix->DeepCopy(elem);
		vtkTransform* xform = vtkTransform::New();
		xform->SetMatrix(matrix);
        xformFilter->SetTransform(xform); xform->Delete();
		matrix->Delete();

		return xformFilter;
	}

	vtkPoints* GetPoints()
	{
		vtkPoints* points = vtkPoints::New();
		points->SetNumberOfPoints(8);
		points->SetPoint(0, -8.66, -5.0, 0.0);
		points->SetPoint(1,  3.0, 10.0, 0.0);
		points->SetPoint(2,  8.66, -5.0, 0.0);
		points->SetPoint(3,  0.0,  0.0, 0.0);
		points->SetPoint(4, -0.38, -0.17, 0.0);
		points->SetPoint(5, -0.40, -0.20, 0.0);
		return points;
	}

	// trianglate from a concave polygon
	// using vtkTriangleFilter or manually
	FilterType* GetFilter(unsigned int id)
	{
		if (id == 0)
			return GetTriangleFilter();
		else
			return GetAppendPolyDataFilter();
	}

	FilterType* GetTriangleFilter()
	{
		vtkTriangleFilter* filter = vtkTriangleFilter::New();
		vtkCellArray* cells = vtkCellArray::New();

		// create a concave polygon (equilateral with a cutout at the bottom)
		vtkPoints* points = GetPoints();

		cells->Allocate(1, 7);
		cells->InsertNextCell(7);
		cells->InsertCellPoint( 0);
		cells->InsertCellPoint( 1);
		cells->InsertCellPoint( 2);
		cells->InsertCellPoint( 3);
		cells->InsertCellPoint( 4);
		cells->InsertCellPoint( 5);
		cells->InsertCellPoint(0);

		vtkPolyData* poly = vtkPolyData::New();
		poly->Initialize();
		poly->SetGlobalWarningDisplay(1);
		poly->SetPoints(points);
		poly->SetPolys(cells);

		points->Delete();
		cells->Delete();

        filter->SetInput(poly); poly->Delete();

		return filter;
	}

	FilterType* GetAppendPolyDataFilter()
	{
		vtkAppendPolyData* filter = vtkAppendPolyData::New();

		vtkCellArray* cells = vtkCellArray::New();
		vtkPoints* points = GetPoints();
		
		cells->Allocate(1, 4);
		cells->InsertNextCell(4);
		cells->InsertCellPoint(5);
		cells->InsertCellPoint(1);
		cells->InsertCellPoint(4);
		cells->InsertCellPoint(5);

		vtkPolyData* poly = vtkPolyData::New();
		poly->Initialize();
		poly->SetGlobalWarningDisplay(1);
		poly->SetPoints(points);
		poly->SetPolys(cells);
        points->Delete();
        cells->Delete();

        filter->AddInput(poly); poly->Delete();
		return filter;
	}

	MapperType* GetMapper()
	{
		// map to graphics library
		MapperType* mapper = MapperType::New();
		mapper->ScalarVisibilityOff();
		vtkCoordinate* coordinate = vtkCoordinate::New();
		coordinate->SetCoordinateSystemToWorld();
		mapper->SetTransformCoordinate(coordinate);
		coordinate->Delete();
		return mapper;
	}

	PropType* GetProp()
	{
		PropType* actor = PropType::New();
		actor->GetProperty()->SetColor(0, 1.0, 0.0);
		actor->GetProperty()->SetLineWidth(1.6);
		actor->GetProperty()->SetOpacity(0.5);
		return actor;
	}
};

bool vtkActor2DTest(bool on)
{
    if (on) {
    	vtkActor2DDriver driver;
	    vtkRenderingTestPipeline<vtkActor2DDriver, vtkInteractorStyleImage> pipeline(driver);

    	pipeline.StartInteraction();
    }
	return true;
}
