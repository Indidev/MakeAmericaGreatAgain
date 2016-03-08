#ifndef MOUSETRACKING_H
#define MOUSETRACKING_H

#include <QWidget>
#include <QMouseEvent>
#include <QGridLayout>

class MouseTracking : public QWidget
{
    Q_OBJECT
public:
    explicit MouseTracking(QWidget *parent = 0);

signals:
    void mouseMoved(QMouseEvent *event);
    void mouseReleased(QMouseEvent *event);

public slots:

protected:
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *event);

};

#endif // MOUSETRACKING_H
