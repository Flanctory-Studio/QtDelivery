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

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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

    hierarchy = new Hierarchy(nullptr, this);
    uiMainWindow->dockHierarchy->setWidget(hierarchy);

    inspector = new Inspector(nullptr, this);
    uiMainWindow->dockInspector->setWidget(inspector);

    scene = new SceneWidget(nullptr, this);
    QVBoxLayout* centralLayout = new QVBoxLayout();
    centralLayout->setMargin(0);
    centralLayout->addWidget(scene);
    uiMainWindow->centralWidget->setLayout(centralLayout);

    connect(uiMainWindow->actionSave, SIGNAL(triggered()), this, SLOT(OnSaveClicked()));
    connect(uiMainWindow->actionOpen, SIGNAL(triggered()), this, SLOT(OnOpenClicked()));

    connect(uiMainWindow->actionNew, SIGNAL(triggered()), this, SLOT(OnNewClicked()));
    connect(uiMainWindow->actionQuit, SIGNAL(triggered()), this, SLOT(OnQuitClicked()));

    connect(hierarchy, SIGNAL(entitySelected(int)), inspector, SLOT(OnHierarchyItemSelected(int)));
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
}

void MainWindow::CreateNewScene()
{
    QString requestedName = QInputDialog::getText(this, "New Scene", "Scene name:", QLineEdit::Normal, "", nullptr, Qt::WindowFlags(), Qt::ImhNone);
    if(requestedName.isNull())
    {
        return;
    }

    currentSceneName = requestedName;
    setWindowTitle("Current Scene: " + currentSceneName);

    hierarchy->ClearGameObjects();

    //TODO: Tell the inspector to redraw its ui
}

//SLOTS

void MainWindow::OnSaveClicked()
{
    QJsonArray arrayJSON;

    hierarchy->SaveScene(arrayJSON);

    currentScene = QJsonDocument();

    QJsonObject object;
    object["GameObjects"] = arrayJSON;

    currentScene.setObject(object);

    QFile file(currentSceneName + ".scene");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write(currentScene.toJson());

        //QDataStream content (&file);
        //content << currentScene.toJson();
    }
}

void MainWindow::OnOpenClicked()
{
    QString requestedName = QInputDialog::getText(this, "Scene to open", "Scene name:", QLineEdit::Normal, "", nullptr, Qt::WindowFlags(), Qt::ImhNone);

    if(requestedName.isNull())
    {
        return;
    }

    QFile file(requestedName + ".scene");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      return;

    setWindowTitle("Current Scene: " + currentSceneName);
    hierarchy->ClearGameObjects();

    QByteArray content = file.readAll();
    currentScene = QJsonDocument::fromJson(content);

    QJsonObject object = currentScene.object();

    QJsonArray array = object["GameObjects"].toArray();

    hierarchy->LoadScene(array);
}

void MainWindow::OnQuitClicked()
{
    exit(EXIT_SUCCESS);
}

void MainWindow::OnNewClicked()
{
    CreateNewScene();
}
