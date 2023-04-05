#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

QString Tovar::getKod()
{
    return QString::number(kod);
}
QString Tovar::getColor()
{
    return color;
}
QString Tovar::getPrice()
{
    return QString::number(price);
}

void Tovar::setNext(Tovar* exemp)
{
    Next = exemp;
}
void Tovar::setPrev(Tovar* exemp)
{
    Prev = exemp;
}
Tovar* Tovar::getNext()
{
    return Next;
}
Tovar* Tovar::getPrev()
{
    return Prev;
}

QString Tovar::getMebel()
{
    return mebel;
}

QString Krovat::getOption()
{
    return ("характеристики кровати: " + forma + ", " + StranaProizv);
}

QString Krovat::getkolNojek()
{
    return QString::number(kolNojek);
}
QString Krovat::getforma()
{
    return forma;
}

QString Krovat::getStranaProizv()
{
    return StranaProizv;
}

QString Stol::getkolNojek()
{
    return QString::number(kolNojek);
}
QString Stol::getforma()
{
    return forma;
}

QString Stol::getOption()
{
    return ("характеристики стола: " + forma);
}

QString Stol::getStranaProizv()
{
    return StranaProizv;
}

QString Shkaf::getforma()
{
    return forma;
}

QString Shkaf::getOption()
{
    return ("характеристики шкафа: " + StranaProizv);
}

QString Shkaf::getStranaProizv()
{
    return StranaProizv;
}

Catalog::Catalog()
{
    Head =  NULL;
    Tail = NULL;
    count = 0;
}
void Catalog::Add_Krovat(int &kod1, QString &color1, double &price1, QString &forma1, QString &StranaProizv1, int &kolNojek1)

{
    Tovar *A = new Krovat(kod1, color1, price1, forma1, StranaProizv1, kolNojek1);
    if (count != 0)
    {
        A->setPrev(Tail);
        A->setNext(Head);
        Head->setPrev(A);
        Tail->setNext(A);
        Head = A;
    }
    else
    {
        A->setNext(A);
        A->setPrev(A);
        Head = Tail = A;
    }
    count++;
}
void Catalog::Add_Stol(int &kod1, QString &color1, double &price1, QString &forma1, QString &StranaProizv1, int &kolNojek1)
{
    Tovar *A = new Stol(kod1, color1, price1, forma1, StranaProizv1, kolNojek1);
    if (count != 0)
    {
        A->setPrev(Tail);
        A->setNext(Head);
        Head->setPrev(A);
        Tail->setNext(A);
        Head = A;
    }
    else
    {
        A->setNext(A);
        A->setPrev(A);
        Head = Tail = A;
    }
    count++;
}
void Catalog::Add_Shkaf(int &kod1, QString &color1, double &price1,QString &forma1, QString &StranaProizv1)
{
    Tovar *A = new Shkaf(kod1, color1, price1, forma1,StranaProizv1);
    if (count != 0)
    {
        A->setPrev(Tail);
        A->setNext(Head);
        Head->setPrev(A);
        Tail->setNext(A);
        Head = A;
    }
    else
    {
        A->setNext(A);
        A->setPrev(A);
        Head = Tail = A;
    }
    count++;
}
void Catalog::Del(int kod)
{
    Tovar *A = Head;
    while (A->getKod() != QString::number(kod))
    {
        A = A->getNext();
    }
    if (count != 1)
    {
        A->getNext()->setPrev(A->getPrev());
        A->getPrev()->setNext(A->getNext());
        if (A == Head) Head = A->getNext();
        if (A == Tail) Tail = A->getPrev();
    }
    else Head = Tail = NULL;
    delete A;
    count--;
}
int Catalog::getCount()
{
    return count;
}
Tovar* Catalog::getHead()
{
    return Head;
}
Tovar* Catalog::getTail()
{
    return Tail;
}
void Catalog::setHead(Tovar* exemp)
{
    Head = exemp;
}
void Catalog::setTail(Tovar* exemp)
{
    Tail = exemp;
}

Shop::Shop(int &koodMag, QString &ciity, QString &oblaast, QString &stret, int &houuse, QString &teleefon, QString &naame)
{
    kodMag = koodMag;
    oblast = oblaast;
    city = ciity;
    street = stret;
    house = houuse;
    name = naame;
    telefon = teleefon;
    furnitures = new Catalog();
}
QString Shop::getShop()
{
    return name;
}
QString Shop::getName()
{
    return name;
}
QString Shop::getTelefon()
{
    return telefon;
}
QString Shop::getOblast()
{
    return oblast;
}
QString Shop::getcity()
{
    return city;
}
QString Shop::getStreet()
{
    return street;
}
QString Shop::gethouse()
{
    return QString::number(house);
}
QString Shop::getkodMag()
{
    return QString::number(kodMag);
}
void Shop::setNext(Shop* exemp)
{
    Next = exemp;
}
void Shop::setPrev(Shop* exemp)
{
    Prev = exemp;
}
Shop* Shop::getNext()
{
    return Next;
}
Shop* Shop::getPrev()
{
    return Prev;
}

Catalog* Shop::get_furnitures()
{
    return furnitures;
}

