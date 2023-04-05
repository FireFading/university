#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->menu->setCurrentIndex(0);

    ui->table->setColumnCount(4);
    ui->table->setRowCount(0);
    ui->table->setSelectionBehavior(QAbstractItemView::SelectRows); //Выбор только строк
    ui->table->setSelectionMode(QAbstractItemView::SingleSelection); //Запрет выбора больше одной
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_table() {
     ui->table->setRowCount(products.size());
     microcontroller* current_node;
     for (int i = 0; i < products.size(); i++) {
         current_node = products[i];
         QTableWidgetItem* item;
         item = new QTableWidgetItem(QString::number(current_node->get_artikul()));
         ui->table->setItem(i, 0, item);
         item = new QTableWidgetItem(current_node->get_name());
         ui->table->setItem(i, 1, item);
         item = new QTableWidgetItem(current_node->get_firma());
         ui->table->setItem(i, 2, item);
         item = new QTableWidgetItem(current_node->get_year_production());
         ui->table->setItem(i, 3, item);
     }
}

void MainWindow::on_add_microcontroller_clicked()
{
    ui->menu->setCurrentIndex(1);
}

void MainWindow::on_add_clicked()
{
    if (!(ui->name_microcontroller->text().isEmpty() || ui->firma_microcontroller->text().isEmpty() || ui->year_microcontroller->text().isEmpty())) {
        QString name = ui->name_microcontroller->text();
        QString firma = ui->firma_microcontroller->text();
        QString year = ui->year_microcontroller->text();

        int artikul = products.size() + 1;
        microcontroller* new_node = new microcontroller(name, firma, year, artikul);
        products.push_back(new_node);

        ui->menu->setCurrentIndex(0);
        ui->name_microcontroller->clear();
        ui->firma_microcontroller->clear();
        ui->year_microcontroller->clear();
        update_table();
    }
}

void MainWindow::on_delete_microcontroller_clicked()
{
    if (ui->table->rowCount() != 0) {
               if (ui->table->currentRow() != -1) {
                   int row = ui->table->currentRow();
                   QTableWidgetItem *curitem = ui->table->item(row, 0);
                   int id_product = curitem->text().toInt();
                   for (int i = 0; i < products.size(); i++) {
                       if (products[i]->get_artikul() == id_product) {
                           products.remove(i);
                           break;
                       }
                   }
                   update_table();
                   ui->menu->setCurrentIndex(0);
               }
           }
}
