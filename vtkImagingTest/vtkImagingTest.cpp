// vtkImagingTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vtkImageResliceTest.h"

bool vtkImagingTest(bool on)
{
    if (on) {
        on = on && vtkImageResliceTest(true);
        return on;
    }
    return true;
}