List::List()
{
    Head = Tail = NULL;
    count = 0;
}
void List::Add_Shop(int &kodMag1, QString &city1, QString &oblast1, QString &street1, int &house1, QString &telefon1, QString &name1)
{
    Shop *A = new Shop(kodMag1, city1, oblast1, street1, house1, telefon1, name1);
    if (count != 0)
    {
        A->setPrev(Tail);
        A->setNext(Head);
        Head->setPrev(A);
        Tail->setNext(A);
        Head = A;
    }
    else
    {
        A->setNext(A);
        A->setPrev(A);
        Head = Tail = A;
    }
    count++;
}
void List::Del(int n)
{
    int i = 0;
    Shop *A = Tail;
    while (i < n)
    {
        A = A->getPrev();
        i++;
    }
    if (count != 1)
    {
        A->getNext()->setPrev(A->getPrev());
        A->getPrev()->setNext(A->getNext());
        if (A == Head) Head = A->getNext();
        if (A == Tail) Tail = A->getPrev();
    }
    else Head = Tail = NULL;
    delete A;
    count--;
}
int List::getCount()
{
    return count;
}
Shop* List::getHead()
{
    return Head;
}
Shop* List::getTail()
{
    return Tail;
}

void List::setHead(Shop* exemp)
{
    Head = exemp;
}
void List::setTail(Shop* exemp)
{
    Tail = exemp;
}


List *Sl;
int kod, kolNojek, k, count_mebel = 0, count_poisk=0, k1, row, column, kod1, shop_count = 0, house,b;
QString forma, StranaProizv, color, proverka, proverka1, adres, str, vidMeb, vid,oblast, city, street, telefon,telefon_1,telefon_2,o, name,a;
double price;
bool zapolnenie = true, pravilnost = true;
Tovar *Tov;
Shop *S;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMessageBox::warning(this, "Привет, это мой курсовой проект!", "Добро пожаловать в программу Кирюши Жданова");
    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->redact_mebel->setDisabled(1);
    ui->search_mebel->setDisabled(1);
    ui->add_mebel->setDisabled(1);
    ui->delete_mebel->setDisabled(1);
    ui->poisk_kod->setChecked(true);

    ui->table->setColumnWidth(0,30);
    ui->table->setColumnWidth(1,100);
    ui->table->setColumnWidth(2,50);
    ui->table->setColumnWidth(3,70);
    ui->table->setColumnWidth(4,120);
    ui->table->setColumnWidth(5,70);
    ui->table->setColumnWidth(6,130);
    ui->table->setColumnWidth(7,90);

    ui->table_2->setColumnWidth(0,30);
    ui->table_2->setColumnWidth(1,100);
    ui->table_2->setColumnWidth(2,50);
    ui->table_2->setColumnWidth(3,70);
    ui->table_2->setColumnWidth(4,120);
    ui->table_2->setColumnWidth(5,70);
    ui->table_2->setColumnWidth(6,130);
    ui->table_2->setColumnWidth(7,90);

    ui->table_3->setColumnWidth(0,85);
    ui->table_3->setColumnWidth(1,70);
    ui->table_3->setColumnWidth(2,100);
    ui->table_3->setColumnWidth(3,100);
    ui->table_3->setColumnWidth(4,80);
    ui->table_3->setColumnWidth(5,80);
    ui->table_3->setColumnWidth(6,50);

    Sl = new List();

}

MainWindow::~MainWindow()
{
    delete ui;
}


int MainWindow::proverka_kod(int kod, int count_mebel)
{
    if (count_mebel != 0)
    {
        Shop *A = Sl->getHead();
        for (int i = 0; i < Sl->getCount(); i++)
        {
            Tovar *B = A->get_furnitures()->getHead();
            for (int j = 0; j < A->get_furnitures()->getCount(); j++)
            {
                if ((B->getKod() == QString::number(kod)) && (B != Tov))
                {
                    QMessageBox::warning(this, "Ошибка", "Такой код уже есть. Введите новый");
                    return 0;
                }
                B = B->getNext();
            }
            A = A->getNext();
        }
    }
    return 1;
}

int MainWindow::proverka_name(QString name, int shop_count)
{
    if (shop_count != 0)
    {
        Shop *A = Sl->getHead();
        for (int i = 0; i < Sl->getCount(); i++)
        {

            if ((A->getName() == name) && (A != S))
            {
                QMessageBox::warning(this, "Ошибка", "Такое название уже есть. Введите другое");
                return 0;
            }
            A = A->getNext();
        }
    }
    return 1;
}

int MainWindow::poisk_kod(int kod)
{
    S = Sl->getHead();
    for (int i = 0; i < Sl->getCount(); i++)
    {
        Tov = S->get_furnitures()->getHead();
        for (int j = 0; j < S->get_furnitures()->getCount(); j++)
        {
            if (Tov->getKod() == QString::number(kod))
            {
                return 0;
            }
            Tov = Tov->getNext();
        }
        S = S->getNext();
    }
    return 0;
}

void MainWindow::table1(Shop *B, Tovar *A, int j)
{
    ui->table->setItem(j, 0, new QTableWidgetItem(A->getKod()));
    ui->table->setItem(j, 1, new QTableWidgetItem(A->getMebel()));
    ui->table->setItem(j, 3, new QTableWidgetItem(A->getColor()));
    ui->table->setItem(j, 2, new QTableWidgetItem(A->getPrice()));
    ui->table->setItem(j, 4, new QTableWidgetItem(B->getShop()));

    if (A->getMebel() == "Кровать")
    {
        ui->table->setItem(j, 5, new QTableWidgetItem(dynamic_cast<Krovat*>(A)->getforma()));
        ui->table->setItem(j, 6, new QTableWidgetItem(dynamic_cast<Krovat*>(A)->getStranaProizv()));
        ui->table->setItem(j, 7, new QTableWidgetItem(dynamic_cast<Krovat*>(A)->getkolNojek()));
    }
    else if (A->getMebel() == "Стол")
    {
        ui->table->setItem(j, 5, new QTableWidgetItem(dynamic_cast<Stol*>(A)->getforma()));
        ui->table->setItem(j, 6, new QTableWidgetItem(dynamic_cast<Stol*>(A)->getStranaProizv()));
        ui->table->setItem(j, 7, new QTableWidgetItem(dynamic_cast<Stol*>(A)->getkolNojek()));
    }
    else if (A->getMebel() == "Шкаф")
    {
        ui->table->setItem(j, 5, new QTableWidgetItem(dynamic_cast<Shkaf*>(A)->getforma()));
        ui->table->setItem(j, 6, new QTableWidgetItem(dynamic_cast<Shkaf*>(A)->getStranaProizv()));
    }

}

