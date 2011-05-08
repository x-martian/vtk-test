#include "vtkPolyDataTest.h"
#include "vtkPolyData.h"
#include "vtkPoints.h"
#include "vtkCellArray.h"
#include "vtkCellData.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkAlgorithmOutput.h"
/*
#include "vtkConeSource.h"
#include "vtkPolyDataAlgorithm.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkObjectFactory.h"
class vtkPolyDataSource : public vtkPolyDataAlgorithm
{
public:
    vtkTypeMacro(vtkPolyDataSource, vtkPolyDataAlgorithm);
    static vtkPolyDataSource* New();
protected:
    vtkPolyDataSource() {};
    ~vtkPolyDataSource() {};

    virtual int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector* outputVector)
    {
        vtkInformation* outInfo = outputVector->GetInformationObject(0);
        outInfo->Set(vtkDataObject::DATA_OBJECT(), vtkPolyDataTest::MakeBox(0,0,0,3.0,2.0,1.0));
        return 1;
    }

private:
    vtkPolyDataSource(const vtkPolyDataSource&);
    void operator=(const vtkPolyDataSource&);
};
vtkStandardNewMacro(vtkPolyDataSource);
*/
vtkPolyDataTest::vtkPolyDataTest(void)
{
}

vtkPolyDataTest::~vtkPolyDataTest(void)
{
}

vtkPolyDataTest::MapperType* vtkPolyDataTest::GetMapper()
{
    return vtkPolyDataTest::MapperType::New();
}

vtkPolyDataTest::FilterType* vtkPolyDataTest::GetFilter()
{
    return vtkPolyDataTest::MakeBox(0.1,0.2,-0.05,3.3,2.2,1.1)->GetProducerPort()->GetProducer();
}

vtkPolyDataTest::PropType* vtkPolyDataTest::GetProp()
{
    return vtkPolyDataTest::PropType::New();
}

vtkPolyData* vtkPolyDataTest::MakeBox(double a, double b, double c, double l, double w, double h)
{
    // the eight corners
    vtkPoints* pts = vtkPoints::New();
    pts->SetNumberOfPoints(8);
    pts->SetPoint(0, a  , b  , c  );
    pts->SetPoint(1, a  , b  , c+h);
    pts->SetPoint(2, a  , b+w, c+h);
    pts->SetPoint(3, a  , b+w, c  );
    pts->SetPoint(4, a+l, b  , c  );
    pts->SetPoint(5, a+l, b  , c+h);
    pts->SetPoint(6, a+l, b+w, c+h);
    pts->SetPoint(7, a+l, b+w, c  );
    
    // the six faces
    vtkCellArray* cells = vtkCellArray::New();
    cells->Allocate(32, 32);
    cells->InsertNextCell(5);
    cells->InsertCellPoint(0);
    cells->InsertCellPoint(1);
    cells->InsertCellPoint(2);
    cells->InsertCellPoint(3);
    cells->InsertCellPoint(0);

    cells->InsertNextCell(5);
    cells->InsertCellPoint(0);
    cells->InsertCellPoint(4);
    cells->InsertCellPoint(5);
    cells->InsertCellPoint(1);
    cells->InsertCellPoint(0);

    cells->InsertNextCell(5);
    cells->InsertCellPoint(0);
    cells->InsertCellPoint(3);
    cells->InsertCellPoint(7);
    cells->InsertCellPoint(4);
    cells->InsertCellPoint(0);

    cells->InsertNextCell(5);
    cells->InsertCellPoint(6);
    cells->InsertCellPoint(5);
    cells->InsertCellPoint(4);
    cells->InsertCellPoint(7);
    cells->InsertCellPoint(6);

    cells->InsertNextCell(5);
    cells->InsertCellPoint(6);
    cells->InsertCellPoint(7);
    cells->InsertCellPoint(3);
    cells->InsertCellPoint(2);
    cells->InsertCellPoint(6);

    cells->InsertNextCell(5);
    cells->InsertCellPoint(6);
    cells->InsertCellPoint(2);
    cells->InsertCellPoint(1);
    cells->InsertCellPoint(5);
    cells->InsertCellPoint(6);

    vtkPolyData* poly = vtkPolyData::New();
    poly->Initialize();
    poly->SetPoints(pts);
    poly->SetPolys(cells);
    pts->Delete();
    cells->Delete();

    // add color codes to the faces
    vtkUnsignedCharArray* colors = vtkUnsignedCharArray::New();
    colors->SetNumberOfComponents(3);
    colors->SetName("Colors");
    unsigned char color[3] = {255,0,0};
    colors->InsertNextTupleValue(color);    // red
    color[1] = 255;
    colors->InsertNextTupleValue(color);    // yellow
    color[0] = 0;
    colors->InsertNextTupleValue(color);    // green
    color[2] = 255;
    colors->InsertNextTupleValue(color);    // cyan
    color[1] = 0;
    colors->InsertNextTupleValue(color);    // blue
    color[0] = 255;
    colors->InsertNextTupleValue(color);    // magenta

    poly->GetCellData()->SetScalars(colors);
    colors->Delete();

    return poly;
}

#include "vtkFilteringTestPipelineTemplate.h"

bool vtkPolyDataTest::Run(bool on)
{
    if (!on)
        return true;

    vtkPolyDataTest driver;
    vtkFilteringTestPipelineTemplate<vtkPolyDataTest> pipeline(driver);

    pipeline.StartInteraction();

    return true;
}