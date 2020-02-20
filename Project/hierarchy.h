#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QWidget>

namespace Ui {
    class Hierarchy;
}

class Hierarchy : public QWidget
{
    Q_OBJECT

public:
    explicit Hierarchy(QWidget *parent = nullptr);
    ~Hierarchy();

signals:
    void entitySelected(int index);

public slots:
    void OnAddEntityClicked();
    void OnRemoveEntityClicked();
    void OnItemSelected(int index);

private:
    Ui::Hierarchy *ui;
};

#endif // HIERARCHY_H
