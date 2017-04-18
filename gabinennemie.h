#ifndef GABINENNEMIE_H
#define GABINENNEMIE_H

#include <QtWidgets>
#include <QGraphicsSvgItem>
#include <QList>
#include "mainwindow.h"

class GabinEnnemie
{
public:
    GabinEnnemie(QGraphicsScene *sceneGabin);
    void calculatepos(void);
    int isGameover(int spritepos, bool hit);
    ~GabinEnnemie();

    QRect screenGeometry;
    QGraphicsPixmapItem* ennemie;
    QPointF pos;
    int posH;//position en hauteur de 0 a 3

    QList<QString> ennemieRessource;
};

#endif // GABINENNEMIE_H
