#ifndef PERSONAL_H
#define PERSONAL_H

#include "barber.h"
#include "beautician.h"
#include "administrator.h"


class personal
{
private:
    employee* head;
    int number_people;

public:
    personal()
    {
        head = nullptr;
        number_people = 0;
    }

    ~personal() {
        employee* r;
        while (head) {
            r = head;
            head = head->get_next();
            delete r;
        }
    }

    employee* get_head();
    int get_number_people();

    employee* follow_node(employee* node);
    employee* prev_node(employee* node);

    employee* find_node(QString name);

    void add_employee(employee* person);
    void del_employee(QString name);
    void clear() {head = nullptr; number_people = 0;}
};

#endif // PERSONAL_H
