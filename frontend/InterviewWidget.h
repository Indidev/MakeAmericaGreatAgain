#ifndef INTERVIEWWIDGET_H
#define INTERVIEWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QPainter>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QMap>
#include <QString>
#include <stdlib.h>
#include <time.h>
#include <QDebug>

#include "frontend/LayeredWidget.h"
#include "backend/MouseTracking.h"
#include "backend/ResourceProvider.h"

using std::rand;

enum QuState{start, newPool, nextQ, showA, end};

class InterviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InterviewWidget(QWidget *parent = 0);
    ~InterviewWidget();

signals:
    void close();
    void stateChanged(QuState newState);
    void pointsChanged(int delta);

protected slots:
    void openTick();
    void closeTick();
    void changeState(QuState newState);
    void mouseMoved(QMouseEvent * event);
    void mouseReleased(QMouseEvent *event);

protected:

    struct Answere {
        bool isRight;
        int points;
        QString shortT;
        QString longT;
    };

    struct Question {
        QString text;
        Answere answeres[4];
    };

    QuState curState;
    int selected;
    int curHover;
    int ticks;
    int widthBoxes;
    QLabel *bgLbl;
    bool inputActive;
    QTimer timer;
    QImage *leftPart;
    QWidget *content;
    QWidget *reporterBox;
    QWidget *answerBox;
    QRect answereRec[4];
    QLabel *optionsBg[4];
    QLabel *optionsTx[4];
    QLabel *qBox;
    QLabel *aBox;
    QMap<QString, QPixmap> bgs;
    QList<Question> curQuestions;
    QList<QString> unfinishedPacks;
    QList<QString> finishedPacks;

    QRect rect(int x, int y, int w, int h);
    void initOptions();
    void initDialog();
    void loadQuestionPack();
    void showNextQuestion();
    void showAnswere();

};

#endif // INTERVIEWWIDGET_H
