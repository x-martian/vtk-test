// vtkRenderingTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vtkRenderingTest.h"
#include "vtkActor2DTest.h"

vtkRenderWindow* win;
vtkRenderer* rndrr;
vtkActor* actor;

int _tmain(int argc, _TCHAR* argv[])
{
	bool ok = true;
	ok = ok && vtkActor2DTest(true);
	ok = ok && vtkActorPositionTest(true);
	ok = ok && vtkActorOriginTest(true);
	ok = ok && vtkActorTest(actor);
	ok = ok && vtkRenderWindowTest(win);
	ok = ok && vtkRendererTest(rndrr);

	return ok;
}

