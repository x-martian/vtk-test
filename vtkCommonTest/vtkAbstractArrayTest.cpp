#include "vtkAbstractArrayTest.h"
#include "vtkAbstractArray.h"
#include "vtkObjectFactory.h"
#include "../lemon.h"
#include "../juice.h"

class vtkTestArray : public vtkAbstractArray
{
public:
    static vtkTestArray* New();
    vtkTypeMacro(vtkTestArray,vtkAbstractArray);
    void PrintSelf(ostream& os, vtkIndent indent)
    {
    }

    void InstanceName(const char* name) {
        strncpy(instanceName, name, 15);
    }

    const char* InstanceName() const {
        return instanceName;
    }

    virtual int Allocate(vtkIdType sz, vtkIdType ext=1000)
    {
        EN(Allocate);
        return 0; //vtkAbstractArray::Allocate(sz, ext);
    }

    virtual void Initialize()
    {
        EN(Initialize);
        //vtkAbstractArray::Initialize();
    }

    virtual int GetDataType()
    {
        EN(GetDataType);
        return 0; //vtkAbstractArray::GetDataType();
    }

    virtual int GetDataTypeSize()
    {
        EN(GetDataTypeSize);
        return 0; //vtkAbstractArray::GetDataTypeSize();
    }

    virtual int GetElementComponentSize()
    {
        EN(GetElementComponentSize);
        return 0; //vtkAbstractArray::GetElementComponentSize();
    }

    virtual void SetNumberOfTuples(vtkIdType number)
    {
        EN(SetNumberOfTuples);
        //vtkAbstractArray::SetNumberOfTuples(number);
    }

    virtual void SetTuple(vtkIdType i, vtkIdType k, vtkAbstractArray* source)
    {
        EN(SetTuple);
        //vtkAbstractArray::SetTuple(i, k, source);
    }

    virtual void InsertTuple(vtkIdType i, vtkIdType k, vtkAbstractArray* source)
    {
        EN(InsertTuple);
        //vtkAbstractArray::InsertTuple(i, k, source);
    }

    virtual vtkIdType InsertNextTuple(vtkIdType k, vtkAbstractArray* source)
    {
        EN(InsertNextTuple);
        return 0; //vtkAbstractArray::InsertNextTuple(k, source);
    }

    virtual void GetTuples(vtkIdList *ptIds, vtkAbstractArray* output)
    {
        EN(GetTuples0);
        vtkAbstractArray::GetTuples(ptIds, output);
    }

    virtual void GetTuples(vtkIdType p1, vtkIdType p2, vtkAbstractArray *output)
    {
        EN(GetTuples1);
        vtkAbstractArray::GetTuples(p1, p2, output);
    }

    virtual void *GetVoidPointer(vtkIdType id)
    {
        EN(GetVoidPointer);
        return 0; //vtkAbstractArray::GetVoidPointer(id);
    }

    virtual void DeepCopy(vtkAbstractArray* da)
    {
        EN(DeepCopy);
        vtkAbstractArray::DeepCopy(da);
    }

    virtual void InterpolateTuple(vtkIdType i, vtkIdList *ptIndices, vtkAbstractArray* source,  double* weights)
    {
        EN(InterpolateTuple0);
        //vtkAbstractArray::InterpolateTuple(i, ptIndices, source, weights);
    }

    virtual void InterpolateTuple(vtkIdType i, vtkIdType id1, vtkAbstractArray* source1, vtkIdType id2, vtkAbstractArray* source2, double t)
    {
        EN(InterpolateTuple1);
        //vtkAbstractArray::InterpolateTuple(i, id1, source1, id2, source2, t);
    }

    virtual void Squeeze()
    {
        EN(Squeeze);
        //vtkAbstractArray::Squeeze();
    }

    virtual int Resize(vtkIdType numTuples)
    {
        EN(Resize);
        return 0; //vtkAbstractArray::Resize(numTuples);
    }

    virtual void SetVoidArray(void *vtkNotUsed(array), vtkIdType vtkNotUsed(size), int vtkNotUsed(save))
    {
        EN(SetVoidArray);
        //vtkAbstractArray::SetVoidArray(array, size, save);
    }

    virtual void ExportToVoidPointer(void *vtkNotUsed(out_ptr))
    {
        EN(ExportToVoidPointer);
    }

    virtual unsigned long GetActualMemorySize()
    {
        EN(GetActualMemorySize);
        return 0; //vtkAbstractArray::GetActualMemorySize();
    }

    virtual const char *GetDataTypeAsString( void )
    {
        EN(GetDataTypeAsString);
        return vtkAbstractArray::GetDataTypeAsString();
    }

    virtual int IsNumeric()
    {
        EN(IsNumeric);
        return true; //vtkAbstractArray::IsNumeric();
    }

    virtual vtkArrayIterator* NewIterator()
    {
        EN(NewIterator);
        return 0; //vtkAbstractArray::NewIterator();
    }

    virtual vtkIdType GetDataSize()
    {
        EN(GetDataSize);
        return vtkAbstractArray::GetDataSize();
    }

