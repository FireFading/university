#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, list_microcontrollers* m_current)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), current(m_current)
{
    ui->setupUi(this);

    current = new list_microcontrollers();

    ui->menu->setCurrentIndex(0);

    ui->table->setColumnCount(4);
    ui->table->setRowCount(0);
    ui->table->setSelectionBehavior(QAbstractItemView::SelectRows); //Выбор только строк
    ui->table->setSelectionMode(QAbstractItemView::SingleSelection); //Запрет выбора больше одной строки
}

MainWindow::~MainWindow()
{
     ui;
}


void MainWindow::update_table() {
    ui->table->setRowCount(current->get_count_microcontrollers());

    microcontroller* current_node = current->get_head();
    int i = 0;
    if (current_node != nullptr) {
        while (i != current->get_count_microcontrollers() + 1) {
            QTableWidgetItem* item;
            item = new QTableWidgetItem(QString::number(current_node->get_artikul()));
            ui->table->setItem(i, 0, item);
            item = new QTableWidgetItem(current_node->get_name());
            ui->table->setItem(i, 1, item);
            item = new QTableWidgetItem(current_node->get_firma());
            ui->table->setItem(i, 2, item);
            item = new QTableWidgetItem(current_node->get_year_production());
            ui->table->setItem(i, 3, item);
            current_node = current->follow(current_node);
            i++;
        }
    }
}

void MainWindow::on_add_clicked()
{
    if (!(ui->name_microcontroller->text().isEmpty() || ui->firma_microcontroller->text().isEmpty() || ui->year_microcontroller->text().isEmpty())) {
        QString name = ui->name_microcontroller->text();
        QString firma = ui->firma_microcontroller->text();
        QString year = ui->year_microcontroller->text();

        int artikul = current->get_count_microcontrollers() + 1;
        microcontroller* new_node = new microcontroller(name, firma, year, artikul);
        current->add_node(new_node);

        ui->menu->setCurrentIndex(0);
        ui->name_microcontroller->clear();
        ui->firma_microcontroller->clear();
        ui->year_microcontroller->clear();
        update_table();
    }
}

void MainWindow::on_cancel_clicked()
{
    ui->menu->setCurrentIndex(0);
}

void MainWindow::on_add_microcontroller_clicked()
{
    ui->menu->setCurrentIndex(1);
}

void MainWindow::on_delete_microcontroller_clicked()
{
    if (ui->table->rowCount() != 0) {
            if (ui->table->currentRow() != -1) {
                int row = ui->table->currentRow();
                QTableWidgetItem *curitem = ui->table->item(row, 0);
                int id_product = curitem->text().toInt();
//                microcontroller* delete_microcontroller = new microcontroller();
//                delete_microcontroller = current->find_node(id_product);
                current->delete_node(id_product);
                update_table();
                ui->menu->setCurrentIndex(0);
            }
        }
}
