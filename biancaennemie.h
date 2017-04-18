#ifndef BIANCAENNEMIE_H
#define BIANCAENNEMIE_H

#include <QtWidgets>
#include "mainwindow.h"

class BiancaEnnemie
{
public:
    BiancaEnnemie(MainWindow* mainW, QGraphicsScene *sceneBianca);

    QList<QString> ennemieRessource;
    QGraphicsPixmapItem* ennemie;
    //QGraphicsRectItem* ennemie;
    int pos;
    bool isBianca = false;

private:
    QRect screenGeometry;
    MainWindow* windows;
};

#endif // BIANCAENNEMIE_H
