#pragma once
class vtkAbstractWidget;
class vtkRenderer;

class vtkTextWidgetTest
{
public:
    vtkTextWidgetTest(void);
    ~vtkTextWidgetTest(void);

    vtkAbstractWidget* CreateScene(vtkRenderer& interactor);

    static bool Run(bool on);
};

