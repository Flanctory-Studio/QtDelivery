#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "gameobject.h"
#include "mainwindow.h"
#include "QJsonObject"
#include "scenewidget.h"

Hierarchy::Hierarchy(QWidget *parent, MainWindow* mainWindow) :
    QWidget(parent),
    mainWindow(mainWindow),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);

    connect(ui->buttonAddEntity, SIGNAL(clicked()), this, SLOT(OnAddEntityClicked()));
    connect(ui->buttonRemoveEntity, SIGNAL(clicked()), this, SLOT(OnRemoveEntityClicked()));
    connect(ui->listEntities, SIGNAL(currentRowChanged(int)), this, SLOT(OnItemSelected(int)));
}

Hierarchy::~Hierarchy()
{
    delete ui;
}

void Hierarchy::OnAddEntityClicked()
{
    GameObject* gameObject = new GameObject();
    gameObjects.push_back(gameObject);

    ui->listEntities->addItem("GameObject");

    mainWindow->scene->update();
}

void Hierarchy::OnRemoveEntityClicked()
{
    if(ui->listEntities->count() <= 0)
        return;

    uint currentRow = ui->listEntities->currentRow();

    std::list<GameObject*>::iterator it = gameObjects.begin();
    std::advance(it, currentRow);

    delete (*it);
    gameObjects.erase(it);

    ui->listEntities->takeItem(currentRow);
    mainWindow->scene->update();
}

void Hierarchy::OnItemSelected(int index)
{
    emit entitySelected(index);
}

void Hierarchy::ClearGameObjects()
{
   for(std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
   {
       delete(*it);
   }
   gameObjects.clear();

   ui->listEntities->clear();
}

void Hierarchy::SaveScene(QJsonArray& array)
{
    for(GameObject* gameObject : gameObjects)
    {
        QJsonObject object;

        object["Position X"] = gameObject->position[0];
        object["Position Y"] = gameObject->position[1];

        object["Border Style"] = gameObject->borderStyle;
        object["Border Color"] = gameObject->borderColor.name();
        object["Border Width"] = gameObject->borderWidth;

        object["Shape Style"] = gameObject->borderStyle;
        object["Shape Color"] = gameObject->shapeColor.name();
        object["Shape"] = (int)gameObject->shape;

        object["Square Width"] = gameObject->squareW;
        object["Square Height"] = gameObject->squareH;

        object["Triangle Size"] = gameObject->triangleS;

        object["Circle Radius"] = gameObject->circleR;

        array.push_back(object);
    }
}

void Hierarchy::LoadScene(QJsonArray& array)
{
    ClearGameObjects();

    for(QJsonValue value : array)
    {
        QJsonObject object = value.toObject();

        GameObject* gameObject = new GameObject();
        gameObject->position[0] = object["Position X"].toDouble();
        gameObject->position[1] = object["Position Y"].toDouble();

        gameObject->borderStyle = (Qt::PenStyle)object["Border Style"].toInt();
        gameObject->borderColor = object["Border Color"].toString();
        gameObject->borderWidth = object["Border Width"].toInt();

        gameObject->shapeStyle = (Qt::BrushStyle)object["Shape Style"].toInt();
        gameObject->shapeColor = object["Shape Color"].toString();
        gameObject->shape = (Shape)object["Shape"].toInt();

        gameObject->squareW = object["Square Width"].toInt();
        gameObject->squareH = object["Square Height"].toInt();

        gameObject->triangleS = object["Triangle Size"].toInt();

        gameObject->circleR = object["Circle Radius"].toInt();

        gameObjects.push_back(gameObject);
        ui->listEntities->addItem("GameObject");
    }

    mainWindow->scene->update();
}
