#include "stdafx.h"
#include "vtkAnnotatedCubeActorTest.h"

bool vtkHybridTest(bool on)
{
    if (!on)
        return true;

    on = on && vtkAnnotatedCubeActorTest(on);
    return on;
}

