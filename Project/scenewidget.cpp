#include "scenewidget.h"

#include <QPaintEvent>
#include <QPainter>

#include "gameobject.h"

SceneWidget::SceneWidget(QWidget *parent) : QWidget(parent)
{

}

QSize SceneWidget::sizeHint() const
{
    return QSize(256,256);
}

QSize SceneWidget::minimumSizeHint() const
{
    return QSize(64,64);
}


void SceneWidget::DrawGameObject(GameObject* gameObject)
{
    QPainter painter(this);

    QPen pen;
    pen.setStyle(Qt::PenStyle::NoPen);

    QBrush brush;



    //for all gameobjects
    {
        // Set the brush for the shape
        brush.setColor(gameObject->shapeColor);
        brush.setStyle(gameObject->shapeStyle);

        // Set the pen for the border
        pen.setWidth(gameObject->borderWidth);
        pen.setColor(gameObject->borderColor);
        pen.setStyle(gameObject->borderStyle);

        // Add brush and pen to painter
        painter.setBrush(brush);
        painter.setPen(pen);


        switch (gameObject->shape)
        {
        case Shape::Square:
        {
            int x = gameObject->position[0];
            int y = gameObject->position[1];
            QRect rect(x, y, gameObject->squareW, gameObject->squareH);

            painter.drawRect(rect);
        }
            break;
        case Shape::Triangle:
        {
            QPolygon polygon;

            int x = gameObject->position[0];
            int y = gameObject->position[1];

            polygon << QPoint(x, y - gameObject->triangleS)
                    << QPoint(x + 2 * gameObject->triangleS / 3, y + gameObject->triangleS / 3)
                    << QPoint(x -  2 * gameObject->triangleS / 3, y + gameObject->triangleS / 3);

            painter.drawPolygon(polygon);
        }
            break;
        case Shape::Circle:
        {
            // Draw circle
            int r = 64;
            int w = r * 2;
            int h = r * 2;
            int x = gameObject->position[0] - r;
            int y = gameObject->position[1] - r;
            QRect circleRect(x, y, w, h);

            painter.drawEllipse(circleRect);
        }
            break;
        }
    }
}


void DrawCircle(SceneWidget* screen, int pos)
{
    QColor blueColor = QColor::fromRgb(127,196,220);
    QColor whiteColor = QColor::fromRgb(255,255,255);
    QColor blackColor = QColor::fromRgb(0,6,0);

    // Prepare the painter for this widget
    QPainter painter(screen);
    //QBrush brush;
    QPen pen;

    // Brush/pen configuration
    //brush.setColor(blueColor);
   // brush.setStyle(Qt::BrushStyle::SolidPattern);
    pen.setStyle(Qt::PenStyle::NoPen);
   // painter.setBrush(brush);
    painter.setPen(pen);

    // Paint background
    painter.drawRect(screen->rect());

    // Brush/pen configuration
   // brush.setColor(whiteColor);
    pen.setWidth(10);
    pen.setColor(blackColor);
    pen.setStyle(Qt::PenStyle::DashDotDotLine);
   // painter.setBrush(brush);
    painter.setPen(pen);

    // Draw circle
    int r = 64;
    int w = r * 2;
    int h = r * 2;
    int x = screen->rect().width() / 2 - r + pos;
    int y = screen->rect().height() / 2 - r;
    QRect circleRect(x, y, w, h);
    painter.drawEllipse(circleRect);
}

void SceneWidget::paintEvent(QPaintEvent *event)
{
    GameObject* go = new GameObject();

    go->position[0] = rect().width() / 2;
    go->position[1] = rect().height() / 2;

    go->borderColor = QColorConstants::Green;
    go->shapeColor = QColorConstants::Yellow;

    go->borderWidth = 0;

    go->shape = Shape::Triangle;

    DrawGameObject(go);

}




















