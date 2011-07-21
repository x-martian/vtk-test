#include "vtkDemandDrivenPipelineTest.h"
#include "vtkDemandDrivenPipeline.h"
#include "vtkAlgorithmTest.h"
#include "vtkObjectFactory.h"
#include "../lemon.h"
#include "../juice.h"
#include "../lime.h"

class vtkTestDemandDrivenPipeline : public vtkDemandDrivenPipeline
{
public:
    static lemon::test<> t;

    static vtkTestDemandDrivenPipeline* New();
    vtkTypeMacro(vtkExecutive, vtkDemandDrivenPipeline);

    void InstanceName(const char* name) {
        strncpy(instanceName, name, 15);
    }

    const char* InstanceName() const {
        return instanceName;
    }

    vtkInformation* GetOutputInforamtion(int port) {
        EN(GetOutputInformation);
        return vtkDemandDrivenPipeline::GetOutputInformation(port);
    }

    vtkAlgorithmOutput* GetProducerPort(vtkDataObject* data) {
        EN(GetProducerPort);
        return vtkDemandDrivenPipeline::GetProducerPort(data);
    }

    int ProcessRequest(vtkInformation* req, vtkInformationVector** in, vtkInformationVector* out) {
        EN(ProcessRequest);
        return vtkDemandDrivenPipeline::ProcessRequest(req, in, out);
    }

    int ComputePipelineMTime(vtkInformation* req, vtkInformationVector** in, vtkInformationVector* out, int reqFromOutputPort, unsigned long* mtime) {
        EN(ComputePipelineMTime);
        return vtkDemandDrivenPipeline::ComputePipelineMTime(req, in, out, reqFromOutputPort, mtime);
    }

    int Update() {
        EN(Update@0);
        return vtkDemandDrivenPipeline::Update();
    }

    vtkDataObject* GetOutputData(int port) {
        EN(GetOutputData);
        return vtkDemandDrivenPipeline::GetOutputData(port);
    }

    void SetOutputData(int port, vtkDataObject* obj, vtkInformation* info) {
        EN(SetOutputData@3);
        vtkDemandDrivenPipeline::SetOutputData(port, obj, info);
    }

    void SetOutputData(int port, vtkDataObject* obj) {
        EN(SetOutputData@2);
        vtkDemandDrivenPipeline::SetOutputData(port, obj);
    }

    vtkDataObject* GetInputData(int port, int conn) {
        EN(GetInputData@2);
        return vtkDemandDrivenPipeline::GetInputData(port, conn);
    }

    vtkDataObject* GetInputData(int port, int conn, vtkInformationVector** infoVec) {
        EN(GetInputData@3);
        return vtkDemandDrivenPipeline::GetInputData(port, conn, infoVec);
    }

    int CallAlgorithm(vtkInformation* req, int dir, vtkInformationVector** in, vtkInformationVector* out) {
        EN(CallAlgorithm);
        return vtkDemandDrivenPipeline::CallAlgorithm(req, dir, in, out);
    }

protected:
    vtkTestDemandDrivenPipeline() {}
    ~vtkTestDemandDrivenPipeline() {}

    int ForwardDownstream(vtkInformation* req) {
        EN(ForwardDownStream);
        return vtkDemandDrivenPipeline::ForwardDownstream(req);
    }

    int ForwardUpstream(vtkInformation* req) {
        EN(ForwardUpstream);
        return vtkDemandDrivenPipeline::ForwardUpstream(req);
    }

    void CopyDefaultInformation(vtkInformation* req, int dir, vtkInformationVector** in, vtkInformationVector* out) {
        EN(CopyDefaultInformation);
        return vtkDemandDrivenPipeline::CopyDefaultInformation(req, dir, in, out);
    }

    void ReportReferences(vtkGarbageCollector* gc) {
        EN(ReportReferences);
        vtkDemandDrivenPipeline::ReportReferences(gc);
    }

    void SetAlgorithm(vtkAlgorithm* algo) {
        EN(SetAlgorithm);
        vtkDemandDrivenPipeline::SetAlgorithm(algo);
    }

    // abstract member implementation
    void ResetPipelineInformation(int port, vtkInformation* info) {
        EN(ResetPipelineInformation);
        vtkDemandDrivenPipeline::ResetPipelineInformation(port, info);
    }

    int UpdateDataObject(void) {
        EN(UpdateDataObject);
        return vtkDemandDrivenPipeline::UpdateDataObject();
    }

    int Update(int port) {
        EN(Update@1);
        return vtkDemandDrivenPipeline::Update(port);
    }

private:
    char instanceName[16];
    vtkTestDemandDrivenPipeline(vtkTestDemandDrivenPipeline& vtkExecutive);
    void operator=(const vtkTestDemandDrivenPipeline&);
};

vtkStandardNewMacro(vtkTestDemandDrivenPipeline);

lemon::test<> vtkTestDemandDrivenPipeline::t;

vtkDemandDrivenPipelineTest::vtkDemandDrivenPipelineTest(void)
{
}

vtkDemandDrivenPipelineTest::~vtkDemandDrivenPipelineTest(void)
{
}

bool vtkDemandDrivenPipelineTest::Run(bool on)
{
    lemon::test<> t;

    vtkTestDemandDrivenPipeline::t.diag("==== Creating the first consumer ====");
    vtkTestDemandDrivenPipeline* exec = vtkTestDemandDrivenPipeline::New();
    exec->InstanceName("Ex_C:");

    vtkAlgorithm* sink = vtkAlgorithmTest::MockAlgorithm("Cons:", 1, 0);
    sink->SetDebug(0);
    sink->SetExecutive(exec);
    exec->Delete();

    vtkTestDemandDrivenPipeline::t.diag("==== Creating the first source ====");
    exec = vtkTestDemandDrivenPipeline::New();
    exec->InstanceName("Ex_A:");
    vtkAlgorithm* src = vtkAlgorithmTest::MockAlgorithm("Pr_A:", 0, 1);
    src->SetExecutive(exec);
    exec->Delete();

    vtkTestDemandDrivenPipeline::t.diag("==== Connecting the first source ====");
    vtkAlgorithmOutput* port = src->GetOutputPort();
    sink->SetInputConnection(0, port);
    src->Delete();

    vtkTestDemandDrivenPipeline::t.diag("==== Creating the second source ====");
    exec = vtkTestDemandDrivenPipeline::New();
    exec->InstanceName("Ex_B:");
    src = vtkAlgorithmTest::MockAlgorithm("Pr_B:", 0, 1);
    src->SetExecutive(exec);
    exec->Delete();

    vtkTestDemandDrivenPipeline::t.diag("==== Connecting the second source ====");
    port = src->GetOutputPort();
    sink->AddInputConnection(0, port);
    src->Delete();

    vtkTestDemandDrivenPipeline::t.diag("==== Updating ====");
    sink->Update();

    return t.done();
}