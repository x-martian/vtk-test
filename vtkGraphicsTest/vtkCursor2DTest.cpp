#include "vtkCursor2DTest.h"

#include "vtkCursor2D.h"
#include "vtkPolyDataMapper2D.h"
#include "vtkActor2D.h"
#include "vtkProperty2D.h"
#include "vtkGraphicsTestPipelineTemplate.h"
#include "vtkInteractorStyleImage.h"
#include "../lemon.h"

vtkCursor2DDriver::vtkCursor2DDriver()
{
}

vtkCursor2DDriver::~vtkCursor2DDriver(void)
{
}

vtkCursor2DDriver::FilterType* vtkCursor2DDriver::GetFilter()
{
	vtkCursor2D* cursor = vtkCursor2D::New();

	cursor->SetModelBounds(15,45,15,45,0,0);
	cursor->SetFocalPoint(30,30,0);
	cursor->AllOff();
	cursor->AxesOn();
	cursor->OutlineOn();
	cursor->PointOn();

	return cursor;
}

vtkCursor2DDriver::PropType* vtkCursor2DDriver::GetProp()
{
	PropType* actor = PropType::New();
	actor->GetProperty()->SetColor(0,0,1); // sphere color blue

	return actor;
}

bool vtkCursor2DTest(bool on)
{
	lemon::test<> t;

	vtkCursor2DDriver driver;
	vtkGraphicsTestPipelineTemplate<vtkCursor2DDriver> pipeline(driver);
	//vtkGraphicsTestPipelineTemplate<vtkCursor2DDriver, vtkInteractorStyleImage> pipeline(driver);

	COLORREF color = pipeline.GetDisplayColor(30,20);
	t.is(color, RGB(0,0,255), "verify left color");

	pipeline.StartInteraction();

	return t.done();
}