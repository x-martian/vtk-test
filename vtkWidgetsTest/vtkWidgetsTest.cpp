// vtkWidgetsTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vtkBalloonWidgetTest.h"

bool vtkWidgetsTest(bool on)
{
    if (!on)
        return !on;

	bool ok = true;
    ok = ok && vtkBalloonWidgetTest::Run(true);

	return ok;
}

