#ifndef BARBER_H
#define BARBER_H

#include "employee.h"


class barber : public employee
{
private:
    QString hairstyle;
    QString qualification;

public:
    barber(QString salary1 = "300", QString name1 = "Pavel", QString age1 = "19", QString experience1 = "2", QString hairstyle1 = "coloring", QString qualification1 = "senior");
    ~barber() = default;

    QString get_hairstyle();
    QString get_qualification();

    void set_hairstyle(QString hairstyle1);
    void set_qualification(QString qualification1);

    QString get_professional_characteristics();
    void set_professional_characteristics(QString a, QString b, QString c = "");

    QString get_one();
    QString get_two();
    QString get_three() {return "abc";}
};

#endif // BARBER_H
