#include "gabin.h"
#include "mainwindow.h"

#include <QtWidgets>

Gabin::Gabin(QWidget *parent, MainWindow* mainW)
    : QGraphicsView(parent)
{
    windows = mainW;
    screenGeometry = QApplication::desktop()->availableGeometry();
    //QRadialGradient radialGrad(QPointF(screenGeometry.width()/2+30,
    //                                   screenGeometry.height()/2+30), 500);
    QLinearGradient linearGrad(QPointF(screenGeometry.width()/2+30,
                                       screenGeometry.height()/2+30),
                               QPointF(-screenGeometry.width()/2+30,
                                       -screenGeometry.height()/2+30));
        linearGrad.setColorAt(0, QColor::fromRgbF(0.7, 0.7, 0.8, 1));
        linearGrad.setColorAt(0.5, QColor::fromRgbF(0.2, 0.5, 0.8, 1));
        linearGrad.setColorAt(1, QColor::fromRgbF(0.7, 0.7, 0.8, 1));
    background = QBrush(linearGrad);

    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
}

void Gabin::drawBackground(QPainter *painter, const QRectF &rect)
{
    //painter->begin(this);
    painter->fillRect(rect, background);
    //painter->end();
}

void Gabin::keyPressEvent(QKeyEvent *event)
{
    switch ( event->key() ) {
            case Qt::Key_Up:
                if (pos > 0)
                {
                   pos--;
                   windows->setSpriteGabin(pos);
                }
                qDebug("GameGabinUp");
                break;
            case Qt::Key_Down:
                if (pos < 3)
                {
                    pos++;
                    windows->setSpriteGabin(pos);
                }
                qDebug("GameGabinDown");
                break;
            case Qt::Key_X:
                QApplication::exit();
                qDebug("GameGabinexit");
                break;
            case Qt::Key_Escape:
                qDebug("GameGabinEsc");
                pos = 0;
                windows->gameOverGabin();
                break;
            case Qt::Key_Enter:
            case Qt::Key_Space:
                windows->setSpriteHitGabin(pos);
                hit = true;
                //QGraphicsView::keyPressEvent(event);
                break;
            default:

                QGraphicsView::keyPressEvent(event);
                break;
        }
}

void Gabin::keyReleaseEvent(QKeyEvent *event)
{
   windows->setSpriteGabin(pos);
   hit = false;
}

Gabin::~Gabin()
{
}
