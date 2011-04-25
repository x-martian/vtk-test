// vtkImagingTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vtkImageResliceTest.h"

bool vtkImagingTest(bool on)
{
	bool rv = true;
	rv = rv && vtkImageResliceTest(true);

	return rv;
}

