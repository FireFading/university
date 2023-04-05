#include "list_salons.h"

salon* list_salons::get_head()
{
    return head;
}

QString list_salons::get_name()
{
    return name;
}

int list_salons::get_number_salons() {
    return count_salons;
}

salon* list_salons::follow_node(salon* node)
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

salon* list_salons::prev_node(salon* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node == head)
    {
        return nullptr;
    }
    salon *p = head;
    while (p->get_next() != node)
    {
        p = p->get_next();
    }
    return p;
}

salon* list_salons::find_node(QString name)
{
    salon* current = head;
    while (current != nullptr && current->get_name() != name) {
        current = current->get_next();
    }
    return current;
}

void list_salons::add_node(salon* node)
{
    if (head == nullptr)
    {
        head = node;
    }
    else
    {
        node->set_next(head);
        head = node;
    }
    count_salons++;
}

void list_salons::del_node(QString name)
{
    salon* current = head;
    while (current != nullptr) {
        if (current->get_name() == name) {
            count_salons--;
            if (current == head) {
                head = current->get_next();
                delete current;
                break;
            }
            else {
                salon* prev = prev_node(current);
                prev->set_next(current->get_next());
                delete current;
                break;
            }
        }
        current = current->get_next();
    }
}
