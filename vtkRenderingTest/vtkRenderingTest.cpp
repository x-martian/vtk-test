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
	bool result = true;
	result = result && vtkActor2DTest(true);

	/*
		   vtkActorPositionTest(true)
	    && vtkActorOriginTest(true)
		&& vtkActorTest(actor)
		&& vtkRenderWindowTest(win)
		&& vtkRendererTest(rndrr)
		;
		*/
	return result;
}

