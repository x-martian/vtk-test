#include "vtkAlgorithmTest.h"
#include "vtkExecutive.h"
#include "vtkDemandDrivenPipeline.h"
#include "vtkAlgorithmOutput.h"
#include "vtkInformation.h"
#include "vtkConeSource.h"
#include "vtkObjectFactory.h"
#include "vtkDebugLeaks.h"

#include "..\lemon.h"
#include "..\juice.h"

bool vtkAlgorithmTest::Run(bool on)
{
    if (!on)
        return true;

    lemon::test<> t;

    vtkAlgorithm* alg = vtkAlgorithm::New();
    t.is(alg->HasExecutive(), 0, "HasExecutive() does not create a default executive");

    // create default executive
    vtkExecutive* exec = alg->GetExecutive();
    t.isnt(alg->HasExecutive(), 0, "GetExecutive() creates a default executive");
    t.is(exec->GetAlgorithm(), alg, "this algorithm attached to the default executive");
    
    exec->Register(0);  // place a hold on this object from garbage collector
    alg->SetExecutive(0);
    t.is(alg->HasExecutive(), 0, "executive removed by SetExecutive() with a null parameter, and");
    t.is(exec->GetAlgorithm(), (void*)0, "algorithm removed from the default executive, and");
    t.is(exec->GetReferenceCount(), 1, "the executive's reference count has be diminished.");
    exec->Delete(); // release the hold

    // executive
    exec = vtkDemandDrivenPipeline::New();
    alg->SetExecutive(exec);
    exec->Delete();
    t.is(alg->GetExecutive(), exec, "Get/Set executive");
    t.is(exec->GetAlgorithm(), alg, "algorithm attached to the external executive");

    // information
    vtkInformation* info = alg->GetInformation();
    t.is(info->GetNumberOfKeys(), 0, "default information has no key");

    alg->SetInformation(0);
    t.is(alg->GetInformation(), (void*)0, "information removed by SetInformation() with a null parameter.");
    info = vtkInformation::New();
    alg->SetInformation(info);
    info->Delete();
    t.is(alg->GetInformation(), info, "Get/Set information");

    // input and output port(s)
    t.is(alg->GetNumberOfInputPorts(), 0, "number of input ports is initially zero");
    t.is(alg->GetNumberOfOutputPorts(), 0, "number of output ports is initally zero");

    alg->Delete();

    // algorithm with ports
    int inputPorts = rand()%10+1, outputPorts = rand()%10+1;
    alg = vtkAlgorithmTest::MockAlgorithm("sink", inputPorts, 0);
    vtkAlgorithm* source = vtkAlgorithmTest::MockAlgorithm("source", 0, outputPorts);

    int inputPort = rand()%inputPorts, outputPort = rand()%outputPorts; // pick a input port and a output port
    info = alg->GetInputPortInformation(inputPort);
    t.is(alg->GetNumberOfInputPorts(), inputPorts, "set/get number of input ports");
    //t.is(info->GetNumberOfKeys(), 0, "no keys for input port information");
    info = source->GetOutputPortInformation(outputPort);
    t.is(source->GetNumberOfOutputPorts(), outputPorts, "Set/Get number of output ports");
    //t.is(info->GetNumberOfKeys(), 0, "no keys for output port information");

    // set all but inputPort as optional (to prevent warning message)
    for (int i=0; i<inputPorts; ++i) {
        if (i != inputPort) {
            alg->GetInputPortInformation(i)->Set(vtkAlgorithm::INPUT_IS_OPTIONAL(), 1);
        }
    }

    vtkAlgorithmOutput* output = source->GetOutputPort(outputPort);
    alg->SetInputConnection(inputPort, output);
    t.is(alg->GetInputConnection(inputPort, 0), output, "Set/Get input connection");
    //output = source->GetOutputPort(0); // get another output port
    alg->AddInputConnection(inputPort, output);
    t.is(alg->GetInputConnection(inputPort, 1), output, "Add/Get input connection");
    t.is(alg->GetNumberOfInputConnections(inputPort), 2, "the number of input connections");
    alg->RemoveInputConnection(inputPort, output);
    t.is(alg->GetNumberOfInputConnections(inputPort), 1, "RemoveInputConnection() remove one connection, and");
    t.is(alg->GetInputConnection(inputPort, 0), output, "leave the others intact");

    vtkDataObject* obj = alg->GetInputDataObject(inputPort, 0);
    t.is(source->GetOutputDataObject(outputPort), obj, "GetInputDataObject and GetOutputDataObject");

    alg->Update();

    alg->Delete();
    source->Delete();

    //vtkDebugLeaks::PrintCurrentLeaks();

    return t.done();
}

