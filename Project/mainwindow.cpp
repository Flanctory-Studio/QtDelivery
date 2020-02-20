#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_transform.h"

#include "hierarchy.h"
#include "inspector.h"
#include "scenewidget.h"

#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    uiMainWindow(new Ui::MainWindow)
{
    uiMainWindow->setupUi(this);

    hierarchy = new Hierarchy();
    uiMainWindow->dockHierarchy->setWidget(hierarchy);

    inspector = new Inspector();
    uiMainWindow->dockInspector->setWidget(inspector);

    scene = new SceneWidget();
    QVBoxLayout* centralLayout = new QVBoxLayout();
    centralLayout->setMargin(0);
    centralLayout->addWidget(scene);
    uiMainWindow->centralWidget->setLayout(centralLayout);

    connect(uiMainWindow->actionSave, SIGNAL(triggered()), this, SLOT(OnSaveClicked()));
    connect(uiMainWindow->actionOpen, SIGNAL(triggered()), this, SLOT(OnOpenClicked()));
    connect(hierarchy, SIGNAL(entitySelected(int)), inspector, SLOT(onHierarchyItemSelected(int)));

//    ins = new Inspector();
//    ui->dockInspector->setWidget(ins);
//    ins->show();
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
}

void MainWindow::OnSaveClicked()
{

}

void MainWindow::OnOpenClicked()
{
    QMessageBox::StandardButton button = QMessageBox::question(this, "Exit application", "Do you want to exit the application without saving the project?");
    if (button == QMessageBox::Yes)
    {
        std::cout << "Exit without saving changes" << std::endl;
    }
    else if (button == QMessageBox::No)
    {
        std::cout << "Cancel exit" << std::endl;
    }
}
