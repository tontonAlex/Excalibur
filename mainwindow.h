#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "excalibur.h"
#include "gabin.h"
#include "gabinennemie.h"
#include "bianca.h"
#include "biancaennemie.h"
#include <QtWidgets>
#include <QApplication>

class Excalibur;
class Gabin;
class Bianca;
class GabinEnnemie;
class BiancaEnnemie;

#define WindowMargin 39
#define nbEnnemieMax 10

#ifndef ANDROID
    #define ANDROID
#endif

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    void setGabinContraste(void);
    void setBiancaContraste(void);
    void setEnclume(void);
    void DisplaySelectScreen(void);
    void setSelectScreen(void);
    void removeExcaliburSelect(void);
    void removeGabinGame(void);
    void removeBiancaGame(void);
    void displayBiancaName(void){nomBianca->setVisible(true);}
    void displayGabinName(void){nomGabin->setVisible(true);}
    void grabGestures(const QList<Qt::GestureType> &gestures);

    void setGabinScreen(void);
    void createSpriteGabin(QGraphicsPixmapItem* sprite1, QGraphicsPixmapItem* sprite2, int pos);
    void setSpriteGabin(int pos);
    void setSpriteHitGabin(int pos);

    void setBiancaScreen(void);
    void hitPos(QPoint point);

    ~MainWindow();

public slots:
    void animateFlechesSelect();
    void animateEnnemies();
    void displayGabinGame();
    void displayBiancaGame();
    void popEnnemie();
    void gameOverGabin();
    void gameOverBianca();
    void popAie();

private:
    QRect screenGeometry;
    QGridLayout *layout;
    QPainter painter;
    enum {
        EXCALIBURSCREEN,
        GABINSCREEN,
        BIANCASCREEN
    };
    int CurrentScreen = EXCALIBURSCREEN;

    /****** excalibur select screen ******/
    Excalibur* excalibur;//graphics view
    QGraphicsScene* scene;
    QGraphicsPixmapItem *ExcaliburFull;
    QGraphicsPixmapItem *ExcaliburBianca;
    QGraphicsPixmapItem *ExcaliburGabin;

    QGraphicsItem *flecheHaut;
    QGraphicsItem *flecheBas;
    int x = 0;
    int taille = 0;
    QTimer *timerFlechesSelect;//timer animation fleches

    QGraphicsItem* nomBianca;//texte
    QGraphicsItem* nomGabin;//texte
    QGraphicsItem *selectPlayer;//texte
    /************************************/

    /************ Gabin Game ************/
    Gabin* gabinGame;//graphics view
    QGraphicsScene* sceneGabin;

    //sprites de gabin chevalier
    QGraphicsPixmapItem* spriteGabin1pos1;
    QGraphicsPixmapItem* spriteGabin1pos2;
    QGraphicsPixmapItem* spriteGabin1pos3;
    QGraphicsPixmapItem* spriteGabin1pos4;
    QGraphicsPixmapItem* spriteGabin2pos1;
    QGraphicsPixmapItem* spriteGabin2pos2;
    QGraphicsPixmapItem* spriteGabin2pos3;
    QGraphicsPixmapItem* spriteGabin2pos4;
    QGraphicsItem* gameOverGabinTxt;//texte
    QGraphicsItem *flecheHautGabin;
    QGraphicsItem *flecheBasGabin;
    QGraphicsItem *espaceCommand;
    QGraphicsSvgItem* nuage;
    QGraphicsPixmapItem* ennemieTab[nbEnnemieMax];


    QTimer* timerEnnemiesRefreshDisplay;
    QList<GabinEnnemie*> ListEnnemies;
    int DelayEntreEnnemie = 0;
    int TimerDisplayCommand = 0;
    int posGabin = 0;

    /************************************/

    /************ Bianca Game ***********/
    Bianca* biancaGame;//graphics view
    QGraphicsScene* sceneBianca;

    QCursor fleau;
    QCursor fleau1;
    QCursor fleau2;
    QGraphicsItem *cube;
    QGraphicsEllipseItem *trouCentre;
    QGraphicsEllipseItem *trouHG;
    QGraphicsEllipseItem *trouHD;
    QGraphicsEllipseItem *trouBG;
    QGraphicsEllipseItem *trouBD;
    QList<QGraphicsSvgItem*> aie;
    int aieIdx = 0;
    QGraphicsSvgItem* souris;
    int timerDisplaySourisCommand = 0;
    QGraphicsSvgItem* pasmoi;
    QGraphicsItem* gameOverBiancaTxt;//texte

    BiancaEnnemie* EnnemieBianca;
    int DelayEntreEnnemieBianca = 0;
    bool ennemieOn = false;
    bool hitted = false;
public:
    QList<QRectF> trous;
    /************************************/

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // MAINWINDOW_H
