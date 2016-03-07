#ifndef OFFICEWIDGET_H
#define OFFICEWIDGET_H

#include <QWidget>

namespace Ui {
class OfficeWidget;
}

class OfficeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OfficeWidget(QWidget *parent = 0);
    ~OfficeWidget();

private:
    Ui::OfficeWidget *ui;
};

#endif // OFFICEWIDGET_H
