#ifndef OFFICEWIDGET_H
#define OFFICEWIDGET_H

#include <QWidget>
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>

namespace Ui {
class OfficeWidget;
}

enum State{sitting, twitter, press, phone, close};

class OfficeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OfficeWidget(QWidget *parent = 0);
    ~OfficeWidget();

protected:
    Ui::OfficeWidget *ui;
    State curState;

    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *);
    QRect rect(int x, int y, int w, int h);
    void checkState(State state);

signals:
    void over(State state);
    void click(State state);
};

#endif // OFFICEWIDGET_H
