#include "inspector.h"
#include "mainwindow.h"
#include "gameobject.h"
#include "hierarchy.h"

#include <ui_transform.h>
#include <ui_size.h>
#include <ui_shape.h>
#include <ui_color.h>
#include <ui_stroke.h>

#include <QVBoxLayout>

#include "gameobject.h"
#include "scenewidget.h"
#include <QDebug>

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

    transform->hide();
    size->hide();
    color->hide();
    shape->hide();
    stroke->hide();

    QSpacerItem* spacer = new QSpacerItem(50, 50, QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addSpacerItem(spacer);

    //Transform modification
    connect(uiTransform->posXBox, SIGNAL(textChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));
    connect(uiTransform->posYBox, SIGNAL(textChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));

    //Size modification
    connect(uiSize->spinRad, SIGNAL(textChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));
    connect(uiSize->spinH, SIGNAL(textChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));
    connect(uiSize->spinW, SIGNAL(textChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));
    connect(uiSize->spinSize, SIGNAL(textChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));

    //Shape modification
    connect(uiShape->shapeSelector, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));

    //Obj Color modification
    connect(uiColor->spinR, SIGNAL(textChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));
    connect(uiColor->spinG, SIGNAL(textChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));
    connect(uiColor->spinB, SIGNAL(textChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));
    connect(uiColor->brushStyle, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));

    //Stroke modification
    connect(uiStroke->pixelSpin, SIGNAL(textChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));
    connect(uiStroke->strokeType, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));
    connect(uiStroke->spinR, SIGNAL(textChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));
    connect(uiStroke->spinG, SIGNAL(textChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));
    connect(uiStroke->spinB, SIGNAL(textChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));

    connect(uiStroke->spinB, SIGNAL(textChanged(const QString &)), this, SLOT(OnInspectorChange(const QString &)));

    ChangeShapeSelection(3);

    setLayout(layout);
}

Inspector::~Inspector()
{
    delete uiTransform;
    delete uiColor;
    delete uiShape;
    delete uiStroke;
}

void Inspector::BlockSignals(bool block)
{
    uiTransform->posXBox->blockSignals(block);
    uiTransform->posYBox->blockSignals(block);

    uiSize->spinRad->blockSignals(block);
    uiSize->spinH->blockSignals(block);
    uiSize->spinW->blockSignals(block);
    uiSize->spinSize->blockSignals(block);

    uiShape->shapeSelector->blockSignals(block);

    uiColor->spinR->blockSignals(block);
    uiColor->spinG->blockSignals(block);
    uiColor->spinB->blockSignals(block);

    uiColor->brushStyle->blockSignals(block);

    uiStroke->pixelSpin->blockSignals(block);
    uiStroke->strokeType->blockSignals(block);

    uiStroke->spinR->blockSignals(block);
    uiStroke->spinG->blockSignals(block);
    uiStroke->spinB->blockSignals(block);
}

void Inspector::OnHierarchyItemSelected(int index)
{
    goIndex = index;

    if(index == -1)
    {
        transform->hide();
        size->hide();
        color->hide();
        shape->hide();
        stroke->hide();
    }

    else if(!mainWindow->hierarchy->gameObjects.empty())
    {
        transform->show();
        size->show();
        color->show();
        shape->show();
        stroke->show();

        std::list<GameObject*>::iterator iter = mainWindow->hierarchy->gameObjects.begin();
        std::advance(iter, index);

        qInfo() << index;

        if(iter != mainWindow->hierarchy->gameObjects.end())
        {
            BlockSignals(true);

            uiTransform->posXBox->setValue((*iter)->position[0]);
            uiTransform->posYBox->setValue((*iter)->position[1]);

            uiSize->spinRad->setValue((*iter)->circleR);
            uiSize->spinH->setValue((*iter)->squareH);
            uiSize->spinW->setValue((*iter)->squareW);
            uiSize->spinSize->setValue(((*iter)->triangleS));

            uiShape->shapeSelector->setCurrentIndex((int)(*iter)->shape);

            ChangeShapeSelection(uiShape->shapeSelector->currentIndex());

            int r,g,b = 0;
            (*iter)->shapeColor.getRgb(&r,&g,&b);
            uiColor->spinR->setValue(r);
            uiColor->spinG->setValue(g);
            uiColor->spinB->setValue(b);

            uiColor->brushStyle->setCurrentIndex((int)(*iter)->shapeStyle);

            uiStroke->pixelSpin->setValue((*iter)->borderWidth);
            uiStroke->strokeType->setCurrentIndex((int)(*iter)->borderStyle);

            (*iter)->borderColor.getRgb(&r,&g,&b);
            uiStroke->spinR->setValue(r);
            uiStroke->spinG->setValue(g);
            uiStroke->spinB->setValue(b);

            BlockSignals(false);

        }
    }
}


