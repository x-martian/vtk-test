#include "vtkViewportTest.h"
#include "vtkFilteringTestPipelineTemplate.h"
#include "vtkRenderer.h"

vtkViewportTest::vtkViewportTest(void)
{
}

vtkViewportTest::~vtkViewportTest(void)
{
}

bool vtkViewportTest::Run(bool on)
{
	if (!on)
		return on;

	vtkViewport* viewport = vtkRenderer::New();
	viewport->SetAspect(1.0, 1.0);
	viewport->SetBackground(0.0, 0.0, 0.0);
	viewport->SetDisplayPoint(0.0, 0.0, 0.0);
	viewport->SetPixelAspect(1.0, 1.0);
	viewport->SetViewport(0.0, 1.0, 0.0, 1.0);
	viewport->ComputeAspect();

	vtkViewportTest test;
//	vtkFilteringTestPipelineTemplate<vtkViewportTest> pipeline(test);
	
}