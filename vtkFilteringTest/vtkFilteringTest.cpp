// vtkFilteringTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vtkImageDataTest.h"

int _tmain(int argc, _TCHAR* argv[])
{
	bool result = true;
	result = result && vtkImageDataTest::Run(true);
	return 0;
}

