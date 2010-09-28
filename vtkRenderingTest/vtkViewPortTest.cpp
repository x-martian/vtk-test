#include "vtkViewPortTest.h"
#include "vtkRenderWindow.h"
#include "vtkRenderingTest.h"

class vtkViewPortTest
{
public:
	vtkViewPortTest(void)
	{
		// create a render window
		vtkRenderWindowTest(win, false);
	}
	~vtkViewPortTest(void);

private:
	vtkRenderWindow* win;
};
