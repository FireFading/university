#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "microcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_microcontroller_clicked();

    void on_add_clicked();

    void on_delete_microcontroller_clicked();

private:
    Ui::MainWindow *ui;

    QVector<microcontroller*> products;

    void update_table();
};
#endif // MAINWINDOW_H
