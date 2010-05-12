// vtkImagingTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vtkImageResliceTest.h"

int _tmain(int argc, _TCHAR* argv[])
{
	bool rv = true;
	rv = rv && vtkImageResliceTest(true);

	return rv;
}

