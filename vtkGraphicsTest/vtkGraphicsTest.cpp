// vtkGraphicsTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vtkVoxelContoursToSurfaceFilterTest.h"
#include "vtkCutterTest.h"
#include "vtkCursor2DTest.h"

int _tmain(int argc, _TCHAR* argv[])
{
	bool result = true;
	result = result && vtkCutterTest(true);
	result = result && vtkCursor2DTest(true);
	result = result && vtkVoxelContourToSurfaceFilterTest(true);
	return result;
}

