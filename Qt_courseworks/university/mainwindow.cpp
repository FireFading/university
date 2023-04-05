#include "mainwindow.h"
#include "ui_mainwindow.h"

List_employees* temp_list;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Information retrieval system \"University\"");
    University = new List_branches(); // список филиалов - университет
    save_flag = false; // флаг сохранения
    filename = ""; //текущий файл

    // установка начального меню
    ui->stackedWidget_3->setCurrentIndex(2);
    ui->stackedWidget->setCurrentIndex(8);

    // установка доступа к кнопкам
    ui->Return->setDisabled(0);
    ui->edit_director->setDisabled(1);
    ui->edit_teacher->setDisabled(1);
    ui->edit_security->setDisabled(1);
    ui->edit_br->setDisabled(1);
    ui->Search->setDisabled(1);

    ui->table1->setEditTriggers(QAbstractItemView::NoEditTriggers); // запрет на изменение
    ui->table1->setSelectionBehavior(QAbstractItemView::SelectRows); // выбор строк
    ui->table1->setSelectionMode(QAbstractItemView::SingleSelection); // только одна строка выбора
    ui->table1->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // размер таблицы в соответствии с контентом

    // установка высоты строк
    ui->table1->setRowHeight(1000, 25);
    ui->table2->setRowHeight(1000, 25);
    ui->table3->setRowHeight(1000, 25);

    ui->table2->setEditTriggers(QAbstractItemView::NoEditTriggers); // запрет на изменение
    ui->table2->setSelectionBehavior(QAbstractItemView::SelectRows); // выбор строк
    ui->table2->setSelectionMode(QAbstractItemView::SingleSelection); // только одна строка выбора
    ui->table2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // размер таблицы в соответствии с контентом

    ui->table3->setEditTriggers(QAbstractItemView::NoEditTriggers); // запрет на изменение
    ui->table3->setSelectionBehavior(QAbstractItemView::SelectRows); // выбор строк
    ui->table3->setSelectionMode(QAbstractItemView::SingleSelection); // только одна строка выбора
    ui->table3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // размер таблицы в соответствии с контентом

    QRegExp num1("[0-9]{1,8}"); //Ввод только цифр
    QValidator *num1Validator = new QRegExpValidator(num1, this);
    QRegExp name("[A-Za-zА-Яа-яЁё]{1}[A-Za-zА-Яа-яЁё\\s\\.]{1,30}"); //Ввод только букв латиницы или кириллицы, пробелов и точек
    QValidator *strValidator = new QRegExpValidator(name, this);
    QRegExp num2("[0-9]{1,11}"); //Ввод только цифр
    QValidator *num2Validator = new QRegExpValidator(num2, this);

    // установка валидаторов
    ui->id_director->setValidator(num1Validator);
    ui->id_teacher->setValidator(num1Validator);
    ui->id_security->setValidator(num1Validator);
    ui->full_name_director->setValidator(strValidator);
    ui->full_name_teacher->setValidator(strValidator);
    ui->full_name_security->setValidator(strValidator);
    ui->age_director->setValidator(num1Validator);
    ui->age_teacher->setValidator(num1Validator);
    ui->age_security->setValidator(num1Validator);
    ui->subject_teacher->setValidator(strValidator);
    ui->salary_director->setValidator(num2Validator);
    ui->salary_teacher->setValidator(num2Validator);
    ui->salary_security->setValidator(num2Validator);
    ui->index_b->setValidator(num1Validator);
    ui->region_b->setValidator(strValidator);
    ui->city_b->setValidator(strValidator);
    ui->number_b->setValidator(num2Validator);
    ui->house_b->setValidator(num2Validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// очистка форм
void MainWindow::clear_director_fields()
{
    ui->id_director->clear();
    ui->full_name_director->clear();
    ui->age_director->clear();
    ui->salary_director->clear();
    ui->subordinates_number_director->clear();
}

void MainWindow::clear_b()
{
    ui->region_b->clear();
    ui->city_b->clear();
    ui->street_b->clear();
    ui->index_b->clear();
    ui->name_b->clear();
    ui->number_b->clear();
}

void MainWindow::clear_teacher_fields()
{
    ui->id_teacher->clear();
    ui->full_name_teacher->clear();
    ui->age_teacher->clear();
    ui->salary_teacher->clear();
    ui->subject_teacher->clear();
}

void MainWindow::clear_security_fields()
{
    ui->id_security->clear();
    ui->full_name_security->clear();
    ui->age_security->clear();
    ui->salary_security->clear();
    ui->gun_license_security->clear();
}

void MainWindow::write_to_file(QString str1) // запись в файл
{
    QFile file(str1);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) // открытие файла
    {
        QTextStream out(&file);
        Branch *B = University->get_head();
        for (int i = 0; i < University->get_count(); i++) // цикл по филиалам
        {
            out << B->get_name() << "|"
                << B->get_index() << "|"
                << B->get_region() << "|"
                << B->get_city() << "|"
                << B->get_street() << "|"
                << B->get_house() << "|"
                << B->get_number() << endl;
            Employee *E = B->get_list()->get_head();
            for (int j = 0; j < B->get_list()->get_count(); j++) // цикл по работникам
            {
                out << " " << E->get_id() << "|"
                    << E->get_type() << "|"
                    << E->get_full_name() << "|"
                    << E->get_age() << "|"
                    << E->get_salary() << "|";
                if (E->get_type() == "Director")
                {
                    out << dynamic_cast<Director *>(E)->get_subordinates_number() << "|"
                        << B->get_name() << endl;
                }
                else if (E->get_type() == "Teacher")
                {
                    out << dynamic_cast<Teacher *>(E)->get_subject() << "|"
                        << B->get_name() << endl;
                }
                else if (E->get_type() == "Security")
                {
                    out << dynamic_cast<Security *>(E)->get_gun_license() << "|"
                        << B->get_name() << endl;
                }

                E = E->get_next();
            }
            B = B->get_next();
        }
    }
    else { // если не получилось открыть файл
        QMessageBox::warning(this, "Error", "Unable to open file");
    }
}

