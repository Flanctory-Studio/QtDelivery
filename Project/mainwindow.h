#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>

namespace Ui {
    class MainWindow;
}
class Hierarchy;
class Inspector;
class SceneWidget;



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void OnQuitClicked();
    void OnNewClicked();

    void OnSaveClicked();
    void OnOpenClicked();

private:
    void CreateNewScene();

public:
    Hierarchy* hierarchy = nullptr;
    Inspector* inspector = nullptr;
    SceneWidget* scene = nullptr;
private:
    Ui::MainWindow* uiMainWindow = nullptr;



    int num = 0;

    QString currentSceneName = "Default";
    QJsonDocument currentScene;
};

#endif // MAINWINDOW_H
