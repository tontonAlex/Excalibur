#ifndef BIANCA_H
#define BIANCA_H

#include "mainwindow.h"
#include <QtWidgets>

class MainWindow;

class Bianca : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Bianca(QWidget *parent =0, MainWindow* mainW=0,
                    QCursor OrigFleau=Qt::OpenHandCursor,
                    QCursor FleauHaut=Qt::OpenHandCursor,
                    QCursor FleauBas=Qt::OpenHandCursor);
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    ~Bianca();

private:
    MainWindow* windows;
    QRect screenGeometry;
    QBrush background;
    QCursor fleau;
    QCursor fleau1;
    QCursor fleau2;
    bool isReleaseFlag = false;

    void keyPressEvent(QKeyEvent *event) override;
    void mouseReleaseEvent ( QMouseEvent * event ) override;
    void mousePressEvent (QMouseEvent * event) override;

private slots:
    void biancaShoot();
};

#endif // BIANCA_H
