#include "vtkAlgorithmTest.h"
#include "vtkAlgorithm.h"
#include "vtkExecutive.h"
#include "vtkDemandDrivenPipeline.h"
#include "vtkInformation.h"
#include "vtkConeSource.h"
#include "vtkObjectFactory.h"

#include "..\lemon.h"
#include "..\juice.h"

class vtkTestAlgorithm : public vtkAlgorithm
{
public:

    // a mock executive
    class vtkExecutive : public vtkDemandDrivenPipeline {
    public:
        static vtkExecutive* New();
        vtkTypeMacro(vtkExecutive, vtkDemandDrivenPipeline);

        void InstanceName(const char* name) {
            strncpy(instanceName, name, 15);
        }

        const char* InstanceName() const {
            return instanceName;
        }

        vtkInformation* GetOutputInforamtion(int port) {
            EN(GetOutputInformation)
            return vtkDemandDrivenPipeline::GetOutputInformation(port);
        }

        vtkAlgorithmOutput* GetProducerPort(vtkDataObject* data) {
            EN(GetProducerPort)
            return vtkDemandDrivenPipeline::GetProducerPort(data);
        }

        int ProcessRequest(vtkInformation* req, vtkInformationVector** in, vtkInformationVector* out) {
            EN(ProcessRequest)
            return vtkDemandDrivenPipeline::ProcessRequest(req, in, out);
        }

        int ComputePipelineMTime(vtkInformation* req, vtkInformationVector** in, vtkInformationVector* out, int reqFromOutputPort, unsigned long* mtime) {
            EN(ComputePipelineMTime)
            return vtkDemandDrivenPipeline::ComputePipelineMTime(req, in, out, reqFromOutputPort, mtime);
        }

        int Update() {
            EN(Update@0)
            return vtkDemandDrivenPipeline::Update();
        }

        vtkDataObject* GetOutputData(int port) {
            EN(GetOutputData)
            return vtkDemandDrivenPipeline::GetOutputData(port);
        }

        void SetOutputData(int port, vtkDataObject* obj, vtkInformation* info) {
            EN(SetOutputData@3)
            vtkDemandDrivenPipeline::SetOutputData(port, obj, info);
        }

        void SetOutputData(int port, vtkDataObject* obj) {
            EN(SetOutputData@2)
            vtkDemandDrivenPipeline::SetOutputData(port, obj);
        }

        vtkDataObject* GetInputData(int port, int conn) {
            EN(GetInputData@2)
            return vtkDemandDrivenPipeline::GetInputData(port, conn);
        }

        vtkDataObject* GetInputData(int port, int conn, vtkInformationVector** infoVec) {
            EN(GetInputData@3)
            return vtkDemandDrivenPipeline::GetInputData(port, conn, infoVec);
        }

        int CallAlgorithm(vtkInformation* req, int dir, vtkInformationVector** in, vtkInformationVector* out) {
            EN(CallAlgorithm)
            return vtkDemandDrivenPipeline::CallAlgorithm(req, dir, in, out);
        }

    protected:
        vtkExecutive() {}
        ~vtkExecutive() {}

        int ForwardDownstream(vtkInformation* req) {
            EN(ForwardDownStream)
            return vtkDemandDrivenPipeline::ForwardDownstream(req);
        }

        int ForwardUpstream(vtkInformation* req) {
            EN(ForwardUpstream)
            return vtkDemandDrivenPipeline::ForwardUpstream(req);
        }

        void CopyDefaultInformation(vtkInformation* req, int dir, vtkInformationVector** in, vtkInformationVector* out) {
            EN(CopyDefaultInformation)
            return vtkDemandDrivenPipeline::CopyDefaultInformation(req, dir, in, out);
        }

        void ReportReferences(vtkGarbageCollector* gc) {
            EN(ReportReferences)
            vtkDemandDrivenPipeline::ReportReferences(gc);
        }

        void SetAlgorithm(vtkAlgorithm* algo) {
            EN(SetAlgorithm)
            vtkDemandDrivenPipeline::SetAlgorithm(algo);
        }

        // abstract member implementation
        void ResetPipelineInformation(int port, vtkInformation* info) {
            EN(ResetPipelineInformation)
            vtkDemandDrivenPipeline::ResetPipelineInformation(port, info);
        }

        int UpdateDataObject(void) {
            EN(UpdateDataObject)
            return vtkDemandDrivenPipeline::UpdateDataObject();
        }

        int Update(int port) {
            EN(Update@1)
            return vtkDemandDrivenPipeline::Update(port);
        }

