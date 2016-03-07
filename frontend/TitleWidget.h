#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class TitleWidget;
}

class TitleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TitleWidget(QWidget *parent = 0);
    ~TitleWidget();

private:
    Ui::TitleWidget *ui;
    QTimer timer;

signals:
    void mouseClicked();

protected:
    void mouseReleaseEvent(QMouseEvent*);

protected slots:
    void tick();
};

#endif // TITLEWIDGET_H
