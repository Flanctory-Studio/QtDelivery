#ifndef COLOR_H
#define COLOR_H

#include <QWidget>

namespace Ui {
    class Color;
}

class Color : public QWidget
{
    Q_OBJECT

public:
    explicit Color(QWidget *parent = nullptr);
    ~Color();

private:
    Ui::Color *ui;
};

#endif // COLOR_H