    private:
        char instanceName[16];
        vtkExecutive(vtkExecutive& vtkExecutive);
        void operator=(const vtkExecutive&);

        static lemon::test<> t;
    };

    static vtkTestAlgorithm* New();

    vtkTypeMacro(vtkTestAlgorithm, vtkAlgorithm);

    void InstanceName(const char* name) {
        // copy up to 15 chars, the 16th char is null by constructor
        strncpy(instanceName, name, 15);
    }

    const char* InstanceName() const {
        return instanceName;
    }

    virtual void SetExecutive(::vtkExecutive* executive) {
        ++setExecutiveCalls;
        EN(SetExecutive)
        vtkAlgorithm::SetExecutive(executive);
    }

    virtual int ProcessRequest(vtkInformation* request, vtkInformationVector** inInfo, vtkInformationVector* outInfo) {
        ++processRequestCalls;
        EN(ProcessRequest)
        return vtkAlgorithm::ProcessRequest(request, inInfo, outInfo);
    }

    virtual int ComputePipelineMTime(vtkInformation* request, vtkInformationVector** inInfoVec, vtkInformationVector* outInfoVec, int requestFromOutputPort, unsigned long* mtime) {
        ++computePipelineMTimeCalls;
        EN(ComputePipeLineMTime)
        return vtkAlgorithm::ComputePipelineMTime(request, inInfoVec, outInfoVec, requestFromOutputPort, mtime);
    }

    virtual int ModifyRequest(vtkInformation* request, int when) {
        ++modifyRequestCalls;
        EN(ModifyRequest)
        return vtkAlgorithm::ModifyRequest(request, when);
    }

    virtual vtkInformation* GetInformation() {
        ++getInformationCalls;
        EN(GetInformation)
        return vtkAlgorithm::GetInformation();
    }

    virtual void SetInformation(vtkInformation* info) {
        ++setInformationCalls;
        EN(SetInformation)
        vtkAlgorithm::SetInformation(info);
    }

    virtual void SetAbortExecute(int arg) {
        ++setAbortExecuteCalls;
        EN(SetAbortExecute)
        vtkAlgorithm::SetAbortExecute(arg);
    }
    virtual int GetAbortExecute() {
        ++getAbortExecuteCalls;
        EN(GetAbortExecute)
        return vtkAlgorithm::GetAbortExecute();
    }

    virtual void SetProgress(double v) {
        ++setProgressCalls;
        EN(GetProgress)
        vtkAlgorithm::SetProgress(v);
    }

    virtual double GetProgress() {
        ++getProgressCalls;
        EN(GetProgress)
        return vtkAlgorithm::GetProgress();
    }

    virtual char* GetProgressText() {
        ++getProgressTextCalls;
        EN(GetProgressText)
        return vtkAlgorithm::GetProgressText();
    }

    virtual unsigned long GetErrorCode() {
        ++getErrorCodeCalls;
        EN(GetErrorCode)
        return vtkAlgorithm::GetErrorCode();
    }

