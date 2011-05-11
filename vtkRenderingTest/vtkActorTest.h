#pragma once
class vtkActor;
class vtkPolyDataMapper;

class vtkActorTest
{
public:
	typedef vtkPolyDataMapper MapperType;

    static vtkActor* MakeBoxPolyDataActor();
};
