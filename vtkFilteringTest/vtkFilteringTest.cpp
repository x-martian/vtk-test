// vtkFilteringTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vtkAlgorithmTest.h"
#include "vtkPolyDataTest.h"
#include "vtkImageDataTest.h"
#include "vtkViewportTest.h"

bool vtkFilteringTest(bool on)
{
    if (on) {
        on = on && vtkAlgorithmTest::Run(on);
        on = on && vtkPolyDataTest::Run(on);
        on = on && vtkViewportTest::Run(on);
        on = on && vtkImageDataTest::Run(on);
        return on;
    }
    return true;
}

