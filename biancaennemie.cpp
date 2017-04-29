#include "biancaennemie.h"

BiancaEnnemie::BiancaEnnemie(MainWindow* mainW, QGraphicsScene *sceneBianca)
{
    screenGeometry = QApplication::desktop()->availableGeometry();
    windows = mainW;

    ennemieRessource << ":/tetebianca2/tetebiancatwo"
                     << ":/tetegabin/tetegabin"
//                     << ":/alex/alex"
                     << ":/jerome/jerome"
//                     << ":/brice/brice"
//                     << ":/carlos/carlos"
//                     << ":/kiwi/kiwi"
                     << ":/bernard/bernard"
                     << ":/radhia/radhia";
//                     << ":/tamara/tamara";
    int TeteIdx = qrand()%5;

    ennemie = sceneBianca->addPixmap(QPixmap(ennemieRessource.at(TeteIdx)));
    if (TeteIdx == 0)
    {
        isBianca = true;
    }
    else {
        isBianca = false;
    }

    pos = qrand()%5;
    /*ennemie = new QGraphicsRectItem(windows->trous.at(pos).x(),
                                  windows->trous.at(pos).y(),
                                  50, 50);
    ennemie->setBrush(QBrush(QColor(0x52, 0xc6, 0x78)));*/

    ennemie->setTransform(QTransform().scale(0.2*(qreal)((qreal)screenGeometry.height()/(qreal)768),
                                             0.2*(qreal)((qreal)screenGeometry.height()/(qreal)768)));
    ennemie->setPos(windows->trous.at(pos).x()+10,
                    windows->trous.at(pos).y()-25);
}
