#include "vtkTransformTest.h"
#include "vtkWindowTest.h"

bool vtkCommonTest(bool on)
{
	bool result = on;
	result = result && vtkTransformTest::Run(on);
	result = result && vtkWindowTest::Run(on);
	return result || !on;
}