void MainWindow::table2(Shop *A, Tovar *B, int j)
{
    ui->table_2->insertRow(ui->table_2->rowCount());
    ui->table_2->setRowHeight(j, 50);
    ui->table_2->setItem(j, 0, new QTableWidgetItem(B->getKod()));
    ui->table_2->setItem(j, 1, new QTableWidgetItem(B->getMebel()));
    ui->table_2->setItem(j, 3, new QTableWidgetItem(B->getColor()));
    ui->table_2->setItem(j, 2, new QTableWidgetItem(B->getPrice()));
    ui->table_2->setItem(j, 4, new QTableWidgetItem(A->getShop()));
    if (B->getMebel() == "Кровать")
    {
        ui->table_2->setItem(j, 5, new QTableWidgetItem(dynamic_cast<Krovat*>(B)->getforma()));
        ui->table_2->setItem(j, 6, new QTableWidgetItem(dynamic_cast<Krovat*>(B)->getStranaProizv()));
        ui->table_2->setItem(j, 7, new QTableWidgetItem(dynamic_cast<Krovat*>(B)->getkolNojek()));
    }
    else if (B->getMebel() == "Стол")
    {
        ui->table_2->setItem(j, 5, new QTableWidgetItem(dynamic_cast<Stol*>(B)->getforma()));
        ui->table_2->setItem(j, 6, new QTableWidgetItem(dynamic_cast<Stol*>(B)->getStranaProizv()));
        ui->table_2->setItem(j, 7, new QTableWidgetItem(dynamic_cast<Stol*>(B)->getkolNojek()));
    }
    else if (B->getMebel() == "Шкаф")
    {
        ui->table_2->setItem(j, 5, new QTableWidgetItem(dynamic_cast<Shkaf*>(B)->getforma()));
        ui->table_2->setItem(j, 6, new QTableWidgetItem(dynamic_cast<Shkaf*>(B)->getStranaProizv()));
    }

}

void MainWindow::table3(Shop *A, int j)
{
    ui->table_3->setItem(j, 0, new QTableWidgetItem(A->getName()));
    ui->table_3->setItem(j, 1, new QTableWidgetItem(A->getkodMag()));
    ui->table_3->setItem(j, 2, new QTableWidgetItem(A->getTelefon()));
    ui->table_3->setItem(j, 3, new QTableWidgetItem(A->getOblast()));
    ui->table_3->setItem(j, 4, new QTableWidgetItem(A->getcity()));
    ui->table_3->setItem(j, 5, new QTableWidgetItem(A->getStreet()));
    ui->table_3->setItem(j, 6, new QTableWidgetItem(A->gethouse()));

}

int MainWindow::proverka_chisel(QString proverka)
{
    for (int i = 0; i < proverka.size(); i++)
    {
        if ((proverka[i] != '.') && (!proverka[i].isDigit())) return 0;
    }
    return 1;
}

int MainWindow::proverka_strok(QString proverka)
{
    for (int i = 0; i < proverka.size(); i++)
    {
        if (!proverka[i].isLetter()) return 0;
    }
    return 1;
}





void MainWindow::on_delete_mebel_clicked()
{
    QItemSelectionModel *selectionModel = ui->table->selectionModel();
    if (selectionModel->hasSelection())
    {
        row = ui->table->currentRow();
        kod = ui->table->item(row, 0)->text().toInt();
        adres = ui->table->item(row, 4)->text();
        ui->table->removeRow(row);
        Shop *A = Sl->getTail();
        for (int i = 0; i < Sl->getCount(); i++)
        {
            if (A->getShop() == adres)
            {
                A->get_furnitures()->Del(kod);
                break;
            }
            A = A->getPrev();
        }
        count_mebel--;
        if (count_mebel<1)
        {
        ui->redact_mebel->setDisabled(1);
        ui->search_mebel->setDisabled(1);
        }
        else
        {
            ui->redact_mebel->setEnabled(1);
            ui->search_mebel->setEnabled(1);
        }
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Выберите товар");
    }

}



void MainWindow::on_Managment_triggered()
{
    QMessageBox::about(this, "Руководство", "Информационно-поисковая система 'Мебельная фабрика' служит для упрощения работы с большими данными\n");
}



