#pragma once
class vtkRenderer;
class vtkAbstractWidget;

class vtkBalloonWidgetTest
{
public:
    vtkBalloonWidgetTest(void);
    ~vtkBalloonWidgetTest(void);

    vtkAbstractWidget* CreateScene(vtkRenderer& win);

    static bool Run(bool on);
};

