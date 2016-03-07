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
    QRect resolution = QApplication::desktop()->screenGeometry();

    float facX = (float) resolution.width() / 1920.f;
    float facY = (float) resolution.height() / 1080.f;

    QRect twitter(800 * facX, 550 * facY, 60 * facX, 100 * facY);
    QRect press(1340 * facX, 90 * facY, 440 * facX, 850 * facY);
    QRect phone(420 * facX, 605 * facY, 160 * facX, 70 * facY);
    QRect close(1130 * facX, 950 * facY, 280 * facX, 120 * facY);

    if (twitter.contains(event->localPos().toPoint())) {
        if (curState != State::twitter) {
            curState = State::twitter;
            emit over(curState);
        }
    } else if (press.contains(event->localPos().toPoint())) {
        if (curState != State::press) {
            curState = State::press;
            emit over(curState);
        }
    } else if (phone.contains(event->localPos().toPoint())) {
        if (curState != State::phone) {
            curState = State::phone;
            emit over(curState);
        }
    } else if (close.contains(event->localPos().toPoint())) {
      if (curState != State::close) {
          curState = State::close;
          emit over(curState);
      }
    } else if (curState != State::sitting) {
        curState = State::sitting;
        emit over(curState);
    }
}

void OfficeWidget::mouseReleaseEvent(QMouseEvent*)
{
    if (curState != sitting)
        emit click(curState);
}
