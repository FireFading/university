#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent,int all, int vit, int bio) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), number(all), number_vit(vit), number_bio(bio)
{
    ui->setupUi(this);

    ui->menu->setCurrentIndex(0);
    ui->table_vitamins->setColumnCount(5);
    ui->table_antibiotics->setColumnCount(5);

    ui->table_vitamins->setSelectionBehavior(QAbstractItemView::SelectRows); //Выбор только строк
    ui->table_vitamins->setSelectionMode(QAbstractItemView::SingleSelection); //Запрет выбора больше одной
    ui->table_antibiotics->setSelectionBehavior(QAbstractItemView::SelectRows); //Выбор только строк
    ui->table_antibiotics->setSelectionMode(QAbstractItemView::SingleSelection); //Запрет выбора больше одной
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_table() {
    ui->table_vitamins->setRowCount(number_vit);
    ui->table_antibiotics->setRowCount(number_bio);

    int j = 0;
    for (int i = 0; i < number; i++) {
        Farm* current_node = ptr[i];
        if (current_node->get_category() == "Vit") {
            QTableWidgetItem* item;
            item = new QTableWidgetItem(current_node->get_artikul());
            ui->table_vitamins->setItem(j, 0, item);
            item = new QTableWidgetItem(current_node->get_name());
            ui->table_vitamins->setItem(j, 1, item);
            item = new QTableWidgetItem(current_node->get_illness());
            ui->table_vitamins->setItem(j, 2, item);
            item = new QTableWidgetItem(current_node->get_first());
            ui->table_vitamins->setItem(j, 3, item);
            item = new QTableWidgetItem(current_node->get_second());
            ui->table_vitamins->setItem(j, 4, item);
            j++;
        }
    }
    j = 0;
    for (int i = 0; i < number; i++) {
        QTableWidgetItem* item;
        Farm* current_node = ptr[i];
        if (current_node->get_category() == "Bio") {
            item = new QTableWidgetItem(current_node->get_artikul());
            ui->table_antibiotics->setItem(j, 0, item);
            item = new QTableWidgetItem(current_node->get_name());
            ui->table_antibiotics->setItem(j, 1, item);
            item = new QTableWidgetItem(current_node->get_illness());
            ui->table_antibiotics->setItem(j, 2, item);
            item = new QTableWidgetItem(current_node->get_first());
            ui->table_antibiotics->setItem(j, 3, item);
            item = new QTableWidgetItem(current_node->get_second());
            ui->table_antibiotics->setItem(j, 4, item);
            j++;
        }
    }
}

void MainWindow::on_vit_add_clicked()
{
    ui->menu->setCurrentIndex(1);
}

void MainWindow::on_bio_add_clicked()
{
    ui->menu->setCurrentIndex(2);
}

void MainWindow::on_cancel_vitamins_clicked()
{
    ui->artikul_vitamins->clear();
    ui->name_vitamins->clear();
    ui->age_vitamins->clear();
    ui->illness_vitamins->clear();
    ui->sezon_vitamins->clear();
    ui->menu->setCurrentIndex(0);
}

void MainWindow::on_cancel_antibiotics_clicked()
{
    ui->artikul_antibiotics->clear();
    ui->name_antibiotics->clear();
    ui->recept_antibiotics->clear();
    ui->illness_antibiotics->clear();
    ui->days_antibiotics->clear();
    ui->menu->setCurrentIndex(0);
}

void MainWindow::on_add_vitamins_clicked()
{
    if (!(ui->artikul_vitamins->text().isEmpty() || ui->name_vitamins->text().isEmpty() || ui->age_vitamins->text().isEmpty() || ui->illness_vitamins->text().isEmpty() || ui->sezon_vitamins->text().isEmpty())) {
        QString artikul = ui->artikul_vitamins->text();
        QString name = ui->name_vitamins->text();
        QString age = ui->age_vitamins->text();
        QString illness = ui->illness_vitamins->text();
        QString sezon = ui->sezon_vitamins->text();

        Farm* new_product = new Vitamins(artikul, name, illness, age, sezon);
        ptr[number] = new_product;
        number++;
        number_vit++;

        update_table();

        ui->artikul_vitamins->clear();
        ui->name_vitamins->clear();
        ui->age_vitamins->clear();
        ui->illness_vitamins->clear();
        ui->sezon_vitamins->clear();
        ui->menu->setCurrentIndex(0);
    }
}

void MainWindow::on_add_antibiotics_clicked()
{
    if (!(ui->artikul_antibiotics->text().isEmpty() || ui->name_antibiotics->text().isEmpty() || ui->recept_antibiotics->text().isEmpty() || ui->illness_antibiotics->text().isEmpty() || ui->days_antibiotics->text().isEmpty())) {
        QString artikul = ui->artikul_antibiotics->text();
        QString name = ui->name_antibiotics->text();
        QString recept = ui->recept_antibiotics->text();
        QString illness = ui->illness_antibiotics->text();
        QString days = ui->days_antibiotics->text();

        Farm* new_product = new Antibiotic(artikul, name, illness, recept, days);
        ptr[number] = new_product;
        number++;
        number_bio++;

        update_table();

        ui->artikul_antibiotics->clear();
        ui->name_antibiotics->clear();
        ui->recept_antibiotics->clear();
        ui->illness_antibiotics->clear();
        ui->days_antibiotics->clear();
        ui->menu->setCurrentIndex(0);
    }
}

void MainWindow::on_delete_farm_clicked()
{
    if (number != 0) {
        int row_vit = ui->table_vitamins->currentRow();
        if (row_vit != -1) {
            QTableWidgetItem *curitem = ui->table_vitamins->item(row_vit, 0);
            QString id_product = curitem->text();
            for (int i = 0; i < number; i++) {
                if (id_product == ptr[i]->get_artikul()) {
                    for (int j = i; (j + 1) < number; j++) {
                        ptr[j] = ptr[j + 1];
                    }
                    number--;
                    number_vit--;
                    break;
                }
            }
        }
        else {
            int row_bio = ui->table_antibiotics->currentRow();
            if (row_bio != -1) {
                QTableWidgetItem *curitem = ui->table_antibiotics->item(row_bio, 0);
                QString id_product = curitem->text();
                for (int i = 0; i < number; i++) {
                    if (id_product == (ptr[i])->get_artikul()) {
                        for (int j = i; (j + 1) < number; j++) {
                            ptr[j] = ptr[j + 1];
                        }
                        number--;
                        number_bio--;
                        break;
                    }
                }
            }
        }
        ui->table_antibiotics->clearFocus();
        ui->table_vitamins->clearFocus();
        update_table();
    }
}
