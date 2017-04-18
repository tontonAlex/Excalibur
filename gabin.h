#ifndef GABIN_H
#define GABIN_H

#include "mainwindow.h"
#include <QtWidgets>

class MainWindow;

class Gabin : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Gabin(QWidget *parent =0, MainWindow* mainW=0);
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    ~Gabin();

    int pos = 0;
    bool hit = false;

private:
    MainWindow* windows;
    QBrush background;
    QRect screenGeometry;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // GABIN_H
