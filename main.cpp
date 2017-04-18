#include "mainwindow.h"
#include "excalibur.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //w.setWindowState(Qt::WindowMaximized);
    w.show();

    //Excalibur excal;
    //excal.show();

    return a.exec();
}
