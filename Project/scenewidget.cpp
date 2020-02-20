#include "scenewidget.h"

#include <QPaintEvent>
#include <QPainter>

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


void SceneWidget::paintEvent(QPaintEvent *event)
{
    QColor blueColor = QColor::fromRgb(127,196,220);
    QColor whiteColor = QColor::fromRgb(255,255,255);
    QColor blackColor = QColor::fromRgb(0,6,0);

    // Prepare the painter for this widget
    QPainter painter(this);
    QBrush brush;
    QPen pen;

    // Brush/pen configuration
    brush.setColor(blueColor);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    pen.setStyle(Qt::PenStyle::NoPen);
    painter.setBrush(brush);
    painter.setPen(pen);

    // Paint background
    painter.drawRect(rect());

    // Brush/pen configuration
    brush.setColor(whiteColor);
    pen.setWidth(10);
    pen.setColor(blackColor);
    pen.setStyle(Qt::PenStyle::DashDotDotLine);
    painter.setBrush(brush);
    painter.setPen(pen);

    // Draw circle
    int r = 64;
    int w = r * 2;
    int h = r * 2;
    int x = rect().width() / 2 - r;
    int y = rect().height() / 2 - r;
    QRect circleRect(x, y, w, h);
    painter.drawEllipse(circleRect);

}
