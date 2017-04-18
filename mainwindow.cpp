#include "mainwindow.h"
#include "excalibur.h"
#include "gabin.h"
#include "bianca.h"
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QGraphicsView>
#include <QDesktopWidget>
#include <qDebug>
#include <QGridLayout>

MainWindow::MainWindow()
{
    excalibur = new Excalibur(0, this);
    gabinGame = new Gabin(0, this);

    QPixmap fleauPix = QPixmap(":/fleau/fleau1");
    fleauPix.setMask(QBitmap(":/fleau/fleau1map"));
    fleau = QCursor(fleauPix);
    QPixmap fleau1Pix = QPixmap(":/fleau/fleau2");
    fleau1Pix.setMask(QBitmap(":/fleau/fleau2map"));
    fleau1 = QCursor(fleau1Pix);
    QPixmap fleau2Pix = QPixmap(":/fleau/fleau3");
    fleau2Pix.setMask(QBitmap(":/fleau/fleau3map"));
    fleau2 = QCursor(fleau2Pix);

    biancaGame = new Bianca(0, this, fleau, fleau1, fleau2);

    // seed pour une vrai fonction random
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    setWindowTitle("Excalibur");
    setWindowIcon(QIcon(":/chateau/chateau"));
    screenGeometry = QApplication::desktop()->availableGeometry();
    this->resize(screenGeometry.width(), screenGeometry.height());
    layout = new QGridLayout;

    this->setSelectScreen();
    this->setGabinScreen();
    this->setBiancaScreen();
    this->DisplaySelectScreen();
    //this->displayGabinGame();
}

void MainWindow::setGabinScreen(void)
{
    sceneGabin = new QGraphicsScene(this);

    spriteGabin1pos1 = sceneGabin->addPixmap(QPixmap(":/spriteGabin1/spriteGabin1"));
    spriteGabin1pos2 = sceneGabin->addPixmap(QPixmap(":/spriteGabin1/spriteGabin1"));
    spriteGabin1pos3 = sceneGabin->addPixmap(QPixmap(":/spriteGabin1/spriteGabin1"));
    spriteGabin1pos4 = sceneGabin->addPixmap(QPixmap(":/spriteGabin1/spriteGabin1"));

    spriteGabin2pos1 = sceneGabin->addPixmap(QPixmap(":/spriteGabin2/spriteGabin2"));
    spriteGabin2pos2 = sceneGabin->addPixmap(QPixmap(":/spriteGabin2/spriteGabin2"));
    spriteGabin2pos3 = sceneGabin->addPixmap(QPixmap(":/spriteGabin2/spriteGabin2"));
    spriteGabin2pos4 = sceneGabin->addPixmap(QPixmap(":/spriteGabin2/spriteGabin2"));
    //taille originale 2414*2242
    //screenGeometry= 1366*768
    createSpriteGabin(spriteGabin1pos1, spriteGabin2pos1, 0);
    createSpriteGabin(spriteGabin1pos2, spriteGabin2pos2, 1);
    createSpriteGabin(spriteGabin1pos3, spriteGabin2pos3, 2);
    createSpriteGabin(spriteGabin1pos4, spriteGabin2pos4, 3);

    flecheHautGabin = new QGraphicsSvgItem(":/select/flechehaut");
    flecheBasGabin = new QGraphicsSvgItem(":/select/flechebas");
    espaceCommand = new QGraphicsSvgItem(":/espace/espace");
    nuage = new QGraphicsSvgItem(":/nuage/nuage");

    gameOverGabinTxt = new QGraphicsSvgItem(":/gameover/gameover");
    gameOverGabinTxt->setPos((screenGeometry.width()-7*WindowMargin)/2,
                     (screenGeometry.height()-3*WindowMargin)/2);
    sceneGabin->addItem(gameOverGabinTxt);
    gameOverGabinTxt->setVisible(false);

    flecheHautGabin->setPos((screenGeometry.width()-8*WindowMargin)/2, 180);
    flecheBasGabin->setPos((screenGeometry.width()-8*WindowMargin)/2+2, 295);
    espaceCommand->setPos((screenGeometry.width()+8*WindowMargin)/2, 242);
    sceneGabin->addItem(flecheHautGabin);
    sceneGabin->addItem(flecheBasGabin);
    sceneGabin->addItem(espaceCommand);
    espaceCommand->setVisible(false);
    flecheHautGabin->setVisible(false);
    flecheBasGabin->setVisible(false);

    sceneGabin->addItem(nuage);
    nuage->setVisible(false);

    sceneGabin->setSceneRect(0,0,screenGeometry.width()-WindowMargin,
                             screenGeometry.height()-WindowMargin);

    gabinGame->setScene(sceneGabin);

    timerEnnemiesRefreshDisplay = new QTimer(this);
    connect(timerEnnemiesRefreshDisplay, SIGNAL(timeout()), this, SLOT(animateEnnemies()));
}