void MainWindow::on_redact_mebel_clicked()
{
    proverka = ui->Edit_kod->text();
    if (!proverka.size())
    {
        zapolnenie = false;
         QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Введите код");
    }
    proverka = ui->Edit_color->text();
    if (!proverka.size())
    {
        zapolnenie = false;
         QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Введите цвет");
    }
    proverka = ui->Edit_form->text();
    if (!proverka.size())
    {
        zapolnenie = false;
         QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Введите форму");
    }
    if ((a=="Кровать")||(a=="Стол")){
    proverka = ui->Edit_kolNojek->text();
    if (!proverka.size())
    {
        zapolnenie = false;
        QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Введите кол-во ножек");
    }
    }
    if (zapolnenie == true)
    {
        proverka1 = ui->Edit_kod->text();
        if (!proverka_chisel(proverka1))
        {
            pravilnost = false;
             QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Код не соответствует");
        }
        else
        {
            kod = ui->Edit_kod->text().toInt();
        }
        if (!proverka_kod(kod, count_mebel))
        {
            pravilnost = false;
        }
        if (ui->choose_country->currentIndex() == 0) StranaProizv = "Германия";
        else if (ui->choose_country->currentIndex() == 1) StranaProizv = "Швейцария";
        else StranaProizv = "Франция";
        proverka1 = ui->Edit_price->text();
        if (!proverka_chisel(proverka1))
        {
            pravilnost = false;
            QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Цена не соответствует");
        }
        else
        {
            price = ui->Edit_price->text().toDouble();
        }
        if ((a=="Кровать")||(a=="Стол")){
        proverka1 = ui->Edit_kolNojek->text();
        if (!proverka_chisel(proverka1))
        {
            pravilnost = false;
            QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Кол-во ножек не соответствует");
        }
        else
        {
            kolNojek = ui->Edit_kolNojek->text().toInt();
        }
        }
         proverka1 = ui->Edit_form->text();
         if (!proverka_strok(proverka1))
         {
             pravilnost = false;
             QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Форма не соответствует");
         }
         else
         {
             forma = ui->Edit_form->text();
         }
         proverka1 = ui->Edit_color->text();
         if (!proverka_strok(proverka1))
         {
             pravilnost = false;
             QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Цвет не соответствует");
         }
         else
         {
             color = ui->Edit_color->text();
         }
        k = ui->choose_mag->currentIndex();
    }
    if (k1 != k)
    {
        S->get_furnitures()->Del(kod1);
        if ((zapolnenie == true) && (pravilnost == true))
        {

            int l = 0;
            Shop* A = Sl->getTail();
            while(l != k)
            {
                A = A->getPrev();
                l++;
            }
            if (a=="Кровать") A->get_furnitures()->Add_Krovat(kod, color, price, forma, StranaProizv, kolNojek);
            else if (a=="Стол") A->get_furnitures()->Add_Stol(kod, color, price, forma, StranaProizv, kolNojek);
            else if(a=="Шкаф") A->get_furnitures()->Add_Shkaf(kod, color, price, forma, StranaProizv);
            Tovar *B = A->get_furnitures()->getHead();
            table1(A, B, row);
            ui->stackedWidget->setCurrentIndex(0);
        }
        if (pravilnost == false)
        {
            pravilnost = true;
        }
        if (zapolnenie == false)
        {
            zapolnenie = true;
        }
    }
    else
    {
        if ((zapolnenie == true) && (pravilnost == true))
        {
            Tovar *A = nullptr;
            if (a=="Кровать") A = new Krovat(kod, color, price, forma, StranaProizv, kolNojek);
            else if (a=="Стол")  A = new Stol(kod, color, price, forma, StranaProizv, kolNojek);
            else if (a=="Шкаф") A = new Shkaf(kod, color, price, forma, StranaProizv);
            if (S->get_furnitures()->getCount() != 1)
            {
                Tov->getPrev()->setNext(A);
                Tov->getNext()->setPrev(A);
                A->setNext(Tov->getNext());
                A->setPrev(Tov->getPrev());
            }
            else
            {
                A->setNext(A);
                A->setPrev(A);
            }
            if (S->get_furnitures()->getHead() == Tov) S->get_furnitures()->setHead(A);
            if (S->get_furnitures()->getTail() == Tov) S->get_furnitures()->setTail(A);
            table1(S, A, row);
        }
        if (pravilnost == false)
        {
            pravilnost = true;
            QMessageBox::warning(this, "Ошибка", "Недопустимое значение");
        }
        if (zapolnenie == false)
        {
            zapolnenie = true;
            QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены");
        }
    }
    ui->vid_product->setCurrentIndex(0);
    ui->choose_country->setCurrentIndex(0);
    ui->Edit_color->clear();
    ui->Edit_kod->clear();
    ui->Edit_price->clear();
    ui->Edit_form->clear();
    ui->Edit_kolNojek->clear();
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->add_mag->setDisabled(0);
    ui->delete_mag->setDisabled(0);
    ui->add_mebel->setDisabled(0);
    ui->delete_mebel->setDisabled(0);
    ui->vhod_poisk->setDisabled(0);
    ui->vid_product->setDisabled(0);
}



void MainWindow::on_delete_mag_clicked()
{
    QItemSelectionModel *selectionModel = ui->table_3->selectionModel();
    if (selectionModel->hasSelection())
    {
        row = ui->table_3->currentRow();
        ui->table_3->removeRow(row);
        shop_count--;
        if (shop_count<1)
        {
        ui->add_mebel->setDisabled(1);
        ui->delete_mebel->setDisabled(1);
        }
        else
        {
            ui->add_mebel->setEnabled(1);
            ui->delete_mebel->setEnabled(1);
        }
        ui->choose_mag->removeItem(row);
        int l = 0;
        Shop* A = Sl->getTail();
        while (l != row)
        {
            A = A->getPrev();
            l++;
        }
        for (int i = 0; i < count_mebel; i++)
        {
            if (ui->table->item(i, 4)->text() == A->getShop())
            {
                ui->table->removeRow(i);
                i--;
                count_mebel--;
                if (count_mebel<1)
                {
                    ui->redact_mebel->setDisabled(1);
                    ui->search_mebel->setDisabled(1);
                }
                else
                {
                    ui->redact_mebel->setEnabled(1);
                    ui->search_mebel->setEnabled(1);
                }
            }
        }
        Sl->Del(row);
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Выберите магазин");
    }
}


