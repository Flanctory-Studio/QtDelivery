#include "inspector.h"

#include <ui_transform.h>
#include <QVBoxLayout>
#include <ui_color.h>

Inspector::Inspector(QWidget *parent) : QWidget(parent)
{
    uiTransform = new Ui::Transform();
    uiColor = new Ui::Color();

    // Create transform widget
    transform = new QWidget();
    uiTransform->setupUi(transform);

    color = new QWidget();
    uiColor->setupUi(color);

    // Add widgets to layout
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(transform);
    layout->addWidget(color);

    setLayout(layout);
}

Inspector::~Inspector()
{
}
