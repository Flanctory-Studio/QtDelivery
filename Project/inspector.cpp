#include "inspector.h"

#include <ui_transform.h>
#include <ui_shape.h>
#include <ui_color.h>
#include <ui_stroke.h>

#include <QVBoxLayout>

Inspector::Inspector(QWidget *parent, MainWindow* mainWindow) : QWidget(parent), mainWindow(mainWindow)
{
    uiTransform = new Ui::Transform();
    uiColor = new Ui::Color();
    uiShape = new Ui::Shape();
    uiStroke = new Ui::Stroke();

    // Create transform widget
    transform = new QWidget();
    uiTransform->setupUi(transform);

    color = new QWidget();
    uiColor->setupUi(color);

    shape = new QWidget();
    uiShape->setupUi(shape);

    stroke = new QWidget();
    uiStroke->setupUi(stroke);

    // Add widgets to layout
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(transform);
    layout->addWidget(color);
    layout->addWidget(shape);
    layout->addWidget(stroke);

    QSpacerItem* spacer = new QSpacerItem(50, 50, QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addSpacerItem(spacer);

    setLayout(layout);
}

Inspector::~Inspector()
{
    delete uiTransform;
    delete uiColor;
}

void Inspector::onHierarchyItemSelected(int index)
{
    if(index != 0)
    {
        color->hide();
    }
    else
    {
        color->show();
    }
}

void Inspector::OnHierarchyItemDeleted(int index)
{

}
