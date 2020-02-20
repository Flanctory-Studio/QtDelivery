#include "color.h"
#include "ui_color.h"
#include <QDoubleSpinBox>


Color::Color(QWidget *parent) : QWidget(parent)
{
    ui->setupUi(this);
}

Color::~Color()
{
    delete ui;
}
