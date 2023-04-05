#ifndef PHARMACY_H
#define PHARMACY_H

#include "medicine.h"


class pharmacy
{
private:
    pharmacy* next;
    int artikul;
    QString name;
    QString adress;
    QString phone;
    medicine_list* medicines;

    static int number_pharmacy;

public:
    pharmacy(QString m_name="Apteca", QString m_adress="Orel, Lenin's street, 89", QString m_phone = "89203345678", medicine_list* m_medicines = nullptr, int m_artikul = 1);

    int get_artikul();
    QString get_name();
    QString get_adress();
    QString get_phone();
    pharmacy* get_next();
    medicine_list* get_medicines();

    static int get_number_pharmaces() { return number_pharmacy; }

    void set_data_pharmacy(QString m_name, QString m_adress, QString m_phone) ;

    void set_name(QString m_name);
    void set_adress(QString m_adress);
    void set_phone(QString m_phone);
    void set_next(pharmacy* m_next);
    void set_artikul(int id);

    friend class list_pharmacy;
    friend class MainWindow;
};


class list_pharmacy
{
private:
    pharmacy* head; // указатель на начало

    static int count_all;

public:
    list_pharmacy();

    ~list_pharmacy() { // деструктор
        pharmacy* r;
        while (head) {
            r = head;
            head = head->next;
            delete r;
        }
    }

    pharmacy* get_head();
    static int get_count_all() { return count_all; }

    pharmacy* Follow(pharmacy* node); // переход к следующему узлу
    pharmacy* Prev(pharmacy* node); // переход к предыдущему узлу

    pharmacy* find_node(int id_shop); // поиск магазина

    void add_node(pharmacy* new_shop); // добавление нового магазина в сеть
    void delete_node(int id_shop); // удаление магазина

    void clear_list(); // очистка сети магазинов
};

#endif // PHARMACY_H
