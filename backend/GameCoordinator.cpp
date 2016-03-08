#include "GameCoordinator.h"

GameCoordinator::GameCoordinator(QObject *parent) :
    QObject(parent)
{
    //load resources
    new ResourceProvider("resources.txt");
    meterStatus = 0;

    //Start screen
    MainFrame::setBg(ResourceProvider::img("titlescreen"));
    TitleWidget* tw = new TitleWidget;
    MainFrame::setContent(tw);

    connect(tw, SIGNAL(mouseClicked()), this, SLOT(showOffice()));
}

void GameCoordinator::showOffice()
{
    updateElektometer(meterStatus);
    OfficeWidget *of = new OfficeWidget;
    MainFrame::setContent(of);
    MainFrame::setBg(ResourceProvider::img("office"));
    setTrump();

    connect(of, SIGNAL(over(State)), this, SLOT(setTrump(State)));
    connect(of, SIGNAL(click(State)), this, SLOT(officeClick(State)));
}

void GameCoordinator::setTrump(State state)
{
    QString trmp = "default";
    switch (state) {
        case State::twitter: trmp = "twitter";
            break;
        case State::press: trmp = "press";
            break;
        case State::phone: trmp = "phone";
            break;
        case State::close: trmp = "exit";
            break;
        default:
            ;//do nothing
    }

    MainFrame::setTrump(ResourceProvider::img(trmp));
}

void GameCoordinator::officeClick(State state)
{
    switch (state) {
        case State::close: QApplication::exit(0);
            break;
        case State:: phone:
            showInterview();
            break;
        default:
            ;//currently ignored because not implemented or not necessary
    }
}

void GameCoordinator::updateElektometer(float percentage)
{
    QImage meter = *ResourceProvider::img("meter-frame");
    QImage bar = *ResourceProvider::img("meter-bar");

    QImage mask(bar);
    mask.fill(Qt::black);

    QPainter painter(&mask);
    painter.fillRect(0, 0, mask.width() * percentage, mask.height(), Qt::white);
    painter.end();

    bar.setAlphaChannel(mask);

    painter.begin(&meter);
    painter.drawImage(22, 41, bar);
    painter.end();

    MainFrame::setElektrometer(&meter);
}

void GameCoordinator::incMeter(int points)
{
    meterStatus += (float) points / 100.f;
    meterStatus = std::max(0.f, std::min(1.f, meterStatus)); //keep it between 0 and 1
    updateElektometer(meterStatus);
}

void GameCoordinator::showInterview()
{
    InterviewWidget *iw = new InterviewWidget;
    MainFrame::setContent(iw);
    setTrump();
    connect(iw, SIGNAL(close()), this, SLOT(showOffice()));
    connect(iw, SIGNAL(pointsChanged(int)), this, SLOT(incMeter(int)));
}
