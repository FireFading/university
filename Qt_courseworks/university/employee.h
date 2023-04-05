#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>

class Employee
{
    QString type;
    QString id;
    QString full_name;
    QString age;
    QString salary;
    Employee *next;

    static int count_all;

public:
    Employee();
    Employee(QString &id1, QString &full_name1, QString &age1, QString &salary1):
        id(id1), full_name(full_name1), age(age1), salary(salary1) {
        next = nullptr;
    }
    virtual ~Employee() = default;

    // получение данных приватных полей
    Employee *get_next();
    QString get_id();
    QString get_full_name();
    QString get_age();
    QString get_salary();

    void set_next(Employee *Obj);

    // работа с количеством сотрудников всего во всех филиалах
    static void add_employee() { count_all++; }
    static void del_employee() { count_all--; }
    static int get_count_all() { return count_all; }
    static void clear_staff() { count_all = 0; }

    virtual QString get_type()  = 0;
    virtual QString get_differents()  = 0;
};


class Director : public Employee
{
    QString subordinates_number;

    static int count_directors;

public:
    Director():
        Employee()
    {}

    Director(QString &id1, QString &full_name1, QString &age1, QString &salary1, QString &subordinates_number1):
        Employee(id1, full_name1, age1, salary1), subordinates_number(subordinates_number1) {}

    QString get_type();
    QString get_subordinates_number();
    QString get_differents();

    static int get_count() { return count_directors; }
};


class Teacher : public Employee
{
    QString subject;

    static int count_teachers;

public:
    Teacher():
        Employee(){}
    Teacher(QString &id1, QString &full_name1, QString &age1, QString &salary1, QString &subject1):
        Employee(id1, full_name1, age1, salary1), subject(subject1) {}

    QString get_type();
    QString get_subject();
    QString get_differents();

    static int get_count() { return count_teachers; }
};


class Security : public Employee
{
    QString gun_license;

    static int count_securities;

public:
    Security():
        Employee()
    {
        count_securities++;
    }

    Security(QString &id1, QString &full_name1, QString &age1, QString &salary1, QString &gun_license1):
        Employee(id1, full_name1, age1, salary1), gun_license(gun_license1) {}

    QString get_type();
    QString get_gun_license();
    QString get_differents();

    static int get_count() { return count_securities; }
};

#endif // EMPLOYEE_H
