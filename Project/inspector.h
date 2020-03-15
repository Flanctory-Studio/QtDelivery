#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

namespace Ui {
    class Transform;
    class Size;
    class Color;
    class Shape;
    class Stroke;
}

class MainWindow;

class Inspector : public QWidget
{
    Q_OBJECT

public:
    explicit Inspector(QWidget* parent = nullptr, MainWindow* mainWindow = nullptr);
    ~Inspector();

    void ChangeShapeSelection(uint index);
    void BlockSignals(bool block);

public slots:
    void OnHierarchyItemSelected(int index);
    void OnHierarchyItemDeleted(int index);

    void OnInspectorChange(const QString &text);

private:
    Ui::Transform* uiTransform = nullptr;
    Ui::Size* uiSize = nullptr;
    Ui::Color* uiColor = nullptr;
    Ui::Shape* uiShape = nullptr;
    Ui::Stroke* uiStroke = nullptr;

    QWidget* transform = nullptr;
    QWidget* size = nullptr;
    QWidget* color = nullptr;
    QWidget* shape = nullptr;
    QWidget* stroke = nullptr;

    MainWindow* mainWindow = nullptr;

    int goIndex = 0;
    bool changeGO = false;
};

#endif // INSPECTOR_H
