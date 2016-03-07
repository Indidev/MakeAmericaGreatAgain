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

    connect(tw, SIGNAL(mouseClicked()), this, SLOT(startGame()));
}

void GameCoordinator::startGame()
{
    MainFrame::setContent(new OfficeWidget);
    MainFrame::setBg(ResourceProvider::img("office"));
    //todo write game stuff
}