void MainWindow::tab1() // обновление таблицы работнико
{
    Branch* current_branch = University->get_head();

    // счетчики для заполнения таблиц
    int j = 0; // количество работников во всех филиалах - счетчик
    int k = 0; // количество филиалов - счетчик
    ui->table1->setRowCount(0); // очистка таблицы
    while (k < University->get_count_branches()) { // цикл по филиалам

        Employee* current_employee = current_branch->get_list()->get_head();

        while (current_employee != nullptr) { // цикл по списку работников
            ui->table1->setRowCount(j+1); // установка нового количества строк

            // заполнение таблицы
            ui->table1->setItem(j, 0, new QTableWidgetItem(current_employee->get_id()));
            ui->table1->setItem(j, 1, new QTableWidgetItem(current_employee->get_type()));
            ui->table1->setItem(j, 2, new QTableWidgetItem(current_employee->get_full_name()));
            ui->table1->setItem(j, 3, new QTableWidgetItem(current_employee->get_age()));
            ui->table1->setItem(j, 4, new QTableWidgetItem(current_employee->get_salary()));
            ui->table1->setItem(j, 6, new QTableWidgetItem(current_branch->get_name()));
            if (current_employee->get_type() == "Director")
            {
                ui->table1->setItem(j, 5, new QTableWidgetItem(dynamic_cast<Director *>(current_employee)->get_subordinates_number()));
            }
            else if (current_employee->get_type() == "Teacher")
            {
                ui->table1->setItem(j, 5, new QTableWidgetItem(dynamic_cast<Teacher *>(current_employee)->get_subject()));
            }
            else if (current_employee->get_type() == "Security")
            {
                ui->table1->setItem(j, 5, new QTableWidgetItem(dynamic_cast<Security *>(current_employee)->get_gun_license()));
            }

            current_employee = current_employee->get_next(); // переход к следующему работнику
            j++;
        }
        current_branch = current_branch->get_next(); // переход к следующему филиалу
        k++;
    }
}

void MainWindow::tab2() // заполнение таблицы с филиалами
{
    ui->table3->setRowCount(University->get_count_branches()); // установка количества строк
    Branch* current_branch = University->get_head();

    int j = 0; // счетчик для заполнения таблицы
    while (j < University->get_count_branches()) { // цикл по филиалам

        // заполнение таблицы
        ui->table3->setItem(j, 0, new QTableWidgetItem(current_branch->get_name()));
        ui->table3->setItem(j, 1, new QTableWidgetItem(current_branch->get_index()));
        ui->table3->setItem(j, 2, new QTableWidgetItem(current_branch->get_region()));
        ui->table3->setItem(j, 3, new QTableWidgetItem(current_branch->get_city()));
        ui->table3->setItem(j, 4, new QTableWidgetItem(current_branch->get_street()));
        ui->table3->setItem(j, 5, new QTableWidgetItem(current_branch->get_house()));
        ui->table3->setItem(j, 6, new QTableWidgetItem(current_branch->get_number()));

        j++;
        current_branch = current_branch->get_next(); // переход к следующему филиалу
    }
}

// переходы в меню по кнопкам
void MainWindow::on_search_by_activated(int index)
{
    if (index == 1)
        ui->stackedWidget_2->setCurrentIndex(1);
    else
        ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_Search_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->Return->setDisabled(0);
}

void MainWindow::on_Return_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(0);
    ui->Return->setDisabled(1);
}

void MainWindow::on_Choose_clicked()
{
    if (University->get_count() != 0)
    {
        ui->add_director->setDisabled(0);
        ui->add_teacher->setDisabled(0);
        ui->add_security->setDisabled(0);
        ui->edit_director->setDisabled(1);
        ui->edit_teacher->setDisabled(1);
        ui->edit_security->setDisabled(1);
        ui->Return->setDisabled(0);
        int x = ui->tip->currentIndex();
        if (x == 0)
            ui->stackedWidget->setCurrentIndex(1);
        if (x == 1)
            ui->stackedWidget->setCurrentIndex(2);
        if (x == 2)
            ui->stackedWidget->setCurrentIndex(3);
    }
    else
        QMessageBox::warning(this, "Error", "Unable to add new employee");
}

