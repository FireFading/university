#ifndef MICROCONTROLLER_H
#define MICROCONTROLLER_H

#include <QString>

class microcontroller
{
private:

    QString name;
    QString firma;
    QString year_production;

    int artikul;
public:
    microcontroller(QString m_name = "Microcontroller", QString m_firma = "Intel", QString m_year_production = "2022", int m_artikul = 0);

    QString get_name();
    QString get_firma();
    QString get_year_production();
    microcontroller* get_next();

    int get_artikul();

    void set_next(microcontroller* node);

    friend class list_microcontrollers;
};


#endif // MICROCONTROLLER_H
