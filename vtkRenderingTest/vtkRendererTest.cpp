#include "vtkRenderer.h"
#include "vtkCamera.h"	// should not need it here
#include "vtkActorCollection.h"
#include "vtkActor2DCollection.h"
#include "vtkRenderingTest.h"
#include "../lemon.h"

bool vtkRendererTest(vtkRenderer*& out, bool on)
{
	lemon::test<> t;

	out = vtkRenderer::New();

	on && t.is(out->GetActors()->GetNumberOfItems(), 0, "initially no actor");
	on && t.is(out->GetActors2D()->GetNumberOfItems(), 0, "initially no 2D actor");

	on && t.is(out->GetCenter()[0], 0, "center");

	// two ways of calling get aspect
	double aspect[2];
	out->GetAspect(aspect);
	on && t.is(out->GetAspect()[1], aspect[1], "two ways of calling GetAspect");

	vtkCamera* camera = out->GetActiveCamera();
	on && t.ok(camera!=0, "A new camera may be created, but not reset");

	double fp[3];
	camera->GetFocalPoint(fp);

	double cr[2];
	camera->GetClippingRange(cr);
	on && t.is(camera->GetThickness(), cr[1]-cr[0], "thickness is of the clipping range");

	vtkActor* actor;
	vtkActorTest(actor, false);
	out->AddActor(actor);

	out->ResetCamera();
	double bounds[6];
	actor->GetBounds(bounds);

	if(on) camera->PrintSelf(std::cout, vtkIndent(3));

	on && t.is(out->GetActors()->GetNumberOfItems(), 1, "added one actor");

	on && t.is(out->GetRenderWindow(), (void*)0, "no render window");

	if(on) out->PrintSelf(std::cout, vtkIndent(1));

	return on ? t.done() : !on;
}