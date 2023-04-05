#ifndef BEAUTICIAN_H
#define BEAUTICIAN_H

#include "employee.h"


class beautician : public employee
{
private:
    QString medicine_education;
    QString sertification;
    QString number_operations;

public:
    beautician(QString salary1 = "300", QString name1 = "Pavel", QString age1 = "19", QString experience1 = "2", QString medicine_education1 = "doctor with high education", QString sertification1 = "Sertificate of USA", QString number_operations1 = "10");
    ~beautician() = default;

    QString get_medicine_education();
    QString get_setification();
    QString get_number_operarions();

    QString get_professional_characteristics();
    void set_professional_characteristics(QString a, QString b, QString c);

    QString get_one();
    QString get_two();
    QString get_three();
};

#endif // BEAUTICIAN_H
