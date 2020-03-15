#include "scenewidget.h"

#include <QPaintEvent>
#include <QPainter>

#include "gameobject.h"
#include "mainwindow.h"
#include "hierarchy.h"

SceneWidget::SceneWidget(QWidget *parent, MainWindow* mainWindow) : QWidget(parent), mainWindow(mainWindow)
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


void SceneWidget::DrawGameObject(const std::list<GameObject*>& gameObjects)
{
    QPainter painter(this);

    QPen pen;
    pen.setStyle(Qt::PenStyle::NoPen);

    QBrush brush;



    for (std::list<GameObject*>::const_iterator it = gameObjects.cbegin(); it != gameObjects.cend(); it++)
    {
        // Set the brush for the shape
        brush.setColor((*it)->shapeColor);
        brush.setStyle((*it)->shapeStyle);

        // Set the pen for the border
        pen.setWidth((*it)->borderWidth);
        pen.setColor((*it)->borderColor);
        pen.setStyle((*it)->borderStyle);

        // Add brush and pen to painter
        painter.setBrush(brush);
        painter.setPen(pen);


        switch ((*it)->shape)
        {
        case Shape::Square:
        {
            int x = (*it)->position[0];
            int y = (*it)->position[1];
            QRect rect(x, y, (*it)->squareW, (*it)->squareH);

            painter.drawRect(rect);
        }
            break;
        case Shape::Triangle:
        {
            QPolygon polygon;

            int x = (*it)->position[0];
            int y = (*it)->position[1];

            polygon << QPoint(x, y - (*it)->triangleS)
                    << QPoint(x + 2 * (*it)->triangleS / 3, y + (*it)->triangleS / 3)
                    << QPoint(x -  2 * (*it)->triangleS / 3, y + (*it)->triangleS / 3);

            painter.drawPolygon(polygon);
        }
            break;
        case Shape::Circle:
        {
            // Draw circle
            int w = (*it)->circleR * 2;
            int h = (*it)->circleR * 2;
            int x = (*it)->position[0] - (*it)->circleR;
            int y = (*it)->position[1] - (*it)->circleR;
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
    //DrawGameObject()




//    GameObject* go = new GameObject();

//    go->position[0] = rect().width() / 2;
//    go->position[1] = rect().height() / 2;

//    go->borderColor = QColorConstants::Green;
//    go->shapeColor = QColorConstants::Yellow;

//    go->borderWidth = 0;

//    go->shape = Shape::Triangle;

    DrawGameObject(mainWindow->hierarchy->gameObjects);

}




















