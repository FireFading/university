#include "salon.h"

salon::salon(salon* next1, QString address1, QString name1, QString number_stars1, QString describe_services1, personal* staf1):
    next(next1), address(address1), name(name1), number_stars(number_stars1), describe_services(describe_services1), staf(staf1)
{
    staf = new personal();
}

salon* salon::get_next()
{
    return next;
}

QString salon::get_address()
{
    return address;
}

QString salon::get_name()
{
    return name;
}

QString salon::get_number_stars()
{
    return number_stars;
}

QString salon::get_describe_services()
{
    return describe_services;
}

personal* salon::get_staf()
{
    return staf;
}

void salon::set_next(salon* next1)
{
    next = next1;
}

void salon::set_address(QString address1)
{
    address = address1;
}

void salon::set_name(QString name1)
{
    name = name1;
}

void salon::set_number_stars(QString number_stars1)
{
    number_stars = number_stars1;
}

void salon::set_describe_services(QString describe_services1)
{
    describe_services = describe_services1;
}

void salon::set_personal(personal* staf1)
{
    staf = staf1;
}

void salon::set_data(QString address1, QString name1, QString number_stars1, QString describe_services1)
{
    address = address1;
    name = name1;
    number_stars = number_stars1;
    describe_services = describe_services1;
}
