// vtkGraphicsTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vtkVoxelContoursToSurfaceFilterTest.h"
#include "vtkCutterTest.h"
#include "vtkCursor2DTest.h"

bool vtkGraphicsTest(bool on)
{
    if (on) {
        on = on && vtkCutterTest(on);
        on = on && vtkCursor2DTest(on);
        on = on && vtkVoxelContourToSurfaceFilterTest(on);
        return on;
    }
    return true;
}

