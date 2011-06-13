#include "vtkInformationKeyTest.h"
#include "vtkInformationIntegerKey.h"
#include "vtkInformationDoubleKey.h"
#include "vtkInformationKey.h"
#include "vtkInformation.h"
#include "vtkObject.h"

#include "../lemon.h"
#include "../juice.h"


vtkInformationKeyTest::vtkInformationKeyTest(void)
{
}

vtkInformationKeyTest::~vtkInformationKeyTest(void)
{
}

bool vtkInformationKeyTest::Run(bool on)
{
    if (!on)
        return true;

    lemon::test<> t;

    // constructor
    char* name = "mock";
    char* loc = "vtkInformationKeyTest";
    vtkInformationIntegerKey* key = new vtkInformationIntegerKey(name, loc);
    t.ok(strcmp(key->GetName(), name)==0, "Verifying GetName()");
    t.ok(strcmp(key->GetLocation(), loc)==0, "Verifying GetLocation()");

    t.isnt((void*)key, (void*)new vtkInformationIntegerKey(name, loc), "keys with the name and location may not be unique");
    t.isnt((void*)key, (void*)new vtkInformationDoubleKey(name, loc), "name/location combination can be shared by different type of keys");

    t.is(key->NewInstance(), (void*)0, "can't create NewInstance");

    // Has method
    vtkInformation* source = vtkInformation::New();
    int keyVal = rand();
    source->Set(key, keyVal);
    t.ok(key->Has(source), "Has() located the key");
    
    // ShallowCopy method
    vtkInformation* dest = vtkInformation::New();
    key->ShallowCopy(source, dest);
    
    t.is(keyVal, source->Get(key), "Source information object is not modified by ShallowCopy");
    t.is(keyVal, dest->Get(key), "Key has been copied to the destination");

    // update key's value
    keyVal>0? --keyVal : ++keyVal;  // avoid over- or underflow

    // key replacement by copying
    key->Set(source, keyVal);
    t.is(keyVal, source->Get(key), "Set() entry to a new value");
    key->ShallowCopy(source, dest);
    t.is(keyVal, dest->Get(key), "Entry updated by ShallowCopy()ing");

    // key removal by copying
    source->Remove(key);
    t.not_ok(key->Has(source), "Key Remov()ed");
    key->ShallowCopy(source, dest);
    t.not_ok(key->Has(dest), "Key removed by ShallowCopy()ing from source that has no entry");

    char* buffer = new char[sizeof(key)];
    memcpy(buffer, key, sizeof(key));
    key->Delete();
    t.ok(memcmp(buffer, key, sizeof(key))==0, "Delete does nothing");
    t.diag("TODO: don't delete a vtkInformationKey object or dangling pointer will be left in the vtkCommonInformationKeyManager");
    delete [] buffer;

    key->Register(0);
    t.is(key->GetReferenceCount(), 1, "Register does not change reference count");
    key->UnRegister(0);
    t.is(key->GetReferenceCount(), 1, "Neither does UnRegister");

    source->Delete();
    dest->Delete();

    return t.done();
}