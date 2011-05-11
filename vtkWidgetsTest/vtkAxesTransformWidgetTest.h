#pragma once
class vtkAbstractWidget;
class vtkInteractor;

class vtkAxesTransformWidgetTest
{
public:
    vtkAxesTransformWidgetTest(void);
    ~vtkAxesTransformWidgetTest(void);

    vtkAbstractWidget* CreateScene(vtkInteractor& interactor);

    static bool Run(bool on);
};

