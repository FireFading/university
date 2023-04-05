#include "administrator.h"


administrator::administrator(QString salary1, QString name1, QString age1, QString experience1, QString number1, QString education1):
    employee(nullptr, "administartor", salary1, name1, age1, experience1), number(number1), education(education1) {}

QString administrator::get_number()
{
    return number;
}

QString administrator::get_education()
{
    return education;
}

void administrator::set_number(QString number1)
{
    number = number1;
}

void administrator::set_education(QString education1)
{
    education = education1;
}

QString administrator::get_professional_characteristics()
{
    QString describe = number + ", " + education;
    return describe;
}

void administrator::set_professional_characteristics(QString a, QString b, QString c)
{
    number = a;
    education = b;
}

QString administrator::get_one()
{
    return number;
}

QString administrator::get_two()
{
    return education;
}