void MainWindow::on_add_mag_clicked()
{
    proverka = ui->name_mag->text();
    if ((!proverka.size() || !proverka_name(proverka, shop_count)))
    {
        zapolnenie = false;
        QMessageBox::warning(this, "Ошибка", "Введите магазин корректно");
    }
    proverka = ui->oblast_mag->text();
    if ((!proverka.size()) || (!proverka_strok(proverka)))
    {
        zapolnenie = false;
        QMessageBox::warning(this, "Ошибка", "Введите область корректно. Это должно быть только буквенное значение");
    }
    proverka = ui->city_mag->text();
    if ((!proverka.size()) || (!proverka_strok(proverka)))
    {
        zapolnenie = false;
        QMessageBox::warning(this, "Ошибка", "Введите город корректно. Это должно быть только буквенное значение");
    }
    proverka = ui->street_mag->text();
    if ((!proverka.size()) || (!proverka_strok(proverka)))
    {
        zapolnenie = false;
        QMessageBox::warning(this, "Ошибка", "Введите улицу корректно. Это должно быть только буквенное значение");
    }
    proverka = ui->house_mag->text();
    if ((!proverka.size()) || (!proverka_chisel(proverka))||(proverka.size()>3))
    {
        zapolnenie = false;
        QMessageBox::warning(this, "Ошибка", "Введите дом корректно. Это должно быть только числовое значение");
    }
    proverka = ui->index_mag->text();
    if ((!proverka.size()) || (!proverka_chisel(proverka))||(proverka.size()!=6))
    {
        zapolnenie = false;
        QMessageBox::warning(this, "Ошибка", "Введите индекс корректно. Это должно быть только числовое значение");
    }
    proverka = ui->telefon_mag->text();
    o=ui->telefon_mag->text();
    for (int i = 0; i < o.size(); i++)
    {
        if (i==0) telefon_1=o[i];
        if (i==1) telefon_2=o[i];
    }
    if ((!proverka.size()) || (!proverka_chisel(proverka))||(proverka.size()!=11)||(telefon_1!="8")||(telefon_2!="9"))
    {
        zapolnenie = false;
        QMessageBox::warning(this, "Ошибка", "Введите телефон корректно. Это должно быть только числовое значение");
    }

    if (zapolnenie == true)
    {
        name = ui->name_mag->text();
        int index = ui->index_mag->text().toInt();
        telefon = ui->telefon_mag->text();
        oblast = ui->oblast_mag->text();
        city = ui->city_mag->text();
        street = ui->street_mag->text();
        house = ui->house_mag->text().toInt();
        Sl->Add_Shop(index, city, oblast, street, house, telefon, name);
        Shop *A = Sl->getHead();
        ui->table_3->insertRow(ui->table_3->rowCount());
        table3(A, shop_count);
        shop_count++;
        if (shop_count<1)
        {
        ui->add_mebel->setDisabled(1);
        ui->delete_mebel->setDisabled(1);
        }
        else
        {
            ui->add_mebel->setEnabled(1);
            ui->delete_mebel->setEnabled(1);
        }
        ui->choose_mag->addItem(name);
        ui->oblast_mag->clear();
        ui->index_mag->clear();
        ui->house_mag->clear();
        ui->city_mag->clear();
        ui->street_mag->clear();
        ui->telefon_mag->clear();
        ui->name_mag->clear();
    }
    else
    {
        zapolnenie = true;
        QMessageBox::warning(this, "Ошибка", "Недопустимое значение");
    }
}


void MainWindow::on_Create_triggered()
{
    if (!str.isNull())
    {
        for (int i = count_mebel-1; i >= 0; i--)
        {
            ui->table->removeRow(i);
        }
        count_mebel = 0;
        for (int i = shop_count-1; i >= 0; i--)
        {
            ui->table_3->removeRow(i);
            ui->choose_mag->removeItem(i);
            Sl->Del(i);
        }
        shop_count = 0;
        ui->stackedWidget->setCurrentIndex(1);
        ui->stackedWidget_2->setCurrentIndex(0);
        ui->redact_mebel->setDisabled(1);
        ui->search_mebel->setDisabled(1);
        ui->add_mebel->setDisabled(1);
        ui->delete_mebel->setDisabled(1);
        ui->poisk_kod->setChecked(true);
    }
    else QMessageBox::warning(this, "Ошибка", "Текущий файл не сохранен");
}


