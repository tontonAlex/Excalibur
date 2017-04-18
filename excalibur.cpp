#include "excalibur.h"
#include "mainwindow.h"

#include <QtWidgets>


Excalibur::Excalibur(QWidget *parent, MainWindow* mainW)
    : QGraphicsView(parent)
{
    windows = mainW;
    chateau = QImage(":/chateau/chateau");
    paysage = QImage(":/paysage/paysage");
    background = QBrush(QColor(0x52, 0xc6, 0x78));
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
}

void Excalibur::drawBackground(QPainter *painter, const QRectF &rect)
{
    QRect screenGeometry = QApplication::desktop()->availableGeometry();
    //painter->begin(this);
    painter->fillRect(rect, background);
    painter->setBrushOrigin(screenGeometry.width()-chateau.width()-30,
                            (screenGeometry.height()-chateau.height())/2-35);
    painter->fillRect(screenGeometry.width()-chateau.width()-30,
                      (screenGeometry.height()-chateau.height())/2-35,
                      chateau.width(), chateau.height(), chateau);
    painter->setBrushOrigin(60,
                            (screenGeometry.height()-paysage.height())/2-35);
    painter->fillRect(60,
                      (screenGeometry.height()-paysage.height())/2-35,
                      paysage.width(), paysage.height(), paysage);

    //painter->end();
    //painter->restore();
}

void Excalibur::keyPressEvent(QKeyEvent *event)
{
    int down = 0;
    int up = 0;
    switch ( event->key() ) {
            case Qt::Key_Up:
                qDebug("Up");
                if (up == 0)
                {
                    //Bianca Selected
                    windows->setGabinContraste();
                    up = 1;
                    BiancaGameSelected = true;
                    GabinGameSelected = false;
                }
                break;
            case Qt::Key_Down:
                qDebug("Down");
                if (down == 0)
                {
                    //Gabin selected
                    windows->setBiancaContraste();
                    down = 1;
                    BiancaGameSelected = false;
                    GabinGameSelected = true;
                }
                break;
            case Qt::Key_X:
                QApplication::exit();
                qDebug("exit");
                break;
            case Qt::Key_Enter:
            case Qt::Key_Return:
            case Qt::Key_Space:
                if (BiancaGameSelected == true) {
                    windows->displayBiancaName();
                    QTimer::singleShot(2500, windows, SLOT(displayBiancaGame()));
                }
                if (GabinGameSelected == true) {
                    windows->displayGabinName();
                    windows->setSpriteGabin(0);
                    QTimer::singleShot(2500, windows, SLOT(displayGabinGame()));
                }
                break;
            default:
                BiancaGameSelected = false;
                GabinGameSelected = false;
                windows->setEnclume();
                QGraphicsView::keyPressEvent(event);
                break;
        }
}

Excalibur::~Excalibur()
{
}
