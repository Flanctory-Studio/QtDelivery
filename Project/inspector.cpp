#include "inspector.h"

#include <ui_transform.h>
#include <ui_size.h>
#include <ui_shape.h>
#include <ui_color.h>
#include <ui_stroke.h>

#include <QVBoxLayout>

Inspector::Inspector(QWidget *parent, MainWindow* mainWindow) : QWidget(parent), mainWindow(mainWindow)
{
    uiTransform = new Ui::Transform();
    uiSize = new Ui::Size();
    uiColor = new Ui::Color();
    uiShape = new Ui::Shape();
    uiStroke = new Ui::Stroke();

    // Create transform widget
    transform = new QWidget();
    uiTransform->setupUi(transform);

    size = new QWidget();
    uiSize->setupUi(size);

    color = new QWidget();
    uiColor->setupUi(color);

    shape = new QWidget();
    uiShape->setupUi(shape);

    stroke = new QWidget();
    uiStroke->setupUi(stroke);

    // Add widgets to layout
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(transform);
    layout->addWidget(size);
    layout->addWidget(color);
    layout->addWidget(shape);
    layout->addWidget(stroke);

    QSpacerItem* spacer = new QSpacerItem(50, 50, QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addSpacerItem(spacer);

    //Transform modification
    connect(uiTransform->posXBox, SIGNAL(clicked()), this, SLOT(OnInspectorChange()));
    connect(uiTransform->posYBox, SIGNAL(clicked()), this, SLOT(OnInspectorChange()));

    //Size modification
    connect(uiSize->spinRad, SIGNAL(clicked()), this, SLOT(OnInspectorChange()));
    connect(uiSize->spinH, SIGNAL(clicked()), this, SLOT(OnInspectorChange()));
    connect(uiSize->spinW, SIGNAL(clicked()), this, SLOT(OnInspectorChange()));

    //Shape modification
    connect(uiShape->shapeSelector, SIGNAL(clicked()), this, SLOT(OnInspectorChange()));

    //Obj Color modification
    connect(uiColor->spinR, SIGNAL(clicked()), this, SLOT(OnInspectorChange()));
    connect(uiColor->spinG, SIGNAL(clicked()), this, SLOT(OnInspectorChange()));
    connect(uiColor->spinB, SIGNAL(clicked()), this, SLOT(OnInspectorChange()));

    //Stroke modification
    connect(uiStroke->pixelSpin, SIGNAL(clicked()), this, SLOT(OnInspectorChange()));
    connect(uiStroke->strokeType, SIGNAL(clicked()), this, SLOT(OnInspectorChange()));
    connect(uiStroke->spinR, SIGNAL(clicked()), this, SLOT(OnInspectorChange()));
    connect(uiStroke->spinG, SIGNAL(clicked()), this, SLOT(OnInspectorChange()));
    connect(uiStroke->spinB, SIGNAL(clicked()), this, SLOT(OnInspectorChange()));

    uiSize->spinRad->hide();
    uiSize->labelRad->hide();

    setLayout(layout);
}

Inspector::~Inspector()
{
    delete uiTransform;
    delete uiColor;
    delete uiShape;
    delete uiStroke;
}

void Inspector::OnHierarchyItemSelected(int index)
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

void Inspector::OnInspectorChange()
{
    //Send to Obj the new information
}
