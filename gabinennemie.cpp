#include "gabinennemie.h"

GabinEnnemie::GabinEnnemie(QGraphicsScene* sceneGabin)
{
    screenGeometry = QApplication::desktop()->availableGeometry();

    posH = qrand()%4;

    /*ennemie = new QGraphicsRectItem(screenGeometry.width()-WindowMargin,
                                  posH*screenGeometry.height()/4,
                                  50, 50);
    ennemie->setBrush(QBrush(QColor(0x52, 0xc6, 0x78)));
    */

    ennemieRessource << ":/teteBianca/teteBianca"
//                     << ":/alex/alex"
//                     << ":/jerome/jerome"
//                     << ":/brice/brice"
//                     << ":/carlos/carlos"
//                     << ":/kiwi/kiwi"
//                     << ":/bernard/bernard"
//                     << ":/radhia/radhia"
//                     << ":/tamara/tamara"
                     << ":/dragon1/dragon1"
                     << ":/dragon2/dragon2"
                     << ":/dragon3/dragon3"
                     << ":/dragon4/dragon4"
                     << ":/grenouille/grenouille"
                     << ":/poulet/poulet"
                     << ":/doudou/doudou"
                     << ":/ours/ours"
                     << ":/tamara/tamara2";

    ennemie = sceneGabin->addPixmap(QPixmap(ennemieRessource.at(qrand()%10)));

    ennemie->setTransform(QTransform().scale(0.2, 0.2));
    ennemie->setPos(screenGeometry.width()-WindowMargin,
                    posH*screenGeometry.height()/4);
}


void GabinEnnemie::calculatepos(void)
{
    pos = ennemie->pos();

    pos.setX(pos.x()-5);
    ennemie->setPos(pos);
}

int GabinEnnemie::isGameover(int spritepos, bool hit)
{
   pos = ennemie->pos();
   if ((spritepos == posH)&&hit)
   {
       /*if ((pos.x() > -screenGeometry.width()-WindowMargin+150) &&
           (pos.x() < -screenGeometry.width()-WindowMargin+200))*/
       if((pos.x() > 80) && (pos.x() < 150))
       {
         return 1;//ennemie elliminé
       }
   }
   //if (pos.x() < -screenGeometry.width()-WindowMargin+120)
   if (pos.x() < 50)
   {
       return 2;//game over
   }

   return 0;
}

GabinEnnemie::~GabinEnnemie()
{
}
