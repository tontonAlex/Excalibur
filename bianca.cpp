#include "bianca.h"
#include "mainwindow.h"

#include <QtWidgets>

Bianca::Bianca(QWidget *parent, MainWindow* mainW, QCursor OrigFleau, QCursor FleauHaut, QCursor FleauBas)
    : QGraphicsView(parent)
{
    windows = mainW;
    fleau = OrigFleau;
    fleau1 = FleauHaut;
    fleau2 = FleauBas;

    screenGeometry = QApplication::desktop()->availableGeometry();
    QLinearGradient linearGrad(QPointF(screenGeometry.width()/2+30,
                                       screenGeometry.height()/2+30),
                               QPointF(-screenGeometry.width()/2+30,
                                       -screenGeometry.height()/2+30));
        linearGrad.setColorAt(0, QColor::fromRgbF(0.8, 0.7, 0.7, 1));
        linearGrad.setColorAt(0.5, QColor::fromRgb(0xfff19696));
        linearGrad.setColorAt(1, QColor::fromRgbF(0.8, 0.7, 0.7, 1));
    background = QBrush(linearGrad);

    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
}

void Bianca::drawBackground(QPainter *painter, const QRectF &rect)
{
    //painter->begin(this);
    painter->fillRect(rect, background);
    //painter->end();
}

void Bianca::keyPressEvent(QKeyEvent *event)
{
    switch ( event->key() ) {
            case Qt::Key_Up:
                qDebug("GameBiancaUp");
                break;
            case Qt::Key_Down:
                qDebug("GameBiancaDown");
                break;
            case Qt::Key_X:
                QApplication::exit();
                qDebug("GameBiancaexit");
                break;
            case Qt::Key_Escape:
                qDebug("GameBiancaEsc");
                windows->removeBiancaGame();
                windows->DisplaySelectScreen();
                break;
            case Qt::Key_Enter:
            case Qt::Key_Space:

                QGraphicsView::keyPressEvent(event);
                break;
            default:

                QGraphicsView::keyPressEvent(event);
                break;
        }
}

//Click event = MousePress->MouseRelease
void Bianca::mouseReleaseEvent ( QMouseEvent * event )
{
  if(event->button() == Qt::LeftButton)
  {
    windows->setCursor(fleau);
    isReleaseFlag = true;
  }
}

void Bianca::mousePressEvent (QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton)
    {
        windows->setCursor(fleau1);
        windows->hitPos(event->globalPos());
        isReleaseFlag = false;
        QTimer::singleShot(100, this, SLOT(biancaShoot()));
    }
}

void Bianca::biancaShoot(void)
{
  if(!isReleaseFlag)
  {
      windows->setCursor(fleau2);
  }
  else{
     windows->setCursor(fleau);
  }
}

Bianca::~Bianca()
{
}

