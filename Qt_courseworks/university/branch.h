#ifndef BRANCH_H
#define BRANCH_H
#include <QString>
#include <list_employees.h>

class Branch // филиал
{
private:
    QString name;
    QString index;
    QString region;
    QString city;
    QString street;
    QString house;
    QString number;
    List_employees* list;
    Branch *next;

public:
    Branch();

    Branch(QString &name1, QString &index1, QString &region1, QString &city1, QString &street1, QString &house1, QString &number1);

    // получение данных из приватных полей
    List_employees* get_list();
    Branch *get_next();
    QString get_name();
    QString get_index();
    QString get_region();
    QString get_city();
    QString get_street();
    QString get_house();
    QString get_number();

    void set_list(List_employees* new_list); // установка нового списка сотрудников
    void set_next(Branch *Obj); // установка следующего филиала в списке
};
#endif // BRANCH_H
