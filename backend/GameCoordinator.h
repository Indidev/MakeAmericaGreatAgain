#ifndef GAMECOORDINATOR_H
#define GAMECOORDINATOR_H

#include <QObject>
#include <QPainter>

#include "frontend/MainFrame.h"
#include "frontend/TitleWidget.h"
#include "backend/ResourceProvider.h"
#include "frontend/OfficeWidget.h"
#include "frontend/InterviewWidget.h"

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
    void updateElektometer(float percentage);
    void incMeter(int points);
    void showInterview();

protected:
    float meterStatus;

};

#endif // GAMECOORDINATOR_H
