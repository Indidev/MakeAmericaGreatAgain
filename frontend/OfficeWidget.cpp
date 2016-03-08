#include "OfficeWidget.h"
#include "ui_OfficeWidget.h"

OfficeWidget::OfficeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OfficeWidget)
{
    ui->setupUi(this);
    curState = State::sitting;
    this->setMouseTracking(true);
}

OfficeWidget::~OfficeWidget()
{
    delete ui;
}

void OfficeWidget::mouseMoveEvent(QMouseEvent *event)
{
    QRect twitter = rect(800, 550, 60, 100);
    QRect press = rect(1340, 90, 440, 850);
    QRect phone = rect(420, 605, 160, 70);
    QRect close = rect(1130, 950, 280, 120);

    if (twitter.contains(event->localPos().toPoint()))
        checkState(State::twitter);
    else if (press.contains(event->localPos().toPoint()))
        checkState(State::press);
    else if (phone.contains(event->localPos().toPoint()))
        checkState(State::phone);
    else if (close.contains(event->localPos().toPoint()))
      checkState(State::close);
    else
        checkState(State::sitting);
}

void OfficeWidget::mouseReleaseEvent(QMouseEvent*)
{
    if (curState != sitting)
        emit click(curState);
}

QRect OfficeWidget::rect(int x, int y, int w, int h)
{
    QRect resolution = QApplication::desktop()->screenGeometry();

    float facX = (float) resolution.width() / 1920.f;
    float facY = (float) resolution.height() / 1080.f;

    return QRect(x * facX, y * facY, w * facX, h * facY);
}

void OfficeWidget::checkState(State state)
{
    if (curState != state) {
        curState = state;
        emit over(curState);
    }
}
