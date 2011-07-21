#include "vtkInformationVectorTest.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "../lemon.h"

vtkInformationVectorTest::vtkInformationVectorTest(void)
{
}

vtkInformationVectorTest::~vtkInformationVectorTest(void)
{
}

bool vtkInformationVectorTest::Run(bool on)
{
    if (!on)
        return true;

    lemon::test<> t;

    vtkInformationVector* iv = vtkInformationVector::New();
    t.is(iv->GetNumberOfInformationObjects(), 0, "Newly create object has no object");

    // simple set/get number of information objects
    iv->SetNumberOfInformationObjects(11);
    t.is(iv->GetNumberOfInformationObjects(), 11, "Verify GetNumberOfInformationObjects Upon being SetNumberOfInformationObjects()");

    // simple set/get informationObject
    vtkInformation* info = vtkInformation::New();
    iv->SetInformationObject(4, info);
    t.is(iv->GetInformationObject(4), info, "Verify GetInformationObject and SetInformatinObject");

    // expanding and conpressing the vector
    iv->SetNumberOfInformationObjects(12);
    t.is(iv->GetNumberOfInformationObjects(), 12, "Verify expanding number of information objects");
    iv->SetNumberOfInformationObjects(7);
    t.is(iv->GetNumberOfInformationObjects(), 7, "verify truncating the information vector");
    t.is(iv->GetInformationObject(4), info, "the information object in the remaining section is intact");

    // append and removal
    iv->Append(info);
    t.is(iv->GetNumberOfInformationObjects(), 8, "appending an elements expands the vector by one");
    t.is(iv->GetInformationObject(7), info, "appended element is found at the end");
    iv->Remove(info);
    t.is(iv->GetNumberOfInformationObjects(), 6, "remove removes all instances of the given object and reduced the size of the vector");

    iv->Delete();
    info->Delete();

    return t.done();
}