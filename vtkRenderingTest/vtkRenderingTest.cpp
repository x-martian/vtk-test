// vtkRenderingTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vtkRenderingTest.h"
#include "vtkActor2DTest.h"

vtkRenderWindow* win;
vtkRenderer* rndrr;
vtkActor* actor;

int coordinateConversion(void);

bool vtkRenderingTest(bool on)
{
    if (on) {
        //coordinateConversion();
        on = on && vtkRendererTest(true);
        on = on && vtkActor2DTest(false);
        on = on && vtkActorPositionTest(false);
        on = on && vtkActorOriginTest(false);
        //on = on && vtkActorTest(actor);
        //on = on && vtkRenderWindowTest(win);
        return on;
    }

    return true;
}

