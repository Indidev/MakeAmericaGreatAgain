#include "OfficeWidget.h"
#include "ui_OfficeWidget.h"

OfficeWidget::OfficeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OfficeWidget)
{
    ui->setupUi(this);
}

OfficeWidget::~OfficeWidget()
{
    delete ui;
}
