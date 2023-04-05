#include "barber.h"

barber::barber(QString salary1, QString name1, QString age1, QString experience1, QString hairstyle1, QString qualification1):
    employee(nullptr, "barber", salary1, name1, age1, experience1), hairstyle(hairstyle1), qualification(qualification1) {}

QString barber::get_hairstyle()
{
    return hairstyle;
}

QString barber::get_qualification()
{
    return qualification;
}

void barber::set_hairstyle(QString hairstyle1)
{
    hairstyle = hairstyle1;
}

void barber::set_qualification(QString qualification1)
{
    qualification = qualification1;
}

QString barber::get_professional_characteristics()
{
    QString describe = hairstyle + ", " + qualification;
    return describe;
}

void barber::set_professional_characteristics(QString a, QString b, QString c)
{
    hairstyle = a;
    qualification = b;
}

QString barber:: get_one()
{
    return hairstyle;
}

QString barber::get_two()
{
    return qualification;
}
