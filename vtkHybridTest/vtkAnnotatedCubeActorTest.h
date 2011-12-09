#pragma once

class vtkAnnotatedCubeActor;
class vtkAnnotatedCubeActorDriver
{
public:
    vtkAnnotatedCubeActorDriver(void);
    ~vtkAnnotatedCubeActorDriver(void);

	typedef vtkAnnotatedCubeActor PropType;

	PropType* GetProp();
};

bool vtkAnnotatedCubeActorTest(bool on);
