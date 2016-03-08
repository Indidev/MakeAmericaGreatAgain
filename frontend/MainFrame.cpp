#include "MainFrame.h"
#include "ui_MainFrame.h"

MainFrame *MainFrame::self = NULL;

MainFrame::MainFrame() :
    ui(new Ui::MainFrame)
{
    init();
}


MainFrame::~MainFrame()
{
    delete ui;
}

void MainFrame::init() {
    curContent = NULL;
    curTrump = NULL;
    curMeter = NULL;
    self = this;

    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->showFullScreen();
    resolution = QApplication::desktop()->screenGeometry().size();

    layeredWidget = new LayeredWidget();
    ui->centralWidget->layout()->addWidget(layeredWidget);

    bgLayer = layeredWidget->addWidget(0);

    bgLayer->setLayout(new QGridLayout);

    bgLayer->layout()->setMargin(0);
    bgLayer->layout()->setSpacing(0);

    bgLabel = new QLabel();
    bgLabel->setMargin(0);
    bgLayer->layout()->addWidget(bgLabel);

    contentLayer = layeredWidget->addWidget(1);
    contentLayer->setLayout(new QGridLayout);
    contentLayer->layout()->setMargin(0);
    contentLayer->layout()->setSpacing(0);

    trumpLayer = layeredWidget->addWidget(2);
    trumpLayer->setLayout(new QGridLayout);
    trumpLayer->layout()->setMargin(0);
    trumpLayer->layout()->setSpacing(0);

    meterLayer = layeredWidget->addWidget(3);
    meterLayer->setLayout(new QGridLayout);
    meterLayer->layout()->setMargin(0);
    meterLayer->layout()->setSpacing(0);

    //connect(InputGrabber::instance(), SIGNAL(inputPress(InputEvent)), this, SLOT(onKey(InputEvent)));

    bgLayer->setAttribute(Qt::WA_TransparentForMouseEvents);
    trumpLayer->setAttribute(Qt::WA_TransparentForMouseEvents);
    meterLayer->setAttribute(Qt::WA_TransparentForMouseEvents);
    //ui->centralWidget->setMinimumSize(resolution);
    //ui->centralWidget->setMaximumSize(resolution);

    ui->centralWidget->showFullScreen();
}

void MainFrame::setBg(QImage *img)
{
    if (!img || !self)
        return;

    self->bgLabel->setPixmap(QPixmap::fromImage(img->scaled(self->resolution)));
}

void MainFrame::setElektrometer(QImage *meter)
{
    if (!meter || !self)
        return;
    QLabel *lbl = new QLabel();
    lbl->setPixmap(QPixmap::fromImage(meter->scaled(self->resolution)));

    QWidget *w = new QWidget;
    w->setLayout(new QGridLayout);
    w->layout()->setSpacing(0);
    w->layout()->setMargin(0);

    w->layout()->addWidget(lbl);

    self->setWidget(self->meterLayer, &(self->curMeter), w, true);
}

void MainFrame::removeMeter()
{
    self->setWidget(self->meterLayer, &(self->curMeter), NULL, true);
}

void MainFrame::setTrump(QImage *trump)
{
    if (!trump || !self)
        return;
    QLabel *lbl = new QLabel();
    lbl->setPixmap(QPixmap::fromImage(trump->scaled(self->resolution)));

    QWidget *w = new QWidget;
    w->setLayout(new QGridLayout);
    w->layout()->setSpacing(0);
    w->layout()->setMargin(0);

    w->layout()->addWidget(lbl);

    self->setWidget(self->trumpLayer, &(self->curTrump), w, true);
}

void MainFrame::removeTrump(){
    self->setWidget(self->trumpLayer, &(self->curTrump), NULL, true);
}

void MainFrame::setContent(QWidget *widget)
{
    if (!self)
        return;

    self->setWidget(self->contentLayer, &(self->curContent), widget);
}

void MainFrame::setWidget(QWidget *layer, QWidget **displayWidget, QWidget *widget, bool mouseTransparent) {
    if (*displayWidget) {
        (*displayWidget)->setVisible(false);
        layer->layout()->removeWidget(*displayWidget);
        (*displayWidget)->deleteLater();
    }
    *displayWidget = widget;
    if (widget)
        layer->layout()->addWidget(widget);

    layer->setAttribute(Qt::WA_TransparentForMouseEvents, mouseTransparent);
}
