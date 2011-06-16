#include "vtkInformationDoubleVectorKeyTest.h"
#include "vtkInformationDoubleVectorKey.h"
#include "vtkInformation.h"
#include "..\lemon.h"
#include "..\juice.h"

vtkInformationDoubleVectorKeyTest::vtkInformationDoubleVectorKeyTest(void)
{
}

vtkInformationDoubleVectorKeyTest::~vtkInformationDoubleVectorKeyTest(void)
{
}

bool vtkInformationDoubleVectorKeyTest::Run(bool on)
{
    if (!on)
        return true;

    lemon::test<> t;

    vtkInformationDoubleVectorKey* key = new vtkInformationDoubleVectorKey("dvKey", "vtkInformationDoubleVectorKeyTest");
    vtkInformation* info = vtkInformation::New();

    // Get and Set values in a vtkInformation
    double* vd = key->Get(info);
    t.is(vd, (void*)0, "Get(information) returns null for non-existing key");

    // append
    double v = t.dbl_rnd();   // don't initialize
    key->Append(info, v);
    t.is(key->Length(info), 1, "Append() to an empty info create a value array of length one");
    t.is(key->Get(info)[0], v, "Get the appended value");

    // set to a info with existing values for this key
    double buffer[7];
    buffer[0] = t.dbl_rnd();
    key->Set(info, buffer, 7);
    t.is(key->Length(info), 7, "Set replaces existing value vector");
    t.is(key->Get(info)[0], buffer[0], "Get(), the first element");
    t.is(key->Get(info)[6], buffer[6], "Get(), the last element");

    key->Append(info, v);
    t.is(key->Length(info), 8, "Append() to existing key increment the length of the vector");
    t.is(key->Get(info, 7), v, "Get()s the appended value by index");

    info->Delete();
    return t.done();
}