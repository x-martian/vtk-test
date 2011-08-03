#include "vtkAlgorithmOutputTest.h"
#include "vtkAlgorithmOutput.h"
#include "vtkAlgorithm.h"
#include "..\lemon.h"

vtkAlgorithmOutputTest::vtkAlgorithmOutputTest(void)
{
}

vtkAlgorithmOutputTest::~vtkAlgorithmOutputTest(void)
{
}

bool vtkAlgorithmOutputTest::Run(bool on)
{
    if (!on)
        return true;

    lemon::test<> t;

    vtkAlgorithmOutput* algOutput = vtkAlgorithmOutput::New();

    int index = rand();
    algOutput->SetIndex(index);
    t.is(algOutput->GetIndex(), index, "Get/Set int index");
    
    vtkAlgorithm* alg = vtkAlgorithm::New();
    algOutput->SetProducer(alg);
    t.is(algOutput->GetProducer(), alg, "Get/Set vtkAlgorithm as producer");

    // clean up
    algOutput->Delete();
    alg->Delete();

    return t.done();
}