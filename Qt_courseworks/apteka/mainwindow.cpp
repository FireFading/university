#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, int m_current_pharmacy_artikul, list_pharmacy* m_pharmacies, pharmacy* m_current_pharmacy, bool m_changed_data, QString m_current_file)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), pharmacies(m_pharmacies), current_pharmacy_artikul(m_current_pharmacy_artikul), current_pharmacy(m_current_pharmacy), changed_data(m_changed_data), current_file(m_current_file)
{
    ui->setupUi(this);

    setWindowTitle(tr("%1[*]").arg("Pharmacies")); // установка заголовка

    pharmacies = new list_pharmacy(); // создание списка аптек
    current_pharmacy = new pharmacy(); // создание аптеки
    pharmacies->add_node(current_pharmacy); // добавление текущей аптеки в список

    ui->main_table->setColumnCount(7); // установка количества колонок в главной таблице
    ui->main_table->setRowCount(0); // количество строк
    QStringList Title;
    Title << "ID"
          << "category"
          << "artikul"
          << "price"
          << "firma"
          << "age"
          << "optional";
    ui->main_table->setHorizontalHeaderLabels(Title); // установка шапки таблицы
    ui->main_table->setEditTriggers(QAbstractItemView::NoEditTriggers); // запрет редактирования
    ui->main_table->setSelectionMode(QAbstractItemView::SingleSelection); // Запрет выбора больше одной строки
    ui->main_table->setSelectionBehavior(QAbstractItemView::SelectRows); // Выбор только строк

    // редактирование колонок
    ui->main_table->setColumnWidth(0, 30);
    ui->main_table->setColumnWidth(1, 90);
    ui->main_table->setColumnWidth(2, 80);
    ui->main_table->setColumnWidth(3, 80);
    ui->main_table->setColumnWidth(4, 120);
    ui->main_table->setColumnWidth(5, 80);
    ui->main_table->setColumnWidth(6, 280);

    ui->search_table->setColumnCount(7); // таблица с результатами поиска
    ui->search_table->setHorizontalHeaderLabels(Title);
    ui->search_table->setRowCount(0);
    ui->search_table->setEditTriggers(QAbstractItemView::NoEditTriggers); // запрет редактирования
    ui->search_table->setSelectionMode(QAbstractItemView::SingleSelection); // выбор только строк

    // редактирование колонок
    ui->search_table->setColumnWidth(0, 30);
    ui->search_table->setColumnWidth(1, 90);
    ui->search_table->setColumnWidth(2, 80);
    ui->search_table->setColumnWidth(3, 80);
    ui->search_table->setColumnWidth(4, 120);
    ui->search_table->setColumnWidth(5, 80);
    ui->search_table->setColumnWidth(6, 280);

    ui->table_shops->setColumnCount(4); // таблица магазинов
    ui->table_shops->setRowCount(current_pharmacy->get_number_pharmaces()); // установка количества строк по количеству аптек
    QStringList Title_shops;
    Title_shops << "ID"
               << "Name"
               << "Adress"
               << "Phone";
    ui->table_shops->setHorizontalHeaderLabels(Title_shops);
    ui->table_shops->setEditTriggers(QAbstractItemView::NoEditTriggers); // запрет редактирования
    ui->table_shops->setSelectionMode(QAbstractItemView::SingleSelection); // Запрет выбора больше одной строки
    ui->table_shops->setSelectionBehavior(QAbstractItemView::SelectRows); // Выбор только строк

    // редактирование колонок
    ui->table_shops->setColumnWidth(0, 50);
    ui->table_shops->setColumnWidth(1, 200);
    ui->table_shops->setColumnWidth(2, 300);
    ui->table_shops->setColumnWidth(3, 210);

    // установка валидаторов
    QRegExp num("[0-9.+]{1,11}"); // валидатор на ввод численных занчений
    QValidator *numValidator = new QRegExpValidator(num, this);
    ui->age_vitamins->setValidator(numValidator);
    ui->age_antibiotic->setValidator(numValidator);
    ui->age_antipyretic->setValidator(numValidator);
    ui->age_vitamins_2->setValidator(numValidator);
    ui->age_antibiotic_2->setValidator(numValidator);
    ui->age_antipyretic_2->setValidator(numValidator);
    ui->artikul_vitamins->setValidator(numValidator);
    ui->artikul_antibiotic->setValidator(numValidator);
    ui->artikul_antipyretic->setValidator(numValidator);
    ui->artikul_vitamins_2->setValidator(numValidator);
    ui->artikul_antibiotic_2->setValidator(numValidator);
    ui->artikul_antipyretic_2->setValidator(numValidator);
    ui->price_vitamins->setValidator(numValidator);
    ui->price_antibiotic->setValidator(numValidator);
    ui->price_antipyretic->setValidator(numValidator);
    ui->price_vitamins_2->setValidator(numValidator);
    ui->price_antibiotic_2->setValidator(numValidator);
    ui->price_antipyretic_2->setValidator(numValidator);
    ui->time->setValidator(numValidator);
    ui->time_2->setValidator(numValidator);
    ui->phone->setValidator(numValidator);

    QRegExp name("[A-Za-z]{1}[A-Za-z\\s\\.]{1,30}"); // Ввод только букв латиницы или кириллицы, пробелов и точек
    QValidator *nameValidator = new QRegExpValidator(name, this);
    ui->country->setValidator(nameValidator);
    ui->country_2->setValidator(nameValidator);
    ui->substance->setValidator(nameValidator);
    ui->substance_2->setValidator(nameValidator);
    ui->name->setValidator(nameValidator);
    ui->name_2->setValidator(nameValidator);

    // установка отображения количества лекартв в аптеке и общее количество аптек
    ui->count_vitamins->setText(QString::number(current_pharmacy->get_medicines()->get_count_vitamins()));
    ui->count_antibiotics->setText(QString::number(current_pharmacy->get_medicines()->get_count_antibiotics()));
    ui->count_antipyretics->setText(QString::number(current_pharmacy->get_medicines()->get_count_antipyretic()));
    ui->all_medicines->setText(QString::number(current_pharmacy->get_medicines()->get_count()));
    ui->number_pharmacies->setText(QString::number(pharmacies->get_count_all()));

    ui->menu->setCurrentIndex(0); // главное меню выбора действий
    ui->tables->setCurrentIndex(0); // отображение таблицы с продуктами

    update_table_pharmacies(); // обновление таблицы аптек
    ui->min_cost->setText("0");
    ui->max_cost->setText("10000000");
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::update_table()
{ // обновление таблицы лекарств аптеки
    ui->main_table->setRowCount(current_pharmacy->get_medicines()->get_count());

    // отображение количества лекартсв в аптеке
    ui->count_vitamins->setText(QString::number(current_pharmacy->get_medicines()->get_count_vitamins()));
    ui->count_antibiotics->setText(QString::number(current_pharmacy->get_medicines()->get_count_antibiotics()));
    ui->count_antipyretics->setText(QString::number(current_pharmacy->get_medicines()->get_count_antipyretic()));
    ui->all_medicines->setText(QString::number(current_pharmacy->get_medicines()->get_count()));
    ui->number_pharmacies->setText(QString::number(pharmacies->get_count_all()));

    medicine* current = current_pharmacy->medicines->get_head(); // для прохода по списку лекарств
    int i = 0; // счетчик строк для заполнения таблицы
    while (current != nullptr)
    {
        QTableWidgetItem *item;
        // заполнение таблицы
        item = new QTableWidgetItem(QString::number(current->get_current()));
        ui->main_table->setItem(i, 0, item);
        item = new QTableWidgetItem(current->get_category());
        ui->main_table->setItem(i, 1, item);
        item = new QTableWidgetItem(current->get_iid());
        ui->main_table->setItem(i, 2, item);
        item = new QTableWidgetItem(current->get_price());
        ui->main_table->setItem(i, 3, item);
        item = new QTableWidgetItem(current->get_firma());
        ui->main_table->setItem(i, 4, item);
        item = new QTableWidgetItem(current->get_age());
        ui->main_table->setItem(i, 5, item);
        item = new QTableWidgetItem(current->get_optional());
        ui->main_table->setItem(i, 6, item);

        current = current->get_next(); // переход к следующему лекарству
        i++;
    }

    ui->main_table->clearSelection(); // очистка фокуса с таблицы
}


void MainWindow::update_table_pharmacies()
{ // обновление таблицы аптек
    ui->number_pharmacies->setText(QString::number(pharmacies->get_count_all())); // отображение количества магазинов
    ui->table_shops->setRowCount(pharmacies->get_count_all()); // установка нового количества строк

    pharmacy* current = pharmacies->get_head();
    int i = 0; // счетчик для заполнения таблицы
    while (current != nullptr) {
        QTableWidgetItem *item;
        item = new QTableWidgetItem(QString::number(current->get_artikul()));
        ui->table_shops->setItem(i, 0, item);
        item = new QTableWidgetItem(current->get_name());
        ui->table_shops->setItem(i, 1, item);
        item = new QTableWidgetItem(current->get_adress());
        ui->table_shops->setItem(i, 2, item);
        item = new QTableWidgetItem(current->get_phone());
        ui->table_shops->setItem(i, 3, item);
        current = current->get_next();
        i++;
    }
}


void MainWindow::on_add_new_clicked() // добавление нового продукта - открытие формы с выбором типа продукта
{
    ui->menu->setCurrentIndex(5); // переход в главное меню
}


void MainWindow::on_vitamins_clicked()
{
    ui->menu->setCurrentIndex(2); // переход в главное меню
}


void MainWindow::on_antibiotic_clicked()
{
    ui->menu->setCurrentIndex(3); // переход в главное меню
}


void MainWindow::on_antipyretic_clicked()
{
    ui->menu->setCurrentIndex(4); // переход в главное меню
}


void MainWindow::on_cancel_clicked()
{
    ui->menu->setCurrentIndex(0); // переход в главное меню
}


void MainWindow::on_cancel_vitamins_clicked()
{
    ui->artikul_vitamins->clear(); // очистка поля
    ui->age_vitamins->clear();
    ui->price_vitamins->clear();
    ui->time->clear();
    ui->menu->setCurrentIndex(0); // переход в главное меню
}


void MainWindow::on_cancel_antibiotic_clicked()
{
    ui->artikul_antibiotic->clear(); // очистка поля
    ui->age_antibiotic->clear();
    ui->price_antibiotic->clear();
    ui->period->clear();
    ui->country->clear();
    ui->menu->setCurrentIndex(0); // переход в главное меню
}


void MainWindow::on_cancel_antipyretic_clicked()
{
    ui->artikul_antipyretic->clear(); // очистка поля
    ui->age_antipyretic->clear();
    ui->price_antipyretic->clear();
    ui->power->clear();
    ui->substance->clear();
    ui->concentration->clear();
    ui->menu->setCurrentIndex(0); // переход в главное меню
}

void MainWindow::on_add_vitamins_clicked() // добавление витаминов
{
    bool correct = true; // флаг корректности данных
    if (ui->artikul_vitamins->text().isEmpty())
    {
        ui->artikul_vitamins->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->artikul_vitamins->setStyleSheet("background-color: white;");
    }
    if (ui->age_vitamins->text().isEmpty())
    {
        ui->age_vitamins->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->age_vitamins->setStyleSheet("background-color: white;");
    }
    if (ui->price_vitamins->text().isEmpty())
    {
        ui->price_vitamins->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->price_vitamins->setStyleSheet("background-color: white;");
    }
    if (ui->time->text().isEmpty())
    {
        ui->time->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->time->setStyleSheet("background-color: white;");
    }

    if (correct)
    { // если данные корректны
        QString artikul = ui->artikul_vitamins->text();
        QString age = ui->age_vitamins->text();
        QString price = ui->price_vitamins->text();
        QString firma = ui->firma_vitamins->currentText();
        QString season = ui->season->currentText();
        QString type = ui->type->currentText();
        QString time = ui->time->text();

        medicine* new_vitamins = new vitamins(artikul,price, firma, age, season, type, time); // создание объекта
        current_pharmacy->medicines->add_node(new_vitamins); // добавление лекарства в список

        update_table(); // обновление таблицы продуктов

        // очистка полей и переход в главное меню
        ui->artikul_vitamins->clear();
        ui->age_vitamins->clear();
        ui->price_vitamins->clear();
        ui->time->clear();
        ui->menu->setCurrentIndex(0);

        changed_data = true;
    }
}


void MainWindow::on_add_antibiotic_clicked() // добавление антибиотиков
{
    bool correct = true;
    if (ui->artikul_antibiotic->text().isEmpty())
    {
        ui->artikul_antibiotic->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->artikul_antibiotic->setStyleSheet("background-color: white;");
    }
    if (ui->age_antibiotic->text().isEmpty())
    {
        ui->age_antibiotic->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->age_antibiotic->setStyleSheet("background-color: white;");
    }
    if (ui->price_antibiotic->text().isEmpty())
    {
        ui->price_antibiotic->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->price_antibiotic->setStyleSheet("background-color: white;");
    }
    if (ui->period->text().isEmpty())
    {
        ui->period->setStyleSheet("background-color: red;");
        correct = false;
    }
    else {
        ui->period->setStyleSheet("background-color: white;");
    }
    if (ui->country->text().isEmpty())
    {
        ui->country->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->country->setStyleSheet("background-color: white;");
    }

    if (correct)
    {  // если данные коорректны
        QString artikul = ui->artikul_antibiotic->text();
        QString age = ui->age_antibiotic->text();
        QString price = ui->price_antibiotic->text();
        QString firma = ui->firma_antibiotic->currentText();
        QString period = ui->period->text();
        QString country = ui->country->text();
        QString danger;
        if (ui->danger->isChecked())
        {
            danger = "take only by prescription";
        }
        else
        {
            danger = "you can use it by yourself";
        }

        medicine* new_antibiotic = new antibiotic(artikul, price, firma, age, period, danger, country); // создание объекта
        current_pharmacy->medicines->add_node(new_antibiotic); // добавление лекарства в список

        update_table(); // обновление таблицы продуктов

        // очистка полей и переход к главному меню
        ui->artikul_antibiotic->clear();
        ui->age_antibiotic->clear();
        ui->price_antibiotic->clear();
        ui->period->clear();
        ui->country->clear();
        ui->menu->setCurrentIndex(0);

        changed_data = true;
    }
}


void MainWindow::on_add_antipyretic_clicked() // добавление жаропонижающего
{
    bool correct = true;
    if (ui->artikul_antipyretic->text().isEmpty())
    {
        ui->artikul_antipyretic->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->artikul_antipyretic->setStyleSheet("background-color: white;");
    }
    if (ui->age_antipyretic->text().isEmpty())
    {
        ui->age_antipyretic->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->age_antipyretic->setStyleSheet("background-color: white;");
    }
    if (ui->price_antipyretic->text().isEmpty())
    {
        ui->price_antipyretic->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->price_antipyretic->setStyleSheet("background-color: white;");
    }
    if (ui->power->text().isEmpty())
    {
        ui->power->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->power->setStyleSheet("background-color: white;");
    }
    if (ui->substance->text().isEmpty())
    {
        ui->substance->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->substance->setStyleSheet("background-color: white;");
    }
    if (ui->concentration->text().isEmpty())
    {
        ui->concentration->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->concentration->setStyleSheet("background-color: white;");
    }

    if (correct)
    { // если данные корректны
        QString artikul = ui->artikul_antipyretic->text();
        QString age = ui->age_antipyretic->text();
        QString price = ui->price_antipyretic->text();
        QString firma = ui->firma_antipyretic->currentText();
        QString power = ui->power->text();
        QString substance = ui->substance->text();
        QString concentration = ui->concentration->text();

        medicine* new_antipyretic = new antipyretic(artikul, price, firma, age, power, substance, concentration); // создание объекта
        current_pharmacy->medicines->add_node(new_antipyretic); // добавление лекарства в список

        update_table(); // обновление таблицы продуктов

        ui->artikul_antipyretic->clear();
        ui->age_antipyretic->clear();
        ui->price_antipyretic->clear();
        ui->power->clear();
        ui->substance->clear();
        ui->concentration->clear();
        ui->menu->setCurrentIndex(0);

        changed_data = true;
    }
}


void MainWindow::on_edit_medicine_clicked() // редактирование
{
    if (ui->main_table->rowCount() == 0) // если таблица пустая
    {
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else
    {
        QItemSelectionModel *selectionModel = ui->main_table->selectionModel();
        if (selectionModel->hasSelection()) // проверка фокуса
        {
            int row = ui->main_table->currentRow(); // считывание фокуса таблицы
            if (row != -1) // если выбрана строка
            {
                QTableWidgetItem *curitem = ui->main_table->item(row, 0); // считывание ячейки, содержащей id
                int id_product = curitem->text().toInt(); // получение индетефикатора для дальнейшего поиска
                medicine* edit_product = current_pharmacy->medicines->find_node(id_product);
                if (edit_product->get_category() == "Vitamins")
                {
                    ui->menu->setCurrentIndex(6); // переход к форме

                    // загрузка текущих данных
                    ui->artikul_vitamins_2->setText(edit_product->get_iid());
                    ui->age_vitamins_2->setText(edit_product->get_age());
                    ui->price_vitamins_2->setText(edit_product->get_price());
                    ui->firma_vitamins_2->setCurrentText(edit_product->get_firma());
                    ui->season_2->setCurrentText(edit_product->get_first());
                    ui->type_2->setCurrentText(edit_product->get_second());
                    ui->time_2->setText(edit_product->get_third());
                }
                if (edit_product->get_category() == "Antibiotic")
                {
                    ui->menu->setCurrentIndex(7); // переход к форме

                    // загрузка текущих данных
                    ui->artikul_antibiotic_2->setText(edit_product->get_iid());
                    ui->age_antibiotic_2->setText(edit_product->get_age());
                    ui->price_antibiotic_2->setText(edit_product->get_price());
                    ui->firma_antibiotic_2->setCurrentText(edit_product->get_firma());
                    ui->period_2->setText(edit_product->get_first());
                    ui->country_2->setText(edit_product->get_second());
                    if (edit_product->get_third() == "take only by prescription")
                    {
                        ui->danger_2->setChecked(true);
                    }
                    else
                    {
                        ui->danger_2->setChecked(false);
                    }
                }
                if (edit_product->get_category() == "Antipyretic")
                {
                    ui->menu->setCurrentIndex(8); // переход к форме

                    // загрузка текущих данных
                    ui->artikul_antipyretic_2->setText(edit_product->get_iid());
                    ui->age_antipyretic_2->setText(edit_product->get_age());
                    ui->price_antipyretic_2->setText(edit_product->get_price());
                    ui->firma_antipyretic_2->setCurrentText(edit_product->get_firma());
                    ui->power_2->setText(edit_product->get_first());
                    ui->substance_2->setText(edit_product->get_second());
                    ui->concentration_2->setText(edit_product->get_third());
                }
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "No line selected!");
        }
    }
    ui->main_table->clearFocus();
    ui->main_table->clearSelection();
}


void MainWindow::on_edit_vitamins_2_clicked() // редактирование витаминов
{
    int row = ui->main_table->currentRow();
    if (row != -1)
    {
        QTableWidgetItem *curitem = ui->main_table->item(row, 0); // считывание ячейки, содержащей id
        int id_product = curitem->text().toInt(); // получение идентификатора лекарства
        medicine* edit_product = current_pharmacy->medicines->find_node(id_product); // поиск лекартсва в списке

        bool correct = true;
        if (ui->artikul_vitamins_2->text().isEmpty())
        {
            ui->artikul_vitamins_2->setStyleSheet("background-color: red;");
            correct = false;
        }
        else
        {
            ui->artikul_vitamins_2->setStyleSheet("background-color: white;");
        }
        if (ui->age_vitamins_2->text().isEmpty())
        {
            ui->age_vitamins_2->setStyleSheet("background-color: red;");
            correct = false;
        }
        else
        {
            ui->age_vitamins_2->setStyleSheet("background-color: white;");
        }
        if (ui->price_vitamins_2->text().isEmpty())
        {
            ui->price_vitamins_2->setStyleSheet("background-color: red;");
            correct = false;
        }
        else
        {
            ui->price_vitamins_2->setStyleSheet("background-color: white;");
        }
        if (ui->time_2->text().isEmpty())
        {
            ui->time_2->setStyleSheet("background-color: red;");
            correct = false;
        }
        else
        {
            ui->time_2->setStyleSheet("background-color: white;");
        }

        if (correct)
        { // если введенные данные корректны
            // считывание новых введенных данных
            QString artikul = ui->artikul_vitamins_2->text();
            QString age = ui->age_vitamins_2->text();
            QString price = ui->price_vitamins_2->text();
            QString firma = ui->firma_vitamins_2->currentText();
            QString season = ui->season_2->currentText();
            QString type = ui->type_2->currentText();
            QString time = ui->time_2->text();

            edit_product->set_data_medicine(artikul, price, firma, age, season, type, time); // изменение данных

            update_table(); // обновление таблицы продуктов

            ui->artikul_vitamins_2->clear();
            ui->age_vitamins_2->clear();
            ui->price_vitamins_2->clear();
            ui->time_2->clear();
            ui->menu->setCurrentIndex(0);

            changed_data = true;
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "No line selected!");
    }
}

void MainWindow::on_edit_antibiotic_2_clicked() // редактирование антибиотика
{
    int row = ui->main_table->currentRow();
    if (row != -1)
    {
        QTableWidgetItem *curitem = ui->main_table->item(row, 0); // считывание ячейки, содержащей id
        int id_product = curitem->text().toInt();// получение идентификатора лекарства
        medicine* edit_product = current_pharmacy->medicines->find_node(id_product);

        bool correct = true;
        if (ui->artikul_antibiotic_2->text().isEmpty())
        {
            ui->artikul_antibiotic_2->setStyleSheet("background-color: red;");
            correct = false;
        }
        else
        {
            ui->artikul_antibiotic_2->setStyleSheet("background-color: white;");
        }
        if (ui->age_antibiotic_2->text().isEmpty())
        {
            ui->age_antibiotic_2->setStyleSheet("background-color: red;");
            correct = false;
        }
        else
        {
            ui->age_antibiotic_2->setStyleSheet("background-color: white;");
        }
        if (ui->price_antibiotic_2->text().isEmpty())
        {
            ui->price_antibiotic_2->setStyleSheet("background-color: red;");
            correct = false;
        }
        else
        {
            ui->price_antibiotic_2->setStyleSheet("background-color: white;");
        }
        if (ui->period_2->text().isEmpty())
        {
            ui->period_2->setStyleSheet("background-color: red;");
            correct = false;
        }
        else
        {
            ui->period_2->setStyleSheet("background-color: white;");
        }
        if (ui->country_2->text().isEmpty())
        {
            ui->country_2->setStyleSheet("background-color: red;");
            correct = false;
        }
        else
        {
            ui->country_2->setStyleSheet("background-color: white;");
        }

        if (correct)
        {
            QString artikul = ui->artikul_antibiotic_2->text();
            QString age = ui->age_antibiotic_2->text();
            QString price = ui->price_antibiotic_2->text();
            QString firma = ui->firma_antibiotic_2->currentText();
            QString period = ui->period_2->text();
            QString country = ui->country_2->text();
            QString danger_text;
            if (ui->danger_2->isChecked())
            {
                danger_text = "take only by prescription";
            }
            else
            {
                danger_text = "you can use it by yourself";
            }

            edit_product->set_data_medicine(artikul, price, firma, age, period, danger_text, country);

            update_table(); // обновление таблицы продуктов

            ui->artikul_antibiotic_2->clear();
            ui->age_antibiotic_2->clear();
            ui->price_antibiotic_2->clear();
            ui->period_2->clear();
            ui->country_2->clear();
            ui->menu->setCurrentIndex(0);

            changed_data = true;
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "No line selected!");
    }
}

void MainWindow::on_edit_antipyretic_2_clicked() // редкактирование жаропонижающего
{
    int row = ui->main_table->currentRow();
    if (row != -1)
    {
        QTableWidgetItem *curitem = ui->main_table->item(row, 0); // считывание ячейки, содержащей id
        int id_product = curitem->text().toInt();// получение идентификатора лекарства
        medicine* edit_product = current_pharmacy->medicines->find_node(id_product);

        bool correct = true;
        if (ui->artikul_antipyretic_2->text().isEmpty())
        {
            ui->artikul_antipyretic_2->setStyleSheet("background-color: red;");
            correct = false;
        }
        else
        {
            ui->artikul_antipyretic_2->setStyleSheet("background-color: white;");
        }
        if (ui->age_antipyretic_2->text().isEmpty())
        {
            ui->age_antipyretic_2->setStyleSheet("background-color: red;");
            correct = false;
        }
        else
        {
            ui->age_antipyretic_2->setStyleSheet("background-color: white;");
        }
        if (ui->price_antipyretic_2->text().isEmpty())
        {
            ui->price_antipyretic_2->setStyleSheet("background-color: red;");
            correct = false;
        }
        else
        {
            ui->price_antipyretic_2->setStyleSheet("background-color: white;");
        }
        if (ui->power_2->text().isEmpty())
        {
            ui->power_2->setStyleSheet("background-color: red;");
            correct = false;
        }
        else
        {
            ui->power_2->setStyleSheet("background-color: white;");
        }
        if (ui->substance_2->text().isEmpty())
        {
            ui->substance_2->setStyleSheet("background-color: red;");
            correct = false;
        }
        else
        {
            ui->substance_2->setStyleSheet("background-color: white;");
        }
        if (ui->concentration_2->text().isEmpty())
        {
            ui->concentration_2->setStyleSheet("background-color: red;");
            correct = false;
        }
        else
        {
            ui->concentration_2->setStyleSheet("background-color: white;");
        }

        if (correct)
        {
            QString artikul = ui->artikul_antipyretic_2->text();
            QString age = ui->age_antipyretic_2->text();
            QString price = ui->price_antipyretic_2->text();
            QString firma = ui->firma_antipyretic_2->currentText();
            QString power = ui->power_2->text();
            QString substance = ui->substance_2->text();
            QString concentration = ui->concentration_2->text();

            edit_product->set_data_medicine(artikul, price, firma, age, power, substance, concentration);

            update_table(); // обновление таблицы продуктов

            ui->artikul_antipyretic_2->clear();
            ui->age_antipyretic_2->clear();
            ui->price_antipyretic_2->clear();
            ui->power_2->clear();
            ui->substance_2->clear();
            ui->concentration_2->clear();
            ui->menu->setCurrentIndex(0);

            changed_data = true;
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "No line selected!");
    }
}


void MainWindow::on_delete_medicine_clicked() // удаление лекарства
{
    if (ui->main_table->rowCount() == 0)
    { // в списке нет элементов
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else
    {
        QItemSelectionModel *selectionModel = ui->main_table->selectionModel();
        if (selectionModel->hasSelection()) // проверка фокуса
            {
            int row = ui->main_table->currentRow(); // считывание фокуса
            if (row != -1)
                {
                QTableWidgetItem *curitem = ui->main_table->item(row, 0); // считывание ячейки, содержащей id
                int id_product = curitem->text().toInt(); // получение индетевикатора продукта
                current_pharmacy->medicines->delete_node(id_product); // удаление по индетефикатору
                update_table();
                }
            }
        else
        {
            QMessageBox::critical(this, "Error", "No line selected!");
        }
    }
    ui->main_table->clearFocus();
    ui->main_table->clearSelection();
}


void MainWindow::on_search_medicine_clicked() // меню поиска
{
    ui->menu->setCurrentIndex(1);
}


void MainWindow::on_search_by_cost_clicked() // поиск по стоимости
{
    ui->menu->setCurrentIndex(12);
    ui->tables->setCurrentIndex(1);
}


void MainWindow::on_search_by_age_clicked() // поиск по возрасту
{
    ui->menu->setCurrentIndex(13);
    ui->tables->setCurrentIndex(1);
}


void MainWindow::on_search_cancel_clicked() // выход из поиска
{
    ui->menu->setCurrentIndex(0);
    ui->tables->setCurrentIndex(0);
}


void MainWindow::on_cancel_search_clicked()
{
    ui->menu->setCurrentIndex(0);
    ui->tables->setCurrentIndex(0);
}

void MainWindow::on_cancel_search_2_clicked()
{
    ui->menu->setCurrentIndex(0);
    ui->tables->setCurrentIndex(0);
}


void MainWindow::on_search_cost_medicine_clicked()
{
    bool correct_data = true; // флаг корректности данных

    // проверка корректности данных
    if (ui->min_cost->text().isEmpty())
    {
        correct_data = false;
        ui->min_cost->setStyleSheet("background-color: red;");
    }
    else
    {
        ui->min_cost->setStyleSheet("background-color: white;");
    }
    if (ui->max_cost->text().isEmpty()) {
        correct_data = false;
        ui->max_cost->setStyleSheet("background-color: red;");
    }
    else
    {
        ui->max_cost->setStyleSheet("background-color: white;");
    }
    if ((ui->min_cost->text()).toFloat() > (ui->max_cost->text()).toFloat())
    { // минимальная стоимость должна не превышать максимальную
        correct_data = false;
        ui->min_cost->setStyleSheet("background-color: red;");
        ui->max_cost->setStyleSheet("background-color: red;");
        QMessageBox::critical(this, "Error", "You entered wrong cost characteristics!");
    }
    else
    {
        ui->min_cost->setStyleSheet("background-color: white;");
        ui->max_cost->setStyleSheet("background-color: white;");
    }

    if (correct_data == true)
    { // если данные корректны
        // считывание данных из полей
        float minimum = (ui->min_cost->text()).toFloat();
        float maximum = (ui->max_cost->text()).toFloat();
        QString type = ui->type_product->currentText();
        bool all_pharmacy_search = ui->where_search->isChecked();

        int count_results = 0; // количество лекарств, соответствующих критериям поиска
        if (type == "Vitamins" || type == "Antibiotic" || type == "Antipyretic")
        {
            if (all_pharmacy_search == true) { // если выбран критерий поиска по всем аптекам
                pharmacy* search_shop = pharmacies->get_head();
                QTableWidgetItem *item;
                int i = 0; // для заполнения таблицы - счетчик строк
                count_results = 0; // количество результатов
                ui->search_table->setRowCount(count_results);
                while (search_shop != nullptr) { // цикл по магазинам
                    medicine_list* search_products = search_shop->get_medicines();
                    medicine* current_search = search_products->head;
                    while (current_search != nullptr) { // цикл по продуктам магазина
                        if ((minimum <= (current_search->get_price()).toFloat()) && ((current_search->get_price()).toFloat() <= maximum) && (current_search->get_category() == type))
                        { // критерия подходящих продуктов
                            count_results++;
                            ui->search_table->setRowCount(count_results); // добавление строк

                            // заполнение таблицы
                            item = new QTableWidgetItem(QString::number(current_search->get_current()));
                            ui->search_table->setItem(i, 0, item);
                            item = new QTableWidgetItem(current_search->get_category());
                            ui->search_table->setItem(i, 1, item);
                            item = new QTableWidgetItem(current_search->get_iid());
                            ui->search_table->setItem(i, 2, item);
                            item = new QTableWidgetItem(current_search->get_price());
                            ui->search_table->setItem(i, 3, item);
                            item = new QTableWidgetItem(current_search->get_firma());
                            ui->search_table->setItem(i, 4, item);
                            item = new QTableWidgetItem(current_search->get_age());
                            ui->search_table->setItem(i, 5, item);
                            item = new QTableWidgetItem(current_search->get_optional());
                            ui->search_table->setItem(i, 6, item);

                            i++;
                        }
                        current_search = current_search->next;
                    }
                    search_shop = search_shop->get_next();
                }
                ui->number_res_search->setText(QString::number(count_results)); // отображение количества найденных лекарств
            }
            else
            { // поиск только в текущем магазине
                medicine_list* search_products = current_pharmacy->get_medicines(); // список продуктов текущей аптеки
                medicine* current_search = search_products->head;
                QTableWidgetItem *item;
                int i = 0;
                count_results = 0;
                ui->search_table->setRowCount(count_results);
                while (current_search != nullptr)
                { // цикл по списку лекарств текущей аптеки
                    if ((minimum <= (current_search->get_price()).toFloat()) && ((current_search->get_price()).toFloat() <= maximum) && (current_search->get_category() == type))
                    { // проверка критериев поиска
                        count_results++;
                        ui->search_table->setRowCount(count_results); // добавление строк

                        // заполнение таблицы
                        item = new QTableWidgetItem(QString::number(current_search->get_current()));
                        ui->search_table->setItem(i, 0, item);
                        item = new QTableWidgetItem(current_search->get_category());
                        ui->search_table->setItem(i, 1, item);
                        item = new QTableWidgetItem(current_search->get_iid());
                        ui->search_table->setItem(i, 2, item);
                        item = new QTableWidgetItem(current_search->get_price());
                        ui->search_table->setItem(i, 3, item);
                        item = new QTableWidgetItem(current_search->get_firma());
                        ui->search_table->setItem(i, 4, item);
                        item = new QTableWidgetItem(current_search->get_age());
                        ui->search_table->setItem(i, 5, item);
                        item = new QTableWidgetItem(current_search->get_optional());
                        ui->search_table->setItem(i, 6, item);

                        i++;
                    }
                    current_search = current_search->next;
                }
            ui->number_res_search->setText(QString::number(count_results)); // отображение количества найденных продуктов
            }
        }
        else
        { // поиск среди лекарств всех типов
            if (all_pharmacy_search == true)
            { // поиск по всем аптекам
                pharmacy* search_shop = pharmacies->get_head();
                QTableWidgetItem *item;
                int i = 0; // счетчик строк для заполнения таблицы
                count_results = 0; // количество найденных продуктов
                ui->search_table->setRowCount(count_results);
                while (search_shop != nullptr)
                { // цикл по магазинам
                    medicine_list* search_products = search_shop->medicines;
                    medicine* current_search = search_products->head;

                    while (current_search != nullptr)
                    { // цикл по списку лекарств
                        if ((minimum <= (current_search->get_price()).toFloat()) && ((current_search->get_price()).toFloat() <= maximum)) {
                            count_results++;
                            ui->search_table->setRowCount(count_results);

                            // заполнение таблицы
                            item = new QTableWidgetItem(QString::number(current_search->get_current()));
                            ui->search_table->setItem(i, 0, item);
                            item = new QTableWidgetItem(current_search->get_category());
                            ui->search_table->setItem(i, 1, item);
                            item = new QTableWidgetItem(current_search->get_iid());
                            ui->search_table->setItem(i, 2, item);
                            item = new QTableWidgetItem(current_search->get_price());
                            ui->search_table->setItem(i, 3, item);
                            item = new QTableWidgetItem(current_search->get_firma());
                            ui->search_table->setItem(i, 4, item);
                            item = new QTableWidgetItem(current_search->get_age());
                            ui->search_table->setItem(i, 5, item);
                            item = new QTableWidgetItem(current_search->get_optional());
                            ui->search_table->setItem(i, 6, item);

                            i++;
                        }
                        current_search = current_search->next;
                    }
                    search_shop = search_shop->get_next();
                }
                ui->number_res_search->setText(QString::number(count_results)); // отображение количества найденных лекарств
            }
            else
            { // поиск по текущему магазину
                medicine_list* search_products = current_pharmacy->get_medicines(); // список продуктов магазина
                medicine* current_search = search_products->head;
                QTableWidgetItem *item;
                int i = 0;
                count_results = 0;
                ui->search_table->setRowCount(count_results);
                while (current_search != nullptr)
                { // цикл по продуктам магазина
                    if ((minimum <= (current_search->get_price()).toFloat()) && ((current_search->get_price()).toFloat() <= maximum)) {
                        count_results++;

                        // заполнение таблицы
                        ui->search_table->setRowCount(count_results);
                        item = new QTableWidgetItem(QString::number(current_search->get_current()));
                        ui->search_table->setItem(i, 0, item);
                        item = new QTableWidgetItem(current_search->get_category());
                        ui->search_table->setItem(i, 1, item);
                        item = new QTableWidgetItem(current_search->get_iid());
                        ui->search_table->setItem(i, 2, item);
                        item = new QTableWidgetItem(current_search->get_price());
                        ui->search_table->setItem(i, 3, item);
                        item = new QTableWidgetItem(current_search->get_firma());
                        ui->search_table->setItem(i, 4, item);
                        item = new QTableWidgetItem(current_search->get_age());
                        ui->search_table->setItem(i, 5, item);
                        item = new QTableWidgetItem(current_search->get_optional());
                        ui->search_table->setItem(i, 6, item);

                        i++;
                    }
                    current_search = current_search->next;
                }
            ui->number_res_search->setText(QString::number(count_results)); // отображение количества найденных результатов
            }
        }
        // установка данных по умолчанию
        ui->min_cost->setText("0");
        ui->max_cost->setText("10000000");
    }
}


void MainWindow::on_search_firm_medicine_clicked()
{
    bool correct_data = true; // флаг корректности данных

       // проверка корректности введенных данных
       if (ui->age_search->text().isEmpty())
       {
           correct_data = false;
           ui->age_search->setStyleSheet("background-color: red;");
       }
       else
       {
           ui->age_search->setStyleSheet("background-color: white;");
       }

       if (correct_data == true)
       { // если данные корректны
           // считывание данных
           float age = (ui->age_search->text()).toInt();
           bool all_shops_search = ui->where_search_2->isChecked();
           QString type = ui->type_product_2->currentText();

           int count_results = 0;
           ui->search_table->setRowCount(count_results);
           if (type == "Vitamins" || type == "Antibiotic" || type == "Antipyretic")
           { // поиск по конкретному типу лекарства
               if (all_shops_search == true) { // поиск по всем магазинам сети
                   pharmacy* search_shop = pharmacies->get_head();
                   QTableWidgetItem *item;
                   int i = 0;
                   count_results = 0;
                   ui->search_table->setRowCount(count_results);
                   while (search_shop != nullptr)
                   { // цикл по магазинам
                       medicine_list* search_products = search_shop->get_medicines();
                       medicine* current_search = search_products->head;
                       while (current_search != nullptr) { // цикл по продуктам магазина
                           if ((current_search->get_age()).toInt() == age && (current_search->get_category() == type)) {
                               count_results++;
                               ui->search_table->setRowCount(count_results);

                               // заполнение таблицы
                               item = new QTableWidgetItem(QString::number(current_search->get_current()));
                               ui->search_table->setItem(i, 0, item);
                               item = new QTableWidgetItem(current_search->get_category());
                               ui->search_table->setItem(i, 1, item);
                               item = new QTableWidgetItem(current_search->get_iid());
                               ui->search_table->setItem(i, 2, item);
                               item = new QTableWidgetItem(current_search->get_price());
                               ui->search_table->setItem(i, 3, item);
                               item = new QTableWidgetItem(current_search->get_firma());
                               ui->search_table->setItem(i, 4, item);
                               item = new QTableWidgetItem(current_search->get_age());
                               ui->search_table->setItem(i, 5, item);
                               item = new QTableWidgetItem(current_search->get_optional());
                               ui->search_table->setItem(i, 6, item);

                               i++;
                           }
                           current_search = current_search->next;
                       }
                       search_shop = search_shop->get_next();
                   }
                   ui->number_res_search->setText(QString::number(count_results)); // отображение количества результатов поиска
               }
               else // поиск только в текущем магазине
               {
                   medicine_list* search_products = current_pharmacy->get_medicines(); // список продуктов магазина
                   medicine* current_search = search_products->head;
                   QTableWidgetItem *item;
                   int i = 0;
                   count_results = 0;
                   ui->search_table->setRowCount(count_results);
                   while (current_search != nullptr)
                   { // цикл по продуктам
                       if ((current_search->get_age()).toInt() == age && (current_search->get_category() == type))
                       {
                           count_results++;
                           ui->search_table->setRowCount(count_results);

                           // заполнение таблицы
                           item = new QTableWidgetItem(QString::number(current_search->get_current()));
                           ui->search_table->setItem(i, 0, item);
                           item = new QTableWidgetItem(current_search->get_category());
                           ui->search_table->setItem(i, 1, item);
                           item = new QTableWidgetItem(current_search->get_iid());
                           ui->search_table->setItem(i, 2, item);
                           item = new QTableWidgetItem(current_search->get_price());
                           ui->search_table->setItem(i, 3, item);
                           item = new QTableWidgetItem(current_search->get_firma());
                           ui->search_table->setItem(i, 4, item);
                           item = new QTableWidgetItem(current_search->get_age());
                           ui->search_table->setItem(i, 5, item);
                           item = new QTableWidgetItem(current_search->get_optional());
                           ui->search_table->setItem(i, 6, item);

                           i++;
                       }
                       current_search = current_search->next;
                   }
               ui->number_res_search->setText(QString::number(count_results)); // отображение количества результатов
               }
           }
           else // поиск среди продуктов всех типов
           {
               if (all_shops_search == true) // поиск во всех магазинах сети
               {
                   pharmacy* search_shop = pharmacies->get_head();
                   QTableWidgetItem *item;
                   int i = 0;
                   count_results = 0;
                   ui->search_table->setRowCount(count_results);
                   while (search_shop != nullptr)
                   { // цикл по магазинам
                       medicine_list* search_products = search_shop->get_medicines();
                       medicine* current_search = search_products->head;
                       while (current_search != nullptr)
                       { // цикл по продуктам
                           if ((current_search->get_age()).toInt() == age)
                           {
                               count_results++;
                               ui->search_table->setRowCount(count_results);

                               // заполнение таблицы
                               item = new QTableWidgetItem(QString::number(current_search->get_current()));
                               ui->search_table->setItem(i, 0, item);
                               item = new QTableWidgetItem(current_search->get_category());
                               ui->search_table->setItem(i, 1, item);
                               item = new QTableWidgetItem(current_search->get_iid());
                               ui->search_table->setItem(i, 2, item);
                               item = new QTableWidgetItem(current_search->get_price());
                               ui->search_table->setItem(i, 3, item);
                               item = new QTableWidgetItem(current_search->get_firma());
                               ui->search_table->setItem(i, 4, item);
                               item = new QTableWidgetItem(current_search->get_age());
                               ui->search_table->setItem(i, 5, item);
                               item = new QTableWidgetItem(current_search->get_optional());
                               ui->search_table->setItem(i, 6, item);

                               i++;
                           }
                           current_search = current_search->next;
                       }
                       search_shop = search_shop->get_next();
                   }
                   ui->number_res_search->setText(QString::number(count_results)); // отображение количества результатов
               }
               else // поиск только в текущем магазине
               {
                   medicine_list* search_products = current_pharmacy->get_medicines(); // список продуктов текущей аптеки
                   medicine* current_search = search_products->head;
                   QTableWidgetItem *item;
                   int i = 0;
                   count_results = 0;

                   while (current_search != nullptr)
                   { // цикл по продуктам магазина
                       if ((current_search->get_age()).toInt() == age)
                       {
                           count_results++;
                           ui->search_table->setRowCount(count_results);

                           // заполнение таблицы
                           item = new QTableWidgetItem(QString::number(current_search->get_current()));
                           ui->search_table->setItem(i, 0, item);
                           item = new QTableWidgetItem(current_search->get_category());
                           ui->search_table->setItem(i, 1, item);
                           item = new QTableWidgetItem(current_search->get_iid());
                           ui->search_table->setItem(i, 2, item);
                           item = new QTableWidgetItem(current_search->get_price());
                           ui->search_table->setItem(i, 3, item);
                           item = new QTableWidgetItem(current_search->get_firma());
                           ui->search_table->setItem(i, 4, item);
                           item = new QTableWidgetItem(current_search->get_age());
                           ui->search_table->setItem(i, 5, item);
                           item = new QTableWidgetItem(current_search->get_optional());
                           ui->search_table->setItem(i, 6, item);

                           i++;
                       }
                       current_search = current_search->next;
                   }
               ui->number_res_search->setText(QString::number(count_results)); // отображение количества результатов
           }
       }
    }
}


void MainWindow::on_add_pharmacy_clicked()
{
    ui->menu->setCurrentIndex(10);
}


void MainWindow::on_cancel_new_pharmacy_clicked()
{
    // очистка полей и переход к главному меню
    ui->menu->setCurrentIndex(0);
    ui->name->clear();
    ui->phone->clear();
    ui->adress->clear();
}


void MainWindow::on_add_new_pharmacy_clicked() // добавление новой аптеки
{
    bool correct_data = true; // флаг корректности данных

    // проверка корректности данных, нет ли пустых полей
    if (ui->name->text().isEmpty())
    {
        ui->name->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else
    {
        ui->name->setStyleSheet("background-color: white;");
    }
    if (ui->phone->text().isEmpty())
    {
        ui->phone->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else
    {
        ui->phone->setStyleSheet("background-color: white;");
    }
    if (ui->adress->text().isEmpty())
    {
        ui->adress->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else
    {
        ui->adress->setStyleSheet("background-color: white;");
    }

    if (correct_data == true)
    { // если введенные данные корректны
        // считывание данных из полей
        QString name = ui->name->text();
        QString phone = ui->phone->text();
        QString adress = ui->adress->text();

        current_pharmacy_artikul++; //новый артикул следующей аптеки
        pharmacy* new_shop = new pharmacy(); // создание нового магазина
        new_shop->set_data_pharmacy(name, adress, phone);
        new_shop->set_artikul(current_pharmacy_artikul);
        pharmacies->add_node(new_shop); // добавление аптеки в список
        current_pharmacy = new_shop; // новый магазин становится текущим

        update_table(); // обновление таблицы лекарств - пустая, т.к. аптека новая
        update_table_pharmacies(); // обновление таблицы магазинов

        // очистка формы и переход в главное меню
        ui->menu->setCurrentIndex(0);
        ui->name->clear();
        ui->phone->clear();
        ui->adress->clear();

        changed_data = true; // флаг модификации данных
    }
}


void MainWindow::on_change_pharmacy_clicked()
{
    ui->menu->setCurrentIndex(9);

}

void MainWindow::on_choose_new_pharmacy_2_clicked()
{
    if (ui->table_shops->rowCount() == 0)  // таблица пустая
    {
            QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else
    {
        QItemSelectionModel *selectionModel = ui->table_shops->selectionModel();
        if (selectionModel->hasSelection())
            {
            int row_shop = ui->table_shops->currentRow(); // считывание фокуса
            if (row_shop != -1)
            {
                QTableWidgetItem *curitem = ui->table_shops->item(row_shop, 0); // считывание артикула аптеки для поиска
                int id_shop = curitem->text().toInt();

                current_pharmacy = pharmacies->find_node(id_shop); // поиск аптеки с таким артикулом
                current_pharmacy_artikul = current_pharmacy->get_artikul();

                update_table(); // обновление таблицы лекарств
                ui->menu->setCurrentIndex(0); // возвращение в главное меню
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "No line is selected!");
        }
    }
    // очистка фокуса с таблицы
    ui->table_shops->clearFocus();
    ui->table_shops->clearSelection();
}


void MainWindow::on_edit_pharmacy_data_clicked() // редкатирование аптеки
{
    QItemSelectionModel *selectionModel = ui->table_shops->selectionModel();
    if (selectionModel->hasSelection()) // проверка фокуса
        {
        int row_shop = ui->table_shops->currentRow(); // считывание фокуса
        if (row_shop != -1)
        {
            ui->menu->setCurrentIndex(11);
            QTableWidgetItem *curitem = ui->table_shops->item(row_shop, 0);
            int id_pharmacy = curitem->text().toInt();
            pharmacy* edit_shop = pharmacies->find_node(id_pharmacy); // поиск магазина

            // запись в форму текущих данных
            ui->name_2->setText(edit_shop->get_name());
            ui->phone_2->setText(edit_shop->get_phone());
            ui->adress_2->setText(edit_shop->get_adress());
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "No line is selected!");
    }
    // очистка фокуса
    ui->table_shops->clearFocus();
    ui->table_shops->clearSelection();
}


void MainWindow::on_cancel_new_pharmacy_2_clicked()
{
    // переход к главному меню и очистка полей
    ui->menu->setCurrentIndex(0);
    ui->name_2->clear();
    ui->phone_2->clear();
    ui->adress_2->clear();
}


void MainWindow::on_edit_pharmacy_done_clicked() // отправка новых данных аптеки
{
    bool correct_data = true; // флаг корректности данных

    // проверка полей
    if (ui->name_2->text().isEmpty())
    {
        ui->name_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else
    {
        ui->name_2->setStyleSheet("background-color: white;");
    }
    if (ui->phone_2->text().isEmpty())
    {
        ui->phone_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else
    {
        ui->phone_2->setStyleSheet("background-color: white;");
    }
    if (ui->adress_2->text().isEmpty())
    {
        ui->adress_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else
    {
        ui->adress_2->setStyleSheet("background-color: white;");
    }

    if (correct_data == true)
    { // если введенные данные корректы
        // считывание данных из полей
        QString name = ui->name_2->text();
        QString phone = ui->phone_2->text();
        QString adress = ui->adress_2->text();

        int row_shop = ui->table_shops->currentRow(); // считывание фокуса
        QTableWidgetItem *curitem = ui->table_shops->item(row_shop, 0); // считывание артикула
        int id_shop = curitem->text().toInt();

        pharmacy* edit_shop = pharmacies->find_node(id_shop); // поиск изменяемого магазина
        edit_shop->set_data_pharmacy(name, adress, phone); // установка новых значений
        if (current_pharmacy_artikul == edit_shop->get_artikul())
        {
            current_pharmacy = edit_shop;
        } // если текущий артикул совпадает с артикулом изменяемого магазина

        update_table_pharmacies(); // обновление таблицы магазинов

        // очистка формы и переход в главное меню
        ui->menu->setCurrentIndex(0);
        ui->name_2->clear();
        ui->phone_2->clear();
        ui->adress_2->clear();

        changed_data = true; // данные изменены
    }
}


void MainWindow::write_in_file(QFile &file) // запись в файл
{ // хапись в файл
    QTextStream stream(&file);
    stream.setCodec("UTF-8");

    stream << pharmacies->get_count_all() << endl; // запись количества магазинов
    pharmacy* write_current_shop = pharmacies->get_head();
    while (write_current_shop != nullptr)
    { // цикл по магазинам
        stream << write_current_shop->get_name() << endl;
        stream << write_current_shop->get_adress() << endl;
        stream << write_current_shop->get_phone() << endl;
        medicine_list* write_current_products = write_current_shop->get_medicines();
        stream << write_current_products->get_count() << endl; // запись количества продуктов магазина
        medicine* write_current_product = write_current_products->get_head();
        while (write_current_product != nullptr)
        { // цикл по продуктам магазина
            stream << write_current_product->get_category() << endl;
            stream << write_current_product->get_iid() << endl;
            stream << write_current_product->get_age() << endl;
            stream << write_current_product->get_price() << endl;
            stream << write_current_product->get_firma() << endl;
            stream << write_current_product->get_first() << endl;
            stream << write_current_product->get_second() << endl;
            stream << write_current_product->get_third() << endl;
            write_current_product = write_current_product->next; // следующий продукт
        }
        write_current_shop = write_current_shop->get_next(); // следующий магазин
    }
}


void MainWindow::on_Save_as_triggered()
{ // сохранение под новым именем
    QFile file;

    QString fileName = QFileDialog::getSaveFileName(this, "Save as ...", QDir::homePath(), "Text file (*.txt)");
    if (!fileName.isEmpty())
    {
        current_file = fileName;
        file.setFileName(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);

        write_in_file(file); // запись в файл
        changed_data = false;
        file.close();
    }
}


void MainWindow::on_Save_triggered()
{ // сохранение файла
    QFile file;

    if(current_file == "")
    {
        on_Save_as_triggered();
    } // если никакой файл не открыт, то просим пользователя создать
    else
    {
        file.setFileName(current_file);
        file.open(QIODevice::WriteOnly | QIODevice::Text);

        write_in_file(file); // запись в файл
        changed_data = false;
        file.close();
    }
}


void MainWindow::on_Create_new_triggered()
{ // создание нового файла
    if (changed_data)
    { // если данные были изменены
        QMessageBox msgBox;
        msgBox.setText("Save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int res = msgBox.exec();
        if(res == QMessageBox::Yes)
        {
            on_Save_triggered();
        } // сохранение изменений перед создание нового файла
    }

    // создание новой сети магазинов с одним магазином по умолчанию
    pharmacies->clear_list();
    current_pharmacy->medicines->clear_list();
    pharmacies->add_node(current_pharmacy);

    update_table(); // обновление таблицы продуктов
    update_table_pharmacies(); // обновление таблицы магазинов
    current_file = "";

    changed_data = false; // сбрасываем флаг модификации данных - файл пустой
}


void MainWindow::on_Exit_triggered()
{ // закрытие программы
    if (changed_data == true)
    {
        QMessageBox msgBox;
        msgBox.setText("Save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int res = msgBox.exec();

        if(res == QMessageBox::Yes)
        {
            on_Save_triggered();
        } // сохранение изменений перед закрытием
    }

    close();
}


void MainWindow::on_About_triggered()
{ // о программе
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    msgBox.setText("The program by \nAll roots reserved");
    msgBox.exec();
}


void MainWindow::on_Help_triggered()
{ // справка
    QMessageBox msgBox;
    msgBox.setWindowTitle("How use this app");
    msgBox.setText("This program is very easy in using!\nYou will get success!\nWe belive that you will enjoy!");
    msgBox.exec();
}


void MainWindow::on_Open_triggered()
{ // открытие файла
    if (changed_data) { // если текущий файл был изменен
        QMessageBox msgBox;
        msgBox.setText("Save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int res = msgBox.exec();

        if(res == QMessageBox::Yes)
        {
            on_Save_triggered();
        } // сохранение изменений перед открытием
    }

    // очистка списков и таблиц
    pharmacies->clear_list();
    current_pharmacy->medicines->clear_list();
    update_table();
    update_table_pharmacies();
    changed_data = false;

    QString fileName = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "Text file (*.txt)");

    if(!fileName.isEmpty()) // если файл не пустой
    {
        current_file = fileName;

        QFile file(fileName);
        file.open(QIODevice::ReadOnly);

        QTextStream stream(&file);
        stream.setCodec("UTF-8");

        int count_shops = (stream.readLine()).toInt(); // считываем количество магазинов

        for(int i = 0; i < count_shops; i++)
        {

            QString name = stream.readLine();
            QString adress = stream.readLine();
            QString phone = stream.readLine();

            int count_products = (stream.readLine()).toInt(); // считываем количество продуктов в конкретном магазине
            pharmacy* current = new pharmacy(); // создание магазина
            current->set_data_pharmacy(name, adress, phone);
            current->set_artikul(current_pharmacy_artikul);
            current_pharmacy_artikul++;

            for (int j = 0; j < count_products; j++)
            {
                // считывание данных
                QString category = stream.readLine();
                QString iid = stream.readLine();
                QString age = stream.readLine();
                QString price = stream.readLine();
                QString firma = stream.readLine();
                // создание узлов и добавление их в список
                if (category == "Vitamins")
                {
                    QString season = stream.readLine();
                    QString type = stream.readLine();
                    QString time = stream.readLine();
                    medicine* new_product = new vitamins(iid, price, firma, age, season, type, time);
                    current->medicines->add_node(new_product);

                }
                if (category == "Antibiotic")
                {
                    QString period = stream.readLine();
                    QString country = stream.readLine();
                    QString danger = stream.readLine();
                    medicine* new_product = new antibiotic(iid, price, firma, age, period, danger, country);
                    current->medicines->add_node(new_product);
                }
                if (category == "Antipyretic")
                {
                    QString power = stream.readLine();
                    QString substance = stream.readLine();
                    QString concentration = stream.readLine();
                    medicine* new_product = new antipyretic(iid, price, firma, age, power, substance, concentration);
                    current->medicines->add_node(new_product);
                }
            }
            pharmacies->add_node(current); // добавление магазина в список
            current_pharmacy = current; // изменение текушего магазина
        }

        update_table(); // обновление таблицы продуктов
        update_table_pharmacies(); // обновление таблицы магазинов
        changed_data = false; // данные еще не изменялись
        file.close(); // закрытие файла
    }
}


void MainWindow::on_delete_pharmacy_clicked() // удаление аптеки
{
    if (ui->table_shops->rowCount() == 0)
    { // таблица пустая
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else
    {
        QItemSelectionModel *selectionModel = ui->table_shops->selectionModel();
        if (selectionModel->hasSelection()) // проверка фокуса
        {
            int row_shop = ui->table_shops->currentRow(); // считывание фокуса
            if (row_shop != -1)
            {

                QTableWidgetItem *curitem = ui->table_shops->item(row_shop, 0); // считывание артикула аптеки для поиска
                int id_shop = curitem->text().toInt();

                pharmacies->delete_node(id_shop); // удаление аптеки с таким артикулом

                update_table(); // обновление таблицы
                update_table_pharmacies(); // обновление таблицы аптек

                ui->menu->setCurrentIndex(0); // возвращение в главное меню

                changed_data = true; // флаг модификации данных
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "No line is selected!");
        }
    }
}


void MainWindow::on_stay_pharmacy_clicked()
{
    // очистка фокуса и переход в главное меню
    ui->menu->setCurrentIndex(0);
    ui->table_shops->clearFocus();
    ui->table_shops->clearSelection();
}


void MainWindow::on_cancel_vitamins_2_clicked()
{
    // очистка фокуса и переход в главное меню
    ui->menu->setCurrentIndex(0);
    ui->main_table->clearFocus();
    ui->main_table->clearSelection();
}


void MainWindow::on_cancel_antibiotic_2_clicked()
{
    // очистка фокуса и переход в главное меню
    ui->menu->setCurrentIndex(0);
    ui->main_table->clearFocus();
    ui->main_table->clearSelection();
}


void MainWindow::on_cancel_antipyretic_2_clicked()
{
     // очистка фокуса и переход в главное меню
    ui->menu->setCurrentIndex(0);
    ui->main_table->clearFocus();
    ui->main_table->clearSelection();
}


void MainWindow::on_search_by_artikul_clicked() // поиск по артикулу - открытие формы
{
    ui->menu->setCurrentIndex(14);
    ui->tables->setCurrentIndex(1);
}


void MainWindow::on_cancel_search_3_clicked() // выход из поиска
{
    ui->menu->setCurrentIndex(0);
    ui->tables->setCurrentIndex(0);
}


void MainWindow::on_search_artikul_medicine_clicked()
{
    bool correct_data = true; // флаг корректности данных

       // проверка корректности введенных данных
       if (ui->artikul_search->text().isEmpty())
       {
           correct_data = false;
           ui->artikul_search->setStyleSheet("background-color: red;");
       }
       else
       {
           ui->artikul_search->setStyleSheet("background-color: white;");
       }

       if (correct_data == true)
       { // если данные корректны
           // считывание данных
           int artikul = (ui->artikul_search->text()).toInt();
           bool all_shops_search = ui->where_search_3->isChecked();
           QString type = ui->type_product_3->currentText();

           int count_results = 0;
           ui->search_table->setRowCount(count_results);
           if (type == "Vitamins" || type == "Antibiotic" || type == "Antipyretic")
           { // поиск по конкретному типу лекарства
               if (all_shops_search == true) { // поиск по всем магазинам сети
                   pharmacy* search_shop = pharmacies->get_head();
                   QTableWidgetItem *item;
                   int i = 0;
                   count_results = 0;
                   ui->search_table->setRowCount(count_results);
                   while (search_shop != nullptr)
                   { // цикл по магазинам
                       medicine_list* search_products = search_shop->get_medicines();
                       medicine* current_search = search_products->head;
                       while (current_search != nullptr) { // цикл по продуктам магазина
                           if ((current_search->get_iid()).toInt() == artikul && (current_search->get_category() == type)) {
                               count_results++;
                               ui->search_table->setRowCount(count_results);

                               // заполнение таблицы
                               item = new QTableWidgetItem(QString::number(current_search->get_current()));
                               ui->search_table->setItem(i, 0, item);
                               item = new QTableWidgetItem(current_search->get_category());
                               ui->search_table->setItem(i, 1, item);
                               item = new QTableWidgetItem(current_search->get_iid());
                               ui->search_table->setItem(i, 2, item);
                               item = new QTableWidgetItem(current_search->get_price());
                               ui->search_table->setItem(i, 3, item);
                               item = new QTableWidgetItem(current_search->get_firma());
                               ui->search_table->setItem(i, 4, item);
                               item = new QTableWidgetItem(current_search->get_age());
                               ui->search_table->setItem(i, 5, item);
                               item = new QTableWidgetItem(current_search->get_optional());
                               ui->search_table->setItem(i, 6, item);

                               i++;
                           }
                           current_search = current_search->next;
                       }
                       search_shop = search_shop->get_next();
                   }
                   ui->number_res_search->setText(QString::number(count_results)); // отображение количества результатов поиска
               }
               else // поиск только в текущем магазине
               {
                   medicine_list* search_products = current_pharmacy->get_medicines(); // список продуктов магазина
                   medicine* current_search = search_products->head;
                   QTableWidgetItem *item;
                   int i = 0;
                   count_results = 0;
                   ui->search_table->setRowCount(count_results);
                   while (current_search != nullptr)
                   { // цикл по продуктам
                       if ((current_search->get_iid()).toInt() == artikul && (current_search->get_category() == type))
                       {
                           count_results++;
                           ui->search_table->setRowCount(count_results);

                           // заполнение таблицы
                           item = new QTableWidgetItem(QString::number(current_search->get_current()));
                           ui->search_table->setItem(i, 0, item);
                           item = new QTableWidgetItem(current_search->get_category());
                           ui->search_table->setItem(i, 1, item);
                           item = new QTableWidgetItem(current_search->get_iid());
                           ui->search_table->setItem(i, 2, item);
                           item = new QTableWidgetItem(current_search->get_price());
                           ui->search_table->setItem(i, 3, item);
                           item = new QTableWidgetItem(current_search->get_firma());
                           ui->search_table->setItem(i, 4, item);
                           item = new QTableWidgetItem(current_search->get_age());
                           ui->search_table->setItem(i, 5, item);
                           item = new QTableWidgetItem(current_search->get_optional());
                           ui->search_table->setItem(i, 6, item);

                           i++;
                       }
                       current_search = current_search->next;
                   }
               ui->number_res_search->setText(QString::number(count_results)); // отображение количества результатов
               }
           }
           else // поиск среди продуктов всех типов
           {

               if (all_shops_search == true) // поиск во всех магазинах сети
               {
                   pharmacy* search_shop = pharmacies->get_head();
                   QTableWidgetItem *item;
                   int i = 0;
                   count_results = 0;
                   ui->search_table->setRowCount(count_results);
                   while (search_shop != nullptr)
                   { // цикл по магазинам
                       medicine_list* search_products = search_shop->get_medicines();
                       medicine* current_search = search_products->head;
                       while (current_search != nullptr)
                       { // цикл по продуктам
                           if ((current_search->get_iid()).toInt() == artikul)
                           {
                               count_results++;
                               ui->search_table->setRowCount(count_results);

                               // заполнение таблицы
                               item = new QTableWidgetItem(QString::number(current_search->get_current()));
                               ui->search_table->setItem(i, 0, item);
                               item = new QTableWidgetItem(current_search->get_category());
                               ui->search_table->setItem(i, 1, item);
                               item = new QTableWidgetItem(current_search->get_iid());
                               ui->search_table->setItem(i, 2, item);
                               item = new QTableWidgetItem(current_search->get_price());
                               ui->search_table->setItem(i, 3, item);
                               item = new QTableWidgetItem(current_search->get_firma());
                               ui->search_table->setItem(i, 4, item);
                               item = new QTableWidgetItem(current_search->get_age());
                               ui->search_table->setItem(i, 5, item);
                               item = new QTableWidgetItem(current_search->get_optional());
                               ui->search_table->setItem(i, 6, item);

                               i++;
                           }
                           current_search = current_search->next;
                       }
                       search_shop = search_shop->get_next();
                   }
                   ui->number_res_search->setText(QString::number(count_results)); // отображение количества результатов
               }
               else // поиск только в текущем магазине
               {
                   medicine_list* search_products = current_pharmacy->get_medicines(); // список продуктов текущей аптеки
                   medicine* current_search = search_products->head;
                   QTableWidgetItem *item;
                   int i = 0;
                   count_results = 0;

                   while (current_search != nullptr)
                   { // цикл по продуктам магазина
                       if ((current_search->get_iid()).toInt() == artikul) // если найден нужный артикул
                       {
                           count_results++;
                           ui->search_table->setRowCount(count_results);

                           // заполнение таблицы
                           item = new QTableWidgetItem(QString::number(current_search->get_current()));
                           ui->search_table->setItem(i, 0, item);
                           item = new QTableWidgetItem(current_search->get_category());
                           ui->search_table->setItem(i, 1, item);
                           item = new QTableWidgetItem(current_search->get_iid());
                           ui->search_table->setItem(i, 2, item);
                           item = new QTableWidgetItem(current_search->get_price());
                           ui->search_table->setItem(i, 3, item);
                           item = new QTableWidgetItem(current_search->get_firma());
                           ui->search_table->setItem(i, 4, item);
                           item = new QTableWidgetItem(current_search->get_age());
                           ui->search_table->setItem(i, 5, item);
                           item = new QTableWidgetItem(current_search->get_optional());
                           ui->search_table->setItem(i, 6, item);

                           i++;
                       }
                       current_search = current_search->next; // переход к следующему узлу
                   }
               ui->number_res_search->setText(QString::number(count_results)); // отображение количества результатов
           }
       }
    }
}
