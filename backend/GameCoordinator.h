#ifndef GAMECOORDINATOR_H
#define GAMECOORDINATOR_H

#include <QObject>

#include "frontend/MainFrame.h"
#include "frontend/TitleWidget.h"
#include "backend/ResourceProvider.h"
#include "frontend/OfficeWidget.h"

class GameCoordinator : public QObject
{
    Q_OBJECT
public:
    explicit GameCoordinator(QObject *parent = 0);

signals:

protected slots:
    void showOffice();
    void setTrump(State state = State::sitting);
    void officeClick(State state);

};

#endif // GAMECOORDINATOR_H
