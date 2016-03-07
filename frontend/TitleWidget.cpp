#include "TitleWidget.h"
#include "ui_TitleWidget.h"

TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleWidget)
{
    ui->setupUi(this);

    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer.start(25);
    ui->label->setStyleSheet("color:transparent");
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
    static int opacity = 0;

    opacity += delta;
    if (opacity < 0) {
        delta *= -1;
        opacity = 0;
    } else if (opacity > 255) {
        delta *= -1;
        opacity = 255;
    }

    ui->label->setStyleSheet("color: rgba(0, 0, 0, " + QString::number(opacity) + ")");
}