void MainWindow::setBiancaScreen(void)
{
    sceneBianca = new QGraphicsScene(this);
    biancaGame->setScene(sceneBianca);

    //QPainter painter;
    biancaGame->drawBackground(&painter, screenGeometry);
    biancaGame->setCacheMode(QGraphicsView::CacheBackground);
    biancaGame->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //biancaGame->setDragMode(QGraphicsView::ScrollHandDrag);

    cube = new QGraphicsSvgItem(":/cube/cube");
    sceneBianca->addItem(cube);
    cube->setPos((qreal)(screenGeometry.width()-cube->boundingRect().width())/2,
                  (qreal)screenGeometry.height()/14.56);

    trous << QRectF((qreal)(screenGeometry.width())/2-30,
                          (qreal)(screenGeometry.height())/2-(qreal)(screenGeometry.height()/2.8)+160,/*-100*/
                          110, 85);
    trous <<  QRectF((qreal)(screenGeometry.width())/2-140,
                   (qreal)(screenGeometry.height())/2-(qreal)(screenGeometry.height()/2.8),/*260*/
                   110, 85);
    trous << QRectF((qreal)(screenGeometry.width())/2+270,
                   (qreal)(screenGeometry.height())/2-(qreal)(screenGeometry.height()/2.8),/*260*/
                   110, 85);
    trous << QRectF((qreal)(screenGeometry.width())/2-360,
                   (qreal)(screenGeometry.height())/2-(qreal)(screenGeometry.height()/2.8)+300,/*+40*/
                   110, 85);
    trous << QRectF((qreal)(screenGeometry.width())/2+140,
                   (qreal)(screenGeometry.height())/2-(qreal)(screenGeometry.height()/2.8)+300,/*+40*/
                   110, 85);

    trouCentre = new QGraphicsEllipseItem(trous.at(0));
    trouCentre->setBrush(Qt::black);
    sceneBianca->addItem(trouCentre);

    trouHG = new QGraphicsEllipseItem(trous.at(1));
    trouHG->setBrush(Qt::black);
    sceneBianca->addItem(trouHG);

    trouHD = new QGraphicsEllipseItem(trous.at(2));
    trouHD->setBrush(Qt::black);
    sceneBianca->addItem(trouHD);

    trouBG = new QGraphicsEllipseItem(trous.at(3));
    trouBG->setBrush(Qt::black);
    sceneBianca->addItem(trouBG);

    trouBD = new QGraphicsEllipseItem(trous.at(4));
    trouBD->setBrush(Qt::black);
    sceneBianca->addItem(trouBD);

    aie << new QGraphicsSvgItem(":/aie/aie")
        << new QGraphicsSvgItem(":/arrete/arrete")
        << new QGraphicsSvgItem(":/drole/drole");

    sceneBianca->addItem(aie.at(0));
    sceneBianca->addItem(aie.at(1));
    sceneBianca->addItem(aie.at(2));
    aie.at(0)->setVisible(false);
    aie.at(1)->setVisible(false);
    aie.at(2)->setVisible(false);

    gameOverBiancaTxt = new QGraphicsSvgItem(":/gameover/gameover");
    gameOverBiancaTxt->setPos((screenGeometry.width()-5*WindowMargin)/2,
                     (screenGeometry.height()-8*WindowMargin)/2);
    sceneBianca->addItem(gameOverBiancaTxt);
    gameOverBiancaTxt->setVisible(false);

    souris = new QGraphicsSvgItem(":/souris/souris");
    souris->setPos(50,50);
    sceneBianca->addItem(souris);

    pasmoi = new QGraphicsSvgItem(":/pasmoi/pasmoi");
    sceneBianca->addItem(pasmoi);
    pasmoi->setVisible(false);
}

