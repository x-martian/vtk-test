// vtkRenderWindowTest.cpp

#include "vtkRenderWindow.h"
#include "vtkRenderingTest.h"
#include "../lemon.h"

class vtkCommand;

// test the properties that is invariant during start and render
void vtkRenderWidnowInvariantDuringStartandRender(vtkRenderWindow* win, lemon::test<>& t, bool on)
{
	on && t.not_ok(win->GetFullScreen()!=0, "Default is not full screen");
	on && t.is(win->GetAlphaBitPlanes(), 0, "No alpha bit planes");
	on && t.not_ok(win->GetBorders()==0, "Default is without borders");
	on && t.is(win->GetCurrentCursor(), 0, "Default cursor");
	on && t.is(win->GetDesiredUpdateRate(), 0.0001, "Default desired update rate");
	on && t.is(win->GetDoubleBuffer(), 1, "Default double buffer");
	on && t.ok(win->GetDPI()>0, "Default display DPI");
	on && t.is(win->GetDPIMaxValue(), 3000, "Default Max display DPI is 3000");
	on && t.is(win->GetDPIMinValue(), 1, "Default Min display DPI is 1");
	on && t.is(win->GetErase(), 1, "Default erase is on");
	on && t.is(win->GetFDFrames(), 0, "Default focal depth frames");
	on && t.is(win->GetGenericParentId(), (void*)0, "No parent");
	on && t.is(win->GetInteractor(), (void*)0, "No iterator");
	on && t.is(win->GetIsPicking(), 0, "Not is picking");
	on && t.is(win->GetLineSmoothing(), 0, "No line smoothing");
	on && t.is(win->GetMultiSamples(), 8, "Default multisamples is 8");
	on && t.is(win->GetNumberOfLayers(), 1, "default number of layers");
	on && t.is(win->GetNumberOfLayersMaxValue(), 2147483647, "max number of layers");
	on && t.is(win->GetNumberOfLayersMinValue(), 1, "min number of layers is one");
	on && t.is(win->GetOffScreenRendering(), 0, "no off screen rendering");
	on && t.ok(win->GetPainterDeviceAdapter()!=0, "has paint device adapter");
	on && t.is(win->GetPointSmoothing(), 0, "no point smoothing");
	on && t.is(win->GetPolygonSmoothing(), 0, "no polygon smoothing");
	on && t.is(win->GetPosition()[0], 0, "default initial position");
	on && t.is(win->GetReferenceCount(), 1, "initial reference count is one");
	on && t.is(win->GetSwapBuffers(), 1, "one initial swap buffers");
	on && t.ok(win->IsTypeOf("vtkObject")!=0, "is type of vtkObject");
	on && t.ok(win->IsA("vtkRenderWindow")!=0, "this is a vtkRenderWindow");
	on && t.is(win->GetAAFrames(), 0, "Default Number of anti-alias Frames: 0");
}

bool vtkRenderWindowTest(vtkRenderWindow*& win, bool on)
{
	lemon::test<> t;
	on && t.diag("vtkRenderWindow");

	vtkObject* o = vtkRenderWindow::New();
	win = vtkRenderWindow::SafeDownCast(o);
	on && t.ok(win!=0, "Safe Down Cast from vtkObject");

	on && t.ok(win->GetActualSize()[0]==0, "ActualSize() initially returns zero");

	vtkRenderWidnowInvariantDuringStartandRender(win, t, on);

	int rgbs[4];
	on && t.is(win->GetSize()[0], 0, "render window width (size) before Start()");
	on && t.is(win->GetColorBufferSizes(rgbs), 32, "Default Color buffer");
	on && t.not_ok(win->IsCurrent(), "is not current");
	on && t.not_ok(win->IsDirect()==1, "hardware acceleration not enable before Start()");
	on && t.is(win->GetGenericWindowId(), (void*)0, "No window");
	on && t.is(win->GetMapped(), 0, "Not mapped");
	win->Start();
	on && t.ok(win->GetMapped()==1, "mapped");
	on && t.ok(win->GetGenericWindowId()!=(void*)0, "window created");
	on && t.ok(win->IsCurrent(), "is current");
	on && t.ok(win->IsDirect()==1, "using hardware acceleratio");
	on && t.is(win->GetColorBufferSizes(rgbs), 32, "Default Color buffer changed after Start()");
	on && t.diag(win->ReportCapabilities());
	on && t.is(win->GetSize()[0], 300, "render window width (size) after Start()");

	vtkRenderWidnowInvariantDuringStartandRender(win, t, on);

	on && t.is(win->GetNeverRendered(), 1, "never rendered true after Start()");
	win->Render();
	on && t.is(win->GetNeverRendered(), 0, "never rendered false after Render()");
	float rgba[4];
	rgba[0] = 1.0;
	rgba[1] = 0.5;
	rgba[2] = 0.0;
	rgba[3] = 0.5;

	win->SetRGBAPixelData(0,0,0,0, rgba, 1, 1);
	float* rgbaPixelData = win->GetRGBAPixelData(0,0,0,0,1);
	on && t.is(unsigned(rgbaPixelData[0]*255.0+0.5), 128, "The final pixel value is the nearest integer of the value multiplied by the color depth");
	on && t.is(unsigned(rgbaPixelData[1]*255.0+0.5), 64, "");
	on && t.is(unsigned(rgbaPixelData[3]*255.0+0.5), 128, "The final pixel value is the nearest integer of the value multiplied by the color depth");
//	on && t.is(rgbaPixelData[3], int(0.5*255.0+0.5)/255.0, "the alpha is always one");

	vtkRenderWidnowInvariantDuringStartandRender(win, t, on);

	double size[2], screenSize[2];
	memcpy(size, win->GetSize(), 2*sizeof(double));
	memcpy(screenSize, win->GetScreenSize(), 2*sizeof(double));
	on && t.isnt(size[0], screenSize[0], "default window is not full screen");

	on && t.is(win->GetSize()[0], win->GetScreenSize()[0], "default window is not full screen");
	on && t.isnt(win->GetScreenSize()[0], win->GetSize()[0], "BAD: GetScreenSize() resizes the render window");

	if (on) win->PrintSelf(std::cout, vtkIndent());
    
	return on ? win->Delete(), t.done() : !on;
}