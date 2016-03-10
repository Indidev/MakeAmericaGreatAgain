#include "InterviewWidget.h"

InterviewWidget::InterviewWidget(QWidget *parent) :
    QWidget(parent)
{
    srand (time(NULL));
    curState = start;
    curHover = -1;
    unfinishedPacks = ResourceProvider::qKeys();
    inputActive = false;
    this->setLayout(new QGridLayout);
    this->layout()->setSpacing(0);
    this->layout()->setMargin(0);

    bgLbl = new QLabel;
    LayeredWidget *lw = new LayeredWidget;
    QWidget *bgWidget = lw->addWidget(0);
    bgWidget->setLayout(new QGridLayout);
    bgWidget->layout()->setSpacing(0);
    bgWidget->layout()->setMargin(0);

    content = lw->addWidget(1);

    bgWidget->layout()->addWidget(bgLbl);

    this->layout()->addWidget(lw);


    leftPart = new QImage(987, 1080, QImage::Format_ARGB32);
    leftPart->fill(Qt::transparent);

    //init right bg
    QPainter painter(leftPart);
    painter.drawImage(0, 0, *ResourceProvider::img("news-up"));
    painter.drawImage(0, 124, *ResourceProvider::img("news-left"));
    painter.drawImage(0, 684, *ResourceProvider::img("news-low"));
    painter.end();

    MouseTracking *tracker = new MouseTracking;

    QWidget *mlw = lw->addWidget(10);
    mlw->setLayout(new QGridLayout);
    mlw->layout()->addWidget(tracker);
    mlw->layout()->setSpacing(0);
    mlw->layout()->setMargin(0);

    connect(&timer, SIGNAL(timeout()), this, SLOT(openTick()));
    connect(this, SIGNAL(stateChanged(QuState)), this, SLOT(changeState(QuState)));

    connect(tracker, SIGNAL(mouseMoved(QMouseEvent*)), this, SLOT(mouseMoved(QMouseEvent*)));
    connect(tracker, SIGNAL(mouseReleased(QMouseEvent*)), this, SLOT(mouseReleased(QMouseEvent*)));

    initOptions();
    initDialog();
    this->setMouseTracking(true);
    ticks = 0;
    timer.start(20);
}

InterviewWidget::~InterviewWidget()
{
    delete leftPart;
}

void InterviewWidget::openTick()
{
    ticks += 2;
    if (ticks >= 100) {
        ticks = 100;
        timer.stop();
        inputActive = true;
        disconnect(&timer, SIGNAL(timeout()),this, SLOT(openTick()));
        emit stateChanged(newPool);
    }

    int leftX = ticks * 987 / 100 - 987;
    int rightX = 1920 - ticks * 933 / 100;
    QImage *rightPart = ResourceProvider::img("news-right");

    QImage full(1920, 1080, QImage::Format_ARGB32);
    full.fill(Qt::transparent);
    QPainter painter(&full);
    painter.drawImage(leftX, 0, *leftPart);
    painter.drawImage(rightX, 0, *rightPart);
    painter.end();

    QRect resolution = QApplication::desktop()->screenGeometry();
    bgLbl->setPixmap(QPixmap::fromImage(full).scaled(resolution.size()));

    int w = bgs["right"].size().width();
    for (QLabel *lbl : optionsBg)
        lbl->setGeometry(lbl->x(), lbl->y(), w * ticks / 100, lbl->height());

    reporterBox->setGeometry(reporterBox->x(), reporterBox->y(), widthBoxes * ticks / 100, reporterBox->height());
    answerBox->setGeometry(answerBox->x(), answerBox->y(), widthBoxes * ticks / 100, answerBox->height());

    if (ticks >= 100)
        for(int i = 0; i < 4; i++)
            answereRec[i] = optionsBg[i]->geometry();
}

void InterviewWidget::closeTick()
{
    ticks += 2;
    if (ticks >= 100) {
        ticks = 100;
        timer.stop();
    }

    int leftX = -ticks * 987 / 100;
    int rightX = 987 + ticks * 933 / 100;
    QImage *rightPart = ResourceProvider::img("news-right");

    QImage full(1920, 1080, QImage::Format_ARGB32);
    full.fill(Qt::transparent);
    QPainter painter(&full);
    painter.drawImage(leftX, 0, *leftPart);
    painter.drawImage(rightX, 0, *rightPart);
    painter.end();

    QRect resolution = QApplication::desktop()->screenGeometry();
    bgLbl->setPixmap(QPixmap::fromImage(full).scaled(resolution.size()));

    int w = bgs["right"].size().width();
    for (QLabel *lbl : optionsBg)
        lbl->setGeometry(lbl->geometry().x(),
                         lbl->geometry().y(),
                         w - w * ticks / 100,
                lbl->geometry().height());

    for (QLabel *lbl : optionsTx)
        lbl->setGeometry(lbl->geometry().x(),
                         lbl->geometry().y(),
                         w - w * ticks / 100,
                lbl->geometry().height());

    reporterBox->setGeometry(reporterBox->x(), reporterBox->y(), widthBoxes - widthBoxes * ticks / 100, reporterBox->height());
    answerBox->setGeometry(answerBox->x(), answerBox->y(), widthBoxes - widthBoxes * ticks / 100, answerBox->height());

    if (ticks >= 100)
        emit close();
}

