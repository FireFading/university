#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QSpinBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QTextStream>
#include <QTableWidgetItem>
//#include <bits/stdc++.h>

class Tovar
{
private:
    int kod;
    QString mebel;
    QString color;
    double price;
    Tovar *Next, *Prev;
public:
    Tovar();
    Tovar(int &kod1, QString &color1, double &price1, QString mebel1):
        kod(kod1), color(color1), price(price1), mebel(mebel1) {}
    virtual ~Tovar(){}

    QString getMebel();

    QString getKod();

    QString getColor();

    QString getPrice();

    virtual QString getOption() = 0;

    void setNext(Tovar* exemp);

    void setPrev(Tovar* exemp);

    Tovar* getNext();

    Tovar* getPrev();

    virtual QString getforma() = 0;

    virtual QString getStranaProizv() = 0;

    virtual QString getkolNojek() = 0;
};

class Krovat: public Tovar
{
private:
    QString forma;
    QString StranaProizv;
    int kolNojek;
public:
    Krovat(): Tovar() {}
    Krovat(int &kod1, QString &color1, double &price1, QString &forma1, QString &StranaProizv1, int &kolNojek1):
        Tovar(kod1, color1, price1, "Кровать"), forma(forma1), StranaProizv(StranaProizv1), kolNojek(kolNojek1) {}

    QString getkolNojek();

    QString getforma();

    QString getStranaProizv();

    QString getOption();
};

class Stol: public Tovar
{
private:
    QString forma;
    QString StranaProizv;
    int kolNojek;
public:
    Stol();
    Stol(int &kod1, QString &color1, double &price1, QString &forma1, QString &StranaProizv1, int &kolNojek1):
        Tovar(kod1, color1, price1, "Стол"), forma(forma1), StranaProizv(StranaProizv1), kolNojek(kolNojek1) {}

    QString getkolNojek();

    QString getforma();

    QString getStranaProizv();

    QString getOption();
};

class Shkaf: public Tovar
{
private:
    QString forma;
    QString StranaProizv;
public:
    Shkaf();
    Shkaf(int &kod1, QString &color1, double &price1,QString &forma1, QString &StranaProizv1):
        Tovar(kod1, color1, price1, "Шкаф"), forma(forma1), StranaProizv(StranaProizv1) {}

    QString getforma();

    QString getStranaProizv();

    QString getkolNojek() { return "a"; }

    QString getOption();
};


class Catalog
{
    Tovar *Head, *Tail;
    int count;
public:
    Catalog();
    void Add_Krovat(int &kod1, QString &color1, double &price1, QString &forma1, QString &StranaProizv1, int &kolNojek1);

    void Add_Stol(int &kod1, QString &color1, double &price1, QString &forma1, QString &StranaProizv1, int &kolNojek1);

    void Add_Shkaf(int &kod1, QString &color1, double &price1,QString &forma1, QString &StranaProizv1);

    void Del(int kod);

    int getCount();

    Tovar* getHead();

    Tovar* getTail();

    void setHead(Tovar* exemp);

    void setTail(Tovar* exemp);
};


class Shop
{
    QString oblast;
    QString city;
    QString street;
    int house;
    int kodMag;
    QString telefon;
    QString name;
    Shop *Prev;
    Shop *Next;
    Catalog* furnitures;
public:
    Shop();
    Shop(int &koodMag, QString &ciity, QString &oblaast, QString &stret, int &houuse, QString &teleefon, QString &naame);

    QString getShop();

    QString getName();

    QString getTelefon();

    QString getOblast();

    QString getcity();

    QString getStreet();

    QString gethouse();

    QString getkodMag();

    void setNext(Shop* exemp);

    void setPrev(Shop* exemp);

    Shop* getNext();

    Shop* getPrev();

    Catalog* get_furnitures();
};

class List
{
    Shop *Head, *Tail;
    int count;
public:
    List();

    void Add_Shop(int &kodMag1, QString &city1, QString &oblast1, QString &street1, int &house1, QString &telefon1, QString &name1);

    void Del(int n);

    int getCount();

    Shop* getHead();

    Shop* getTail();

    void setHead(Shop* exemp);

    void setTail(Shop* exemp);
};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void table1(Shop *B, Tovar *A, int j);
    int proverka_kod(int kod, int n);
    int proverka_name(QString name, int s);
    int proverka_chisel(QString proverka);
    int proverka_strok(QString proverka);
    void table2(Shop *A, Tovar *B, int j);
    void table3(Shop *A, int j);
    int poisk_kod(int kod);
    void write1(QString str1);

private slots:
    void on_Exit_triggered();

    void on_add_mag_clicked();

    void on_delete_mebel_clicked();

    void on_Create_triggered();

    void on_Open_triggered();

    void on_Save_triggered();

    void on_Save_As_triggered();

    void on_About_the_program_triggered();

    void on_Managment_triggered();

    void on_redact_mebel_clicked();

    void on_delete_mag_clicked();

    void on_add_mebel_clicked();

    void on_search_mebel_clicked();

//    void on_pushButton_clicked();

    void on_vhod_poisk_clicked();

    void on_vihod_poisk_clicked();

//    void on_stackedWidget_currentChanged(int arg1);

    void on_nachat_redact_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
