#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QStatusBar>
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

#include "frontend/LayeredWidget.h"

namespace Ui {
class MainFrame;
}

class MainFrame : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainFrame();
    ~MainFrame();

    static void setContent(QWidget *widget);
    static void setBg(QImage* img);
    static void setTrump(QImage* trump);
    static void removeTrump();

protected:
    static MainFrame* self;
    Ui::MainFrame *ui;
    LayeredWidget *layeredWidget;
    QWidget *bgLayer;
    QWidget *contentLayer;
    QWidget *trumpLayer;
    QWidget *curContent;
    QWidget *curTrump;
    QLabel *bgLabel;
    QSize resolution;

    void setWidget(QWidget *layer, QWidget **displayWidget, QWidget *widget, bool mouseTransparent = false);
    void init();
};

#endif // MAINFRAME_H