    virtual void SetInputArrayToProcess(int idx, int port, int connection, int fieldAssociation, const char *name) {
        ++setInputArrayToProcessCalls;
        EN(SetInputArrayToProcess)
        vtkAlgorithm::SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);
    }
    virtual void SetInputArrayToProcess(int idx, int port, int connection, int fieldAssociation, int fieldAttributeType) {
        ++setInputArrayToProcessCalls;
        EN(SetInputArrayToProcess)
        vtkAlgorithm::SetInputArrayToProcess(idx, port, connection, fieldAssociation, fieldAttributeType);
    }
    virtual void SetInputArrayToProcess(int idx, vtkInformation *info) {
        ++setInputArrayToProcessCalls;
        EN(SetInputArrayToProcess)
        vtkAlgorithm::SetInputArrayToProcess(idx, info);
    }
    virtual void SetInputArrayToProcess(int idx, int port, int connection, const char* fieldAssociation, const char* attributeTypeorName) {
        ++setInputArrayToProcessCalls;
        EN(SetInputArrayToProcess)
        vtkAlgorithm::SetInputArrayToProcess(idx, port, connection, fieldAssociation, attributeTypeorName);
    }

    virtual void SetInputConnection(int port, vtkAlgorithmOutput* input) {
        ++setInputConnectionCalls;
        EN(SetInputConnection)
        vtkAlgorithm::SetInputConnection(port, input);
    }
    virtual void SetInputConnection(vtkAlgorithmOutput* input) {
        ++setInputConnectionCalls;
        EN(SetInputConnection)
        vtkAlgorithm::SetInputConnection(input);
    }

    virtual void AddInputConnection(int port, vtkAlgorithmOutput* input) {
        ++addInputConnectionCalls;
        EN(AddInputConnection)
        vtkAlgorithm::AddInputConnection(port, input);
    }
    virtual void AddInputConnection(vtkAlgorithmOutput* input) {}

    virtual void RemoveInputConnection(int port, vtkAlgorithmOutput* input) {
        ++removeInputConnectionCalls;
        EN(RemoveInputConnection)
        vtkAlgorithm::RemoveInputConnection(port, input);
    }

    virtual void Update() {
        ++updateCalls;
        EN(Update)
        vtkAlgorithm::Update();
    }

    virtual void UpdateInformation() {
        ++updateInformationCalls;
        EN(UpdateInformation)
        vtkAlgorithm::UpdateInformation();
    }

    virtual void UpdateWholeExtent() {
        ++updateWholeExtentCalls;
        EN(UpdateWholeExtent)
        vtkAlgorithm::UpdateWholeExtent();
    }

    virtual double ComputePriority() {
        ++computePriorityCalls;
        EN(ComputePriority)
        return vtkAlgorithm::ComputePriority();
    }

    virtual int FillInputPortInformation(int port, vtkInformation* info) {
        ++fillInputPortInformationCalls;
        EN(FillInputPortInformation)
        info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkDataObjet");
        return 1;
    }

    virtual int FillOutputPortInformation(int port, vtkInformation* info) {
        ++fillOutputPortInformationCalls;
        EN(FillOutputPortInformation)
        info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkDataObject");
        return 1;
    }

    virtual void SetNumberOfInputPorts(int n) {
        ++setNumberOfInputPortsCalls;
        EN(SetNumberOfInputPorts)
        vtkAlgorithm::SetNumberOfInputPorts(n);
    }

    void SetNumberOfOutputPorts(int n) {
        ++setNumberOfOutputPortsCalls;
        EN(SetNumberOfOutputPorts)
        vtkAlgorithm::SetNumberOfOutputPorts(n);
    }

    virtual ::vtkExecutive* CreateDefaultExecutive() {
        ++createDefaultExecutiveCalls;
        EN(CreateDefaultExecutive)
        return vtkAlgorithm::CreateDefaultExecutive();
    }

    virtual void SetErrorCode(unsigned long code) {
        ++setErrorCodeCalls;
        EN(SetErrorCode)
        vtkAlgorithm::SetErrorCode(code);
    }

    virtual void ReportReferences(vtkGarbageCollector* v) {
        ++reportReferencesCalls;
        EN(ReportReferences)
        vtkAlgorithm::ReportReferences(v);
    }

    virtual void SetNthInputConnection(int port, int index, vtkAlgorithmOutput* input)
    {
        ++setNthInputConnectionCalls;
        EN(SetNthInputConnection)
        vtkAlgorithm::SetNthInputConnection(port, index, input);
    }

    virtual void SetNumberOfInputConnections(int port, int n) {
        ++setNumberOfInputConnectionsCalls;
        EN(SetNumberOfInputConnections)
        vtkAlgorithm::SetNumberOfInputConnections(port, n);
    }

    unsigned setExecutiveCalls;
    unsigned modifyRequestCalls;
    unsigned removeInputConnectionCalls;
    unsigned updateCalls;
    unsigned updateInformationCalls;
    unsigned updateWholeExtentCalls;
    unsigned computePriorityCalls;
    unsigned processRequestCalls;
    unsigned computePipelineMTimeCalls;
    unsigned getInformationCalls;
    unsigned setInformationCalls;
    unsigned setAbortExecuteCalls;
    unsigned getAbortExecuteCalls;
    unsigned abortExecuteOnCalls;
    unsigned abortExecuteOffCalls;
    unsigned setProgressCalls;
    unsigned getProgressCalls;
    unsigned getProgressTextCalls;
    unsigned getErrorCodeCalls;
    unsigned setInputArrayToProcessCalls;
    unsigned setInputConnectionCalls;
    unsigned addInputConnectionCalls;
    unsigned setReleaseDataFlagCalls;
    unsigned getReleaseDataFlagCalls;

    unsigned fillInputPortInformationCalls;
    unsigned fillOutputPortInformationCalls;
    unsigned setNumberOfInputPortsCalls;
    unsigned setNumberOfOutputPortsCalls;
    unsigned createDefaultExecutiveCalls;
    unsigned setErrorCodeCalls;
    unsigned reportReferencesCalls;
    unsigned setNumberOfInputConnectionsCalls;
    unsigned setNthInputConnectionCalls;

    static lemon::test<> t;

