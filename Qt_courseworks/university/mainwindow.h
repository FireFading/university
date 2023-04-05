#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QStackedWidget>
#include <QSpinBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>

#include "branch.h"
#include "employee.h"
#include "list_branches.h"
#include "list_employees.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // очистка полей
    void clear_director_fields();
    void clear_teacher_fields();
    void clear_security_fields();
    void clear_b();

    void write_to_file(QString str); // запись в файл

    // обновление таблиц с сотрудниками и филиалами
    void tab1();
    void tab2();

public slots:
    void on_search_by_activated(int index);
    void on_Search_clicked();
    void on_Return_clicked();
    void on_Choose_clicked();
    void on_add_br_clicked();

    void on_add_b_clicked();

    // добавление сотрудников
    void on_add_director_clicked();
    void on_add_teacher_clicked();
    void on_add_security_clicked();

    void on_Edit_clicked();
    void open_check();


    void on_Exit_triggered();
    void on_about_triggered();
    void on_manual_triggered();
    void on_Create_triggered();
    void on_Open_triggered();
    void on_Save_triggered();
    void on_Save_As_triggered();

private slots:
    void on_branch_clicked();
    void on_edit_b_clicked();

    // редактирование сотрудников
    void on_edit_teacher_clicked();
    void on_edit_director_clicked();
    void on_edit_security_clicked();

    void on_edit_br_clicked();

    void on_Delete_clicked();
    void on_delete_b_clicked();
    void on_search_clicked();

private:
    Ui::MainWindow *ui;
    List_branches* University;
    bool save_flag;
    QString filename;
};
#endif // MAINWINDOW_H
