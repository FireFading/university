#include "mainwindow.h"

#include <QApplication>

int Director:: count_directors = 0;
int Teacher:: count_teachers = 0;
int Security:: count_securities = 0;
int List_branches:: count_branches = 0;
int Employee:: count_all = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
