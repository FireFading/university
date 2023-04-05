#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    result = 0;
    first = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_17_clicked()
{
    QString Current, Result;
    Current = ui->line->text();
    current = Current.toDouble();
    ui->line->setText("");
    switch(flag) {
    case 1:
        result = result + current;
        break;
    case 2:
        result = result / current;
        break;
    case 3:
        result = result * current;
        break;
    case 4:
        result = result - current;
    }
    Result = QString:: number(result);
    ui->result->setText(Result);
    last_result = result;
    first = 0;
}

void MainWindow::on_pushButton_clicked()
{
    QString Current;
    Current = ui->line->text();
    if (first == 1) {
        result = Current.toDouble();
    }
    else {
        current = Current.toDouble();
    }
    flag = 1;
    ui->line->setText("");
}

void MainWindow::on_pushButton_4_clicked()
{
    QString Current;
    Current = ui->line->text();
    if (first == 1) {
        result = Current.toDouble();
    }
    else {
        current = Current.toDouble();
    }
    flag = 2;
    ui->line->setText("");
}

void MainWindow::on_pushButton_3_clicked()
{
    QString Current;
    Current = ui->line->text();
    if (first == 1) {
        result = Current.toDouble();
    }
    else {
        current = Current.toDouble();
    }
    flag = 3;
    ui->line->setText("");
}

void MainWindow::on_pushButton_2_clicked()
{
    QString Current;
    Current = ui->line->text();
    if (first == 1) {
        result = Current.toDouble();
    }
    else {
        current = Current.toDouble();
    }
    flag = 4;
    ui->line->setText("");
}

void MainWindow::on_pushButton_7_clicked()
{
    QString Current;
    Current = ui->line->text();
    current = Current.toDouble();
    QString current_line;
    current_line = ui->line->text();
    ui->line->setText(current_line + "1");
}

void MainWindow::on_pushButton_10_clicked()
{
    QString Current;
    Current = ui->line->text();
    current = Current.toDouble();
    QString current_line;
    current_line = ui->line->text();
    ui->line->setText(current_line + "2");
}

void MainWindow::on_pushButton_13_clicked()
{
    QString Current;
    Current = ui->line->text();
    current = Current.toDouble();
    QString current_line;
    current_line = ui->line->text();
    ui->line->setText(current_line + "3");
}

void MainWindow::on_pushButton_16_clicked()
{
    QString Current;
    Current = ui->line->text();
    current = Current.toDouble();
    QString current_line;
    current_line = ui->line->text();
    ui->line->setText(current_line + "4");
}

void MainWindow::on_pushButton_8_clicked()
{
    QString Current;
    Current = ui->line->text();
    current = Current.toDouble();
    QString current_line;
    current_line = ui->line->text();
    ui->line->setText(current_line + "5");
}

void MainWindow::on_pushButton_11_clicked()
{
    QString Current;
    Current = ui->line->text();
    current = Current.toDouble();
    QString current_line;
    current_line = ui->line->text();
    ui->line->setText(current_line + "6");
}

void MainWindow::on_pushButton_14_clicked()
{
    QString Current;
    Current = ui->line->text();
    current = Current.toDouble();
    QString current_line;
    current_line = ui->line->text();
    ui->line->setText(current_line + "7");
}

void MainWindow::on_pushButton_5_clicked()
{
    QString Current;
    Current = ui->line->text();
    current = Current.toDouble();
    QString current_line;
    current_line = ui->line->text();
    ui->line->setText(current_line + "8");
}

void MainWindow::on_pushButton_9_clicked()
{
    QString Current;
    Current = ui->line->text();
    current = Current.toDouble();
    QString current_line;
    current_line = ui->line->text();
    ui->line->setText(current_line + "9");
}

void MainWindow::on_pushButton_15_clicked()
{
    result = 0;
    current = 0;
    first = 1;
    last_result = 0;
    ui->line->setText("");
    ui->result->setText("");
}

void MainWindow::on_pushButton_18_clicked()
{
    QString current_line;
    current_line = ui->line->text();
    ui->line->setText(current_line + ".");
}

void MainWindow::on_pushButton_6_clicked()
{
    double new_current;
    QString current_line, Result;
    current_line = ui->line->text();
    new_current = current_line.toDouble();
    new_current = -new_current;
    Result = QString:: number(new_current);
    ui->line->setText(Result);
}

void MainWindow::on_pushButton_12_clicked()
{
    QString Current;
    Current = ui->line->text();
    current = Current.toDouble();
    QString current_line;
    current_line = ui->line->text();
    ui->line->setText(current_line + "0");
}
