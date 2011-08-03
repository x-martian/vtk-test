#include "vtkImagePlaneWidgetTest.h"
#include "vtkImagePlaneWidget.h"
#include "vtkImageDataTest.h"
#include "vtkImageData.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"

vtkImagePlaneWidgetTest::vtkImagePlaneWidgetTest(void)
{
}

vtkImagePlaneWidgetTest::~vtkImagePlaneWidgetTest(void)
{
}

vtkImagePlaneWidget* vtkImagePlaneWidgetTest::CreateScene(vtkRenderer& renderer)
{
    vtkImageData* img = vtkImageDataTest::MakeImageData(32, 32, 32);
    vtkImagePlaneWidget* widget = vtkImagePlaneWidget::New();
    widget->SetInput(img);
    img->Delete();
    widget->SetPlaneOrientationToXAxes();
    widget->SetSliceIndex(16);
    widget->SetInteractor(renderer.GetRenderWindow()->GetInteractor());
    return widget;
}

bool vtkImagePlaneWidgetTest::Run(bool on)
{
    return true;
}