#include "branch.h"

Branch::Branch(QString &name1, QString &index1, QString &region1, QString &city1, QString &street1, QString &house1, QString &number1)
{
    name = name1;
    index = index1;
    region = region1;
    city = city1;
    street = street1;
    house = house1;
    number = number1;
    list = new List_employees();
}

void Branch::set_next(Branch *Obj) { next = Obj; }

Branch* Branch::get_next() { return next; }
QString Branch::get_name() { return name; }
QString Branch::get_index() { return index; }
QString Branch::get_region() { return region; }
QString Branch::get_city() { return city; }
QString Branch::get_street() { return street; }
QString Branch::get_house() { return house; }
QString Branch::get_number() { return number; }
List_employees* Branch::get_list() { return list; }

void Branch::set_list(List_employees* new_list) {
    list = new_list;
}
