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
    if(!mainWindow->hierarchy->gameObjects.empty())
    {
        std::list<GameObject*>::iterator iter = mainWindow->hierarchy->gameObjects.begin();
        std::advance(iter, index);

        if(*iter != nullptr)
        {
            uiTransform->posXBox->setValue((*iter)->position[0]);
            uiTransform->posYBox->setValue((*iter)->position[1]);

            uiSize->spinRad->setValue((*iter)->circleR);
            uiSize->spinH->setValue((*iter)->squareH);
            uiSize->spinW->setValue((*iter)->squareW);

            uiShape->shapeSelector->setCurrentIndex((int)(*iter)->shape);

            ChangeShapeSelection(uiShape->shapeSelector->currentIndex());

            int r,g,b = 0;
            (*iter)->shapeColor.getRgb(&r,&g,&b);
            uiColor->spinR->setValue(r);
            uiColor->spinG->setValue(g);
            uiColor->spinB->setValue(b);

            uiColor->brushStyle->setCurrentIndex((int)(*iter)->shapeStyle + 1);

            uiStroke->pixelSpin->setValue((*iter)->borderWidth);
            uiStroke->strokeType->setCurrentIndex((int)(*iter)->borderStyle + 1);

            (*iter)->borderColor.getRgb(&r,&g,&b);
            uiStroke->spinR->setValue(r);
            uiStroke->spinG->setValue(g);
            uiStroke->spinB->setValue(b);

            goIndex = index;
        }
    }
}
void Inspector::OnHierarchyItemDeleted(int index)
{



    goIndex = index;
}

void Inspector::OnInspectorChange()
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

        currentGO->borderStyle = Qt::PenStyle(uiStroke->strokeType->currentIndex() + 1);
        currentGO->borderColor.setRgb(uiStroke->spinR->value(), uiStroke->spinG->value(), uiStroke->spinB->value());
        currentGO->borderWidth = uiStroke->pixelSpin->value();

        // TODO
        //currentGO->shapeStyle =  Qt::BrushStyle(uiShape->shapeSelector->currentIndex());
        currentGO->shapeColor.setRgb(uiColor->spinR->value(), uiColor->spinG->value(), uiColor->spinB->value());

        currentGO->shape = Shape(uiShape->shapeSelector->currentIndex());

        currentGO->squareW = uiSize->spinW->value();
        currentGO->squareH = uiSize->spinH->value();

        currentGO->triangleS = uiSize->spinRad->value();

        // TODO
        //currentGO->circleR =

    }
    else
        printf("Error! No GameObject selected! Current GO is nullptr");

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

































