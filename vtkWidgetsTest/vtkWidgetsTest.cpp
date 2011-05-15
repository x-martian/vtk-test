// vtkWidgetsTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vtkImagePlaneWidgetTest.h"
#include "vtkTextWidgetTest.h"
#include "vtkBalloonWidgetTest.h"
#include "vtkWidgetsTestPipelineTemplate.h"

bool vtkWidgetsTest(bool on)
{
    if (!on)
        return !on;

	bool ok = true;
    ok = ok && vtkWidgetsTestPipelineTemplate<vtkImagePlaneWidgetTest>::Run(true);
    ok = ok && vtkTextWidgetTest::Run(true);
    ok = ok && vtkBalloonWidgetTest::Run(true);

	return ok;
}

