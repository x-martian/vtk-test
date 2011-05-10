#include "vtkBalloonWidgetTest.h"
#include "vtkBalloonRepresentation.h"
#include "vtkBalloonWidget.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkSphereSource.h"
#include "vtkRegularPolygonSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"

vtkBalloonWidgetTest::vtkBalloonWidgetTest(void)
{
}

vtkBalloonWidgetTest::~vtkBalloonWidgetTest(void)
{
}

vtkAbstractWidget* vtkBalloonWidgetTest::CreateScene(vtkRenderer& renderer)
{
    // Create the widget and its representation
    vtkBalloonRepresentation* rep = vtkBalloonRepresentation::New();
    rep->SetBalloonLayoutToImageRight();

    vtkBalloonWidget* widget = vtkBalloonWidget::New();
    widget->SetInteractor(renderer.GetRenderWindow()->GetInteractor());
    widget->SetRepresentation(rep);
    rep->Delete();

    // Sphere
    vtkSphereSource* sphereSource = vtkSphereSource::New();
    sphereSource->SetCenter(-4.0, 0.0, 0.0);
    sphereSource->SetRadius(4.0);

    vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());
    sphereSource->Delete();

    vtkActor* actor = vtkActor::New();
    actor->SetMapper(mapper);
    mapper->Delete();
    widget->AddBalloon(actor, "This is a sphere",NULL);
    renderer.AddActor(actor);
    actor->Delete();

    // Regular Polygon
    vtkRegularPolygonSource* regularPolygonSource = vtkRegularPolygonSource::New();
    regularPolygonSource->SetCenter(4.0, 0.0, 0.0);
    regularPolygonSource->SetRadius(4.0);

    mapper = vtkPolyDataMapper::New();
    mapper->SetInputConnection(regularPolygonSource->GetOutputPort());
    regularPolygonSource->Delete();

    actor = vtkActor::New();
    actor->SetMapper(mapper);
    mapper->Delete();
    widget->AddBalloon(actor, "This is a regular polygon",NULL);
    renderer.AddActor(actor);
    actor->Delete();

    return widget;
}

#include "vtkWidgetsTestPipelineTemplate.h"

bool vtkBalloonWidgetTest::Run(bool run)
{
    vtkBalloonWidgetTest test;
    vtkWidgetsTestPipelineTemplate<vtkBalloonWidgetTest> pipeline(test);
    pipeline.StartInteractor();

    return true;
}