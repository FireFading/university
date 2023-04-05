#ifndef LIST_EMPLOYEES_H
#define LIST_EMPLOYEES_H
#include <QString>
#include <employee.h>

class List_employees // список людей, связанных с филиалом
{
private:
    Employee *Head;
    int count;
    void add(Employee *E);

public:
    List_employees();

    // добавление сотрудников в список
    void add_director(QString &id1, QString &full_name1, QString &age1, QString &salary1, QString &subordinates_number1);
    void add_teacher(QString &id1, QString &full_name1, QString &age1, QString &salary1, QString &subject1);
    void add_security(QString &id1, QString &full_name1, QString &age1, QString &salary1, QString &gun_license1);
    void del(int id);

    Employee *get_head();
    int get_count();

    void set_head(Employee *Obj);
    void set_count(int count1);

    // работа с указателями
    Employee* Follow(Employee* node);
    Employee* Prev(Employee* node);
    Employee* Last_node();

    friend class Branch;
};


#endif // LIST_EMPLOYEES_H
