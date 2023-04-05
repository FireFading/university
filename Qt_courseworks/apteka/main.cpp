#include "mainwindow.h"

#include <QApplication>

// объявление статических полей классов
int medicine::number_medicines = 0;
int list_pharmacy::count_all = 0;
int vitamins::number_vitamins = 0;
int antibiotic::number_antibiotics = 0;
int antipyretic::number_antipyretic = 0;
int pharmacy::number_pharmacy = 0;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
