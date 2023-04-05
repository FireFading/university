d#ifndef MEDICINE_H
#define MEDICINE_H

#include <QString>

class medicine
{
protected:
    medicine* next; // адрес следующего узла

private:
    QString category; // категория лекарства
    // поля-характеристики
    QString iid;
    QString price;
    QString firma;
    QString age;

    int current; // индивидуальный индетефикатор, каждому лекарству назначается автоматически для удобного поиска

    static int number_medicines; // количество товаров во всей сети магазинов
public:
    medicine(QString m_category = "Vitamins", QString m_iid = "0", QString m_price = "0", QString m_firma = "Evalar", QString m_age = "18", medicine* m_next = nullptr, int m_current = 0); // конструктор

    virtual ~medicine() = default; // виртуальный деструктор

    // получение данных из приватных полей
    QString get_category();
    QString get_iid();
    QString get_price();
    QString get_firma();
    QString get_age();
    medicine* get_next();
    int get_current();

    // установка новых данных в приватные поля
    void set_category(QString m_category);
    void set_iid(QString m_iid);
    void set_price(QString m_price);
    void set_firma(QString m_firma);
    void set_age(QString m_age);
    void set_next(medicine* m_next);

    static int get_number_medicines() { return number_medicines; } // получение данных об общем количестве лекарств

    void set_data(QString m_iid, QString m_price, QString m_firma, QString m_age); // установка данных о лекарстве

    // для получение информации о полях наследников класса
    virtual QString get_optional() = 0;
    virtual QString get_first() = 0;
    virtual QString get_second() = 0;
    virtual QString get_third() = 0;

    virtual void set_data_medicine(QString, QString, QString, QString, QString, QString, QString) = 0; // установка данных о лекарстве для наследуемых классов

    friend class medicine_list;  // для того, чтобы в классе List было доступно поле next
    friend class MainWindow;
};


class vitamins: public medicine
{
private:
    // поля-характеристики
    QString season;
    QString type;
    QString time;

    static int number_vitamins; // количество витаминов во всей сети магазинов

public:
    vitamins(QString m_iid = "0", QString m_price = "0", QString m_firma = "Evalar", QString m_age = "18", QString m_season = "winter", QString m_type = "tabs", QString m_time = "3"); // конструктор

     ~vitamins() = default; // деструктор

    // получение данных из приватных полей
    QString get_first();
    QString get_second();
    QString get_third();
    QString get_optional();

    static int get_number_vitamins() { return number_vitamins; }

    void set_data_medicine(QString m_iid, QString m_price, QString m_firma, QString m_age, QString m_season, QString m_type, QString m_time); // установка данных о товаре
};


class antibiotic: public medicine
{
private:
    QString period;
    QString danger;
    QString country;

    static int number_antibiotics; // количество витаминов во всей сети магазинов

public:
    antibiotic(QString m_iid = "0", QString m_price = "0", QString m_firma = "Evalar", QString m_age = "18", QString m_period = "7", QString m_danger = "take only by prescription", QString m_country = "Russia"); // конструктор

     ~antibiotic() = default; // деструктор

    // получение данных из приватных полей
    QString get_first();
    QString get_second();
    QString get_third();
    QString get_optional();

    static int get_number_antibiotics() { return number_antibiotics; }

    void set_data_medicine(QString m_iid, QString m_price, QString m_firma, QString m_age, QString m_period, QString m_danger, QString m_country); // установка данных о товаре
};


class antipyretic: public medicine
{
private:
    QString power;
    QString substance;
    QString concentration;

    static int number_antipyretic; // количество витаминов во всей сети магазинов

public:
    antipyretic(QString m_iid = "0", QString m_price = "0", QString m_firma = "Evalar", QString m_age = "18", QString m_power = "about 2 hours", QString m_substance = "paracetamol", QString m_concentration = "200"); // конструктор

     ~antipyretic() = default; // деструктор

    // получение данных из приватных полей
    QString get_first();
    QString get_second();
    QString get_third();
    QString get_optional();

    static int get_number_antipyretic() { return number_antipyretic; }

    void set_data_medicine(QString m_iid, QString m_price, QString m_firma, QString m_age, QString m_power, QString m_substance, QString m_concentration); // установка данных о товаре
};


class medicine_list {
private:
    medicine* head; // указатель на начало
    int count; // количество узлов

    int count_vitamins;
    int count_antibiotics;
    int count_antipyretic;
public:
    medicine_list(medicine* m_head = nullptr, int m_count = 0, int m_count_vitamins = 0, int m_count_antibiotics = 0, int m_count_antipyretic = 0); // конструктор

    ~medicine_list() { // деструктор - очистка
        medicine *r;
        while (head)
        {
            r = head;
            head = head->next;
            delete r;
          }
    }

    void clear_list(); // очистка списка

    // получение данных приватных полей
    int get_count();
    int get_count_vitamins();
    int get_count_antibiotics();
    int get_count_antipyretic();
    medicine* get_head();

    medicine* Follow(medicine* node); // переход к следующему узлу
    medicine* Prev(medicine* node); // переход к предыдущему узлу
    medicine* Last_node(); // переход к последнему узлу

    medicine* find_node(int id_product); // поиск лекарства

    void add_node(medicine* new_node); // добавление лекарства
    void delete_node(int id_product); // удаление лекарства

    friend class MainWindow;
};

#endif // MEDICINE_H
