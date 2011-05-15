#pragma once

class vtkRenderWindow;
class vtkRenderer;
class vtkActor;

bool vtkRenderWindowTest(vtkRenderWindow*& out, bool on=true);
bool vtkRendererTest(bool on=true);
bool vtkActorTest(vtkActor*& out, bool on=true);
bool vtkActorPositionTest(bool on);
bool vtkActorOriginTest(bool on);
