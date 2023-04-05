#ifndef SALON_H
#define SALON_H

#include "personal.h"


class salon
{
private:
    salon* next;
    QString address;
    QString name;
    QString number_stars;
    QString describe_services;

    personal* staf;
public:
    salon(salon* next1 = nullptr, QString address1 = "Orel", QString name1 = "default", QString number_stars1 = "brilliant", QString describe_services1 = "haircut", personal* staf1 = nullptr);
    ~salon() {}

    salon* get_next();
    QString get_address();
    QString get_name();
    QString get_number_stars();
    QString get_describe_services();
    personal* get_staf();

    void set_next(salon* next1);
    void set_address(QString address1);
    void set_name(QString name1);
    void set_number_stars(QString number_stars1);
    void set_describe_services(QString describe_services1);
    void set_personal(personal* staf1);
    void set_data(QString address1, QString name1, QString number_stars1, QString describe_services1);
};

#endif // SALON_H
