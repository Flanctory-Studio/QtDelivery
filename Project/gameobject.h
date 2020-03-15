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
    float* position = new float[2] {0,0};

    Qt::PenStyle borderStyle = Qt::PenStyle::SolidLine;
    QColor borderColor = QColorConstants::Black;
    int borderWidth = 10;

    Qt::BrushStyle shapeStyle = Qt::BrushStyle::SolidPattern;
    QColor shapeColor = QColorConstants::White;

    Shape shape = Shape::Square;

    int squareW = 128;
    int squareH = 128;

    int triangleS = 128;

    int circleR = 64;

public:
    void Paint(SceneWidget* screen);
};

#endif // GAMEOBJECT_H
