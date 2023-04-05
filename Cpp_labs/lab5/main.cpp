#include "mainwindow.h"
#include "farm.h"

#include <QApplication>

int Farm::count_all = 0;
int Vitamins::count_vitamins = 0;
int Antibiotic::count_antibiotics = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