void MainWindow::setSelectScreen(void)
{
    scene = new QGraphicsScene(this);


    ExcaliburFull = scene->addPixmap(QPixmap(":/excalibur/excaliburFull"));

    ExcaliburFull->setPos(screenGeometry.width()-463,
                          (screenGeometry.height()-QImage(":/chateau/chateau").height())/2+26);
                          //90.0);
    ExcaliburFull->setTransform(QTransform().scale(0.2, 0.2));
    ExcaliburFull->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    ExcaliburFull->setVisible(true);

    ExcaliburBianca = scene->addPixmap(QPixmap(":/excalibur/excaliburBiancaContraste"));
    ExcaliburBianca->setPos(screenGeometry.width()-453,
                           (screenGeometry.height()-QImage(":/chateau/chateau").height())/2+32);
                            //96.0);
    ExcaliburBianca->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    ExcaliburBianca->setTransform(QTransform().scale(0.2, 0.2));
    ExcaliburBianca->setVisible(false);

    ExcaliburGabin = scene->addPixmap(QPixmap(":/excalibur/excaliburGabinContraste"));
    ExcaliburGabin->setPos(screenGeometry.width()-398,
                          (screenGeometry.height()-QImage(":/chateau/chateau").height())/2+172);
                           //236.0);
    ExcaliburGabin->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    ExcaliburGabin->setTransform(QTransform().scale(0.2, 0.2));
    ExcaliburGabin->setVisible(false);

    selectPlayer = new QGraphicsSvgItem(":/select/select");
    flecheHaut = new QGraphicsSvgItem(":/select/flechehaut");
    flecheBas = new QGraphicsSvgItem(":/select/flechebas");
    selectPlayer->setPos(100, 30);
    flecheHaut->setPos((screenGeometry.width()-4*WindowMargin)/2, 180);
    flecheBas->setPos((screenGeometry.width()-4*WindowMargin)/2+2, 295);
    scene->addItem(selectPlayer);
    scene->addItem(flecheHaut);
    scene->addItem(flecheBas);
    selectPlayer->setVisible(true);
    flecheHaut->setVisible(true);
    flecheBas->setVisible(true);

    nomBianca = new QGraphicsSvgItem(":/nombianca/nombianca");
    nomBianca->setPos(screenGeometry.width()-415, 10);
    scene->addItem(nomBianca);
    nomBianca->setVisible(false);
    nomGabin = new QGraphicsSvgItem(":/nomgabin/nomgabin");
    nomGabin->setPos(screenGeometry.width()-415, (screenGeometry.height()-nomGabin->boundingRect().height()*3));
    scene->addItem(nomGabin);
    nomGabin->setVisible(false);

    scene->setSceneRect(0,0,screenGeometry.width()-WindowMargin,
                        screenGeometry.height()-WindowMargin);

    //affichage de la nouvelle scene
    excalibur->setScene(scene);

    excalibur->setRenderHint(QPainter::Antialiasing);

    QPainter painter;
    excalibur->drawBackground(&painter, screenGeometry);
    excalibur->setCacheMode(QGraphicsView::CacheBackground);
    excalibur->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    excalibur->setDragMode(QGraphicsView::ScrollHandDrag);

    timerFlechesSelect = new QTimer(this);
    connect(timerFlechesSelect, SIGNAL(timeout()), this, SLOT(animateFlechesSelect()));

}

void MainWindow::DisplaySelectScreen(void)
{
    qDebug("StartSlectScreen");

    nomGabin->setVisible(false);
    nomBianca->setVisible(false);
    excalibur->BiancaGameSelected = false;
    excalibur->GabinGameSelected = false;
    setEnclume();

    layout->addWidget(excalibur, 0, 0);
    setLayout(layout);
    this->setCursor(Qt::OpenHandCursor);

    excalibur->show();
    excalibur->setFocus();
    CurrentScreen = EXCALIBURSCREEN;

    timerFlechesSelect->start(50);
}


void MainWindow::animateFlechesSelect()
{
    repaint();
}

