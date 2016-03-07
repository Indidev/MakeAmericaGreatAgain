#include "GameCoordinator.h"

GameCoordinator::GameCoordinator(QObject *parent) :
    QObject(parent)
{
    //load resources
    new ResourceProvider("resources.txt");

    //Start screen
    MainFrame::setBg(ResourceProvider::img("titlescreen"));
    TitleWidget* tw = new TitleWidget;
    MainFrame::setContent(tw);

    connect(tw, SIGNAL(mouseClicked()), this, SLOT(showOffice()));
}

void GameCoordinator::showOffice()
{
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
    }

    MainFrame::setTrump(ResourceProvider::img(trmp));
}

void GameCoordinator::officeClick(State state)
{
    switch (state) {
        case State::close: QApplication::exit(0);
            break;
        case State:: phone:
        //todo implement this
            break;
    }
}