void MainWindow::on_Open_triggered()
{
    on_Create_triggered();
    QString P, p;
    int row1 = 0, column = 0, row = 0;
    QString selFilter="All files (*.*)";
    str = QFileDialog::getOpenFileName(this,"Open file",QDir::currentPath(),
    "Text files (*.txt);;All files (*.*)",&selFilter);
    QFile file(str);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            P = in.readLine();
            if (P[0] != ' ')
            {
                ui->table_3->insertRow(ui->table_3->rowCount());
                for (int i = 0; i < P.size(); i++)
                {
                    if((P[i] == '|'))
                    {
                        ui->table_3->setItem(row1, column, new QTableWidgetItem(p));
                        column++;
                        p.clear();
                    }
                    else p += P[i];
                }
                ui->table_3->setItem(row1, column, new QTableWidgetItem(p));
                int index = ui->table_3->item(row1, 1)->text().toInt();
                name = ui->table_3->item(row1, 0)->text();
                street = ui->table_3->item(row1, 5)->text();
                city = ui->table_3->item(row1, 4)->text();
                oblast = ui->table_3->item(row1, 3)->text();
                house = ui->table_3->item(row1, 6)->text().toInt();
                telefon = ui->table_3->item(row1, 2)->text();
                Sl->Add_Shop(index, city, oblast, street, house, telefon, name);
                ui->choose_mag->addItem(name);
                shop_count++;
                column = 0;
                row1++;
                p.clear();
            }
            else
            {
                ui->table->insertRow(ui->table->rowCount());
                ui->table->setRowHeight(row, 50);
                for (int i = 1; i < P.size(); i++)
                {
                    if((P[i] == '|'))
                    {
                        ui->table->setItem(row, column, new QTableWidgetItem(p));
                        if (column == 3)
                        {
                            column++;
                            ui->table->setItem(row, column, new QTableWidgetItem(Sl->getHead()->getShop()));
                        }
                        if (column == 6)
                        {
                            if (ui->table->item(row, 1)->text() == "Шкаф") column++;
                        }
                        column++;
                        if (column > 7) i = P.size();
                        p.clear();
                    }
                    else p += P[i];
                }
                ui->table->setItem(row, column, new QTableWidgetItem(p));
                p.clear();
                QString vidMeb = ui->table->item(row, 1)->text();
                if (vidMeb == "Кровать")
                {
                    kod = ui->table->item(row, 0)->text().toInt();
                    StranaProizv = ui->table->item(row, 6)->text();
                    price = ui->table->item(row, 2)->text().toDouble();
                    forma = ui->table->item(row, 5)->text();
                    kolNojek = ui->table->item(row, 7)->text().toInt();
                    color = ui->table->item(row, 3)->text();
                    Shop *A = Sl->getTail();
                    adres = ui->table->item(row, 4)->text();
                    int l = 0;
                    while(l != Sl->getCount())
                    {
                        if (A->getShop() == adres) break;
                        l++;
                        A = A->getPrev();
                    }
                    A->get_furnitures()->Add_Krovat(kod,  color, price,forma, StranaProizv, kolNojek);
                    count_mebel++;
                }
                else if (vidMeb == "Стол")
                {
                    kod = ui->table->item(row, 0)->text().toInt();
                    StranaProizv = ui->table->item(row, 6)->text();
                    price = ui->table->item(row, 2)->text().toDouble();
                    forma = ui->table->item(row, 5)->text();
                    kolNojek = ui->table->item(row, 7)->text().toInt();
                    color = ui->table->item(row, 3)->text();
                    Shop *A = Sl->getTail();
                    adres = ui->table->item(row, 4)->text();
                    int l = 0;
                    while(l != Sl->getCount())
                    {
                        if (A->getShop() == adres) break;
                        l++;
                        A = A->getPrev();
                    }
                    A->get_furnitures()->Add_Stol(kod, color, price, forma, StranaProizv, kolNojek);
                    count_mebel++;
                }
                else if (vidMeb == "Шкаф")
                {
                    kod = ui->table->item(row, 0)->text().toInt();
                    StranaProizv = ui->table->item(row, 6)->text();
                    price = ui->table->item(row, 2)->text().toDouble();
                    forma = ui->table->item(row, 5)->text();
                    color = ui->table->item(row, 3)->text();
                    Shop *A = Sl->getTail();
                    adres = ui->table->item(row, 4)->text();
                    int l = 0;
                        while(l != Sl->getCount())
                        {
                            if (A->getShop() == adres) break;
                            l++;
                            A = A->getPrev();
                        }
                        A->get_furnitures()->Add_Shkaf(kod, color, price, forma, StranaProizv);
                        count_mebel++;


                }
                row++;
                column = 0;
            }
        }
        file.close();
        ui->search_mebel->setDisabled(0);
        ui->add_mebel->setDisabled(0);
        ui->delete_mebel->setDisabled(0);
        ui->redact_mebel->setDisabled(0);
    }
}


