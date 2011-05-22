// vtkRenderingTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vtkRenderingTest.h"
#include "vtkActor2DTest.h"

vtkRenderWindow* win=0;
vtkRenderer* rndrr;
vtkActor* actor=0;

int coordinateConversion(void);

bool vtkRenderingTest(bool on)
{
    if (on) {
        //coordinateConversion();
        on = on && vtkRendererTest(on);
        on = on && vtkActor2DTest(on);
        on = on && vtkActorPositionTest(on);
        on = on && vtkActorOriginTest(on);
        on = on && vtkActorTest(actor, on);
        on = on && vtkRenderWindowTest(win, on);
        return on;
    }

    return true;
}

