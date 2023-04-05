#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>

class employee
{
private:
    employee* next;
    QString profession;
    QString salary;
    QString name;
    QString age;
    QString experience;

public:
    employee(employee* next1 = nullptr, QString profession1 = "barber", QString salary1 = "300", QString name1 = "Pavel", QString age1 = "19", QString experience1 = "2");
    virtual ~employee() = default;

    employee* get_next();
    QString get_profession();
    QString get_salary();
    QString get_name();
    QString get_age();
    QString get_experience();

    void set_next(employee* next1);
    void set_profession(QString profession1);
    void set_salary(QString salary1);
    void set_name(QString name1);
    void set_age(QString age1);
    void set_experience(QString experience1);

    virtual QString get_professional_characteristics() = 0;
    virtual void set_professional_characteristics(QString a = "", QString b = "", QString c = "") = 0;
    virtual QString get_one() = 0;
    virtual QString get_two() = 0;
    virtual QString get_three() = 0;
};

#endif // EMPLOYEE_H
