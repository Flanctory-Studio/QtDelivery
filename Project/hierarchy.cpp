#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "gameobject.h"
#include "mainwindow.h"

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
}

void Hierarchy::OnRemoveEntityClicked()
{
    uint currentRow = ui->listEntities->currentRow();

    std::list<GameObject*>::iterator it = gameObjects.begin();
    std::advance(it, currentRow);

    delete (*it);
    gameObjects.erase(it);

    ui->listEntities->takeItem(currentRow);
}

void Hierarchy::OnItemSelected(int index)
{
    emit entitySelected(index);
}