void Inspector::OnHierarchyItemDeleted(int index)
{



    goIndex = index - 1;
}


void Inspector::OnInspectorChange(const QString &text)
{
    //Send to Obj the new information

   GameObject* currentGO = nullptr;

    std::list<GameObject*>::iterator it = mainWindow->hierarchy->gameObjects.begin();
    std::advance(it, goIndex);
    currentGO = *it;

    if (currentGO != nullptr)
    {

        // Position
        currentGO->position[0] = uiTransform->posXBox->value();
        currentGO->position[1] = uiTransform->posYBox->value();

        currentGO->borderStyle = Qt::PenStyle(uiStroke->strokeType->currentIndex());
        currentGO->borderColor.setRgb(uiStroke->spinR->value(), uiStroke->spinG->value(), uiStroke->spinB->value());
        currentGO->borderWidth = uiStroke->pixelSpin->value();

        currentGO->shapeStyle =  Qt::BrushStyle(uiColor->brushStyle->currentIndex());
        currentGO->shapeColor.setRgb(uiColor->spinR->value(), uiColor->spinG->value(), uiColor->spinB->value());

        currentGO->shape = Shape(uiShape->shapeSelector->currentIndex());

        ChangeShapeSelection((uint)currentGO->shape);

        currentGO->squareW = uiSize->spinW->value();
        currentGO->squareH = uiSize->spinH->value();

        currentGO->triangleS = uiSize->spinSize->value();

        currentGO->circleR = uiSize->spinRad->value();

    }
    else
        printf("Error! No GameObject selected! Current GO is nullptr");

    mainWindow->scene->update();
}

void Inspector::ChangeShapeSelection(uint index)
{
    switch (index)
    {
    case 0://Square
        uiSize->spinRad->hide();
        uiSize->labelRad->hide();
        uiSize->labelSize->hide();
        uiSize->spinSize->hide();

        uiSize->spinH->show();
        uiSize->labelH->show();
        uiSize->spinW->show();
        uiSize->labelW->show();
        break;

    case 1://Triangle
        uiSize->spinRad->hide();
        uiSize->labelRad->hide();
        uiSize->spinH->hide();
        uiSize->labelH->hide();
        uiSize->spinW->hide();
        uiSize->labelW->hide();

        uiSize->labelSize->show();
        uiSize->spinSize->show();
        break;

    case 2://Sphere
        uiSize->spinH->hide();
        uiSize->labelH->hide();
        uiSize->spinW->hide();
        uiSize->labelW->hide();
        uiSize->labelSize->hide();
        uiSize->spinSize-> hide();

        uiSize->spinRad->show();
        uiSize->labelRad->show();
        break;
    default:
        uiSize->spinH->hide();
        uiSize->labelH->hide();
        uiSize->spinW->hide();
        uiSize->labelW->hide();
        uiSize->labelSize->hide();
        uiSize->spinSize-> hide();
        uiSize->spinRad->hide();
        uiSize->labelRad->hide();
        break;

    }
}

































