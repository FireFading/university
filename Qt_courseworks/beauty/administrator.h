#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "employee.h"


class administrator : public employee
{
private:
    QString number;
    QString education;

public:
    administrator(QString salary1 = "300", QString name1 = "Pavel", QString age1 = "19", QString experience1 = "2", QString number1 = "12345678910", QString education1 = "high");
    ~administrator() = default;

    QString get_number();
    QString get_education();

    void set_number(QString number1);
    void set_education(QString education1);

    QString get_professional_characteristics();
    void set_professional_characteristics(QString a, QString b, QString c = "");

    QString get_one();
    QString get_two();
    QString get_three() { return "abc";}
};

#endif // ADMINISTRATOR_H
