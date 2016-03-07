#include "frontend/MainFrame.h"
#include "backend/GameCoordinator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainFrame w;
    w.show();

    GameCoordinator g;

    return a.exec();
}