void MainWindow::on_add_br_clicked() // добавление филиала
{
    ui->Return->setDisabled(1);
    bool not_correct = false;
    if (ui->name_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_name_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_name_b->setStyleSheet("QLabel { color : white; }");
    QString temp_name = ui->name_b->text();
    bool correct_name = true;
    for (int i = 0; i < ui->table3->rowCount(); i++)
    {
        if (ui->table3->item(i, 0)->text() == temp_name)
        {
            correct_name = false;
        }
    }
    if (!correct_name)
    {
        not_correct = true;
        ui->label_name_b->setStyleSheet("QLabel { color : red; }");
    }

    if (ui->number_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_number_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_number_b->setStyleSheet("QLabel { color : white; }");
    if (ui->index_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_index_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_index_b->setStyleSheet("QLabel { color : white; }");
    if (ui->region_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_region_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_region_b->setStyleSheet("QLabel { color : white; }");
    if (ui->city_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_city_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_city_b->setStyleSheet("QLabel { color : white; }");
    if (ui->street_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_street_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_street_b->setStyleSheet("QLabel { color : white; }");
    if (ui->house_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_house_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_house_b->setStyleSheet("QLabel { color : white; }");
    if (!not_correct) // если все данные корретны
    {
        // считывание данных из полей
        QString region = ui->region_b->text();
        QString city = ui->city_b->text();
        QString street = ui->street_b->text();
        QString index = ui->index_b->text();
        QString number = ui->number_b->text();
        QString house = ui->house_b->text();
        QString name = ui->name_b->text();

        University->add_branch(name, index, region, city, street, house, number); // добавление нового филиала в университет
        // обновление таблиц
        tab1();
        tab2();

        // добавление нового филиала в выбор при добавлениии сотрудника
        ui->branch_director->addItem(name);
        ui->branch_security->addItem(name);
        ui->branch_teacher->addItem(name);
        ui->choice_b->addItem(name);

        clear_b(); // очистка полей

        // переход в главное меню
        ui->stackedWidget->setCurrentIndex(0);
        ui->stackedWidget_3->setCurrentIndex(0);

        if (University->get_count() != 0)
            ui->tip->setDisabled(0);
        save_flag = false;
    }
    else // данные некорректны
    {
        QMessageBox::warning(this, "Error", "Incorrect data entered");
    }
}

void MainWindow::on_add_b_clicked() // переход к форме добавления филиала
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->add_br->setDisabled(0);
    ui->edit_br->setDisabled(1);
}


void MainWindow::on_add_director_clicked() // добавление директорв
{
    ui->Return->setDisabled(1);
    bool not_correct = false;
    if (ui->id_director->text().isEmpty())
    {
        not_correct = true;
        ui->label_id_director->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_id_director->setStyleSheet("QLabel { color : white; }");
    QString temp_id = ui->id_director->text();
    bool correct_id = true;
    for (int i = 0; i < ui->table1->rowCount(); i++)
    {
        if (ui->table1->item(i, 0)->text() == temp_id)
        {
            correct_id = false;
        }
    }
    if (!correct_id)
    {
        not_correct = true;
        ui->label_id_director->setStyleSheet("QLabel { color : red; }");
    }

    if (ui->full_name_director->text().isEmpty())
    {
        not_correct = true;
        ui->label_full_name_director->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_full_name_director->setStyleSheet("QLabel { color : white; }");
    if (ui->age_director->text().isEmpty())
    {
        not_correct = true;
        ui->label_age_director->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_age_director->setStyleSheet("QLabel { color : white; }");
    if (ui->salary_director->text().isEmpty())
    {
        not_correct = true;
        ui->label_salary_director->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_salary_director->setStyleSheet("QLabel { color : white; }");
    if (ui->subordinates_number_director->text().isEmpty())
    {
        not_correct = true;
        ui->label_subordinates_number_director->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_subordinates_number_director->setStyleSheet("QLabel { color : white; }");
    if (!not_correct) // данные корректны
    {
        QString current_name = ui->branch_director->currentText(); // считывание филиала, в котором будет работник
        Branch *B = University->get_head();
        int j = 0;
        while (B->get_name() != current_name) // поиск филиала в списке по имени
        {
            B = B->get_next();
            j++;
        }

        // считывание данных из полей
        QString id = ui->id_director->text();
        QString full_name = ui->full_name_director->text();
        QString age = ui->age_director->text();
        QString salary = ui->salary_director->text();
        QString subordinates_number = ui->subordinates_number_director->text();

        B->get_list()->add_director(id, full_name, age, salary, subordinates_number); // добавление сотрудника
        tab1(); // обновление таблицы
        clear_director_fields(); // очистка полей

        // переход в главное меню
        ui->stackedWidget->setCurrentIndex(0);
        ui->Search->setDisabled(0);

        save_flag = false;
    }
    else // данные некорректны
    {
        QMessageBox::warning(this, "Error", "Incorrect data entered");
    }
}

void MainWindow::on_add_teacher_clicked() // добавление учителя
{
    ui->Return->setDisabled(1);
    bool not_correct = false;
    if (ui->id_teacher->text().isEmpty())
    {
        not_correct = true;
        ui->label_id_teacher->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_id_teacher->setStyleSheet("QLabel { color : white; }");
    QString temp_id = ui->id_teacher->text();
    bool correct_id = true;
    for (int i = 0; i < ui->table1->rowCount(); i++)
    {
        if (ui->table1->item(i, 0)->text() == temp_id)
        {
            correct_id = false;
        }
    }
    if (!correct_id)
    {
        not_correct = true;
        ui->label_id_teacher->setStyleSheet("QLabel { color : red; }");
    }

    if (ui->full_name_teacher->text().isEmpty())
    {
        not_correct = true;
        ui->label_full_name_teacher->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_full_name_teacher->setStyleSheet("QLabel { color : white; }");
    if (ui->age_teacher->text().isEmpty())
    {
        not_correct = true;
        ui->label_age_teacher->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_age_teacher->setStyleSheet("QLabel { color : white; }");
    if (ui->salary_teacher->text().isEmpty())
    {
        not_correct = true;
        ui->label_salary_teacher->setStyleSheet("QLabel { color : red; }");
    }
    if (ui->subject_teacher->text().isEmpty())
    {
        not_correct = true;
        ui->label_subject_teacher->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_subject_teacher->setStyleSheet("QLabel { color : white; }");
    if (!not_correct) // данные корреткны
    {
        QString current_name = ui->branch_teacher->currentText(); // считывание филиала, в котором будет работник
        Branch *B = University->get_head();
        while (B->get_name() != current_name) // поиск филиала по названию
        {
            B = B->get_next();
        }

        // считывание данных из полей
        QString id = ui->id_teacher->text();
        QString full_name = ui->full_name_teacher->text();
        QString age = ui->age_teacher->text();
        QString salary = ui->salary_teacher->text();
        QString subject = ui->subject_teacher->text();

        B->get_list()->add_teacher(id, full_name, age, salary, subject); // добавление сотрудника
        tab1(); // обновление таблицы
        clear_teacher_fields(); // очистка полей

        // переход в главное меню
        ui->stackedWidget->setCurrentIndex(0);
        ui->Search->setDisabled(0);
        save_flag = false;
    }
    else // данные некорректны
    {
        QMessageBox::warning(this, "Error", "Incorrect data entered");
    }
}


void MainWindow::on_add_security_clicked()
{
    ui->Return->setDisabled(1);
    bool not_correct = false;
    if (ui->id_security->text().isEmpty())
    {
        not_correct = true;
        ui->label_id_security->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_id_security->setStyleSheet("QLabel { color : white; }");
    QString temp_id = ui->id_security->text();
    bool correct_id = true;
    for (int i = 0; i < ui->table1->rowCount(); i++)
    {
        if (ui->table1->item(i, 0)->text() == temp_id)
        {
            correct_id = false;
        }
    }
    if (!correct_id)
    {
        not_correct = true;
        ui->label_id_security->setStyleSheet("QLabel { color : red; }");
    }

    if (ui->full_name_security->text().isEmpty())
    {
        not_correct = true;
        ui->label_full_name_security->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_full_name_security->setStyleSheet("QLabel { color : white; }");
    if (ui->age_security->text().isEmpty())
    {
        not_correct = true;
        ui->label_age_security->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_age_security->setStyleSheet("QLabel { color : white; }");
    if (ui->salary_security->text().isEmpty())
    {
        not_correct = true;
        ui->label_salary_security->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_salary_security->setStyleSheet("QLabel { color : white; }");
    if (ui->gun_license_security->text().isEmpty())
    {
        not_correct = true;
        ui->label_gun_license_security->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_gun_license_security->setStyleSheet("QLabel { color : white; }");
    if (!not_correct) // данные корректны
    {
        QString current_name = ui->branch_security->currentText(); // считывание филиала, в котором будет сотрудник
        Branch *B = University->get_head();
        while (B->get_name() != current_name) // поиск филиала по названию
        {
            B = B->get_next();
        }

        // считывание данных из полей
        QString id = ui->id_security->text();
        QString full_name = ui->full_name_security->text();
        QString age = ui->age_security->text();
        QString salary = ui->salary_security->text();
        QString gun_license = ui->gun_license_security->text();

        B->get_list()->add_security(id, full_name, age, salary, gun_license); // добавление сотрудника
        tab1(); // обновление таблицы

        clear_security_fields(); // очистка полей

        // переход в главное меню
        ui->stackedWidget->setCurrentIndex(0);
        ui->Search->setDisabled(0);
        save_flag = false;
    }
    else // данные корретны
    {
        QMessageBox::warning(this, "Error", "Incorrect data entered");
    }
}

void MainWindow::on_Edit_clicked() // изменение данных о сотруднике
{
    QItemSelectionModel *selectionModel = ui->table1->selectionModel();
    if (selectionModel->hasSelection()) // проверка фокуса
    {
        ui->edit_director->setDisabled(0);
        ui->edit_teacher->setDisabled(0);
        ui->edit_security->setDisabled(0);
        ui->add_director->setDisabled(1);
        ui->add_teacher->setDisabled(1);
        ui->add_security->setDisabled(1);
        int item = ui->table1->currentRow(); // считывание текущей строки

        QString type = ui->table1->item(item, 1)->text(); // считывание профессии работника
        save_flag = false;
        if (type == "Director")
        {
            ui->stackedWidget->setCurrentIndex(1); // переход к форме

            // заполнение формы текущими данными
            ui->id_director->setText(ui->table1->item(item, 0)->text());
            ui->full_name_director->setText(ui->table1->item(item, 2)->text());
            ui->age_director->setText(ui->table1->item(item, 3)->text());
            ui->salary_director->setText(ui->table1->item(item, 4)->text());
            ui->subordinates_number_director->setText(ui->table1->item(item, 5)->text());
            QString name = ui->table1->item(item, 6)->text();
            ui->branch_director->setCurrentText(name);

            Branch* edit_branch = University->get_head(); // поиск филиала, в которм находится работник
            while (edit_branch->get_name() != name) {
                edit_branch = edit_branch->get_next();
            }
            edit_branch->get_list()->del(ui->id_director->text().toInt()); // удаление старых данных
        }
        else if (type == "Teacher")
        {
            ui->stackedWidget->setCurrentIndex(2); // переход к форме

            // заполнение формы текущими данными
            ui->id_teacher->setText(ui->table1->item(item, 0)->text());
            ui->full_name_teacher->setText(ui->table1->item(item, 2)->text());
            ui->age_teacher->setText(ui->table1->item(item, 3)->text());
            ui->salary_teacher->setText(ui->table1->item(item, 4)->text());
            ui->subject_teacher->setText(ui->table1->item(item, 5)->text());
            QString name = ui->table1->item(item, 6)->text();
            ui->branch_director->setCurrentText(name);

            Branch* edit_branch = University->get_head(); // поиск филиала, в которм находится работник
            while (edit_branch->get_name() != name) {
                edit_branch = edit_branch->get_next();
            }
            edit_branch->get_list()->del(ui->id_teacher->text().toInt()); // удаление старых данных
        }
        else if (type == "Security")
        {
            ui->stackedWidget->setCurrentIndex(3); // переход к форме

            // заполнение формы текущими данными
            ui->id_security->setText(ui->table1->item(item, 0)->text());
            ui->full_name_security->setText(ui->table1->item(item, 2)->text());
            ui->age_security->setText(ui->table1->item(item, 3)->text());
            ui->salary_security->setText(ui->table1->item(item, 4)->text());
            ui->gun_license_security->setText(ui->table1->item(item, 5)->text());
            QString name = ui->table1->item(item, 6)->text();
            ui->branch_director->setCurrentText(name);

            Branch* edit_branch = University->get_head(); // поиск филиала, в которм находится работник
            while (edit_branch->get_name() != name) {
                edit_branch = edit_branch->get_next();
            }
            edit_branch->get_list()->del(ui->id_security->text().toInt()); // удаление старых данных
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", "Choose a line");
    }
}

void MainWindow::on_edit_director_clicked() // редактирование директора
{
    bool not_correct = false;
    if (ui->id_director->text().isEmpty())
    {
        not_correct = true;
        ui->label_id_director->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_id_director->setStyleSheet("QLabel { color : white; }");
    QString temp_id = ui->id_director->text();
    bool correct_id = true;
    for (int i = 0; i < ui->table1->rowCount(); i++)
    {
        if ((ui->table1->item(i, 0)->text() == temp_id) && (ui->table1->item(ui->table1->currentRow(), 0)->text() != temp_id))
        {
            correct_id = false;
        }
    }
    if (!correct_id)
    {
        not_correct = true;
        ui->label_id_director->setStyleSheet("QLabel { color : red; }");
    }

    if (ui->full_name_director->text().isEmpty())
    {
        not_correct = true;
        ui->label_full_name_director->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_full_name_director->setStyleSheet("QLabel { color : white; }");
    if (ui->age_director->text().isEmpty())
    {
        not_correct = true;
        ui->label_age_director->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_age_director->setStyleSheet("QLabel { color : white; }");
    if (ui->salary_director->text().isEmpty())
    {
        not_correct = true;
        ui->label_salary_director->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_salary_director->setStyleSheet("QLabel { color : white; }");
    if (ui->subordinates_number_director->text().isEmpty())
    {
        not_correct = true;
        ui->label_subordinates_number_director->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_subordinates_number_director->setStyleSheet("QLabel { color : white; }");
    if (!not_correct) // данные корректны
    {
        // считывание данных из полей
        QString id = ui->id_director->text();
        QString full_name = ui->full_name_director->text();
        QString age = ui->age_director->text();
        QString salary = ui->salary_director->text();
        QString subordinates_number = ui->subordinates_number_director->text();
        QString name_branch = ui->branch_director->currentText();

        Branch* edit_branch = University->get_head();
        while (name_branch != edit_branch->get_name()) { // поиск филиала по названию
            edit_branch = edit_branch->get_next();
        }

        edit_branch->get_list()->add_director(id, full_name, age, salary, subordinates_number); // добавление директора в филиал
        tab1(); // обновление таблицы
        clear_director_fields(); // очистка полей
        ui->stackedWidget->setCurrentIndex(0);
        ui->Search->setDisabled(0);
        save_flag = false;
    }

    else // данные некорректны
    {
        QMessageBox::warning(this, "Error", "Incorrect data entered");
    }
}

void MainWindow::on_branch_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(2);
    ui->stackedWidget->setCurrentIndex(8);
    ui->Return->setDisabled(0);
}


void MainWindow::on_edit_b_clicked() // редактирование филиала
{
    QItemSelectionModel *selectionModel = ui->table3->selectionModel();
    if (selectionModel->hasSelection()) // проверка фокуса
    {
        ui->stackedWidget->setCurrentIndex(6);
        ui->edit_br->setDisabled(0);
        ui->add_br->setDisabled(1);
        int item = ui->table3->currentRow(); // считывание текущей строки

        // установка текущих давнных в поля
        ui->index_b->setText(ui->table3->item(item, 1)->text());
        ui->name_b->setText(ui->table3->item(item, 0)->text());
        ui->street_b->setText(ui->table3->item(item, 4)->text());
        ui->city_b->setText(ui->table3->item(item, 3)->text());
        ui->region_b->setText(ui->table3->item(item, 2)->text());
        ui->number_b->setText(ui->table3->item(item, 5)->text());

        Branch* edit_branch = University->get_head(); // поиск филиала по названию
        while (edit_branch->get_name() != ui->name_b->text()) {
            edit_branch = edit_branch->get_next();
        }
        temp_list = edit_branch->get_list(); // запись списка сотрудников во временный лист

        University->del(ui->name_b->text()); // удаление филиала по названию
        save_flag = false;
    }
    else // данные некорректны
    {
        QMessageBox::warning(this, "Error", "Choose a line");
    }
}

void MainWindow::on_edit_teacher_clicked() // редактирование учителя
{
    bool not_correct = false;
    if (ui->id_teacher->text().isEmpty())
    {
        not_correct = true;
        ui->label_id_teacher->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_id_teacher->setStyleSheet("QLabel { color : white; }");
    QString temp_id = ui->id_teacher->text();
    bool correct_id = true;
    for (int i = 0; i < ui->table1->rowCount(); i++)
    {
        if ((ui->table1->item(i, 0)->text() == temp_id) && (ui->table1->item(ui->table1->currentRow(), 0)->text() != temp_id))
        {
            correct_id = false;
        }
    }
    if (!correct_id)
    {
        not_correct = true;
        ui->label_id_teacher->setStyleSheet("QLabel { color : red; }");
    }

    if (ui->full_name_teacher->text().isEmpty())
    {
        not_correct = true;
        ui->label_full_name_teacher->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_full_name_teacher->setStyleSheet("QLabel { color : white; }");
    if (ui->age_teacher->text().isEmpty())
    {
        not_correct = true;
        ui->label_age_teacher->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_age_teacher->setStyleSheet("QLabel { color : white; }");
    if (ui->salary_teacher->text().isEmpty())
    {
        not_correct = true;
        ui->label_salary_teacher->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_salary_teacher->setStyleSheet("QLabel { color : white; }");
    if (ui->subject_teacher->text().isEmpty())
    {
        not_correct = true;
        ui->label_subject_teacher->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_subject_teacher->setStyleSheet("QLabel { color : white; }");
    if (!not_correct) // данные корректны
    {
        // считывание данных из полей
        QString id = ui->id_teacher->text();
        QString full_name = ui->full_name_teacher->text();
        QString age = ui->age_teacher->text();
        QString salary = ui->salary_teacher->text();
        QString subject = ui->subject_teacher->text();

        QString name_branch = ui->branch_teacher->currentText();
        Branch* edit_branch = University->get_head(); // поиск филиала по названию
        while (name_branch != edit_branch->get_name()) {
            edit_branch = edit_branch->get_next();
        }

        edit_branch->get_list()->add_teacher(id, full_name, age, salary, subject); // добавление учителя
        ui->add_teacher->setDisabled(0);
        ui->edit_teacher->setDisabled(1);
        ui->stackedWidget->setCurrentIndex(0);
        clear_teacher_fields();
        save_flag = false;
        tab1();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Incorrect data entered");
    }
}

void MainWindow::on_edit_security_clicked() // редактирование охраника
{
    bool not_correct = false;
    if (ui->id_security->text().isEmpty())
    {
        not_correct = true;
        ui->label_id_security->setStyleSheet("QLabel { color : red; }");
    }
    else {
        ui->label_id_security->setStyleSheet("QLabel { color : white; }");
    }
    QString temp_id = ui->id_security->text();
    bool correct_id = true;
    for (int i = 0; i < ui->table1->rowCount(); i++)
    {
        if ((ui->table1->item(i, 0)->text() == temp_id) && (ui->table1->item(ui->table1->currentRow(), 0)->text() != temp_id))
        {
            correct_id = false;
        }
    }
    if (!correct_id)
    {
        not_correct = true;
        ui->label_id_security->setStyleSheet("QLabel { color : red; }");
    }

    if (ui->full_name_security->text().isEmpty())
    {
        not_correct = true;
        ui->label_full_name_security->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_full_name_security->setStyleSheet("QLabel { color : white; }");
    if (ui->age_security->text().isEmpty())
    {
        not_correct = true;
        ui->label_age_security->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_age_security->setStyleSheet("QLabel { color : white; }");
    if (ui->salary_security->text().isEmpty())
    {
        not_correct = true;
        ui->label_salary_security->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_salary_security->setStyleSheet("QLabel { color : white; }");
    if (ui->gun_license_security->text().isEmpty())
    {
        not_correct = true;
        ui->label_gun_license_security->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_gun_license_security->setStyleSheet("QLabel { color : white; }");
    if (!not_correct) // данные корректны
    {
        // считывание данных из полей
        QString id = ui->id_security->text();
        QString full_name = ui->full_name_security->text();
        QString age = ui->age_security->text();
        QString salary = ui->salary_security->text();
        QString gun_license = ui->gun_license_security->text();

        QString name_branch = ui->branch_security->currentText();
        Branch* edit_branch = University->get_head();
        while (name_branch != edit_branch->get_name()) { // поиск филиала по названию
            edit_branch = edit_branch->get_next();
        }

        edit_branch->get_list()->add_security(id, full_name, age, salary, gun_license); // добавлнение охраника
        tab1();
        ui->add_security->setDisabled(0);
        ui->edit_security->setDisabled(1);
        ui->stackedWidget->setCurrentIndex(0);
        clear_security_fields();
        save_flag = false;
    }
    else
    {
        QMessageBox::warning(this, "Error", "Incorrect data entered");
    }
}

void MainWindow::on_edit_br_clicked() // редактирование филиала
{
    bool not_correct = false;
    if (ui->name_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_name_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_name_b->setStyleSheet("QLabel { color : white; }");
    QString temp_name = ui->name_b->text();
    bool correct_name = true;
    for (int i = 0; i < ui->table3->rowCount(); i++)
    {
        if ((ui->table3->item(i, 0)->text() == temp_name) && (ui->table3->item(ui->table3->currentRow(), 0)->text() != temp_name))
        {
            correct_name = false;
        }
    }
    if (!correct_name)
    {
        not_correct = true;
        ui->label_name_b->setStyleSheet("QLabel { color : red; }");
    }

    if (ui->number_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_number_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_number_b->setStyleSheet("QLabel { color : white; }");
    if (ui->index_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_index_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_index_b->setStyleSheet("QLabel { color : white; }");
    if (ui->region_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_region_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_region_b->setStyleSheet("QLabel { color : white; }");
    if (ui->city_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_city_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_city_b->setStyleSheet("QLabel { color : white; }");
    if (ui->street_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_street_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_street_b->setStyleSheet("QLabel { color : white; }");
    if (ui->house_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_house_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_house_b->setStyleSheet("QLabel { color : white; }");
    if (!not_correct) // данные корректны
    {
        // считывание данных из полей
        QString region = ui->region_b->text();
        QString city = ui->city_b->text();
        QString street = ui->street_b->text();
        QString index = ui->index_b->text();
        QString number = ui->number_b->text();
        QString name = ui->name_b->text();
        QString house = ui->house_b->text();

        University->add_branch(name, index, region, city, street, house, number); // добавлнение филиала с новыми данными
        University->get_head()->set_list(temp_list); // загрузка списка сотрудников в филиал

        Branch* temp = University->get_head();
        int i = 0;
        ui->branch_director->clear();
        ui->branch_teacher->clear();
        ui->branch_security->clear();
        ui->choice_b->clear();

        while (i < University->get_count_branches()) { // добавление филиала в пункт выбора при добавлении сотрудника
            ui->branch_director->addItem(temp->get_name());
            ui->branch_teacher->addItem(temp->get_name());
            ui->branch_security->addItem(temp->get_name());
            ui->choice_b->addItem(temp->get_name());
            temp = temp->get_next();
            i++;
        }

        // переход в главное меню и очистка формы
        ui->add_br->setDisabled(0);
        ui->edit_br->setDisabled(1);
        ui->stackedWidget->setCurrentIndex(8);
        clear_b();
        save_flag = false;

        // обновление таблиц
        tab2();
        tab1();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Incorrect data entered");
    }
}

void MainWindow::on_Delete_clicked() // удаление ыотрудника
{
    if (ui->stackedWidget_3->currentIndex() == 1)
        QMessageBox::warning(this, "Error", "Error");
    else
    {
        QItemSelectionModel *selectionModel = ui->table1->selectionModel();
        if (selectionModel->hasSelection()) // проверка фокуса
        {
            int item = ui->table1->currentRow(); // считывание текущей строки
            int id = ui->table1->item(item, 0)->text().toInt(); // получение индетефикатора сотрудника
            QString address = ui->table1->item(item, 6)->text(); // филиал, где работает сотрудник
            ui->table1->removeRow(item); //удаление строки из таблицы

            Branch *edit_branch = University->get_head();
            while (edit_branch->get_name() != address) { // поиск филиала по названию
                edit_branch = edit_branch->get_next();
            }
            edit_branch->get_list()->del(id); // удаление сотрудника из списка
            ui->Search->setDisabled(1);
            save_flag = false;

            tab1(); // обновление таблицы
        }
        else
        {
            QMessageBox::warning(this, "Error", "Choose a line");
        }
    }
}

void MainWindow::on_delete_b_clicked()
{
    QItemSelectionModel *selectionModel = ui->table3->selectionModel();
    if (selectionModel->hasSelection()) // проверка фокуса
    {
        int item = ui->table3->currentRow(); // считывание строки
        QString name = ui->table3->item(item, 0)->text(); // считывание названия филиала
        University->del(name); // удаление филиала по названию из списка

        ui->table3->removeRow(item); // удаление строки из таблицы

        Branch* temp = University->get_head();
        int i = 0;
        ui->branch_director->clear();
        ui->branch_teacher->clear();
        ui->branch_security->clear();
        ui->choice_b->clear();

        while (i < University->get_count_branches()) { // удаление филиала из возможности выбора при добавлениии сотрудника
            ui->branch_director->addItem(temp->get_name());
            ui->branch_teacher->addItem(temp->get_name());
            ui->branch_security->addItem(temp->get_name());
            ui->choice_b->addItem(temp->get_name());
            temp = temp->get_next();
            i++;
        }

        ui->Search->setDisabled(1);
        save_flag = false;
        // обновление таблиц
        tab1();
        tab2();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Choose a line");
    }
}

void MainWindow::on_search_clicked() // поиск
{
    ui->stackedWidget_3->setCurrentIndex(1);
    int f = 0;
    if (ui->search_by->currentIndex() == 0) // поиск по индетефикатору
    {
        Branch *B = University->get_head();
        for (int i = 0; i < University->get_count(); i++) // цикл по всем филиалам
        {
            Employee *E = B->get_list()->get_head();
            for (int j = 0; j < B->get_list()->get_count(); j++) // цикл по сотрудникам
            {
                if (E->get_id() == ui->data->text()) // проверка условия
                {
                    ui->table2->setRowCount(f+1); // установка нового количества строк

                    // заполнение таблицы
                    ui->table2->setItem(f, 0, new QTableWidgetItem(E->get_id()));
                    ui->table2->setItem(f, 1, new QTableWidgetItem(E->get_type()));
                    ui->table2->setItem(f, 2, new QTableWidgetItem(E->get_full_name()));
                    ui->table2->setItem(f, 3, new QTableWidgetItem(E->get_age()));
                    ui->table2->setItem(f, 4, new QTableWidgetItem(E->get_salary()));
                    ui->table2->setItem(f, 6, new QTableWidgetItem(B->get_name()));

                    if (E->get_type() == "Director")
                    {
                        ui->table2->setItem(f, 5, new QTableWidgetItem(dynamic_cast<Director *>(E)->get_subordinates_number()));
                    }
                    else if (E->get_type() == "Teacher")
                    {
                        ui->table2->setItem(f, 5, new QTableWidgetItem(dynamic_cast<Teacher *>(E)->get_subject()));
                    }
                    else if (E->get_type() == "Security")
                    {
                        ui->table2->setItem(f, 5, new QTableWidgetItem(dynamic_cast<Security *>(E)->get_gun_license()));
                    }

                    f++;
                }
                E = E->get_next(); // переход к следующему сотруднику
            }
            B = B->get_next(); // преход к следующему филиалу
        }
        f = 0;
    }
    else if (ui->search_by->currentIndex() == 1) // поиск по филиалу
    {
        Branch *B = University->get_head();
        QString name = ui->choice_b->currentText(); // название филиала

        while (B->get_name() != name) // поиск филиала по названию
        {
            B = B->get_next();
        }
        Employee *E = B->get_list()->get_head();
        {
            for (int i = 0; i < B->get_list()->get_count(); i++) // цикл по работникам
            {
                ui->table2->setRowCount(f+1); // установка нового количества строк

                // заполнение таблицы
                ui->table2->setItem(f, 0, new QTableWidgetItem(E->get_id()));
                ui->table2->setItem(f, 1, new QTableWidgetItem(E->get_type()));
                ui->table2->setItem(f, 2, new QTableWidgetItem(E->get_full_name()));
                ui->table2->setItem(f, 3, new QTableWidgetItem(E->get_age()));
                ui->table2->setItem(f, 4, new QTableWidgetItem(E->get_salary()));
                ui->table2->setItem(f, 6, new QTableWidgetItem(B->get_name()));

                if (E->get_type() == "Director")
                {
                    ui->table2->setItem(f, 5, new QTableWidgetItem(dynamic_cast<Director *>(E)->get_subordinates_number()));
                }
                else if (E->get_type() == "Teacher")
                {
                    ui->table2->setItem(f, 5, new QTableWidgetItem(dynamic_cast<Teacher *>(E)->get_subject()));
                }
                else if (E->get_type() == "Security")
                {
                    ui->table2->setItem(f, 5, new QTableWidgetItem(dynamic_cast<Security *>(E)->get_gun_license()));
                }

                f++;
                E = E->get_next(); // переход к следующему
            }
        }
        f = 0;
    }
    else if (ui->search_by->currentIndex() == 2) // поиск по профессии
    {
        Branch *B = University->get_head();
        for (int i = 0; i < University->get_count(); i++) // проиход по филиалам
        {
            Employee *E = B->get_list()->get_head();
            for (int j = 0; j < B->get_list()->get_count(); j++) // цикл по работникам
            {
                if (E->get_type() == ui->data->text()) // если профессия нужная
                {
                    ui->table2->setRowCount(f+1); // установка нового количества строк

                    // заполнение таблицы
                    ui->table2->setItem(f, 0, new QTableWidgetItem(E->get_id()));
                    ui->table2->setItem(f, 1, new QTableWidgetItem(E->get_type()));
                    ui->table2->setItem(f, 2, new QTableWidgetItem(E->get_full_name()));
                    ui->table2->setItem(f, 3, new QTableWidgetItem(E->get_age()));
                    ui->table2->setItem(f, 4, new QTableWidgetItem(E->get_salary()));
                    ui->table2->setItem(f, 6, new QTableWidgetItem(B->get_name()));

                    if (E->get_type() == "Director")
                    {
                        ui->table2->setItem(f, 5, new QTableWidgetItem(dynamic_cast<Director *>(E)->get_subordinates_number()));
                    }
                    else if (E->get_type() == "Teacher")
                    {
                        ui->table2->setItem(f, 5, new QTableWidgetItem(dynamic_cast<Teacher *>(E)->get_subject()));
                    }
                    else if (E->get_type() == "Security")
                    {
                        ui->table2->setItem(f, 5, new QTableWidgetItem(dynamic_cast<Security *>(E)->get_gun_license()));
                    }

                    f++;
                }
                E = E->get_next(); // переход  к следующему работнику
            }
            B = B->get_next(); // переход к следующему филиалу
        }
        f = 0;
    }

    // очистка полей и переход в главное меню
    ui->data->clear();
    ui->choice_b->setCurrentText(0);
}

void MainWindow::on_Exit_triggered() // дружественный выход
{
    QMessageBox::StandardButton reply =
    QMessageBox::question(this, "Exit", "Are you sure you want to exit the program?", QMessageBox::Yes | QMessageBox::No); // окно вопроса
    if (reply == QMessageBox::Yes)
    {
    QApplication::quit(); // не сохранять изменения и закрыть программу
    }
    if (reply == QMessageBox::No)
    {
    }
}

void MainWindow::on_about_triggered() // о программе
{
    QMessageBox::about(this, "About", "The program is designed to record data on students and university employees\nDeveloper: Bykov Vladislav\nEmail: vlad.bykov2004@mail.ru");
}

void MainWindow::on_manual_triggered() // справка - мануал
{
    QUrl help_file = QUrl::fromLocalFile("Курсовая.docx");
    QDesktopServices::openUrl(QUrl("Курсовая.docx", QUrl::TolerantMode));;
}

void MainWindow::on_Create_triggered() // новый файл
{
        QMessageBox::warning(this, "Error", "Current file not saved");
        // очистка форм, таблиц, счетчиков и названия текущего файла
        filename.clear();
        ui->table1->setRowCount(0);
        ui->table2->setRowCount(0);
        ui->table3->setRowCount(0);
        ui->tip->setDisabled(1);
        ui->branch_director->clear();
        ui->branch_teacher->clear();
        ui->branch_security->clear();
        ui->choice_b->clear();

        University->new_university(); // очистка списка
        University = new List_branches();

        ui->Return->setDisabled(1);
        ui->edit_director->setDisabled(1);
        ui->add_director->setDisabled(0);
        ui->edit_teacher->setDisabled(1);
        ui->add_teacher->setDisabled(0);
        ui->edit_security->setDisabled(1);
        ui->add_security->setDisabled(0);
        ui->edit_br->setDisabled(1);
        ui->add_b->setDisabled(0);
        ui->Search->setDisabled(1);
        ui->stackedWidget->setCurrentIndex(0);
        ui->stackedWidget_2->setCurrentIndex(0);
        ui->stackedWidget_3->setCurrentIndex(0);
}

void MainWindow::open_check(){ // открытие файла
    filename.clear();
    ui->table1->setRowCount(0);
    ui->table2->setRowCount(0);
    ui->table3->setRowCount(0);
    ui->tip->setDisabled(1);
    ui->branch_director->clear();
    ui->branch_teacher->clear();
    ui->branch_security->clear();
    ui->choice_b->clear();

    ui->Return->setDisabled(1);
    ui->edit_teacher->setDisabled(1);
    ui->add_director->setDisabled(0);
    ui->edit_teacher->setDisabled(1);
    ui->add_teacher->setDisabled(0);
    ui->edit_security->setDisabled(1);
    ui->add_security->setDisabled(0);
    ui->edit_br->setDisabled(1);
    ui->add_b->setDisabled(0);
    ui->Search->setDisabled(1);
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->stackedWidget_3->setCurrentIndex(0);
    QString P, p;
    int row1 = 0, column = 0, row = 0;
    QString selFilter = "All files (*.*)";
    filename = QFileDialog::getOpenFileName(this, "Open file", QDir::currentPath(),
                                       "Text files (*.txt);;All files (*.*)", &selFilter);
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            P = in.readLine();
            if (P[0] != ' ')
            {
                ui->table3->insertRow(ui->table3->rowCount());
                for (int i = 0; i < P.size(); i++)
                {
                    if ((P[i] == "|"))
                    {
                        ui->table3->setItem(row1, column, new QTableWidgetItem(p));
                        column++;
                        p.clear();
                    }
                    else
                        p += P[i];
                }
                ui->table3->setItem(row1, column, new QTableWidgetItem(p));
                // запись данных в таблицу
                QString index = ui->table3->item(row1, 1)->text();
                QString name = ui->table3->item(row1, 0)->text();
                QString street = ui->table3->item(row1, 4)->text();
                QString city = ui->table3->item(row1, 3)->text();
                QString region = ui->table3->item(row1, 2)->text();
                QString number = ui->table3->item(row1, 5)->text();
                QString house = ui->table3->item(row1, 6)->text();

                // добавление филиалов в меню выбора
                University->add_branch(name, index, region, city, street, house, number);
                ui->branch_director->addItem(name);
                ui->branch_teacher->addItem(name);
                ui->branch_security->addItem(name);
                ui->choice_b->addItem(name);
                column = 0;
                row1++;
                p.clear();
            }
            else
            {
                ui->table1->insertRow(ui->table1->rowCount());
                for (int i = 1; i < P.size(); i++)
                {
                    if ((P[i] == "|"))
                    {
                        ui->table1->setItem(row, column, new QTableWidgetItem(p));
                        if (column == 5)
                        {
                            ui->table1->setItem(row, 6, new QTableWidgetItem(University->get_head()->get_name()));
                            column++;
                        }
                        column++;
                        if (column > 6)
                            i = P.size();
                        p.clear();
                    }
                    else
                        p += P[i];
                }
                ui->table1->setItem(row, column, new QTableWidgetItem(p));
                p.clear();
                QString type = ui->table1->item(row, 1)->text();

                // запись данных в списки из таблицы
                if (type == "Director")
                {
                    // считывание данных из таблицы
                    QString id = ui->table1->item(row, 0)->text();
                    QString full_name = ui->table1->item(row, 2)->text();
                    QString age = ui->table1->item(row, 3)->text();
                    QString salary = ui->table1->item(row, 4)->text();
                    QString subordinates_number = ui->table1->item(row, 5)->text();

                    Branch *B = University->get_head();
                    QString address = ui->table1->item(row, 6)->text();
                    while (B->get_name() != address) { // поиск филиала по названию
                        B = B->get_next();
                    }
                    B->get_list()->add_director(id, full_name, age, salary, subordinates_number); // добавление сотрудника
                }
                else if (type == "Teacher")
                {
                    // считывание данных из таблицы
                    QString id = ui->table1->item(row, 0)->text();
                    QString full_name = ui->table1->item(row, 2)->text();
                    QString age = ui->table1->item(row, 3)->text();
                    QString salary = ui->table1->item(row, 4)->text();
                    QString subject = ui->table1->item(row, 5)->text();

                    Branch *B = University->get_head();
                    QString address = ui->table1->item(row, 6)->text();
                    while (B->get_name() != address) {  // поиск филиала по названию
                        B = B->get_next();
                    }
                    B->get_list()->add_teacher(id, full_name, age, salary, subject); // добавление сотрудника
                }
                else if (type == "Security")
                {
                    // считывание данных из таблицы
                    QString id = ui->table1->item(row, 0)->text();
                    QString full_name = ui->table1->item(row, 2)->text();
                    QString age = ui->table1->item(row, 3)->text();
                    QString salary = ui->table1->item(row, 4)->text();
                    QString gun_license = ui->table1->item(row, 5)->text();

                    Branch *B = University->get_head();
                    QString address = ui->table1->item(row, 6)->text();
                    while (B->get_name() != address) { // поиск филиала по названию
                        B = B->get_next();
                    }
                    B->get_list()->add_security(id, full_name, age, salary, gun_license); // добавление сотрудника
                }
                row++;
                column = 0;
            }
        }
        file.close(); // закрытие файла
        ui->Search->setDisabled(0);
        if (University->get_count() != 0)
            ui->tip->setDisabled(0);
    }
}

void MainWindow::on_Open_triggered() // открытие файла - меню
{
    if(!save_flag){
    QMessageBox::StandardButton reply =
    QMessageBox::question(this, "Current file not saved", "Save changes?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    { // открытие с сохранением предыдущих данных
        on_Save_As_triggered();
        open_check();
    }
    if (reply == QMessageBox::No)
    { // открытие без сохранения
        open_check();
    }
    }
    else{
        open_check();
    }

}

void MainWindow::on_Save_triggered() // быстрое сохранение
{
    if (!filename.isNull())
    {
        save_flag = true;
        QFile file(filename);
        file.open(QFile::WriteOnly | QFile::Truncate);
        file.close();
        write_to_file(filename); // записб в файл
    }
    else
        QMessageBox::warning(this, "Error", "No current file");
}

void MainWindow::on_Save_As_triggered() // сохранить как
{
    QString selFilter = "All files (*.*)";
    QString str1 = QFileDialog::getSaveFileName(this, "Save file", QDir::currentPath(),
                                                "Text files (*.txt);;All files (*.*)", &selFilter);
    write_to_file(str1);
    filename = str1;
}