void InterviewWidget::changeState(QuState newState)
{
    //QState old = curState;
    curState = newState;
    switch (newState) {
        case newPool:
            if (unfinishedPacks.isEmpty()) {
                //todo display message before...
                emit stateChanged(end);
            } else {
                loadQuestionPack();
                emit stateChanged(nextQ);
            }
            break;
        case nextQ:
            if (curQuestions.isEmpty())
                emit stateChanged(newPool);
            else {
                showNextQuestion();
            }
            break;
        case showA:
            showAnswere();
            break;
        case end:
            connect(&timer, SIGNAL(timeout()), this, SLOT(closeTick()));
            inputActive = false;
            ticks = 0;
            timer.start();
        break;
        default:
            ;//ignore

    }
}

void InterviewWidget::mouseMoved(QMouseEvent *event)
{
    if (!inputActive)
        return;

    QPoint pos = event->localPos().toPoint();

    if (curState == nextQ) {
        if (curHover >= 0) {
            if (!answereRec[curHover].contains(pos)) {
                optionsBg[curHover]->setPixmap(bgs["def"]);
                curHover = -1;
                aBox->setText("");
            }
        }
        for (int i = 0; i < 4 && curHover < 0; i++) {
            if (answereRec[i].contains(pos)) {
                curHover = i;
                optionsBg[i]->setPixmap(bgs["sel"]);
                aBox->setText(curQuestions[0].answeres[i].longT);
            }
        }
    }
}

void InterviewWidget::mouseReleased(QMouseEvent* event)
{
    if (!inputActive)
        return;

    QPoint pos = event->localPos().toPoint();

    QRect closeB = rect(62, 162, 86, 86);
    if (closeB.contains(pos)) {
        emit stateChanged(end);
        return;
    }

    if (curState == nextQ && curHover >= 0) {
        selected = curHover;
        emit stateChanged(showA);
    } else if (curState == showA) {
        if (rightAnswere)
            emit stateChanged(nextQ);
        else
            emit stateChanged(newPool);
    }
}

QRect InterviewWidget::rect(int x, int y, int w, int h)
{
    QRect resolution = QApplication::desktop()->screenGeometry();

    float facX = (float) resolution.width() / 1920.f;
    float facY = (float) resolution.height() / 1080.f;

    return QRect(x * facX, y * facY, w * facX, h * facY);
}

void InterviewWidget::initOptions()
{

    QSize s = rect(0, 0, 439, 50).size();
    bgs["right"] = QPixmap::fromImage(ResourceProvider::img("right-ans")->scaled(s));
    bgs["sel"] = QPixmap::fromImage(ResourceProvider::img("sel-ans")->scaled(s));
    bgs["def"] = QPixmap::fromImage(ResourceProvider::img("def-ans")->scaled(s));
    bgs["false"] = QPixmap::fromImage(ResourceProvider::img("false-ans")->scaled(s));

    for(int i = 0; i < 4; i++) {
        QLabel *optionBg = new QLabel(content);

        QRect pos = rect(545, 289 + i * 60, 0, 50); //439

        optionBg->setGeometry(pos);
        optionBg->setPixmap(bgs["def"]);
        QLabel *lbltxt = new QLabel(content);
        QRect posT = rect(605, 294 + i* 60, 380, 40);
        lbltxt->setGeometry(posT);
        lbltxt->setStyleSheet("color:white;font-size:" + QString::number(s.width() / 20)+ "pt;");
        lbltxt->setAlignment(Qt::AlignVCenter);

        optionsBg[i] = optionBg;
        optionsTx[i] = lbltxt;
    }
}

