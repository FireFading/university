#include "beautician.h"


beautician::beautician(QString salary1, QString name1, QString age1, QString experience1, QString medicine_education1, QString sertification1, QString number_operations1):
    employee(nullptr, "beautician", salary1, name1, age1, experience1), medicine_education(medicine_education1), sertification(sertification1), number_operations(number_operations1) {}

QString beautician::get_medicine_education()
{
    return medicine_education;
}

QString beautician::get_setification()
{
    return sertification;
}

QString beautician::get_number_operarions()
{
    return number_operations;
}

QString beautician::get_professional_characteristics()
{
    QString describe = medicine_education + ", " + sertification + ", " + number_operations;
    return describe;
}

void beautician::set_professional_characteristics(QString a, QString b, QString c)
{
    medicine_education = a;
    sertification = b;
    number_operations = c;
}

QString beautician::get_one()
{
    return medicine_education;
}

QString beautician::get_two()
{
    return sertification;
}

QString beautician::get_three()
{
    return number_operations;
}
