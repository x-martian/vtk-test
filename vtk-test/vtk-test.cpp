// vtk-test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

bool vtkRenderingTest(bool on);
bool vtkGraphicsTest(bool on);
bool vtkFilteringTest(bool on);
bool vtkImagingTest(bool on);
bool vtkCommonTest(bool on);

int _tmain(int argc, _TCHAR* argv[])
{
	int count = 5;
	bool result = true;
    result = result && vtkCommonTest(true) && --count;
	result = result && vtkFilteringTest(true) && --count;
	result = result && vtkRenderingTest(true) && --count;
	result = result && vtkGraphicsTest(true) && --count;
	result = result && vtkImagingTest(true) && --count;
	return count;
}