void MainWindow::on_add_mebel_clicked()
{

    proverka = ui->Edit_kod->text();
    if (!proverka.size())
    {
        zapolnenie = false;
        QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Введите код");
    }
    proverka = ui->Edit_color->text();
    if (!proverka.size())
    {
        zapolnenie = false;
        QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Введите цвет");
    }
    proverka = ui->Edit_price->text();
    if (!proverka.size())
    {
        zapolnenie = false;
        QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Введите цену");
    }
    proverka = ui->Edit_form->text();
    if (!proverka.size())
    {
        zapolnenie = false;
        QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Введите форму");
    }
    if ((ui->vid_product->currentIndex() == 1)|| (ui->vid_product->currentIndex() == 0)){
    proverka = ui->Edit_kolNojek->text();
    if (!proverka.size())
    {
        zapolnenie = false;
        QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Введите кол-во ножек");
    }
    }
    if (zapolnenie == true)
    {
        proverka1 = ui->Edit_kod->text();
        if (!proverka_chisel(proverka1))
        {
            pravilnost = false;
            QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Код не соответствует");
        }
        else
        {
            kod = ui->Edit_kod->text().toInt();
        }
        if (!proverka_kod(kod, count_mebel))
        {
            pravilnost = false;
            QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Код не соответствует, есть такой");
        }
        if (ui->choose_country->currentIndex() == 0) StranaProizv = "Германия";
        else if (ui->choose_country->currentIndex() == 1) StranaProizv = "Швейцария";
        else StranaProizv = "Франция";
        proverka1 = ui->Edit_price->text();
        if (!proverka_chisel(proverka1))
        {
            pravilnost = false;
            QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Цена не соответствует");
        }
        else
        {
            price = ui->Edit_price->text().toDouble();
        }

        if ((ui->vid_product->currentIndex() == 1)|| (ui->vid_product->currentIndex() == 0)){

            proverka1 = ui->Edit_kolNojek->text();
        if (!proverka_chisel(proverka1))
        {
            pravilnost = false;
            QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Кол-во ножек не соответствует");
        }
        else
        {
            kolNojek = ui->Edit_kolNojek->text().toInt();
        }
        }

         proverka1 = ui->Edit_form->text();
         if (!proverka_strok(proverka1))
         {
             pravilnost = false;
             QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Форма не соответствует");
         }
         else
         {
             forma = ui->Edit_form->text();
         }
         proverka1 = ui->Edit_color->text();
         if (!proverka_strok(proverka1))
         {
             pravilnost = false;
             QMessageBox::warning(this, "Ошибка", "Невозможно добавить новый товар. Цвет не соответствует");
         }
         else
         {
             color = ui->Edit_color->text();
         }
         k = ui->choose_mag->currentIndex();

    }
    if ((zapolnenie == true) && (pravilnost == true))
    {
        int l = 0;
        Shop* A = Sl->getTail();
        while(l != k)
        {
            A = A->getPrev();
            l++;
        }
        if (ui->vid_product->currentIndex() == 0) A->get_furnitures()->Add_Krovat(kod, color, price, forma, StranaProizv, kolNojek);
        else if (ui->vid_product->currentIndex() == 1) A->get_furnitures()->Add_Stol(kod, color, price, forma, StranaProizv, kolNojek);
        else A->get_furnitures()->Add_Shkaf(kod, color, price, forma, StranaProizv);
        Tovar *B = A->get_furnitures()->getHead();
        ui->table->insertRow(ui->table->rowCount());
        ui->table->setRowHeight(count_mebel, 50);
        table1(A, B, count_mebel);
        count_mebel++;
        if (count_mebel<1)
        {
            ui->redact_mebel->setDisabled(1);
            ui->search_mebel->setDisabled(1);
        }
        else
        {
            ui->redact_mebel->setEnabled(1);
            ui->search_mebel->setEnabled(1);
        }
        ui->choose_country->setCurrentIndex(0);
        ui->Edit_color->clear();
        ui->Edit_kod->clear();
        ui->Edit_form->clear();
        ui->Edit_kolNojek->clear();
        ui->Edit_price->clear();
    }
    if (pravilnost == false)
    {
        pravilnost = true;
    }
    if (zapolnenie == false)
    {
        zapolnenie = true;
    }
}


void MainWindow::on_search_mebel_clicked()
{
        int count_mebel_2 = count_mebel;
        for (int i = 0; i < count_mebel_2; i++)
        {
            ui->table_2->removeRow(i);
            i--;
            count_mebel_2--;
        }
        int count_poisk = 0;
        if (ui->poisk_kod->isChecked())
        {
            Shop *A = Sl->getTail();
            for (int i = 0; i < Sl->getCount(); i++)
            {
                Tovar *B = A->get_furnitures()->getTail();
                for (int j = 0; j < A->get_furnitures()->getCount(); j++)
                {
                    if (B->getKod() == ui->poisk_vvod->text())
                    {
                        table2(A, B, count_poisk);
                        count_poisk++;
                    }
                    B = B->getPrev();
                }
                A = A->getPrev();
            }
            count_poisk = 0;
        }
        if (ui->poisk_color->isChecked())
        {
            Shop *A = Sl->getTail();
            for (int i = 0; i < Sl->getCount(); i++)
            {
                Tovar *B = A->get_furnitures()->getTail();
                for (int j = 0; j < A->get_furnitures()->getCount(); j++)
                {
                    if (B->getColor() == ui->poisk_vvod->text())
                    {
                        table2(A, B, count_poisk);
                        count_poisk++;
                    }
                    B = B->getPrev();
                }
                A = A->getPrev();
            }
            count_poisk = 0;
        }
        else if (ui->poisk_vid->isChecked())
        {
            Shop *A = Sl->getTail();
            for (int i = 0; i < Sl->getCount(); i++)
            {
                Tovar *B = A->get_furnitures()->getTail();
                for (int j = 0; j < A->get_furnitures()->getCount(); j++)
                {
                    if (B->getMebel() == ui->poisk_vvod->text())
                    {
                        table2(A, B, count_poisk);
                        count_poisk++;
                    }
                    B = B->getPrev();
                }
                A = A->getPrev();
            }
            count_poisk = 0;
        }
        ui->poisk_vvod->clear();
}




void MainWindow::on_vhod_poisk_clicked()
{
    if (count_mebel<1)
    {
        ui->redact_mebel->setDisabled(1);
        ui->search_mebel->setDisabled(1);
    }
    else
    {
        ui->redact_mebel->setEnabled(1);
        ui->search_mebel->setEnabled(1);
    }
    ui->stackedWidget->setCurrentIndex(0);
    ui->add_mag->setDisabled(1);
    ui->delete_mag->setDisabled(1);
    ui->add_mebel->setDisabled(1);
    ui->delete_mebel->setDisabled(1);
    ui->redact_mebel->setDisabled(1);
    ui->nachat_redact->setDisabled(1);
}


