#include "vtkInformationKeyTest.h"
#include "vtkInformationDoubleVectorKeyTest.h"
#include "vtkInformationTest.h"
#include "vtkTransformTest.h"
#include "vtkWindowTest.h"

bool vtkCommonTest(bool on)
{
    if (on) {
        on = on && vtkInformationKeyTest::Run(on);
        on = on && vtkInformationDoubleVectorKeyTest::Run(on);
        on = on && vtkInformationTest::Run(on);
	    on = on && vtkTransformTest::Run(on);
	    on = on && vtkWindowTest::Run(on);
	    return on;
    }
    return true;
}