protected:
    vtkTestAlgorithm()
        : setExecutiveCalls(0)
        , modifyRequestCalls(0)
        , removeInputConnectionCalls(0)
        , updateCalls(0)
        , updateInformationCalls(0)
        , updateWholeExtentCalls(0)
        , computePriorityCalls(0)
        , processRequestCalls(0)
        , computePipelineMTimeCalls(0)
        , getInformationCalls(0)
        , setInformationCalls(0)
        , setAbortExecuteCalls(0)
        , getAbortExecuteCalls(0)
        , abortExecuteOnCalls(0)
        , abortExecuteOffCalls(0)
        , setProgressCalls(0)
        , getProgressCalls(0)
        , getProgressTextCalls(0)
        , getErrorCodeCalls(0)
        , setInputArrayToProcessCalls(0)
        , setInputConnectionCalls(0)
        , addInputConnectionCalls(0)
        , setReleaseDataFlagCalls(0)
        , getReleaseDataFlagCalls(0)
        , fillInputPortInformationCalls(0)
        , fillOutputPortInformationCalls(0)
        , setNumberOfInputPortsCalls(0)
        , setNumberOfOutputPortsCalls(0)
        , createDefaultExecutiveCalls(0)
        , setErrorCodeCalls(0)
        , reportReferencesCalls(0)
        , setNumberOfInputConnectionsCalls(0)
        , setNthInputConnectionCalls(0)
    {
        instanceName[15] = 0;
    }

    ~vtkTestAlgorithm() {
    }

private:
    char instanceName[16];
    vtkTestAlgorithm(const vtkTestAlgorithm&);
    void operator=(const vtkTestAlgorithm&);
};

lemon::test<> vtkTestAlgorithm::t;

vtkTestAlgorithm::vtkExecutive* vtkTestAlgorithm::vtkExecutive::New()
{
    vtkObject* ret = vtkObjectFactory::CreateInstance("vtkTestAlgorithm::vtkExecutive");
    if(ret)
    {
        return static_cast<vtkTestAlgorithm::vtkExecutive*>(ret);
    }
    return new vtkTestAlgorithm::vtkExecutive();
}

vtkTestAlgorithm* vtkTestAlgorithm::New()
{
    vtkObject* obj = vtkObjectFactory::CreateInstance("vtkTestAlgorithm");
    if (obj)
        return static_cast<vtkTestAlgorithm*>(obj);
    return new vtkTestAlgorithm;
}/*
extern vtkObject* vtkInstantiatorvtkTestAlgorithmNew();
vtkObject* vtkInstantiatorvtkTestAlgorithmNew()
{
    return vtkTestAlgorithm::New();
}*/

vtkAlgorithmTest::vtkAlgorithmTest(void)
{
}

vtkAlgorithmTest::~vtkAlgorithmTest(void)
{
}

bool vtkAlgorithmTest::Run(bool on)
{
    if (!on)
        return true;

    vtkTestAlgorithm* sink = vtkTestAlgorithm::New();
    sink->InstanceName("Cons:");
    vtkTestAlgorithm::vtkExecutive* exec = vtkTestAlgorithm::vtkExecutive::New();
    exec->InstanceName("Ex_C:");

    sink->SetExecutive(exec);
    exec->Delete();
    sink->SetDebug(0);
    sink->SetNumberOfInputPorts(1);

    vtkTestAlgorithm::t.diag("==== Creating the first source ====");
    vtkTestAlgorithm* src = vtkTestAlgorithm::New();
    src->InstanceName("Pr_A:");
    exec = vtkTestAlgorithm::vtkExecutive::New();
    exec->InstanceName("Ex_A:");
    src->SetExecutive(exec);
    exec->Delete();
    src->SetNumberOfOutputPorts(1);

    vtkTestAlgorithm::t.diag("==== Connecting the first source ====");
    vtkAlgorithmOutput* port = src->GetOutputPort();
    sink->SetInputConnection(port);
    src->Delete();

    src = vtkTestAlgorithm::New();
    src->InstanceName("Pr_B:");
    exec = vtkTestAlgorithm::vtkExecutive::New();
    exec->InstanceName("Ex_B:");
    src->SetExecutive(exec);
    exec->Delete();
    src->SetNumberOfOutputPorts(1);

    vtkTestAlgorithm::t.diag("==== Connecting the second source ====");
    port = src->GetOutputPort();
    sink->AddInputConnection(port);
    src->Delete();

    vtkTestAlgorithm::t.diag("==== Updating ====");
    sink->Update();

//    vtkTestAlgorithm::t.diag("==== Updating using vtkExecutive ====");
//    sink->Modified();
//    sink->Update();

    return true;
}