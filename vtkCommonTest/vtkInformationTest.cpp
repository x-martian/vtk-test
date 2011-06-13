#include "vtkInformationTest.h"
#include "vtkInformation.h"
#include "vtkInformationRequestKey.h"
#include "vtkInformationIntegerKey.h"
#include "..\lemon.h"
#include "..\juice.h"

vtkInformationTest::vtkInformationTest(void)
{
}

vtkInformationTest::~vtkInformationTest(void)
{
}

bool vtkInformationTest::Run(bool on)
{
    if (!on)
        return true;

    lemon::test<> t;

    vtkInformation* info = vtkInformation::New();
    vtkInformationRequestKey* request = info->GetRequest();
    t.is(request, (void*)0, "Initially, there's no request");

    request = new vtkInformationRequestKey("setkey", "vtkInformationTest");
    unsigned long mTime = info->GetMTime();
    info->SetRequest(request);
    t.is(info->Has(request), 1, "Has (request) method");
    t.is(info->GetRequest(), request, "get and set request");
    t.is(info->GetMTime(), mTime, "SetRequest does not reset Modified");

    info->Remove(request);
    t.is(info->Has(request), 0, "Remove(ing) request");

    info->Set(request);
    t.is(info->Has(request), 1, "Set request by Set method");
    t.is(info->GetRequest(), request, "");
    t.isnt(info->GetMTime(), mTime, "TODO: Set(request) resets modified");

    int intVal = rand();
    vtkInformationIntegerKey* intKey = new vtkInformationIntegerKey("intKey", "vtkInformationTest");

    t.is(info->Get(intKey), 0, "default int value for non-existing key is null");
    info->Set(intKey, intVal);
    t.is(info->Get(intKey), intVal, "Get(vtkInformationIntegerKey)");
    t.is(info->GetKey(intKey), intKey, "GetKey()");

    info->Set(new vtkInformationIntegerKey("anotherIntKey", "vtkInformationTest"), rand());
    t.is(info->GetKey(intKey), intKey, "Set() does not replace existing key");
    t.is(info->Get(intKey), intVal, "Attempt to Set() to a different key does not replace key's value either");

    info->Set(intKey, rand());
    t.isnt(info->Get(intKey), intVal, "Replacing the value by Set()ting with the existing key");

    info->Delete();
    return t.done();
}