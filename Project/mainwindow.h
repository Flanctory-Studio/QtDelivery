#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow* uiMainWindow = nullptr;

    Hierarchy* hierarchy = nullptr;
    Inspector* inspector = nullptr;
    SceneWidget* scene = nullptr;
    int num = 0;

    QString currentSceneName = "Default";
};

#endif // MAINWINDOW_H