/// a mock vtkAlgorithm
/// this class monitors virtual function calls to vtkAlgorithm
/// in a pipeline
class vtkTestAlgorithm : public vtkAlgorithm
{
public:
    // a mock executive
    class vtkExecutive : public ::vtkExecutive
    {
    public:
        static vtkExecutive* New();
        vtkTypeMacro(vtkExecutive, ::vtkExecutive);

        void InstanceName(const char* name) {
            strncpy_s(instanceName, 15, name, 15);
        }

        const char* InstanceName() const {
            return instanceName;
        }

        vtkInformation* GetOutputInforamtion(int port) {
            EN(GetOutputInformation);
            return 0;
        }

        vtkAlgorithmOutput* GetProducerPort(vtkDataObject* data) {
            EN(GetProducerPort);
            return 0;
        }

        int ProcessRequest(vtkInformation* req, vtkInformationVector** in, vtkInformationVector* out) {
            EN(ProcessRequest);
            return 1;
        }

        int ComputePipelineMTime(vtkInformation* req, vtkInformationVector** in, vtkInformationVector* out, int reqFromOutputPort, unsigned long* mtime) {
            EN(ComputePipelineMTime);
            return 1;
        }

        int Update() {
            ++UpdateCalls;
            return 1;
        }

        vtkDataObject* GetOutputData(int port) {
            EN(GetOutputData);
            return 0;
        }

        void SetOutputData(int port, vtkDataObject* obj, vtkInformation* info) {
            EN(SetOutputData@3);
        }

        void SetOutputData(int port, vtkDataObject* obj) {
            EN(SetOutputData@2);
        }

        vtkDataObject* GetInputData(int port, int conn) {
            EN(GetInputData@2);
            return 0;
        }

        vtkDataObject* GetInputData(int port, int conn, vtkInformationVector** infoVec) {
            EN(GetInputData@3);
            return 0;
        }

        int CallAlgorithm(vtkInformation* req, int dir, vtkInformationVector** in, vtkInformationVector* out) {
            EN(CallAlgorithm);
            return 0;
        }

        int UpdateCalls;

    protected:
        vtkExecutive()
            : UpdateCalls(0)
        {}

        ~vtkExecutive() {}
        
        int ForwardDownstream(vtkInformation* req) {
            EN(ForwardDownStream);
            return 1;
        }

        int ForwardUpstream(vtkInformation* req) {
            EN(ForwardUpstream);
            return ::vtkExecutive::ForwardUpstream(req);
        }

        void CopyDefaultInformation(vtkInformation* req, int dir, vtkInformationVector** in, vtkInformationVector* out) {
            EN(CopyDefaultInformation);
        }

        void ReportReferences(vtkGarbageCollector* gc) {
            EN(ReportReferences);
        }

        void SetAlgorithm(vtkAlgorithm* algo) {
            EN(SetAlgorithm);
            ::vtkExecutive::SetAlgorithm(algo);
        }

        // abstract member implementation
        void ResetPipelineInformation(int port, vtkInformation* info) {
            EN(ResetPipelineInformation);
        }

        int UpdateDataObject(void) {
            EN(UpdateDataObject);
            return 1;
        }
        
        int Update(int port) {
            ++UpdateCalls;
            return 1;
        }

    private:
        char instanceName[16];
        vtkExecutive(vtkExecutive& vtkExecutive);
        void operator=(const vtkExecutive&);
        int count;
        static lemon::test<> t;
    };

    static vtkTestAlgorithm* New();

