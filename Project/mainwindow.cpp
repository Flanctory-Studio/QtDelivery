#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_transform.h"

#include "hierarchy.h"
#include "inspector.h"
#include "scenewidget.h"

#include <QFile>
#include <QMessageBox>
#include <QStyleFactory>
#include <QTextStream>
#include <iostream>

#include "qinputdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    uiMainWindow(new Ui::MainWindow)
{
    QFile f(":qdarkstyle/style.qss");

    if (!f.exists())   {
        printf("Unable to set stylesheet, file not found\n");
    }
    else   {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }


    uiMainWindow->setupUi(this);

    setWindowTitle("Current Scene: " + currentSceneName);

    hierarchy = new Hierarchy(this);
    uiMainWindow->dockHierarchy->setWidget(hierarchy);

    inspector = new Inspector(this);
    uiMainWindow->dockInspector->setWidget(inspector);

    scene = new SceneWidget();
    QVBoxLayout* centralLayout = new QVBoxLayout();
    centralLayout->setMargin(0);
    centralLayout->addWidget(scene);
    uiMainWindow->centralWidget->setLayout(centralLayout);

    connect(uiMainWindow->actionSave, SIGNAL(triggered()), this, SLOT(OnSaveClicked()));
    connect(uiMainWindow->actionOpen, SIGNAL(triggered()), this, SLOT(OnOpenClicked()));

    connect(uiMainWindow->actionNew, SIGNAL(triggered()), this, SLOT(OnNewClicked()));
    connect(uiMainWindow->actionQuit, SIGNAL(triggered()), this, SLOT(OnQuitClicked()));

    connect(hierarchy, SIGNAL(entitySelected(int)), inspector, SLOT(onHierarchyItemSelected(int)));


//    ins = new Inspector();
//    ui->dockInspector->setWidget(ins);
//    ins->show();
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
}

void MainWindow::CreateNewScene()
{
    currentSceneName = QInputDialog::getText(this, "New Scene", "Scene name:", QLineEdit::Normal, "", nullptr, Qt::WindowFlags(), Qt::ImhNone);
    setWindowTitle("Current Scene: " + currentSceneName);


//    QInputDialog dialog( this );
//    dialog.setModal( true );
//    dialog.setLabelText("Scene name:");
//    dialog.exec();
//    currentSceneName = dialog.textValue();

//    setWindowTitle("Current Scene: " + currentSceneName);
}

//SLOTS

void MainWindow::OnSaveClicked()
{

}

void MainWindow::OnOpenClicked()
{
//    QMessageBox::StandardButton button = QMessageBox::question(this, "Exit application", "Do you want to exit the application without saving the project?");
//    if (button == QMessageBox::Yes)
//    {
//        std::cout << "Exit without saving changes" << std::endl;
//    }
//    else if (button == QMessageBox::No)
//    {
//        std::cout << "Cancel exit" << std::endl;
//    }
}

void MainWindow::OnQuitClicked()
{
    exit(EXIT_SUCCESS);
}

void MainWindow::OnNewClicked()
{
    CreateNewScene();
}