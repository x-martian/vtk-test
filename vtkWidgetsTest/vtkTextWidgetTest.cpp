#include "vtkTextWidgetTest.h"
#include "vtkTextRepresentation.h"
#include "vtkTextWidget.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkTextActor.h"
#include "vtkActor.h"
#include "vtkActorTest.h"

vtkTextWidgetTest::vtkTextWidgetTest(void)
{
}

vtkTextWidgetTest::~vtkTextWidgetTest(void)
{
}

vtkAbstractWidget* vtkTextWidgetTest::CreateScene(vtkRenderer& renderer)
{
    vtkActor* actor = vtkActorTest::MakeBoxPolyDataActor();
    renderer.AddActor(actor);
    actor->Delete();

    vtkTextActor* text = vtkTextActor::New();
    text->SetInput("A Text");
    vtkTextRepresentation* rep = vtkTextRepresentation::New();
    rep->GetPositionCoordinate()->SetValue(.15, .15);
    rep->GetPosition2Coordinate()->SetValue(.7, .2);
    vtkTextWidget* widget = vtkTextWidget::New();
    widget->SetRepresentation(rep);
    rep->Delete();
    widget->SetInteractor(renderer.GetRenderWindow()->GetInteractor());
    widget->SetTextActor(text);
    widget->SelectableOff();
    text->Delete();

    return widget;
}

#include "vtkWidgetsTestPipelineTemplate.h"

bool vtkTextWidgetTest::Run(bool on)
{
    if (!on)
        return true;

    vtkTextWidgetTest test;
    vtkWidgetsTestPipelineTemplate<vtkTextWidgetTest> pipeline(test);
    pipeline.StartInteractor();

    return true;
}