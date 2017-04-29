#include "excalibur.h"
#include "mainwindow.h"

#include <QtWidgets>


Excalibur::Excalibur(QWidget *parent, MainWindow* mainW)
    : QGraphicsView(parent)
{
    QRect screenGeometry = QApplication::desktop()->availableGeometry();
    windows = mainW;
    chateau = QPixmap(":/chateau/chateau");
    chateau = chateau.transformed(QTransform().scale((qreal)((qreal)screenGeometry.height()/(qreal)768),
                                             (qreal)((qreal)screenGeometry.height()/(qreal)768)));
    paysage = QPixmap(":/paysage/paysage");
    paysage = paysage.transformed(QTransform().scale((qreal)((qreal)screenGeometry.height()/(qreal)768),
                                             (qreal)((qreal)screenGeometry.height()/(qreal)768)));
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

//bool Excalibur::gestureEvent(QGestureEvent *event)
//{
//    qDebug() << "gestureEvent():" << event;
//        //if (QGesture *tap = event->gesture(Qt::TapGesture))
//        //    tapTriggered();
//        if (QGesture *swipe = event->gesture(Qt::SwipeGesture))
//            swipeTriggered(static_cast<QSwipeGesture *>(swipe));
//        else if (QGesture *pan = event->gesture(Qt::PanGesture))
//            panTriggered(static_cast<QPanGesture *>(pan));
//        if (QGesture *pinch = event->gesture(Qt::PinchGesture))
//            pinchTriggered(static_cast<QPinchGesture *>(pinch));
//        return true;
//}

bool Excalibur::event(QEvent *event)
{

//    if (event->type() == QEvent::Gesture)
//            return gestureEvent(static_cast<QGestureEvent*>(event));
//        return QGraphicsView::event(event);

    switch (event->type()) {
        case QEvent::TouchBegin:
        {
            QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
            QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
            const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();
            firstPos = touchPoint0.pos().y();
            break;
        }
        case QEvent::TouchEnd:
        case QEvent::TouchUpdate:
        {
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
        const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();
            updatepos = touchPoint0.pos().y();
            if ((firstPos - updatepos) > 0)
            {
                //Bianca Selected
                windows->setGabinContraste();
                BiancaGameSelected = true;
                GabinGameSelected = false;
            }
            else if ((firstPos - updatepos) < 0)
            {
                //Gabin selected
                windows->setBiancaContraste();
                BiancaGameSelected = false;
                GabinGameSelected = true;
            }
            else {
                if (BiancaGameSelected == true) {
                    filtreBianca++;
                    if (filtreBianca == 3)
                    {
                        windows->displayBiancaName();
                        QTimer::singleShot(2500, windows, SLOT(displayBiancaGame()));
                        filtreBianca = 0;
                    }
                }
                if (GabinGameSelected == true) {
                    filtreGabin++;
                    if (filtreGabin == 3)
                    {
                        windows->displayGabinName();
                        windows->setSpriteGabin(0);
                        QTimer::singleShot(2500, windows, SLOT(displayGabinGame()));
                        filtreGabin = 0;
                    }
                }
            }
            return true;
        }
        default:
        {
            return QGraphicsView::event(event);
        }
    }
     //return QGraphicsView::event(event);
}

//void Excalibur::panTriggered(QPanGesture *gesture)
//{
//#ifndef QT_NO_CURSOR
//    switch (gesture->state()) {
//        case Qt::GestureStarted:
//        case Qt::GestureUpdated:
//            setCursor(Qt::SizeAllCursor);
//            break;
//        default:
//            setCursor(Qt::ArrowCursor);
//    }
//#endif
//    QPointF delta = gesture->delta();
//    qDebug() << "panTriggered():" << gesture;
//    //horizontalOffset += delta.x();
//    //verticalOffset += delta.y();
//    update();
//}

//void Excalibur::pinchTriggered(QPinchGesture *gesture)
//{
//    QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();
//    if (changeFlags & QPinchGesture::RotationAngleChanged) {
//        qreal rotationDelta = gesture->rotationAngle() - gesture->lastRotationAngle();
//        //rotationAngle += rotationDelta;
//        qDebug() << "pinchTriggered(): rotate by" << "test";
//           // rotationDelta << "->" << rotationAngle;
//    }
//    if (changeFlags & QPinchGesture::ScaleFactorChanged) {
//        //currentStepScaleFactor = gesture->totalScaleFactor();
//        qDebug() << "pinchTriggered(): zoom by" << "test";
//           // gesture->scaleFactor() << "->" << currentStepScaleFactor;
//    }
//    if (gesture->state() == Qt::GestureFinished) {
//        //scaleFactor *= currentStepScaleFactor;
//        //currentStepScaleFactor = 1;
//    }
//    update();
//}

//void Excalibur::swipeTriggered(QSwipeGesture *gesture)
//{
//    if (gesture->state() == Qt::GestureFinished) {
//        if (gesture->horizontalDirection() == QSwipeGesture::Left
//            || gesture->verticalDirection() == QSwipeGesture::Up) {
//            qDebug() << "swipeTriggered(): swipe to previous";
//            //goPrevImage();
//        } else {
//            qDebug() << "swipeTriggered(): swipe to next";
//            //goNextImage();
//        }
//        update();
//    }
//}

//void Excalibur::tapTriggered()
//{
//    qDebug() << "tap";
//}

void Excalibur::grabGestures(const QList<Qt::GestureType> &gestures)
{
    //! [enable gestures]
    foreach (Qt::GestureType gesture, gestures)
        grabGesture(gesture);
    //! [enable gestures]
}

Excalibur::~Excalibur()
{
}
