// vtkGraphicsTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vtkVoxelContoursToSurfaceFilterTest.h"
#include "vtkCutterTest.h"
#include "vtkCursor2DTest.h"

bool vtkGraphicsTest(bool on)
{
	bool result = true;
	result = result && vtkCutterTest(true);
	result = result && vtkCursor2DTest(true);
	result = result && vtkVoxelContourToSurfaceFilterTest(true);
	return result;
}