void InterviewWidget::initDialog()
{
    reporterBox = new QWidget(content);
    QRect recRep = rect(213, 705, 800, 150);
    widthBoxes = recRep.width();
    recRep.setWidth(0);
    reporterBox->setGeometry(recRep);
    reporterBox->setLayout(new QHBoxLayout);
    reporterBox->setStyleSheet("background-color:rgba(0, 0, 0, 130);");
    QLabel *reporterLbl = new QLabel("Reporter:");
    reporterLbl->setStyleSheet("color:#001d9a;background-color:transparent;font-size:" + QString::number(recRep.height() / 7) + "pt");
    reporterBox->layout()->addWidget(reporterLbl);
    reporterLbl->setAlignment(Qt::AlignTop);
    reporterLbl->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);

    qBox = new QLabel;
    qBox->setStyleSheet("color:white; background-color:transparent; font-size:" + QString::number(widthBoxes / 43) + "pt");
    reporterBox->layout()->addWidget(qBox);
    qBox->setAlignment(Qt::AlignTop);
    qBox->setWordWrap(true);

    answerBox = new QWidget(content);
    QRect recAns = rect(213, 865, 0, 230);
    answerBox->setGeometry(recAns);
    answerBox->setLayout(new QHBoxLayout);
    answerBox->setStyleSheet("background-color:rgba(0, 0, 0, 130);");
    QLabel *yourLbl = new QLabel("You:");
    yourLbl->setStyleSheet("color:#aa0000;background-color:transparent;font-size:" + QString::number(recRep.height() / 7) + "pt");
    answerBox->layout()->addWidget(yourLbl);
    yourLbl->setAlignment(Qt::AlignTop);
    yourLbl->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);

    aBox = new QLabel;
    aBox->setStyleSheet("color:grey; background-color:transparent; font-size:" + QString::number(widthBoxes / 43) + "pt");
    answerBox->layout()->addWidget(aBox);
    aBox->setAlignment(Qt::AlignTop);
    aBox->setWordWrap(true);
}

void InterviewWidget::loadQuestionPack()
{
    QString key = unfinishedPacks[rand() % unfinishedPacks.size()];
    unfinishedPacks.removeAll(key);
    finishedPacks.append(key);

    //load pack
    curQuestions.clear();
    QList<QString> qPack = ResourceProvider::qPack(key);
    for (int i = 0; i < qPack.size(); i++) {
        if (qPack[i].startsWith("Q:")) {
            bool error = false;
            Question q;
            q.text = qPack[i++].remove("Q:").trimmed();
            if ( qPack.size() - i < 4) {
                error = true;
            }
            for (int j = 0; j < 4 && !error; i++, j++) {
                QList<QString> splitted = qPack[i].split(":");
                if (splitted.size() != 4)
                    error = true;
                else {
                    Answere a;
                    a.isRight = splitted[0].trimmed() == "true";
                    a.points = splitted[1].trimmed().toInt();
                    a.shortT = splitted[2].trimmed();
                    a.longT = splitted[3].trimmed();
                    q.answeres[j] = a;
                }
            }

            if (!error) {
                //shuffle Answeres
                for (int j = 0; j < 5; j++) {
                    int r1 = rand() % 4;
                    int r2 = rand() % 4;
                    Answere tmpA = q.answeres[r1];
                    q.answeres[r1] = q.answeres[r2];
                    q.answeres[r2] = tmpA;
                }

                //append to question list
                curQuestions.append(q);
            } else {
                qDebug() << "Error with qPack: " << key << "\nFailed to Load Answeres to: " << q.text;
            }
        }
    }
}

void InterviewWidget::showNextQuestion()
{
    aBox->setStyleSheet("color:grey; background-color:transparent; font-size:" + QString::number(widthBoxes / 43) + "pt");
    //reset answer bgs
    for (QLabel* l : optionsBg)
        l->setPixmap(bgs["def"]);

    //show answeres
    for (int i = 0; i < 4; i++) {
        optionsTx[i]->setText(curQuestions[0].answeres[i].shortT);
    }

    //show question
    qBox->setText(curQuestions[0].text);
    aBox->setText("");
}

void InterviewWidget::showAnswere()
{
    aBox->setStyleSheet("color:white; background-color:transparent; font-size:" + QString::number(widthBoxes / 43) + "pt");
    //solve
    for (int i = 0; i < 4; i++) {
        optionsBg[i]->setPixmap(bgs[curQuestions[0].answeres[i].isRight?"right":"false"]);
    }

    //show selected answere
    aBox->setText(curQuestions[0].answeres[selected].longT);

    int delta = curQuestions[0].answeres[selected].points;

    emit pointsChanged(delta);
    //remove question
    curQuestions.removeFirst();

    rightAnswere = delta >= 0;
}