void MainWindow::animateEnnemies()
{
   repaint();
}

void MainWindow::setGabinContraste(void)
{

    ExcaliburGabin->setVisible(true);
    ExcaliburBianca->setVisible(false);

    //affichage de la nouvelle scene
    excalibur->setScene(scene);
}

void MainWindow::setBiancaContraste(void)
{

    ExcaliburBianca->setVisible(true);
    ExcaliburGabin->setVisible(false);

    //affichage de la nouvelle scene
    excalibur->setScene(scene);
}

void MainWindow::setEnclume(void)
{
    ExcaliburFull->setVisible(true);
    ExcaliburBianca->setVisible(false);
    ExcaliburGabin->setVisible(false);

    //affichage de la nouvelle scene
    excalibur->setScene(scene);
}

void MainWindow::removeGabinGame(void)
{
    layout->removeWidget(gabinGame);
    gabinGame->hide();
}

void MainWindow::removeBiancaGame(void)
{
    layout->removeWidget(biancaGame);
    biancaGame->hide();
}

void MainWindow::removeExcaliburSelect(void)
{
    layout->removeWidget(excalibur);
    excalibur->hide();
    //timerFlechesSelect->stop();
}

void MainWindow::displayGabinGame(void)
{
    removeExcaliburSelect();

    gabinGame->drawBackground(&painter, screenGeometry);
    gabinGame->setCacheMode(QGraphicsView::CacheBackground);
    gabinGame->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    gabinGame->setDragMode(QGraphicsView::ScrollHandDrag);
    layout->addWidget(gabinGame, 0, 0);
    setLayout(layout);
    this->setCursor(Qt::OpenHandCursor);

    gabinGame->setFocus();
    gabinGame->show();
    TimerDisplayCommand = 0;
    CurrentScreen = GABINSCREEN;

    //timerEnnemiesRefreshDisplay->start(50);
}

void MainWindow::displayBiancaGame(void)
{
    removeExcaliburSelect();

    biancaGame->drawBackground(&painter, screenGeometry);
    biancaGame->setCacheMode(QGraphicsView::CacheBackground);
    biancaGame->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    layout->addWidget(biancaGame, 0, 0);
    setLayout(layout);
    this->setCursor(fleau);

    sceneBianca->setSceneRect(0,0,screenGeometry.width()-WindowMargin,
                        screenGeometry.height()-WindowMargin);

    biancaGame->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    biancaGame->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    souris->setVisible(true);

    biancaGame->setFocus();
    biancaGame->show();
    timerDisplaySourisCommand = 0;
    CurrentScreen = BIANCASCREEN;
}

