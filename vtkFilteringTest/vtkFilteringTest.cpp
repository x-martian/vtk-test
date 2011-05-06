// vtkFilteringTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vtkImageDataTest.h"
#include "vtkViewportTest.h"

bool vtkFilteringTest(bool on)
{
	bool result = on;
	result = result && vtkViewportTest::Run(on);
	result = result && vtkImageDataTest::Run(true);
	return result || !on;
}