    vtkTypeMacro(vtkTestAlgorithm, vtkAlgorithm);

    /// set the name of this instance of vtkTestAlgorithm object
    /// \param name the name to set the instance to
    void InstanceName(const char* name) {
        // copy up to 15 chars, the 16th char is null by constructor
        strncpy_s(instanceName, 15, name, 15);
    }

    /// get the name of this instance of the vtkTestAlgorithm object
    /// \return the instance name
    const char* InstanceName() const {
        return instanceName;
    }

    virtual void SetExecutive(::vtkExecutive* executive) {
        ++setExecutiveCalls;
        EN(SetExecutive);
        vtkAlgorithm::SetExecutive(executive);
    }

    virtual int ProcessRequest(vtkInformation* request, vtkInformationVector** inInfo, vtkInformationVector* outInfo) {
        ++processRequestCalls;
        EN(ProcessRequest);
        return vtkAlgorithm::ProcessRequest(request, inInfo, outInfo);
    }

    virtual int ComputePipelineMTime(vtkInformation* request, vtkInformationVector** inInfoVec, vtkInformationVector* outInfoVec, int requestFromOutputPort, unsigned long* mtime) {
        ++computePipelineMTimeCalls;
        EN(ComputePipeLineMTime);
        return vtkAlgorithm::ComputePipelineMTime(request, inInfoVec, outInfoVec, requestFromOutputPort, mtime);
    }

    virtual int ModifyRequest(vtkInformation* request, int when) {
        ++modifyRequestCalls;
        EN(ModifyRequest);
        return vtkAlgorithm::ModifyRequest(request, when);
    }

    virtual vtkInformation* GetInformation() {
        ++getInformationCalls;
        EN(GetInformation);
        return vtkAlgorithm::GetInformation();
    }

    virtual void SetInformation(vtkInformation* info) {
        ++setInformationCalls;
        EN(SetInformation);
        vtkAlgorithm::SetInformation(info);
    }

    virtual void SetAbortExecute(int arg) {
        ++setAbortExecuteCalls;
        EN(SetAbortExecute);
        vtkAlgorithm::SetAbortExecute(arg);
    }
    virtual int GetAbortExecute() {
        ++getAbortExecuteCalls;
        EN(GetAbortExecute);
        return vtkAlgorithm::GetAbortExecute();
    }

    virtual void SetProgress(double v) {
        ++setProgressCalls;
        EN(GetProgress);
        vtkAlgorithm::SetProgress(v);
    }

    virtual double GetProgress() {
        ++getProgressCalls;
        EN(GetProgress);
        return vtkAlgorithm::GetProgress();
    }

    virtual char* GetProgressText() {
        ++getProgressTextCalls;
        EN(GetProgressText);
        return vtkAlgorithm::GetProgressText();
    }

    virtual unsigned long GetErrorCode() {
        ++getErrorCodeCalls;
        EN(GetErrorCode);
        return vtkAlgorithm::GetErrorCode();
    }

    virtual void SetInputArrayToProcess(int idx, int port, int connection, int fieldAssociation, const char *name) {
        ++setInputArrayToProcessCalls;
        EN(SetInputArrayToProcess);
        vtkAlgorithm::SetInputArrayToProcess(idx, port, connection, fieldAssociation, name);
    }
    virtual void SetInputArrayToProcess(int idx, int port, int connection, int fieldAssociation, int fieldAttributeType) {
        ++setInputArrayToProcessCalls;
        EN(SetInputArrayToProcess);
        vtkAlgorithm::SetInputArrayToProcess(idx, port, connection, fieldAssociation, fieldAttributeType);
    }
    virtual void SetInputArrayToProcess(int idx, vtkInformation *info) {
        ++setInputArrayToProcessCalls;
        EN(SetInputArrayToProcess);
        vtkAlgorithm::SetInputArrayToProcess(idx, info);
    }
    virtual void SetInputArrayToProcess(int idx, int port, int connection, const char* fieldAssociation, const char* attributeTypeorName) {
        ++setInputArrayToProcessCalls;
        EN(SetInputArrayToProcess);
        vtkAlgorithm::SetInputArrayToProcess(idx, port, connection, fieldAssociation, attributeTypeorName);
    }