void MainWindow::paintEvent(QPaintEvent *event)
 {
//     QPainter painter;
     //painter.begin(this);

     switch (CurrentScreen) {
     case EXCALIBURSCREEN:
         if (taille == 0)
         {
             flecheHaut->setTransform(QTransform().scale(1+0.05*x, 1+0.05*x));
             flecheBas->setTransform(QTransform().scale(1+0.05*x, 1+0.05*x));
             flecheHaut->setPos((screenGeometry.width())/2-flecheHaut->boundingRect().width()-x,
                                (screenGeometry.height()-flecheHaut->boundingRect().height()-flecheBas->boundingRect().height())/2-flecheHaut->boundingRect().height()-20-x);
                                     //210-x);
             flecheBas->setPos((screenGeometry.width())/2+3-flecheHaut->boundingRect().width()-x,
                               (screenGeometry.height()-flecheHaut->boundingRect().height()-flecheBas->boundingRect().height())/2+20-x);
                                    //325-x);
             x++;
             if (x == 10)taille=1;
         }
         else
         {
             flecheHaut->setTransform(QTransform().scale(1+0.05*x, 1+0.05*x));
             flecheBas->setTransform(QTransform().scale(1+0.05*x, 1+0.05*x));
             flecheHaut->setPos((screenGeometry.width())/2-flecheHaut->boundingRect().width()-x,
                                (screenGeometry.height()-flecheHaut->boundingRect().height()-flecheBas->boundingRect().height())/2-flecheHaut->boundingRect().height()-20-x);
                                     //210-x);
             flecheBas->setPos((screenGeometry.width())/2+3-flecheHaut->boundingRect().width()-x,
                               (screenGeometry.height()-flecheHaut->boundingRect().height()-flecheBas->boundingRect().height())/2+20-x);
                                    //325-x);
             x--;
             if (x == 0)taille=0;
         }

         excalibur->setScene(scene);
         break;
     case GABINSCREEN:
         if (TimerDisplayCommand < 60)
         {
             flecheHautGabin->setVisible(true);
             flecheBasGabin->setVisible(true);
             espaceCommand->setVisible(true);

             if (taille == 0)
             {
                 flecheHautGabin->setTransform(QTransform().scale(1+0.05*x, 1+0.05*x));
                 flecheBasGabin->setTransform(QTransform().scale(1+0.05*x, 1+0.05*x));
                 espaceCommand->setTransform(QTransform().scale(1+0.05*x, 1+0.05*x));
                 flecheHautGabin->setPos((screenGeometry.width()-espaceCommand->boundingRect().width())/2-x,
                                         (screenGeometry.height()-flecheHautGabin->boundingRect().height()-flecheBasGabin->boundingRect().height())/2-flecheHautGabin->boundingRect().height()-20-x);
                                         //210-x);
                 flecheBasGabin->setPos((screenGeometry.width()-espaceCommand->boundingRect().width())/2+3-x,
                                        (screenGeometry.height()-flecheHautGabin->boundingRect().height()-flecheBasGabin->boundingRect().height())/2+20-x);
                                        //325-x);
                 espaceCommand->setPos((screenGeometry.width()-flecheHautGabin->boundingRect().width())/2+flecheHautGabin->boundingRect().width()-x,
                                       (screenGeometry.height())/2-espaceCommand->boundingRect().height()-25-x);
                                       //278-x);
                 x++;
                 if (x == 10)taille=1;
             }
             else
             {
                 flecheHautGabin->setTransform(QTransform().scale(1+0.05*x, 1+0.05*x));
                 flecheBasGabin->setTransform(QTransform().scale(1+0.05*x, 1+0.05*x));
                 espaceCommand->setTransform(QTransform().scale(1+0.05*x, 1+0.05*x));
                 flecheHautGabin->setPos((screenGeometry.width()-espaceCommand->boundingRect().width())/2-x,
                                         (screenGeometry.height()-flecheHautGabin->boundingRect().height()-flecheBasGabin->boundingRect().height())/2-flecheHautGabin->boundingRect().height()-20-x);
                                         //210-x);
                 flecheBasGabin->setPos((screenGeometry.width()-espaceCommand->boundingRect().width())/2+3-x,
                                        (screenGeometry.height()-flecheHautGabin->boundingRect().height()-flecheBasGabin->boundingRect().height())/2+20-x);
                                        //325-x);
                 espaceCommand->setPos((screenGeometry.width()-flecheHautGabin->boundingRect().width())/2+flecheHautGabin->boundingRect().width()-x,
                                       (screenGeometry.height())/2-espaceCommand->boundingRect().height()-25-x);
                                       //278-x);
                 x--;
                 if (x == 0)taille=0;
             }

             TimerDisplayCommand++;
         }
         else {
             flecheHautGabin->setVisible(false);
             flecheBasGabin->setVisible(false);
             espaceCommand->setVisible(false);
         }
         if (DelayEntreEnnemie > 50)
         {
             //creation d'un ennemie
             DelayEntreEnnemie = 0;
             ListEnnemies.append(new GabinEnnemie(sceneGabin));
             sceneGabin->addItem(ListEnnemies.last()->ennemie);
             qDebug("addItem %d", ListEnnemies.size());
         }
         DelayEntreEnnemie++;
         for(int i = 0; i< ListEnnemies.size();i++)
         {
             //rafraichi la position de chaque ennemie
             ListEnnemies.at(i)->calculatepos();
         }
         if (!ListEnnemies.isEmpty()){
             if(ListEnnemies.first()->isGameover(gabinGame->pos, gabinGame->hit) == 1)
             {
                 //enemie elliminé
                 nuage->setPos(120,
                               posGabin*screenGeometry.height()/4+20);
                 nuage->setVisible(true);
                 sceneGabin->removeItem(ListEnnemies.first()->ennemie);
                 ListEnnemies.pop_front();
                 QTimer::singleShot(500, this, SLOT(popEnnemie()));
             }
             else if (ListEnnemies.first()->isGameover(gabinGame->pos, gabinGame->hit) == 2)
             {
                 //game over
                 gameOverGabinTxt->setVisible(true);
                 timerFlechesSelect->stop();
                 //timerEnnemiesRefreshDisplay->stop();
                 QTimer::singleShot(4000, this, SLOT(gameOverGabin()));
             }
         }

         gabinGame->setScene(sceneGabin);
         break;
     case BIANCASCREEN:
         if (timerDisplaySourisCommand < 60)
         {
             if (taille == 0)
             {
                 souris->setTransform(QTransform().scale(1+0.02*x, 1+0.02*x));
                 souris->setPos(50-x,50-x);
                 x++;
                 if (x == 10)taille=1;
             }
             else {
                 souris->setTransform(QTransform().scale(1+0.02*x, 1+0.02*x));
                 souris->setPos(50-x, 50-x);
                 x--;
                 if (x == 0)taille=0;
             }
             timerDisplaySourisCommand++;
         }
         else {
             souris->setVisible(false);
             int rot = 0;
             if (DelayEntreEnnemieBianca == 30)
             {
                 //creation d'un ennemie
                 EnnemieBianca = new BiancaEnnemie(this, sceneBianca);
                 sceneBianca->addItem(EnnemieBianca->ennemie);
                 ennemieOn = true;

             }
             else if ((DelayEntreEnnemieBianca > 30) && (DelayEntreEnnemieBianca < 35)) {
                 rot++;
                 EnnemieBianca->ennemie->setTransformOriginPoint(150,300);
                 EnnemieBianca->ennemie->setRotation(rot);
                 if (hitted == true)
                 {
                     hitted = false;
                     DelayEntreEnnemieBianca = 0;
                     if (EnnemieBianca->isBianca == false) {
                        sceneBianca->removeItem(EnnemieBianca->ennemie);
                        ennemieOn = false;
                     }
                     else {
                         ennemieOn = false;
                         gameOverBiancaTxt->setVisible(true);
                         timerFlechesSelect->stop();
                         //timerEnnemiesRefreshDisplay->stop();
                         QTimer::singleShot(4000, this, SLOT(gameOverBianca()));
                     }
                 }
             }
             else if ((DelayEntreEnnemieBianca > 35) && (DelayEntreEnnemieBianca < 45)) {
                 rot--;
                 EnnemieBianca->ennemie->setTransformOriginPoint(150,300);
                 EnnemieBianca->ennemie->setRotation(rot);
                 if (hitted == true)
                 {
                     hitted = false;
                     DelayEntreEnnemieBianca = 0;
                     if (EnnemieBianca->isBianca == false) {
                        sceneBianca->removeItem(EnnemieBianca->ennemie);
                        ennemieOn = false;
                     }
                     else {
                         ennemieOn = false;
                         gameOverBiancaTxt->setVisible(true);
                         timerFlechesSelect->stop();
                         //timerEnnemiesRefreshDisplay->stop();
                         QTimer::singleShot(4000, this, SLOT(gameOverBianca()));
                     }
                 }
             }
             else if ((DelayEntreEnnemieBianca > 45) && (DelayEntreEnnemieBianca < 50)) {
                 rot++;
                 EnnemieBianca->ennemie->setTransformOriginPoint(150,300);
                 EnnemieBianca->ennemie->setRotation(rot);
                 if (hitted == true)
                 {
                     hitted = false;
                     DelayEntreEnnemieBianca = 0;
                     if (EnnemieBianca->isBianca == false) {
                        sceneBianca->removeItem(EnnemieBianca->ennemie);
                        ennemieOn = false;
                     }
                     else {
                         ennemieOn = false;
                         gameOverBiancaTxt->setVisible(true);
                         timerFlechesSelect->stop();
                         //timerEnnemiesRefreshDisplay->stop();
                         QTimer::singleShot(4000, this, SLOT(gameOverBianca()));
                     }
                 }
             }
             else if ((DelayEntreEnnemieBianca > 50) && (DelayEntreEnnemieBianca < 55)) {
                 rot--;
                 EnnemieBianca->ennemie->setTransformOriginPoint(150,300);
                 EnnemieBianca->ennemie->setRotation(rot);
                 if (hitted == true)
                 {
                     hitted = false;
                     DelayEntreEnnemieBianca = 0;
                     if (EnnemieBianca->isBianca == false) {
                        sceneBianca->removeItem(EnnemieBianca->ennemie);
                        ennemieOn = false;
                     }
                     else {
                         ennemieOn = false;
                         gameOverBiancaTxt->setVisible(true);
                         timerFlechesSelect->stop();
                         //timerEnnemiesRefreshDisplay->stop();
                         QTimer::singleShot(4000, this, SLOT(gameOverBianca()));
                     }
                 }
             }
             else if ((DelayEntreEnnemieBianca == 55)) {
                 //hitted = false;
                 DelayEntreEnnemieBianca = 0;
                 if ((hitted == true) && (EnnemieBianca->isBianca == true))
                 {
                   hitted = false;
                   gameOverBiancaTxt->setVisible(true);
                   timerFlechesSelect->stop();
                   //timerEnnemiesRefreshDisplay->stop();
                   QTimer::singleShot(4000, this, SLOT(gameOverBianca()));
                 }
                 else {
                     sceneBianca->removeItem(EnnemieBianca->ennemie);
                     ennemieOn = false;
                 }
             }
             DelayEntreEnnemieBianca++;
        }

         biancaGame->setScene(sceneBianca);
         break;
     }


    //painter.end();
 }

