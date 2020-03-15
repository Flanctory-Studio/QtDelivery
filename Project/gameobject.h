#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QPen>
#include <QColor>


class SceneWidget;

enum class Shape
{
    Square,
    Triangle,
    Circle
};


class GameObject
{
public:
    GameObject();

public:
    float* position = new float[3] {0,0,0};
    float* scale = new float[3] {1, 1, 1};

    Qt::PenStyle borderStyle = Qt::PenStyle::SolidLine;
    QColor borderColor = QColorConstants::Black;
    int lineSize = 10;

    Qt::BrushStyle shapeStyle = Qt::BrushStyle::SolidPattern;
    QColor shapeColor = QColorConstants::White;

    Shape shape = Shape::Square;

public:
    void Paint(SceneWidget* screen);
};

#endif // GAMEOBJECT_H