    virtual void SetInputConnection(int port, vtkAlgorithmOutput* input) {
        ++setInputConnectionCalls;
        EN(SetInputConnection);
        vtkAlgorithm::SetInputConnection(port, input);
    }
    virtual void SetInputConnection(vtkAlgorithmOutput* input) {
        throw std::exception("use the two parameter SetInputConnection");
    }

    virtual void AddInputConnection(int port, vtkAlgorithmOutput* input) {
        ++addInputConnectionCalls;
        EN(AddInputConnection);
        vtkAlgorithm::AddInputConnection(port, input);
    }

    virtual void AddInputConnection(vtkAlgorithmOutput* input) {
        throw std::exception("use the two parameter AddInputConnection");
    }

    virtual void RemoveInputConnection(int port, vtkAlgorithmOutput* input) {
        ++removeInputConnectionCalls;
        EN(RemoveInputConnection);
        vtkAlgorithm::RemoveInputConnection(port, input);
    }

    virtual void Update() {
        ++updateCalls;
        EN(Update);
        vtkAlgorithm::Update();
    }

    virtual void UpdateInformation() {
        ++updateInformationCalls;
        EN(UpdateInformation);
        vtkAlgorithm::UpdateInformation();
    }

    virtual void UpdateWholeExtent() {
        ++updateWholeExtentCalls;
        EN(UpdateWholeExtent);
        vtkAlgorithm::UpdateWholeExtent();
    }

    virtual double ComputePriority() {
        ++computePriorityCalls;
        EN(ComputePriority);
        return vtkAlgorithm::ComputePriority();
    }

    virtual int FillInputPortInformation(int port, vtkInformation* info) {
        ++fillInputPortInformationCalls;
        EN(FillInputPortInformation);
        info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkDataObjet");
        return 1;
    }

    virtual int FillOutputPortInformation(int port, vtkInformation* info) {
        ++fillOutputPortInformationCalls;
        EN(FillOutputPortInformation);
        info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkDataObject");
        return 1;
    }

    virtual void SetNumberOfInputPorts(int n) {
        ++setNumberOfInputPortsCalls;
        EN(SetNumberOfInputPorts);
        vtkAlgorithm::SetNumberOfInputPorts(n);
    }

    void SetNumberOfOutputPorts(int n) {
        ++setNumberOfOutputPortsCalls;
        EN(SetNumberOfOutputPorts);
        vtkAlgorithm::SetNumberOfOutputPorts(n);
    }

    virtual ::vtkExecutive* CreateDefaultExecutive() {
        ++createDefaultExecutiveCalls;
        EN(CreateDefaultExecutive);
        return vtkAlgorithm::CreateDefaultExecutive();
    }

    virtual void SetErrorCode(unsigned long code) {
        ++setErrorCodeCalls;
        EN(SetErrorCode);
        vtkAlgorithm::SetErrorCode(code);
    }

    virtual void ReportReferences(vtkGarbageCollector* v) {
        ++reportReferencesCalls;
        EN(ReportReferences);
        vtkAlgorithm::ReportReferences(v);
    }

    virtual void SetNthInputConnection(int port, int index, vtkAlgorithmOutput* input)
    {
        ++setNthInputConnectionCalls;
        EN(SetNthInputConnection);
        vtkAlgorithm::SetNthInputConnection(port, index, input);
    }

    virtual void SetNumberOfInputConnections(int port, int n) {
        ++setNumberOfInputConnectionsCalls;
        EN(SetNumberOfInputConnections);
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
    unsigned addInputConnection1Calls;
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
        , addInputConnection1Calls(0)
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

vtkAlgorithm* vtkAlgorithmTest::MockAlgorithm(const char* name, unsigned inPort, unsigned outPort)
{
    vtkTestAlgorithm* algorithm = vtkTestAlgorithm::New();
    algorithm->InstanceName(name);
    algorithm->SetNumberOfInputPorts(inPort);
    algorithm->SetNumberOfOutputPorts(outPort);
    return algorithm;
}
