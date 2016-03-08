#include "MouseTracking.h"

MouseTracking::MouseTracking(QWidget *parent) :
    QWidget(parent)
{
    this->setMouseTracking(true);
    this->setAttribute(Qt::WA_TransparentForMouseEvents, false);
}

void MouseTracking::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(event);
}

void MouseTracking::mouseReleaseEvent(QMouseEvent *event)
{
    emit mouseReleased(event);
}
