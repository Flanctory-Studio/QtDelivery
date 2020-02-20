#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

namespace Ui {
    class Transform;
    class Color;
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

    QWidget* transform = nullptr;
    QWidget* color = nullptr;
};

#endif // INSPECTOR_H
