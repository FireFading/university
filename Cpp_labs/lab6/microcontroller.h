#ifndef MICROCONTROLLER_H
#define MICROCONTROLLER_H

#include <QString>

class microcontroller
{
private:
    microcontroller *next;

    QString name;
    QString firma;
    QString year_production;

    int artikul;
public:
    microcontroller(QString m_name = "Microcontroller", QString m_firma = "Intel", QString m_year_production = "2022", int m_artikul = 0);

    QString get_name();
    QString get_firma();
    QString get_year_production();
    microcontroller* get_next();

    int get_artikul();

    void set_next(microcontroller* node);

    friend class list_microcontrollers;
};


class list_microcontrollers {
private:
    microcontroller* head;

    static int count_microcontrollers;

public:
    list_microcontrollers();

    microcontroller* get_head();

    void add_node(microcontroller* new_node);
    void delete_node(int &id_product);

    microcontroller* find_node(int id_microcontroller);

    static int get_count_microcontrollers() { return count_microcontrollers; }

    microcontroller* last_node();
    microcontroller* follow(microcontroller* node);
    microcontroller* prev(microcontroller* node);
};

#endif // MICROCONTROLLER_H
