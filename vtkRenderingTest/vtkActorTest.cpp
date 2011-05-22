#include "vtkActorTest.h"
#include "vtkActor.h"
#include "vtkPolyDataTest.h"
#include "SpherePipeline.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "Visualizer.h"
#include "vtkRenderer.h"
#include "vtkCamera.h"
#include "vtkLightCollection.h"
#include "vtkLight.h"
#include "../vtkPipelineTemplate.h"
#include "../lemon.h"
#include <assert.h>

class vtkPropCollection;

bool vtkActorTest(vtkActor*& actor, bool on)
{
	lemon::test<> t;

	actor = vtkActor::New();
	//vtkPropCollection* props = 0;
	//actor->GetActors(props);	// props == 0 will crash

	double p0[3] = {t.dbl_rnd()*20.0, t.dbl_rnd()*20.0, t.dbl_rnd()*20.0}, p1[3];
	actor->SetPosition(p0);
	actor->GetPosition(p1);
	on && t.is(p0[0], p1[0], "get/set position");

	double o1[3] = {t.dbl_rnd()*20.0, t.dbl_rnd()*20.0, t.dbl_rnd()*20.0}, o2[3];
	actor->SetOrigin(o1);
	actor->GetOrigin(o2);
	on && t.is(o1[0], o2[0], "get/set origin");

	on && t.ok(actor->GetUseBounds(), "use bounds true by default");

	if(on) actor->PrintSelf(std::cout, vtkIndent(1));

    if (on)
        actor->Delete();

	return on ? t.done() : !on;
}

bool vtkActorPositionTest(bool on)
{
    if (!on)
        return true;

	lemon::test<> t;

	SpherePipeline pipeline;
	vtkActor* a = pipeline.GetActor();
	vtkActor* b = pipeline.GetActor();

	double p[3];
	a->GetPosition(p);
	p[0] += 1.0;
	p[1] += 0.25;
	p[2] += 0.5;
	a->SetPosition(p);

	Visualizer visual;
	visual.AddActorToViewPortA(a, true);
	visual.AddActorToViewPortB(b, true);

	p[3];
	b->GetPosition(p);
	p[0] += 1.0;
	p[1] += 0.25;
	p[2] += 0.5;
	b->SetPosition(p);

	visual.StartInteraction();

	return t.done();
}

bool vtkActorOriginTest(bool on)
{
    if (!on)
        return true;

	lemon::test<> t;

	SpherePipeline pipeline;
	vtkActor* a = pipeline.GetActor();
	vtkActor* b = pipeline.GetActor();

	double p[3];
	a->GetOrigin(p);
	p[0] += 1.0;
	p[1] += 0.25;
	p[2] += 0.5;
	a->SetOrigin(p);

	Visualizer visual;
	visual.AddActorToViewPortA(a, true);
	visual.AddActorToViewPortB(b, true);

	vtkRenderer& viewA = visual.GetViewPort(0);
	viewA.PrintSelf(std::cout, vtkIndent(2));
	vtkRenderer& viewB = visual.GetViewPort(1);
	vtkLight* light = vtkLight::SafeDownCast(viewB.GetLights()->GetItemAsObject(0));
	light->PrintSelf(std::cout, vtkIndent(5));
	viewB.PrintSelf(std::cout, vtkIndent(2));

	p[3];
	b->GetOrigin(p);
	p[0] += 10.0;
	p[1] += 2.5;
	p[2] += 5.0;
	b->SetOrigin(p);

	visual.StartInteraction();

	return t.done();
}

bool vtkActorOriginTest()
{
	lemon::test<> t;
/*
	vtkActorTest actorTest;
	vtkPipelineTemplate<vtkActorTest> pipeline(actorTest);
*/
	return t.done();
}

vtkActor* vtkActorTest::MakeBoxPolyDataActor()
{
    vtkPolyData* poly = vtkPolyDataTest::MakeBox(0.0,0.0,0.0,3.0,2.0,1.5);
    vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
    mapper->SetInput(poly);
    poly->Delete();
    vtkActor* actor = vtkActor::New();
    actor->SetMapper(mapper);
    mapper->Delete();
    return actor;
}