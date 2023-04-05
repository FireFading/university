#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "farm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, int all = 0, int vit = 0, int bio = 0);
    ~MainWindow();

private slots:


    void on_vit_add_clicked();

    void on_bio_add_clicked();

    void on_cancel_vitamins_clicked();

    void on_cancel_antibiotics_clicked();

    void on_add_vitamins_clicked();

    void on_add_antibiotics_clicked();

    void on_delete_farm_clicked();

private:
    Ui::MainWindow *ui;

    Farm* ptr[10];
    int number;
    int number_vit;
    int number_bio;

    void update_table();
};

#endif // MAINWINDOW_H