void MainWindow::popEnnemie()
{
   nuage->setVisible(false);
}

void MainWindow::gameOverGabin()
{
    for(int j = 0; j< ListEnnemies.size();j++)
    {
        sceneGabin->removeItem(ListEnnemies.at(j)->ennemie);
    }
    ListEnnemies.clear();
    gabinGame->pos = 0;//gabin en haut
    gameOverGabinTxt->setVisible(false);
    removeGabinGame();
    DisplaySelectScreen();
}

void MainWindow::gameOverBianca()
{
    sceneBianca->removeItem(EnnemieBianca->ennemie);
    ennemieOn = false;
    gameOverBiancaTxt->setVisible(false);
    pasmoi->setVisible(false);
    removeBiancaGame();
    DisplaySelectScreen();
}

void MainWindow::createSpriteGabin(QGraphicsPixmapItem* sprite1, QGraphicsPixmapItem* sprite2, int pos)
{
    sprite1->setTransform(QTransform().scale((qreal)((qreal)screenGeometry.height()/(4*2242)),
                                                  (qreal)((qreal)screenGeometry.height()/(4*2242))));
    if (pos == 0) {
        sprite1->setPos(10,
                         pos*screenGeometry.height()/4);
    }
    else{
        sprite1->setPos(10,
                         pos*screenGeometry.height()/4-25);
    }
    sprite1->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    sprite1->setVisible(false);

    sprite2->setTransform(QTransform().scale((qreal)((qreal)screenGeometry.height()/(4*2242)),
                                                  (qreal)((qreal)screenGeometry.height()/(4*2242))));
    if (pos == 0){
        sprite2->setPos(10,
                         pos*screenGeometry.height()/4);
    }
    else {
        sprite2->setPos(10,
                         pos*screenGeometry.height()/4-25);
    }
    sprite2->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    sprite2->setVisible(false);
}

