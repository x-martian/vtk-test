#include "vtkInformationKeyTest.h"
#include "vtkInformationIntegerKey.h"
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

    char* name = "mock";
    char* loc = "vtkInformationKeyTest";
    int keyVal = rand();
    vtkInformationIntegerKey* key = new vtkInformationIntegerKey(name, loc);
    t.ok(strcmp(key->GetName(), name)==0, "Verifying GetName()");
    t.ok(strcmp(key->GetLocation(), loc)==0, "Verifying GetLocation()");

    vtkInformation* source = vtkInformation::New();
    source->Set(key, keyVal);
    t.ok(key->Has(source), "Has() located the key");
    
    vtkInformation* dest = vtkInformation::New();
    key->ShallowCopy(source, dest);
    
    t.is(keyVal, source->Get(key), "Source information object is not modified by ShallowCopy");
    t.is(keyVal, dest->Get(key), "Key has been copied to the destination");

    // update key's value
    keyVal>0? --keyVal : ++keyVal;  // avoid over- or underflow

    key->Set(source, keyVal);
    t.is(keyVal, source->Get(key), "Set() entry to a new value");
    key->ShallowCopy(source, dest);
    t.is(keyVal, dest->Get(key), "Entry updated by ShallowCopy()ing");

    source->Remove(key);
    t.not_ok(key->Has(source), "Key Remov()ed");
    key->ShallowCopy(source, dest);
    t.not_ok(key->Has(dest), "Key removed by ShallowCopy()ing from source that has no entry");

    source->Delete();
    dest->Delete();
    delete key;

    return on;
}