void MainWindow::on_vihod_poisk_clicked()
{
    if (count_mebel<1)
    {
        ui->redact_mebel->setDisabled(1);
    }
    else
    {
        ui->redact_mebel->setEnabled(1);
    }
    if (shop_count<1)
    {
        ui->add_mebel->setDisabled(1);
        ui->delete_mebel->setDisabled(1);
    }
    else
    {
        ui->add_mebel->setEnabled(1);
        ui->delete_mebel->setEnabled(1);
    }
    ui->add_mag->setDisabled(0);
    ui->delete_mag->setDisabled(0);
    ui->nachat_redact->setDisabled(0);
    int count_mebel_2 = count_mebel;
    for (int i = 0; i < count_mebel_2; i++)
    {
        ui->table_2->removeRow(i);
        i--;
        count_mebel_2--;
    }
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_nachat_redact_clicked()
{
    QItemSelectionModel *selectionModel = ui->table->selectionModel();
    if (selectionModel->hasSelection())
    {
        ui->stackedWidget_2->setCurrentIndex(1);
        row = ui->table->currentRow();
        QString vidMeb = ui->table->item(row, 1)->text();
        ui->Edit_kod->setText(ui->table->item(row, 0)->text());
        if (ui->table->item(row, 6)->text() == "Германия") ui->choose_country->setCurrentIndex(0);
        else if(ui->table->item(row, 6)->text() == "Швейцария") ui->choose_country->setCurrentIndex(1);
        else if(ui->table->item(row, 6)->text() == "Франция") ui->choose_country->setCurrentIndex(2);
        ui->Edit_price->setText(ui->table->item(row, 2)->text());
        ui->Edit_color->setText(ui->table->item(row, 3)->text());
        ui->Edit_form->setText(ui->table->item(row, 5)->text());
        if((vidMeb=="Кровать")||(vidMeb=="Стол"))
        {
            ui->Edit_kolNojek->setText(ui->table->item(row, 7)->text());
        }
        Shop *A = Sl->getTail();
        adres = ui->table->item(row, 4)->text();
        a = ui->table->item(row, 1)->text();
        int l = 0;
        while(l != Sl->getCount())
        {
            if (A->getShop() == adres) break;
            l++;
            A = A->getPrev();
        }
        ui->choose_mag->setCurrentIndex(l);
        k1 = l;
        poisk_kod(ui->table->item(row, 0)->text().toInt());
        kod1 = ui->table->item(row, 0)->text().toInt();
        ui->add_mag->setDisabled(1);
        ui->delete_mag->setDisabled(1);
        ui->add_mebel->setDisabled(1);
        ui->delete_mebel->setDisabled(1);
        ui->vhod_poisk->setDisabled(1);
        ui->vid_product->setDisabled(1);
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Кликните на нужный вам товар");
    }
}

void MainWindow::on_Exit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_About_the_program_triggered()
{
    QMessageBox::about(this, "О программе", "Программа служит главным условием защиты курсовой работы\nРазработал Жданов Кирилл\nПреподаватель: Захарова Ольга Владимировна\nГруппа 11-ПГ\nС помощью программы вы можете вносить определённые данные о мебели, редактировать их, сохранять и считывать информацию из других файлов");
}



void MainWindow::write1(QString str1)
{
    QFile file(str1);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        Shop *A = Sl->getTail();
        for (int i = 0; i < Sl->getCount(); i++)
        {
            out << A->getName() << "|"
                << A->getkodMag() << "|"
                << A->getOblast() << "|"
                << A->getcity() << "|"
                << A->getStreet() << "|"
                << A->gethouse() << "|"
                << A->getTelefon()<<"|"<<"\n";
            Tovar *B = A->get_furnitures()->getTail();
            for (int j = 0; j < A->get_furnitures()->getCount(); j++)
            {
                out << " " << B->getKod() << "|"
                    << B->getMebel() << "|";
                if (B->getMebel() == "Кровать")
                {
                    out << B->getPrice() << "|"
                    << B->getColor()<< "|"
                    << dynamic_cast<Krovat*>(B)->getforma()<< "|"
                    << dynamic_cast<Krovat*>(B)->getStranaProizv()<< "|"
                    << dynamic_cast<Krovat*>(B)->getkolNojek()<< "|"<<"\n";
                }
                else if (B->getMebel() == "Стол")
                {
                    out << B->getPrice() << "|"
                    << B->getColor()<< "|"
                    << dynamic_cast<Stol*>(B)->getforma()<< "|"
                    << dynamic_cast<Stol*>(B)->getStranaProizv()<< "|"
                    << dynamic_cast<Stol*>(B)->getkolNojek() << "|"<<"\n";
                }

                else if (B->getMebel() == "Шкаф")
                {
                    out << B->getPrice() << "|"
                    << B->getColor()<< "|"
                    << dynamic_cast<Shkaf*>(B)->getforma()<< "|"
                    << dynamic_cast<Shkaf*>(B)->getStranaProizv() << "|"<<"\n";
                }

                B = B->getPrev();
            }
            A = A->getPrev();
        }
    }
    else QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
}

void MainWindow::on_Save_triggered()
{
    if (!str.isNull())
    {
        QFile file(str);
        file.open(QFile::WriteOnly|QFile::Truncate);
        file.close();
        write1(str);
    }
    else QMessageBox::warning(this, "Ошибка", "Нет открытого файла");
}

void MainWindow::on_Save_As_triggered()
{
    QString selFilter="All files (*.*)";
    QString str1 = QFileDialog::getSaveFileName(this,"Save file",QDir::currentPath(),
    "Text files (*.txt);;All files (*.*)",&selFilter);
    write1(str1);
    str = str1;
}
