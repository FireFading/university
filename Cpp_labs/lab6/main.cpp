#include "mainwindow.h"

#include <QApplication>
#include "microcontroller.h"

int list_microcontrollers::count_microcontrollers = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