    virtual vtkIdType LookupValue(vtkVariant value)
    {
        EN(LokupValue);
        return 0; //vtkAbstractArray::LookupValue(value);
    }

    virtual void LookupValue(vtkVariant value, vtkIdList* ids)
    {
        EN(LookupValue);
        //vtkAbstractArray::LookupValue(value, ids);
    }

    virtual vtkVariant GetVariantValue(vtkIdType idx)
    {
        EN(GetVariantValue);
        return vtkAbstractArray::GetVariantValue(idx);
    }

    virtual void InsertVariantValue(vtkIdType idx, vtkVariant value)
    {
        EN(InsertVariantValue);
        //vtkAbstractArray::InsertVariantValue(idx, value);
    }

    virtual void DataChanged()
    {
        EN(DataChanged);
        //vtkAbstractArray::DataChanged();
    }

    virtual void ClearLookup()
    {
        EN(ClearLookup);
        //vtkAbstractArray::ClearLookup();
    }

    virtual int CopyInformation(vtkInformation *infoFrom, int deep=1)
    {
        EN(CopyInformation);
        return vtkAbstractArray::CopyInformation(infoFrom, deep);
    }

    static lemon::test<> t;
private:

    vtkTestArray()
    {
    }

    char instanceName[16];

    unsigned allocateCalls;
    unsigned initializeCalls;
    unsigned getDataTypeCalls;
    unsigned getDataTypeSizeCalls;
    unsigned getElementComponentSizeCalls;
    unsigned setNumberOfTuplesCalls;
    unsigned setTupleCalls;
    unsigned insertTupleCalls;
    unsigned insertNextTupleCalls;
    unsigned setTuples0Calls;
    unsigned setTuples1Calls;
    unsigned getVoidPointerCalls;
    unsigned deepCopyCalls;
    unsigned interpolateTuple0Calls;
    unsigned interpolateTuple1Calls;
    unsigned squeezeCalls;
    unsigned resizeCalls;
    unsigned setVoidArrayCalls;
    unsigned exportToVoidPointerCalls;
    unsigned getActualMemorySizeCalls;
    unsigned getDataTypeAsStringCalls;
    unsigned isNumericCalls;
    unsigned newIteratorCalls;
    unsigned getDataSizeCalls;
    unsigned lookupValue0Calls;
    unsigned lookupValue1Calls;
    unsigned setVariantValueCalls;
    unsigned insertVariantValueCalls;
    unsigned dataChangedCalls;
    unsigned clearLookupCalls;
    unsigned copyInformationCalls;

    vtkTestArray(const vtkTestArray&);
    void operator=(const vtkTestArray& rhs);
};

vtkStandardNewMacro(vtkTestArray);

lemon::test<> vtkTestArray::t;

vtkAbstractArrayTest::vtkAbstractArrayTest(void)
{
}

vtkAbstractArrayTest::~vtkAbstractArrayTest(void)
{
}

bool vtkAbstractArrayTest::Run(bool on)
{
    if (!on)
        return true;

    lemon::test<>& t = vtkTestArray::t;

    // test GetDataTypeSize
    t.diag("vtk data sizes");
    t.is(vtkAbstractArray::GetDataTypeSize(VTK_CHAR), 1, "char: 1");
    t.is(vtkAbstractArray::GetDataTypeSize(VTK_SHORT), 2, "short: 2");
    t.is(vtkAbstractArray::GetDataTypeSize(VTK_INT), 4, "int: 4");
    t.is(vtkAbstractArray::GetDataTypeSize(VTK_LONG), 4, "long: 8");
    t.is(vtkAbstractArray::GetDataTypeSize(VTK_FLOAT), 4, "float: 4");
    t.is(vtkAbstractArray::GetDataTypeSize(VTK_DOUBLE), 8, "double: 8");

    vtkAbstractArray* a = vtkTestArray::CreateArray(VTK_CHAR);

    // get set name
    char name[16] = "test array";
    a->SetName(name);
    t.ok(strcmp(a->GetName(), name)==0, "Set and Get array name");

    t.is(a->GetDataSize(), 0, "GetDataSize() of array create by CreateArray is zero");
    a->SetNumberOfComponents(0);
    t.is(a->GetNumberOfComponents(), 1, "The minumum number of components is one");
    t.is(a->GetNumberOfTuples(), 0, "array initialized with no tuples");
    t.ok(strcmp(a->GetDataTypeAsString(), "char")==0, "GetDataTypeAsTring()");
    t.is(a->GetDataTypeSize(), 1, "VTK_CHAR array size is one");
    t.is(a->HasInformation(), false, "HasInformation() is false");
    t.ok(a->GetInformation()!=0, "GetInformation() creates one");

    a->Reset();
    t.is(a->GetMaxId(), -1, "Reset() max id to -1");
    a->GetSize();
    
    a->Delete();

    a = vtkTestArray::New();
    ((vtkTestArray&)(*a)).InstanceName("vtkTestArray");
    
    a->IsNumeric();
    a->Delete();

    return t.done();
}