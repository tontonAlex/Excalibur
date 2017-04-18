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
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    bool GabinGameSelected = false;
    bool BiancaGameSelected = false;
    ~Excalibur();

private:
    MainWindow* windows;
    QImage chateau;
    QImage paysage;
    QBrush background;
    void keyPressEvent(QKeyEvent *event) override;

};

#endif // EXCALIBUR_H
