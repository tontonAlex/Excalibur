#ifndef EXCALIBUR_H
#define EXCALIBUR_H

#include "mainwindow.h"
#include <QtWidgets>

class MainWindow;

class Excalibur : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Excalibur(QWidget *parent =0, MainWindow* mainW=0);
    void grabGestures(const QList<Qt::GestureType> &gestures);
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    bool GabinGameSelected = false;
    bool BiancaGameSelected = false;
    ~Excalibur();

private:
    MainWindow* windows;
    QPixmap chateau;
    QPixmap paysage;
    QBrush background;
    void keyPressEvent(QKeyEvent *event) override;
//    bool gestureEvent(QGestureEvent *event);
//    void panTriggered(QPanGesture*);
//    void pinchTriggered(QPinchGesture*);
//    void swipeTriggered(QSwipeGesture*);
//    void tapTriggered();

    qreal firstPos;
    qreal updatepos;
    int filtreBianca = 0;
    int filtreGabin = 0;

protected:
    bool event(QEvent *event) override;

};

#endif // EXCALIBUR_H