void MainWindow::setSpriteGabin(int pos)
{
  switch (pos)
  {
      case 0:
          spriteGabin1pos1->setVisible(true);
          spriteGabin1pos2->setVisible(false);
          spriteGabin1pos3->setVisible(false);
          spriteGabin1pos4->setVisible(false);
          spriteGabin2pos1->setVisible(false);
          spriteGabin2pos2->setVisible(false);
          spriteGabin2pos3->setVisible(false);
          spriteGabin2pos4->setVisible(false);
          posGabin = 0;
          break;
      case 1:
          spriteGabin1pos1->setVisible(false);
          spriteGabin1pos2->setVisible(true);
          spriteGabin1pos3->setVisible(false);
          spriteGabin1pos4->setVisible(false);
          spriteGabin2pos1->setVisible(false);
          spriteGabin2pos2->setVisible(false);
          spriteGabin2pos3->setVisible(false);
          spriteGabin2pos4->setVisible(false);
          posGabin = 1;
          break;
      case 2:
          spriteGabin1pos1->setVisible(false);
          spriteGabin1pos2->setVisible(false);
          spriteGabin1pos3->setVisible(true);
          spriteGabin1pos4->setVisible(false);
          spriteGabin2pos1->setVisible(false);
          spriteGabin2pos2->setVisible(false);
          spriteGabin2pos3->setVisible(false);
          spriteGabin2pos4->setVisible(false);
          posGabin = 2;
          break;
      case 3:
          spriteGabin1pos1->setVisible(false);
          spriteGabin1pos2->setVisible(false);
          spriteGabin1pos3->setVisible(false);
          spriteGabin1pos4->setVisible(true);
          spriteGabin2pos1->setVisible(false);
          spriteGabin2pos2->setVisible(false);
          spriteGabin2pos3->setVisible(false);
          spriteGabin2pos4->setVisible(false);
          posGabin = 3;
          break;
  }
}

