#include "employee.h"

QString Employee::get_id() { return id; }
QString Employee::get_full_name() { return full_name; }
QString Employee::get_age() { return age; }
QString Employee::get_salary() { return salary; }
Employee* Employee::get_next() { return next; }
void Employee::set_next(Employee *Obj) { next = Obj; }

QString Director::get_type() { return "Director"; }
QString Director::get_subordinates_number() { return subordinates_number; }
QString Director::get_differents()
{
    QString data = get_subordinates_number();
    return data;
}

QString Teacher::get_type() { return "Teacher"; }
QString Teacher::get_subject() { return subject; }
QString Teacher::get_differents()
{
    QString data = get_subject();
    return data;
}

QString Security::get_type() { return "Security"; }
QString Security::get_gun_license() { return gun_license; }
QString Security::get_differents()
{
    QString data = get_gun_license();
    return data;
}
