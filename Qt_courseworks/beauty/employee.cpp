#include "employee.h"


employee::employee(employee* next1, QString profession1, QString salary1, QString name1, QString age1, QString experience1):
    next(next1), profession(profession1), salary(salary1), name(name1), age(age1), experience(experience1) {}

employee* employee::get_next()
{
    return next;
}

QString employee::get_profession()
{
    return profession;
}

QString employee::get_salary()
{
    return salary;
}

QString employee::get_name()
{
    return name;
}

QString employee::get_age()
{
    return age;
}

QString employee::get_experience()
{
    return experience;
}

void employee::set_next(employee* next1)
{
    next = next1;
}

void employee::set_profession(QString profession1)
{
    profession = profession1;
}

void employee::set_salary(QString salary1)
{
    salary = salary1;
}

void employee::set_name(QString name1)
{
    name = name1;
}

void employee::set_age(QString age1)
{
    age = age1;
}

void employee::set_experience(QString experience1)
{
    experience = experience1;
}
