#include "microcontroller.h"

microcontroller::microcontroller(QString m_name, QString m_firma, QString m_year_production, int m_artikul):
    name(m_name), firma(m_firma), year_production(m_year_production), artikul(m_artikul) {}

QString microcontroller::get_name() { return name; }
QString microcontroller::get_firma() { return firma; }
QString microcontroller::get_year_production() { return year_production; }
int microcontroller::get_artikul() { return artikul; }
microcontroller* microcontroller::get_next() { return next; }

void microcontroller::set_next(microcontroller* node) {
    next = node;
}


list_microcontrollers::list_microcontrollers() { head = nullptr; }

microcontroller* list_microcontrollers::get_head() {
    return head;
}

microcontroller* list_microcontrollers::last_node() {
    microcontroller* p = head;
    while(follow(p) != head) {
        p = follow(p);
    }
    return p;
}

microcontroller* list_microcontrollers::follow(microcontroller* node) {
    return node->next;
}

microcontroller* list_microcontrollers::prev(microcontroller* node) {
    microcontroller* p = head;
    while (follow(p) != node) {
        p = follow(p);
    }
    return p;
}

microcontroller* list_microcontrollers::find_node(int id_microcontroller) {
    microcontroller* cur = head;
    while(cur->get_artikul() != id_microcontroller) {
        cur = follow(cur);
    }
    return cur;
}

void list_microcontrollers::add_node(microcontroller* new_node) {
    if (head == nullptr) {
        head = new_node;
        new_node->next = new_node;
    }
    else {
        new_node->next = head->next;
        head->next = new_node;
    }
    count_microcontrollers++;
}

void list_microcontrollers::delete_node(int &id_product) {
    microcontroller* node = find_node(id_product);
    microcontroller* current = prev(node);
    if (node == head) {
        head = node->next;
        last_node()->next = head;
    }
    current->next = node->next;
    count_microcontrollers--;
}
