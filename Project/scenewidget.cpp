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
        pen.setWidth(gameObject->lineSize);
        pen.setColor(gameObject->borderColor);
        pen.setStyle(gameObject->borderStyle);

        // Add brush and pen to painter
        painter.setBrush(brush);
        painter.setPen(pen);


        switch (gameObject->shape)
        {
        case Shape::Square:

            break;
        case Shape::Triangle:

            break;
        case Shape::Circle:
            // Draw circle
            int r = 64;
            int w = r * 2;
            int h = r * 2;
            int x = rect().width() / 2 - r;
            int y = rect().height() / 2 - r;
            QRect circleRect(x, y, w, h);
            painter.drawEllipse(circleRect);

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

   // DrawCircle(this, -64);
    DrawCircle(this, 64);

}
