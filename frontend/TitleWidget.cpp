#include "TitleWidget.h"
#include "ui_TitleWidget.h"

TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleWidget)
{
    ui->setupUi(this);

    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer.start(50);
    ui->label->setStyleSheet("color:rgba(0, 0, 0, 100)");
}

TitleWidget::~TitleWidget()
{
    delete ui;
}

void TitleWidget::mouseReleaseEvent(QMouseEvent*)
{
    emit mouseClicked();
}

void TitleWidget::tick()
{
    static int delta = +10;
    static int opacity = 100;

    opacity += delta;
    if (opacity < 100) {
        delta *= -1;
        opacity = 100;
    } else if (opacity > 255) {
        delta *= -1;
        opacity = 255;
    }

    ui->label->setStyleSheet("color: rgba(0, 0, 0, " + QString::number(opacity) + ")");
}
