#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

namespace Ui {
    class Transform;
    class Color;
    class Shape;
    class Stroke;
}

class Inspector : public QWidget
{
    Q_OBJECT

public:
    explicit Inspector(QWidget* parent = nullptr);
    ~Inspector();

public slots:
    void onHierarchyItemSelected(int index);

private:
    Ui::Transform* uiTransform = nullptr;
    Ui::Color* uiColor = nullptr;
    Ui::Shape* uiShape = nullptr;
    Ui::Stroke* uiStroke = nullptr;

    QWidget* transform = nullptr;
    QWidget* color = nullptr;
    QWidget* shape = nullptr;
    QWidget* stroke = nullptr;
};

#endif // INSPECTOR_H
