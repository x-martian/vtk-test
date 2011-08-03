#pragma once
#include "vtkImagePlaneWidget.h"
class vtkRenderer;

class vtkImagePlaneWidgetTest
{
public:
    vtkImagePlaneWidgetTest(void);
    ~vtkImagePlaneWidgetTest(void);

    vtkImagePlaneWidget* CreateScene(vtkRenderer& renderer);

    static bool Run(bool on);
};

