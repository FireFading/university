#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, list_salons* company1, bool changed_data1, QString current_file1)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), company(company1), changed_data(changed_data1), current_file(current_file1)
{
    ui->setupUi(this);
    setWindowTitle(tr("%1[*]").arg("SALONS of BEAUTY"));

    company = new list_salons();
    current_salon = new salon();

    ui->table_people->setColumnCount(6);
    ui->table_people->setRowCount(0);
    QStringList Title;
    Title << "Name"
          << "Profession"
          << "salary"
          << "age"
          << "experience"
          << "oprofessional characteristics";
    ui->table_people->setHorizontalHeaderLabels(Title);
    ui->table_people->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_people->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table_people->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->table_people->setColumnWidth(0, 80);
    ui->table_people->setColumnWidth(1, 100);
    ui->table_people->setColumnWidth(2, 80);
    ui->table_people->setColumnWidth(3, 60);
    ui->table_people->setColumnWidth(4, 80);
    ui->table_people->setColumnWidth(5, 350);

    ui->table_salons->setColumnCount(4);
    ui->table_salons->setRowCount(0);
    QStringList Title2;
    Title2 << "Name"
           << "Address"
           << "Services"
           << "Stars";
    ui->table_salons->setHorizontalHeaderLabels(Title2);
    ui->table_salons->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_salons->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table_salons->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->table_salons->setColumnWidth(0, 200);
    ui->table_salons->setColumnWidth(1, 260);
    ui->table_salons->setColumnWidth(2, 220);
    ui->table_salons->setColumnWidth(3, 140);

    QRegExp num("[0-9.+]{1,11}");
    QValidator *numValidator = new QRegExpValidator(num, this);

    ui->number_stars->setValidator(numValidator);
    ui->number_stars_2->setValidator(numValidator);

    ui->age_barber->setValidator(numValidator);
    ui->age_beautician->setValidator(numValidator);
    ui->age_administrator->setValidator(numValidator);
    ui->age_barber_2->setValidator(numValidator);
    ui->age_beautician_2->setValidator(numValidator);
    ui->age_administrator_2->setValidator(numValidator);

    ui->salary_barber->setValidator(numValidator);
    ui->salary_beautician->setValidator(numValidator);
    ui->salary_administrator->setValidator(numValidator);
    ui->salary_barber_2->setValidator(numValidator);
    ui->salary_beautician_2->setValidator(numValidator);
    ui->salary_administrator_2->setValidator(numValidator);
    ui->number_operations->setValidator(numValidator);
    ui->number_operations_2->setValidator(numValidator);
    ui->number->setValidator(numValidator);
    ui->number_2->setValidator(numValidator);

    QRegExp name("[A-Za-z]{1}[A-Za-z\\s\\.]{1,30}");
    QValidator *nameValidator = new QRegExpValidator(name, this);
    ui->name->setValidator(nameValidator);
    ui->name_2->setValidator(nameValidator);
    ui->name_barber->setValidator(nameValidator);
    ui->name_barber_2->setValidator(nameValidator);
    ui->name_beautician->setValidator(nameValidator);
    ui->name_beautician_2->setValidator(nameValidator);
    ui->name_administrator->setValidator(nameValidator);
    ui->name_administrator_2->setValidator(nameValidator);

    ui->menu->setCurrentIndex(13);
    ui->tables->setCurrentIndex(1);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::update_table1()
{
    ui->table_people->setRowCount(current_salon->get_staf()->get_number_people());
    employee* current = current_salon->get_staf()->get_head();
    int i = 0;
    while (current != nullptr)
    {
        QTableWidgetItem *item;
        item = new QTableWidgetItem(current->get_name());
        ui->table_people->setItem(i, 0, item);
        item = new QTableWidgetItem(current->get_profession());
        ui->table_people->setItem(i, 1, item);
        item = new QTableWidgetItem(current->get_salary());
        ui->table_people->setItem(i, 2, item);
        item = new QTableWidgetItem(current->get_age());
        ui->table_people->setItem(i, 3, item);
        item = new QTableWidgetItem(current->get_experience());
        ui->table_people->setItem(i, 4, item);
        item = new QTableWidgetItem(current->get_professional_characteristics());
        ui->table_people->setItem(i, 5, item);

        current = current->get_next();
        i++;
    }

    ui->table_people->clearSelection();
}


void MainWindow::update_table2()
{
    ui->table_salons->setRowCount(company->get_number_salons());
    salon* current = company->get_head();
    int i = 0;
    while (current != nullptr) {
        QTableWidgetItem *item;
        item = new QTableWidgetItem(current->get_name());
        ui->table_salons->setItem(i, 0, item);
        item = new QTableWidgetItem(current->get_address());
        ui->table_salons->setItem(i, 1, item);
        item = new QTableWidgetItem(current->get_describe_services());
        ui->table_salons->setItem(i, 2, item);
        item = new QTableWidgetItem(current->get_number_stars());
        ui->table_salons->setItem(i, 3, item);
        current = current->get_next();
        i++;
    }
}


void MainWindow::on_add_employee_clicked()
{
    if (company->get_number_salons() > 0)
    {
        ui->menu->setCurrentIndex(4);
        ui->tables->setCurrentIndex(0);
    }
    else
    {
        QMessageBox::critical(this, "Error", "There are no salons!");
    }
}


void MainWindow::on_barber_clicked()
{
    ui->menu->setCurrentIndex(1);
}


void MainWindow::on_beautician_clicked()
{
    ui->menu->setCurrentIndex(2);
}


void MainWindow::on_administrator_clicked()
{
    ui->menu->setCurrentIndex(3);
}


void MainWindow::on_cancel_clicked()
{
    ui->menu->setCurrentIndex(13);
}


void MainWindow::on_cancel_barber_clicked()
{
    ui->menu->setCurrentIndex(13);
    ui->name_barber->clear();
    ui->age_barber->clear();
    ui->salary_barber->clear();
    ui->experience_barber->clear();
}


void MainWindow::on_add_barber_clicked()
{
    bool correct = true; // флаг корректности данных
    if (ui->name_barber->text().isEmpty())
    {
        ui->name_barber->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->name_barber->setStyleSheet("background-color: white;");
    }
    if (ui->age_barber->text().isEmpty())
    {
        ui->age_barber->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->age_barber->setStyleSheet("background-color: white;");
    }
    if (ui->salary_barber->text().isEmpty())
    {
        ui->salary_barber->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->salary_barber->setStyleSheet("background-color: white;");
    }
    if (ui->experience_barber->text().isEmpty())
    {
        ui->experience_barber->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->experience_barber->setStyleSheet("background-color: white;");
    }

    if (correct)
    {
        if (company->get_number_salons() > 0)
        {
            QString name = ui->name_barber->text();
            QString age = ui->age_barber->text();
            QString salary = ui->salary_barber->text();
            QString experience = ui->experience_barber->text();
            QString hairstyle = ui->hairstyle->currentText();
            QString qualification = ui->qualification->currentText();

            employee* new_barber = new barber(salary, name, age, experience, hairstyle, qualification);
            current_salon->get_staf()->add_employee(new_barber);

            update_table1();

            ui->menu->setCurrentIndex(13);
            ui->name_barber->clear();
            ui->age_barber->clear();
            ui->salary_barber->clear();
            ui->experience_barber->clear();

            changed_data = true;
        }
        else {
            QMessageBox::critical(this, "Error", "There are no salons!");
        }
    }
}


void MainWindow::on_cancel_beautician_clicked()
{
    ui->menu->setCurrentIndex(13);
    ui->name_beautician->clear();
    ui->age_beautician->clear();
    ui->salary_beautician->clear();
    ui->experience_beautician->clear();
    ui->sertification->clear();
    ui->number_operations->clear();
}


void MainWindow::on_add_beautician_clicked()
{
    bool correct = true; // флаг корректности данных
    if (ui->name_beautician->text().isEmpty())
    {
        ui->name_beautician->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->name_beautician->setStyleSheet("background-color: white;");
    }
    if (ui->age_beautician->text().isEmpty())
    {
        ui->age_beautician->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->age_beautician->setStyleSheet("background-color: white;");
    }
    if (ui->salary_beautician->text().isEmpty())
    {
        ui->salary_beautician->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->salary_beautician->setStyleSheet("background-color: white;");
    }
    if (ui->experience_beautician->text().isEmpty())
    {
        ui->experience_beautician->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->experience_beautician->setStyleSheet("background-color: white;");
    }

    if (correct)
    {
        if (company->get_number_salons() > 0)
        {
            QString name = ui->name_beautician->text();
            QString age = ui->age_beautician->text();
            QString salary = ui->salary_beautician->text();
            QString experience = ui->experience_beautician->text();
            QString sertification = ui->sertification->text();
            QString number_operations = ui->number_operations->text();
            QString employee_education;
            if (ui->medicine_education->isChecked())
            {
                employee_education = "doctor with high education";
            }
            else
            {
                employee_education = "doctor without high education";
            }


            employee* new_beautician = new beautician(salary, name, age, experience, employee_education, sertification, number_operations);
            current_salon->get_staf()->add_employee(new_beautician);

            update_table1();

            ui->menu->setCurrentIndex(13);
            ui->name_beautician->clear();
            ui->age_beautician->clear();
            ui->salary_beautician->clear();
            ui->experience_beautician->clear();
            ui->sertification->clear();
            ui->number_operations->clear();

            changed_data = true;
        }
        else {
            QMessageBox::critical(this, "Error", "There are no salons!");
        }
    }
}


void MainWindow::on_cancel_administrator_clicked()
{
    ui->menu->setCurrentIndex(13);
    ui->name_administrator->clear();
    ui->age_administrator->clear();
    ui->salary_administrator->clear();
    ui->experience_administrator->clear();
    ui->number->clear();
    ui->education->clear();
}


void MainWindow::on_add_administrator_clicked()
{
    bool correct = true; // флаг корректности данных
    if (ui->name_administrator->text().isEmpty())
    {
        ui->name_administrator->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->name_administrator->setStyleSheet("background-color: white;");
    }
    if (ui->age_administrator->text().isEmpty())
    {
        ui->age_administrator->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->age_administrator->setStyleSheet("background-color: white;");
    }
    if (ui->salary_administrator->text().isEmpty())
    {
        ui->salary_administrator->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->salary_administrator->setStyleSheet("background-color: white;");
    }
    if (ui->experience_administrator->text().isEmpty())
    {
        ui->experience_administrator->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->experience_administrator->setStyleSheet("background-color: white;");
    }
    if (ui->number->text().isEmpty())
    {
        ui->number->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->number->setStyleSheet("background-color: white;");
    }
    if (ui->education->text().isEmpty())
    {
        ui->education->setStyleSheet("background-color: red;");
        correct = false;
    }
    else
    {
        ui->education->setStyleSheet("background-color: white;");
    }

    if (correct)
    {
        if (company->get_number_salons() > 0)
        {
            QString name = ui->name_administrator->text();
            QString age = ui->age_administrator->text();
            QString salary = ui->salary_administrator->text();
            QString experience = ui->experience_administrator->text();
            QString number = ui->number->text();
            QString education = ui->education->text();

            employee* new_administrator = new beautician(salary, name, age, experience, number, education);
            current_salon->get_staf()->add_employee(new_administrator);

            update_table1();

            ui->menu->setCurrentIndex(13);
            ui->name_administrator->clear();
            ui->age_administrator->clear();
            ui->salary_administrator->clear();
            ui->experience_administrator->clear();
            ui->number->clear();
            ui->education->clear();

            changed_data = true;
        }
        else {
            QMessageBox::critical(this, "Error", "There are no salons!");
        }
    }
}


void MainWindow::on_edit_employee_clicked()
{
    if (ui->table_people->rowCount() == 0)
    {
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else
    {
        QItemSelectionModel *selectionModel = ui->table_people->selectionModel();
        if (selectionModel->hasSelection())
        {
            int row = ui->table_people->currentRow();
            if (row != -1)
            {
                ui->menu->setCurrentIndex(4);
                QTableWidgetItem *curitem = ui->table_people->item(row, 0);
                QString name = curitem->text();
                employee* edit_employee = current_salon->get_staf()->find_node(name);
                if (edit_employee->get_profession() == "barber") {
                    ui->menu->setCurrentIndex(5);
                    ui->name_barber_2->setText(edit_employee->get_name());
                    ui->age_barber_2->setText(edit_employee->get_age());
                    ui->salary_barber_2->setText(edit_employee->get_salary());
                    ui->experience_barber_2->setText(edit_employee->get_experience());
                    ui->hairstyle_2->setCurrentText(edit_employee->get_one());
                    ui->qualification_2->setCurrentText(edit_employee->get_two());
                }
                if (edit_employee->get_profession() == "beautician")
                {
                    ui->menu->setCurrentIndex(6);
                    ui->name_beautician_2->setText(edit_employee->get_name());
                    ui->age_beautician_2->setText(edit_employee->get_age());
                    ui->salary_beautician_2->setText(edit_employee->get_salary());
                    ui->experience_beautician_2->setText(edit_employee->get_experience());
                    ui->sertification_2->setText(edit_employee->get_two());
                    ui->number_operations_2->setText(edit_employee->get_three());
                    if (edit_employee->get_one() == "doctor with high education")
                    {
                        ui->medicine_education_2->setChecked(true);
                    }
                    else
                    {
                        ui->medicine_education_2->setChecked(false);
                    }
                }
                if (edit_employee->get_profession() == "administrator")
                {
                    ui->menu->setCurrentIndex(7);
                    ui->name_administrator_2->setText(edit_employee->get_name());
                    ui->age_administrator_2->setText(edit_employee->get_age());
                    ui->salary_administrator_2->setText(edit_employee->get_salary());
                    ui->experience_administrator_2->setText(edit_employee->get_experience());
                    ui->number_2->setText(edit_employee->get_one());
                    ui->education_2->setText(edit_employee->get_two());
                }
            }
            else
            {
                QMessageBox::critical(this, "Error", "No line selected!");
            }
        }
    }
}


void MainWindow::on_add_salon_clicked()
{
    ui->menu->setCurrentIndex(8);
}


void MainWindow::on_cancel_new_salon_clicked()
{
    ui->menu->setCurrentIndex(13);
}


void MainWindow::on_add_new_salon_clicked()
{
    bool correct_data = true;
    if (ui->name->text().isEmpty())
    {
        ui->name->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else
    {
        ui->name->setStyleSheet("background-color: white;");
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
    if (ui->number_stars->text().isEmpty())
    {
        ui->number_stars->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else
    {
        ui->number_stars->setStyleSheet("background-color: white;");
    }
    if (ui->describe_services->text().isEmpty())
    {
        ui->describe_services->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else
    {
        ui->describe_services->setStyleSheet("background-color: white;");
    }

    if (correct_data == true)
    {
        QString name = ui->name->text();
        QString adress = ui->adress->text();
        QString number_stars = ui->number_stars->text();
        QString services = ui->describe_services->text();

        salon* new_salon = new salon();
        new_salon->set_data(adress, name, number_stars, services);
        company->add_node(new_salon);
        current_salon = new_salon;

        update_table1();
        update_table2();

        ui->menu->setCurrentIndex(13);
        ui->name->clear();
        ui->number_stars->clear();
        ui->adress->clear();
        ui->describe_services->clear();

        changed_data = true;
    }
}


void MainWindow::on_delete_employee_clicked()
{
    if (ui->table_people->rowCount() == 0)
    {
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else
    {
        QItemSelectionModel *selectionModel = ui->table_people->selectionModel();
        if (selectionModel->hasSelection())
        {
            int row = ui->table_people->currentRow();
            if (row != -1)
            {
                QTableWidgetItem *curitem = ui->table_people->item(row, 0);
                QString name = curitem->text();
                current_salon->get_staf()->del_employee(name);
                update_table1();
            }
        }
        else
        {
             QMessageBox::critical(this, "Error", "No line selected!");
        }
    }
    ui->table_people->clearFocus();
    ui->table_people->clearSelection();
}


void MainWindow::on_change_salon_clicked()
{
    ui->tables->setCurrentIndex(1);
    ui->menu->setCurrentIndex(14);
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->table_salons->rowCount() == 0)
    {
            QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else
    {
        QItemSelectionModel *selectionModel = ui->table_salons->selectionModel();
        if (selectionModel->hasSelection())
            {
            int row_shop = ui->table_salons->currentRow();
            if (row_shop != -1)
            {
                QTableWidgetItem *curitem = ui->table_salons->item(row_shop, 0);
                QString name = curitem->text();

                current_salon = company->find_node(name);

                update_table1();
                ui->menu->setCurrentIndex(13);
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "No line is selected!");
        }
    }

    ui->table_salons->clearFocus();
    ui->table_salons->clearSelection();
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->menu->setCurrentIndex(13);
}


void MainWindow::on_pushButton_2_clicked()
{
    if (ui->table_salons->rowCount() == 0)
    {
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else
    {
        QItemSelectionModel *selectionModel = ui->table_salons->selectionModel();
        if (selectionModel->hasSelection())
        {
            int row = ui->table_salons->currentRow();
            if (row != -1)
            {
                QTableWidgetItem *curitem = ui->table_salons->item(row, 0);
                QString name = curitem->text();

                company->del_node(name);
                update_table1();
                update_table2();

                ui->menu->setCurrentIndex(13);
                changed_data = true;
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "No line is selected!");
        }
    }
}


void MainWindow::on_done_edit_salon_clicked()
{
    bool correct_data = true;

    if (ui->name_2->text().isEmpty())
    {
        ui->name_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else
    {
        ui->name_2->setStyleSheet("background-color: white;");
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
    if (ui->number_stars_2->text().isEmpty())
    {
        ui->number_stars_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else
    {
        ui->number_stars_2->setStyleSheet("background-color: white;");
    }
    if (ui->describe_services_2->text().isEmpty())
    {
        ui->describe_services_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else
    {
        ui->describe_services_2->setStyleSheet("background-color: white;");
    }

    if (correct_data == true)
    {
        QString name = ui->name_2->text();
        QString stars = ui->number_stars_2->text();
        QString adress = ui->adress_2->text();
        QString services = ui->describe_services_2->text();

        int row = ui->table_salons->currentRow();
        QTableWidgetItem *curitem = ui->table_salons->item(row, 0);
        QString nickname = curitem->text();

        salon* edit_shop = company->find_node(nickname);
        edit_shop->set_data(adress, name, stars, services);
        current_salon = edit_shop;
        update_table2();

        ui->menu->setCurrentIndex(0);
        ui->name_2->clear();
        ui->number_stars_2->clear();
        ui->adress_2->clear();
        ui->describe_services_2->clear();

        changed_data = true; // данные изменены
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    QItemSelectionModel *selectionModel = ui->table_salons->selectionModel();
    if (selectionModel->hasSelection())
        {
        int row_shop = ui->table_salons->currentRow();
        if (row_shop != -1)
        {
            ui->menu->setCurrentIndex(9);
            QTableWidgetItem *curitem = ui->table_salons->item(row_shop, 0);
            QString name = curitem->text();
            salon* edit_salon = company->find_node(name);

            ui->name_2->setText(edit_salon->get_name());
            ui->number_stars_2->setText(edit_salon->get_number_stars());
            ui->adress_2->setText(edit_salon->get_address());
            ui->describe_services_2->setText(edit_salon->get_describe_services());
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "No line is selected!");
    }

    ui->table_salons->clearFocus();
    ui->table_salons->clearSelection();

}


void MainWindow::on_search_employee_clicked()
{
    ui->menu->setCurrentIndex(0);
    ui->tables->setCurrentIndex(0);
}


void MainWindow::on_search_by_salary_clicked()
{
    ui->menu->setCurrentIndex(10);
}

void MainWindow::on_search_salary_clicked()
{
    bool correct_data = true;
    if (ui->max_cost->text().isEmpty())
    {
        correct_data = false;
        ui->max_cost->setStyleSheet("background-color: red;");
    }
    else
    {
       ui->max_cost->setStyleSheet("background-color: white;");
    }
    if (ui->min_cost->text().isEmpty())
    {
        correct_data = false;
        ui->min_cost->setStyleSheet("background-color: red;");
    }
    else
    {
       ui->min_cost->setStyleSheet("background-color: white;");
    }
    if (correct_data)
    {
        QString type = ui->prof->currentText();
        if (type != "all")
        {
            salon* search_salon = company->get_head();
            QTableWidgetItem *item;
            int i = 0;
            int count_results = 0;
            int min_cost = (ui->min_cost->text()).toDouble();
            int max_cost = (ui->max_cost->text()).toDouble();
            ui->table_people->setRowCount(count_results);
            while (search_salon != nullptr)
            {
               personal* search_people = search_salon->get_staf();
               employee* current_search = search_people->get_head();
               while (current_search != nullptr) {
                   if ((current_search->get_salary()).toDouble() >= min_cost && ((current_search->get_salary().toDouble()) <= max_cost) && (current_search->get_profession() == type)) {
                       count_results++;
                       ui->table_people->setRowCount(count_results);

                       item = new QTableWidgetItem(current_search->get_name());
                       ui->table_people->setItem(i, 0, item);
                       item = new QTableWidgetItem(current_search->get_profession());
                       ui->table_people->setItem(i, 1, item);
                       item = new QTableWidgetItem(current_search->get_salary());
                       ui->table_people->setItem(i, 2, item);
                       item = new QTableWidgetItem(current_search->get_age());
                       ui->table_people->setItem(i, 3, item);
                       item = new QTableWidgetItem(current_search->get_experience());
                       ui->table_people->setItem(i, 4, item);
                       item = new QTableWidgetItem(current_search->get_professional_characteristics());
                       ui->table_people->setItem(i, 5, item);

                       i++;
                   }
                   current_search = current_search->get_next();
               }
               search_salon = search_salon->get_next();
            }
        }
        else
        {
            salon* search_salon = company->get_head();
            QTableWidgetItem *item;
            int i = 0;
            int count_results = 0;
            int min_cost = (ui->min_cost->text()).toDouble();
            int max_cost = (ui->max_cost->text()).toDouble();
            ui->table_people->setRowCount(count_results);
            while (search_salon != nullptr)
            {
               personal* search_people = search_salon->get_staf();
               employee* current_search = search_people->get_head();
               while (current_search != nullptr) {
                   if ((current_search->get_salary()).toDouble() >= min_cost && ((current_search->get_salary().toDouble()) <= max_cost)) {
                       count_results++;
                       ui->table_people->setRowCount(count_results);

                       item = new QTableWidgetItem(current_search->get_name());
                       ui->table_people->setItem(i, 0, item);
                       item = new QTableWidgetItem(current_search->get_profession());
                       ui->table_people->setItem(i, 1, item);
                       item = new QTableWidgetItem(current_search->get_salary());
                       ui->table_people->setItem(i, 2, item);
                       item = new QTableWidgetItem(current_search->get_age());
                       ui->table_people->setItem(i, 3, item);
                       item = new QTableWidgetItem(current_search->get_experience());
                       ui->table_people->setItem(i, 4, item);
                       item = new QTableWidgetItem(current_search->get_professional_characteristics());
                       ui->table_people->setItem(i, 5, item);

                       i++;
                   }
                   current_search = current_search->get_next();
               }
               search_salon = search_salon->get_next();
            }
        }
    }
}


void MainWindow::on_search_by_name_clicked()
{
    ui->menu->setCurrentIndex(12);
    ui->salon->clear();
    salon* name_salons = company->get_head();
    while (name_salons != nullptr)
    {
        QString name_q = name_salons->get_name();
        ui->salon->addItem(name_q);
        name_salons = name_salons->get_next();
    }
}


void MainWindow::on_search_artikul_medicine_clicked()
{
    QString type = ui->prof_2->currentText();
    if (type != "all")
    {
        salon* search_salon = company->get_head();
        QTableWidgetItem *item;
        int i = 0;
        int count_results = 0;
        QString salon = ui->salon->currentText();
        QString age = ui->age->text();
        ui->table_people->setRowCount(count_results);
        while (search_salon != nullptr)
        {
            if (search_salon->get_name() == salon)
            {
               personal* search_people = search_salon->get_staf();
               employee* current_search = search_people->get_head();
               while (current_search != nullptr) {
                   if ((current_search->get_age() == age) && (current_search->get_profession() == type)) {
                       count_results++;
                       ui->table_people->setRowCount(count_results);

                       item = new QTableWidgetItem(current_search->get_name());
                       ui->table_people->setItem(i, 0, item);
                       item = new QTableWidgetItem(current_search->get_profession());
                       ui->table_people->setItem(i, 1, item);
                       item = new QTableWidgetItem(current_search->get_salary());
                       ui->table_people->setItem(i, 2, item);
                       item = new QTableWidgetItem(current_search->get_age());
                       ui->table_people->setItem(i, 3, item);
                       item = new QTableWidgetItem(current_search->get_experience());
                       ui->table_people->setItem(i, 4, item);
                       item = new QTableWidgetItem(current_search->get_professional_characteristics());
                       ui->table_people->setItem(i, 5, item);

                       i++;
                   }
                   current_search = current_search->get_next();
               }
            }
           search_salon = search_salon->get_next();
        }
    }
    else
    {
        salon* search_salon = company->get_head();
        QTableWidgetItem *item;
        int i = 0;
        int count_results = 0;
        QString salon = ui->salon->currentText();
        QString age = ui->age->text();
        ui->table_people->setRowCount(count_results);
        while (search_salon != nullptr)
        {
            if (search_salon->get_name() == salon)
            {
               personal* search_people = search_salon->get_staf();
               employee* current_search = search_people->get_head();
               while (current_search != nullptr) {
                   if ((current_search->get_age() == age)) {
                       count_results++;
                       ui->table_people->setRowCount(count_results);

                       item = new QTableWidgetItem(current_search->get_name());
                       ui->table_people->setItem(i, 0, item);
                       item = new QTableWidgetItem(current_search->get_profession());
                       ui->table_people->setItem(i, 1, item);
                       item = new QTableWidgetItem(current_search->get_salary());
                       ui->table_people->setItem(i, 2, item);
                       item = new QTableWidgetItem(current_search->get_age());
                       ui->table_people->setItem(i, 3, item);
                       item = new QTableWidgetItem(current_search->get_experience());
                       ui->table_people->setItem(i, 4, item);
                       item = new QTableWidgetItem(current_search->get_professional_characteristics());
                       ui->table_people->setItem(i, 5, item);

                       i++;
                   }
                   current_search = current_search->get_next();
               }
            }
           search_salon = search_salon->get_next();
        }
    }

}


void MainWindow::on_cancel_search_3_clicked()
{
    ui->menu->setCurrentIndex(13);
    update_table1();
}

void MainWindow::write_in_file(QFile &file)
{
    QTextStream stream(&file);
    stream.setCodec("UTF-8");

    stream << company->get_number_salons() << endl;
    salon* write_current_shop = company->get_head();
    while (write_current_shop != nullptr)
    {
        stream << write_current_shop->get_address() << endl;
        stream << write_current_shop->get_name() << endl;
        stream << write_current_shop->get_number_stars() << endl;
        stream << write_current_shop->get_describe_services() << endl;
        personal* write_current_products = write_current_shop->get_staf();
        stream << write_current_products->get_number_people() << endl;
        employee* write_current_product = write_current_products->get_head();
        while (write_current_product != nullptr)
        {
            stream << write_current_product->get_profession() << endl;
            stream << write_current_product->get_salary() << endl;
            stream << write_current_product->get_name() << endl;
            stream << write_current_product->get_age() << endl;
            stream << write_current_product->get_experience() << endl;
            stream << write_current_product->get_one() << endl;
            stream << write_current_product->get_two() << endl;
            stream << write_current_product->get_three() << endl;
            write_current_product = write_current_product->get_next();
        }
        write_current_shop = write_current_shop->get_next();
    }
}


void MainWindow::on_Save_as_triggered()
{
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
{
    QFile file;

    if(current_file == "")
    {
        on_Save_as_triggered();
    }
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
{
    if (changed_data)
    {
        QMessageBox msgBox;
        msgBox.setText("Save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int res = msgBox.exec();
        if(res == QMessageBox::Yes)
        {
            on_Save_triggered();
        }
    }

    company->clear();
    current_salon->get_staf()->clear();

    update_table1();
    update_table2();
    current_file = "";

    changed_data = false;
}


void MainWindow::on_Exit_triggered()
{
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
        }
    }

    close();
}


void MainWindow::on_About_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    msgBox.setText("The program by \nAll roots reserved");
    msgBox.exec();
}


void MainWindow::on_Help_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("How use this app");
    msgBox.setText("This program is very easy in using!\nYou will get success!\nWe belive that you will enjoy!");
    msgBox.exec();
}


void MainWindow::on_Open_triggered()
{
    if (changed_data) {
        QMessageBox msgBox;
        msgBox.setText("Save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int res = msgBox.exec();

        if(res == QMessageBox::Yes)
        {
            on_Save_triggered();
        }
    }

    company->clear();
    current_salon->get_staf()->clear();
    update_table1();
    update_table2();
    changed_data = false;

    QString fileName = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "Text file (*.txt)");

    if(!fileName.isEmpty()) // если файл не пустой
    {
        current_file = fileName;

        QFile file(fileName);
        file.open(QIODevice::ReadOnly);

        QTextStream stream(&file);
        stream.setCodec("UTF-8");

        int count_shops = (stream.readLine()).toInt();

        for(int i = 0; i < count_shops; i++)
        {
            QString adress = stream.readLine();
            QString name = stream.readLine();
            QString number_stars = stream.readLine();
            QString services = stream.readLine();

            int count_products = (stream.readLine()).toInt();
            salon* current = new salon();
            current->set_data(adress, name, number_stars, services);

            for (int j = 0; j < count_products; j++)
            {

                QString profession = stream.readLine();
                QString salary = stream.readLine();
                QString name = stream.readLine();
                QString age = stream.readLine();
                QString experience = stream.readLine();
                if (profession == "barber")
                {
                    QString a = stream.readLine();
                    QString b = stream.readLine();
                    QString c = stream.readLine();
                    employee* new_ = new barber(salary, name, age, experience, a, b);
                    current->get_staf()->add_employee(new_);

                }
                if (profession == "beautician")
                {
                    QString a = stream.readLine();
                    QString b = stream.readLine();
                    QString c = stream.readLine();
                    employee* new_ = new beautician(salary, name, age, experience, a, b, c);
                    current->get_staf()->add_employee(new_);
                }
                if (profession == "administrator")
                {
                    QString a = stream.readLine();
                    QString b = stream.readLine();
                    QString c = stream.readLine();
                    employee* new_ = new administrator(salary, name, age, experience, a, b);
                    current->get_staf()->add_employee(new_);
                }
            }
            company->add_node(current);
            current_salon = current;
        }

        update_table1();
        update_table2();
        changed_data = false;
        file.close();
    }
}
