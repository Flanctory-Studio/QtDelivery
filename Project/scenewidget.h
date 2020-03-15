#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include <QWidget>


class MainWindow;
class GameObject;


class SceneWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SceneWidget(QWidget *parent = nullptr, MainWindow* mainWindow = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void DrawGameObject(const std::list<GameObject*>& gameObjects);


signals:

public slots:

private:
    void paintEvent(QPaintEvent* event) override;

private:
    MainWindow* mainWindow = nullptr;
};

#endif // SCENEWIDGET_H
