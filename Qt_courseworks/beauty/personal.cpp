#include "personal.h"


employee* personal::get_head()
{
    return head;
}

int personal::get_number_people()
{
    return number_people;
}

employee* personal::follow_node(employee* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else
    {
        return node->get_next();
    }
}
employee* personal::prev_node(employee* node)
{
    if (node == nullptr) { return nullptr; }
    if (node == head) { return nullptr; }
    employee *p = head;
    while (p->get_next() != node) {
        p = p->get_next();
    }
    return p;
}

employee* personal::find_node(QString name)
{
    employee* current = head;
    while (current != nullptr && current->get_name() != name) {
        current = current->get_next();
    }
    return current;
}

void personal::add_employee(employee* person)
{
    if (head == nullptr) {
        head = person;
    }
    else {
        person->set_next(head);
        head = person;
    }
    number_people++;
}

void personal::del_employee(QString name)
{
    employee* current = head;
    while (current != nullptr) {
        if (current->get_name() == name) {
            number_people--;
            if (current == head) {
                head = current->get_next();
                delete current;
                break;
            }
            else {
                employee* prev = prev_node(current);
                prev->set_next(current->get_next());
                delete current;
                break;
            }
        }
        current = current->get_next();
    }
}
