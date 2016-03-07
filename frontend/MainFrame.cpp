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
    self = this;

    ui->setupUi(this);
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

    //connect(InputGrabber::instance(), SIGNAL(inputPress(InputEvent)), this, SLOT(onKey(InputEvent)));

    bgLayer->setAttribute(Qt::WA_TransparentForMouseEvents);
    //ui->centralWidget->setMinimumSize(resolution);
    //ui->centralWidget->setMaximumSize(resolution);

    this->showFullScreen();
}

void MainFrame::setBg(QImage *img)
{
    if (!img || !self)
        return;

    self->bgLabel->setPixmap(QPixmap::fromImage(img->scaled(self->resolution)));
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
