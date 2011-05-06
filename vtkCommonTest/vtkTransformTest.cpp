#include "..\lemon.h"
#include "vtkTransformTest.h"
#include "vtkTransform.h"
#include "vtkMath.h"

const double vtkTransformTest::rx = 31.0;
const double vtkTransformTest::ry = 29.0;
const double vtkTransformTest::rz = 30.0;
const double vtkTransformTest::translate[3] = {0.9, 1.0, 1.1};

const double vtkTransformTest::pt[3] = {1.0, 1.0, 1.0};

vtkTransformTest::vtkTransformTest(void)
{
}

vtkTransformTest::~vtkTransformTest(void)
{
}

bool vtkTransformTest::Run(bool on)
{
    if (!on)
        return true;

    lemon::test<> t;
    double* pp;

    vtkTransform* xform = vtkTransform::New();
    xform->Translate(translate);
    pp = xform->TransformDoublePoint(pt);
    t.diag("Translation of a point moves the point in the direction of the translation:");
    t.is(pt[0]+translate[0], pp[0], "verifying x-component of translating a point");
    t.is(pt[1]+translate[1], pp[1], "verifying y-component of translating a point");
    t.is(pt[2]+translate[2], pp[2], "verifying z-component of translating a point");

    pp = xform->TransformDoubleNormal(pt);
    t.diag("Translation of normal has no effect");
    t.is(xform->TransformDoubleNormal(1.0, 0.0, 0.0)[0], 1.0, "verifying x-component of translated norm");
    t.is(xform->TransformDoubleNormal(0.0, 1.0, 0.0)[1], 1.0, "verifying y-component of translated norm");
    t.is(xform->TransformDoubleNormal(0.0, 0.0, 1.0)[2], 1.0, "verifying z-component of translated norm");

    xform->Identity();
    xform->RotateX(rx);
    pp = xform->TransformDoublePoint(pt);
    t.diag("Rotation about x-axis (in degrees) of a point w.r.t the orgin");
    double deg = vtkMath::RadiansFromDegrees(rx);
    t.is(pt[0], pp[0], "verifying invariance of the x-component");
    t.is(pt[1]*cos(deg)-pt[2]*sin(deg), pp[1], "verifying y-component of the rotation");
    t.is(pt[1]*sin(deg)+pt[2]*cos(deg), pp[2], "verifying z-component of the rotation");

    t.diag("Rotation of a normal causes the direction to be rotated");
    t.is(xform->TransformDoubleNormal(1.0, 0.0, 0.0)[0], 1.0, "verifying the x-component of a rotated normal");
    t.is(xform->TransformDoubleNormal(0.0, 1.0, 0.0)[1], cos(deg), "verifying the y-component of a unit vector in the y-direction after rotation");
    t.is(xform->TransformDoubleNormal(0.0, 0.0, 1.0)[1], -sin(deg), "verifying the y-component of a unit vector in the z-direction after rotation");

    t.diag("Combination of transforms using pre-multiply (default)");
    xform->Identity();
    xform->RotateX(10);
    xform->RotateY(20);
    xform->RotateZ(30);
    xform->Translate(translate);
    pp = xform->TransformDoublePoint(-translate[0], -translate[1], -translate[2]);
    t.is(pp[0], 0.0, "verifying the x-component");
    t.is(pp[1], 0.0, "verifying the y-component");
    t.is(pp[2], 0.0, "verifying the z-component");

    t.diag("Combination of transforms using post-multiply");
    t.diag("Method: combine several rotations with a translation with PostMultiply");
    t.diag("and use the result to translate a point at origin.");
    t.diag("Result: the rotations has no effect to the orgin.");
    xform->PostMultiply();
    xform->Identity();
    xform->RotateX(10);
    xform->RotateY(20);
    xform->RotateZ(30);
    xform->Translate(translate);
    pp = xform->TransformDoublePoint(0.0, 0.0, 0.0);
    t.is(pp[0], translate[0], "verifying the x-component");
    t.is(pp[1], translate[1], "verifying the y-component");
    t.is(pp[2], translate[2], "verifying the z-component");

    return t.done();
}