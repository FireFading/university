#include "list_employees.h"

void List_employees::add(Employee *E)
{
    if (Head != nullptr)
    {
        E->set_next(Head);
        Head = E;
    }
    else
    {
        Head = E;
    }
    count++;
    E->add_employee();
}

List_employees::List_employees()
{
    Head = nullptr;
    count = 0;
}

void List_employees::add_director(QString &id1, QString &full_name1, QString &age1, QString &salary1, QString &subordinates_number1)
{
    Employee *E = new Director(id1, full_name1, age1, salary1, subordinates_number1);
    add(E);
}
void List_employees::add_teacher(QString &id1, QString &full_name1, QString &age1, QString &salary1, QString &subject1)
{
    Employee *E = new Teacher(id1, full_name1, age1, salary1, subject1);
    add(E);
}
void List_employees::add_security(QString &id1, QString &full_name1, QString &age1, QString &salary1, QString &gun_license1)
{
    Employee *E = new Security(id1, full_name1, age1, salary1, gun_license1);
    add(E);
}
void List_employees::del(int id)
{
    Employee *E = Head;
    if (count != 1)
    {
        while ((E->get_id().toInt()) != id)
        {
            E = E->get_next();
        }
        if (E == Head)
            Head = E->get_next();
        else {
            Employee* prev = Prev(E);
            prev->set_next(E->get_next());
        }
    }
    else {
        Head = nullptr;
    }
    E->del_employee();
    delete E;
    count--;
}

Employee* List_employees::Follow(Employee* node)
{
    if (node == nullptr) { return nullptr; }
    return node->get_next();
}
Employee* List_employees::Prev(Employee* node)
{
    if (node == nullptr) { return nullptr; }
    if (node == Head) { return nullptr; }
    Employee *p = Head;
    while (p->get_next() != node) {
        p = p->get_next();
    }
    return p;
}
Employee* List_employees::Last_node()
{
    Employee* p = Head;
    while (Follow(p) != nullptr) { p = Follow(p); }
    return p;
}

Employee* List_employees::get_head() { return Head; }
void List_employees::set_head(Employee *Obj) { Head = Obj; }
int List_employees::get_count() { return count; }
void List_employees::set_count(int count1) { count = count1; }