void MainWindow::setSpriteHitGabin(int pos)
{
    switch (pos)
    {
        case 0:
            spriteGabin1pos1->setVisible(false);
            spriteGabin1pos2->setVisible(false);
            spriteGabin1pos3->setVisible(false);
            spriteGabin1pos4->setVisible(false);
            spriteGabin2pos1->setVisible(true);
            spriteGabin2pos2->setVisible(false);
            spriteGabin2pos3->setVisible(false);
            spriteGabin2pos4->setVisible(false);
            break;
        case 1:
            spriteGabin1pos1->setVisible(false);
            spriteGabin1pos2->setVisible(false);
            spriteGabin1pos3->setVisible(false);
            spriteGabin1pos4->setVisible(false);
            spriteGabin2pos1->setVisible(false);
            spriteGabin2pos2->setVisible(true);
            spriteGabin2pos3->setVisible(false);
            spriteGabin2pos4->setVisible(false);
            break;
        case 2:
            spriteGabin1pos1->setVisible(false);
            spriteGabin1pos2->setVisible(false);
            spriteGabin1pos3->setVisible(false);
            spriteGabin1pos4->setVisible(false);
            spriteGabin2pos1->setVisible(false);
            spriteGabin2pos2->setVisible(false);
            spriteGabin2pos3->setVisible(true);
            spriteGabin2pos4->setVisible(false);
            break;
        case 3:
            spriteGabin1pos1->setVisible(false);
            spriteGabin1pos2->setVisible(false);
            spriteGabin1pos3->setVisible(false);
            spriteGabin1pos4->setVisible(false);
            spriteGabin2pos1->setVisible(false);
            spriteGabin2pos2->setVisible(false);
            spriteGabin2pos3->setVisible(false);
            spriteGabin2pos4->setVisible(true);
            break;
    }
}

void MainWindow::hitPos(QPoint point)
{
    if (ennemieOn == true)
    {
        if ((point.x() > EnnemieBianca->ennemie->x()) &&
            (point.x() < EnnemieBianca->ennemie->x() + 120) &&
            (point.y() > EnnemieBianca->ennemie->y()) &&
            (point.y() < EnnemieBianca->ennemie->y() + 150))
        {
            hitted = true;
            if (EnnemieBianca->isBianca == true) {
               pasmoi->setVisible(true);
               pasmoi->setPos(EnnemieBianca->ennemie->x()+65,
                              EnnemieBianca->ennemie->y()-30);
            }
            else {
                aieIdx = qrand()%3;
                if(aieIdx != 2) {
                    aie.at(aieIdx)->setPos(EnnemieBianca->ennemie->x()+50,
                        EnnemieBianca->ennemie->y()-30);
                }
                else {//c'est meme pas drole
                    aie.at(aieIdx)->setPos(EnnemieBianca->ennemie->x()+60,
                        EnnemieBianca->ennemie->y()-70);
                }
                aie.at(aieIdx)->setVisible(true);
                QTimer::singleShot(800, this, SLOT(popAie()));
            }
        }
    }
}

void MainWindow::popAie()
{
    aie.at(aieIdx)->setVisible(false);
}

MainWindow::~MainWindow()
{
}
