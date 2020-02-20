#include "hierarchy.h"
#include "ui_hierarchy.h"

Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
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
    ui->listEntities->addItem("Entity");
}

void Hierarchy::OnRemoveEntityClicked()
{
    ui->listEntities->takeItem(ui->listEntities->currentRow());
}

void Hierarchy::OnItemSelected(int index)
{
    emit entitySelected(index);
}
