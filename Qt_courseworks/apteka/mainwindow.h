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

#include "medicine.h"
#include "pharmacy.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, int m_current_pharmacy_artikul = 1, list_pharmacy* m_pharmacies = nullptr, pharmacy* m_current_pharmacy = nullptr, bool m_changed_data = false, QString m_current_file = "");
    ~MainWindow();

private slots:

    void on_add_new_clicked();

    void on_vitamins_clicked();

    void on_antibiotic_clicked();

    void on_antipyretic_clicked();

    void on_cancel_clicked();

    void on_cancel_vitamins_clicked();

    void on_cancel_antibiotic_clicked();

    void on_cancel_antipyretic_clicked();

    void on_add_vitamins_clicked();

    void on_add_antibiotic_clicked();

    void on_add_antipyretic_clicked();

    void on_edit_medicine_clicked();


    void on_edit_vitamins_2_clicked();

    void on_edit_antibiotic_2_clicked();

    void on_edit_antipyretic_2_clicked();

    void on_delete_medicine_clicked();

    void on_search_medicine_clicked();

    void on_search_by_cost_clicked();

    void on_search_by_age_clicked();

    void on_search_cancel_clicked();

    void on_cancel_search_clicked();

    void on_cancel_search_2_clicked();

    void on_search_cost_medicine_clicked();

    void on_search_firm_medicine_clicked();

    void on_add_pharmacy_clicked();

    void on_cancel_new_pharmacy_clicked();

    void on_add_new_pharmacy_clicked();

    void on_change_pharmacy_clicked();

    void on_choose_new_pharmacy_2_clicked();

    void on_edit_pharmacy_data_clicked();

    void on_cancel_new_pharmacy_2_clicked();

    void on_edit_pharmacy_done_clicked();

    // функции меню
   void on_Create_new_triggered(); // новый файл
   void on_Open_triggered(); // открытие файла
   void on_Save_triggered(); // быстрое сохранение
   void on_Save_as_triggered(); // сохранение под новым именем
   void on_Exit_triggered(); // выход из программы
   void on_Help_triggered(); // справка
   void on_About_triggered(); // немного о программе

   void on_delete_pharmacy_clicked();

   void on_stay_pharmacy_clicked();

   void on_cancel_vitamins_2_clicked();

   void on_cancel_antibiotic_2_clicked();

   void on_cancel_antipyretic_2_clicked();

   void on_search_by_artikul_clicked();

   void on_cancel_search_3_clicked();

   void on_search_artikul_medicine_clicked();

private:
    Ui::MainWindow *ui;

    list_pharmacy* pharmacies; // список всех магазинов сети
    int current_pharmacy_artikul; // артикул текущего магазина - для удобства поиска в общем списке
    pharmacy* current_pharmacy; // текущий магазин

    bool changed_data; // флаг изменения данных - для выдачи предупреждения о несохраненных данных
    QString current_file; // имя текущего файла

    void update_table(); // обновление таблицы с продуктами текущего магазина
    void update_table_pharmacies(); // обновление таблицы с магазинами

    void write_in_file(QFile &file); // запись в файл
};
#endif // MAINWINDOW_H
