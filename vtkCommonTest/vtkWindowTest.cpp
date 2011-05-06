#include "vtkWindowTest.h"
#include "vtkRenderWindow.h"
#include "../lemon.h"

vtkWindowTest::vtkWindowTest(void)
{
}


vtkWindowTest::~vtkWindowTest(void)
{
}

vtkWindow* MakeWindow(void)
{
    vtkWindow* win = vtkRenderWindow::New();
    win->SetSize(10, 10);
    return win;
}

bool vtkWindowTest::Run(bool on)
{
    if (!on)
        return on;

    lemon::test<> t;

    vtkWindow* win = MakeWindow();
    t.is(win->GetSize()[0], 10, "verifying GetSize[0]");
    t.is(win->GetSize()[1], 10, "verifying GetSize[1]");
}