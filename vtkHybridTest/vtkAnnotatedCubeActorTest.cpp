#include "stdafx.h"
#include "vtkAnnotatedCubeActorTest.h"
#include "vtkAnnotatedCubeActor.h"
#include "vtkMatrix4x4.h"
#include "vtkTransform.h"
#include "../lemon.h"

vtkAnnotatedCubeActorDriver::vtkAnnotatedCubeActorDriver(void)
{
}

vtkAnnotatedCubeActorDriver::~vtkAnnotatedCubeActorDriver(void)
{
}

vtkAnnotatedCubeActorDriver::PropType* vtkAnnotatedCubeActorDriver::GetProp()
{
    vtkAnnotatedCubeActor* actor = vtkAnnotatedCubeActor::New();
    vtkMatrix4x4* matrix = vtkMatrix4x4::New();
    static double elem[16] = {
         0, 0,-1, 0,
        -1, 0, 0, 0,
         0, 1, 0, 0,
         0, 0, 0, 1 };
    matrix->DeepCopy(elem);
    actor->SetUserMatrix(matrix);
    vtkTransform* xform = vtkTransform::New();
    xform->SetMatrix(matrix);
    matrix->Delete();
    actor->SetUserTransform(xform);
    xform->Delete();
//    actor->RotateX(90);
    return actor;
}

#include "vtkHybridTestPipelineTemplate.h"
bool vtkAnnotatedCubeActorTest(bool on)
{
    lemon::test<> t;

    vtkHybridTestPipelineTemplate<vtkAnnotatedCubeActorDriver>::Run(on);

    return t.done();
}