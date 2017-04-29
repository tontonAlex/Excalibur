#include "mainwindow.h"
#include "excalibur.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QList<Qt::GestureType> gestures;
    gestures << Qt::TapAndHoldGesture;
//    gestures << Qt::SwipeGesture;
//    gestures << Qt::TapGesture;
//    gestures << Qt::PanGesture;
//    gestures << Qt::PinchGesture;


    MainWindow w;
    w.grabGestures(gestures);
    //w.setWindowState(Qt::WindowMaximized);
    w.show();

    //Excalibur excal;
    //excal.show();

    return a.exec();
}
