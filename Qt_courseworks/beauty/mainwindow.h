#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QDate>
#include <QMenu>
#include <QMenuBar>


#include "list_salons.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, list_salons* company1 = nullptr, bool changed_data1 = false, QString current_file1 = "");
    ~MainWindow();

private slots:
    void on_Create_new_triggered();
    void on_Open_triggered();
    void on_Save_triggered();
    void on_Save_as_triggered();
    void on_Exit_triggered();
    void on_Help_triggered();
    void on_About_triggered();
    void on_add_employee_clicked();

    void on_barber_clicked();

    void on_beautician_clicked();

    void on_administrator_clicked();

    void on_cancel_clicked();

    void on_add_barber_clicked();

    void on_cancel_barber_clicked();

    void on_cancel_beautician_clicked();

    void on_add_beautician_clicked();

    void on_cancel_administrator_clicked();

    void on_add_administrator_clicked();

    void on_edit_employee_clicked();

    void on_add_salon_clicked();

    void on_cancel_new_salon_clicked();

    void on_add_new_salon_clicked();

    void on_delete_employee_clicked();

    void on_change_salon_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_done_edit_salon_clicked();


    void on_search_employee_clicked();

    void on_search_by_salary_clicked();

    void on_search_salary_clicked();

    void on_search_by_name_clicked();

    void on_search_artikul_medicine_clicked();

    void on_cancel_search_3_clicked();

private:
    Ui::MainWindow *ui;

    list_salons* company;
    salon* current_salon;
    bool changed_data;
    QString current_file;
    void update_table1();
    void update_table2();
    void write_in_file(QFile &file);
};
#endif // MAINWINDOW_H
