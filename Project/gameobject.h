#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QPen>
#include <QColor>
#include <QWidget>

class GameObject
{
public:
    GameObject();

public:
    float* position = new float[3] {0,0,0};
    float* scale = new float[3] {1, 1, 1};

    Qt::PenCapStyle borderStyle = Qt::PenCapStyle::FlatCap;
    QColor borderColor = QColorConstants::Black;

    Qt::BrushStyle shapeStyle = Qt::BrushStyle::SolidPattern;
    QColor shapeColor = QColorConstants::White;

    void Paint(QWidget* centralWidget);
};

#endif // GAMEOBJECT_H
