#ifndef LIST_SALONS_H
#define LIST_SALONS_H

#include "salon.h"


class list_salons
{
private:
    salon* head;
    QString name;
    int count_salons;
public:
    list_salons() {
        head = nullptr;
        name = "default salons";
        count_salons = 0;
    }
    ~list_salons() {
        salon* r;
        while (head) {
            r = head;
            head = head->get_next();
            delete r;
        }
    }

    salon* get_head();
    QString get_name();
    int get_number_salons();

    salon* follow_node(salon* node);
    salon* prev_node(salon* node);

    salon* find_node(QString name);

    void add_node(salon* node);
    void del_node(QString name);
    void clear() { count_salons = 0; head = nullptr; }
};

#endif // LIST_SALONS_H
