#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QWidget>
#include <list>

class MainWindow;

class GameObject;

namespace Ui
{
    class Hierarchy;
}

class Hierarchy : public QWidget
{
    Q_OBJECT

public:
    explicit Hierarchy(QWidget *parent = nullptr, MainWindow* mainWindow = nullptr);
    ~Hierarchy();

signals:
    void entitySelected(int index);

public slots:
    void OnAddEntityClicked();
    void OnRemoveEntityClicked();
    void OnItemSelected(int index);

public:
    void ClearGameObjects();

private:

    MainWindow* mainWindow = nullptr;
    Ui::Hierarchy *ui;
public:

    std::list<GameObject*> gameObjects;
};

#endif // HIERARCHY_H
