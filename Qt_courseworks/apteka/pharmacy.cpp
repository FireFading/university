#include "pharmacy.h"

pharmacy::pharmacy(QString m_name, QString m_adress, QString m_phone, medicine_list* m_medicines, int m_artikul):
    name(m_name), adress(m_adress), phone(m_phone), medicines(m_medicines), artikul(m_artikul)
{
    medicines = new medicine_list(); // создание списка лекарств аптеки
    number_pharmacy++;
}

// получение данных приватных полей
int pharmacy::get_artikul() { return artikul; }
QString pharmacy::get_name() { return name; }
QString pharmacy::get_adress() { return adress; }
QString pharmacy::get_phone() { return phone; }
pharmacy* pharmacy::get_next() { return next; }
medicine_list* pharmacy::get_medicines() { return medicines; }

void pharmacy::set_data_pharmacy(QString m_name, QString m_adress, QString m_phone) { // установка новых данных в поля
    name = m_name;
    adress = m_adress;
    phone = m_phone;
}

void pharmacy::set_name(QString m_name) { name = m_name; }
void pharmacy::set_adress(QString m_adress) { adress = m_adress; }
void pharmacy::set_phone(QString m_phone) { phone = m_phone; }
void pharmacy::set_next(pharmacy* m_next) { next = m_next; }
void pharmacy::set_artikul(int id) { artikul = id; }


list_pharmacy::list_pharmacy() {
    head = nullptr;
    count_all = 0;
}

pharmacy* list_pharmacy::get_head() { return head; }

pharmacy* list_pharmacy::Follow(pharmacy* node) { // получение следующего узла
    if (node == nullptr) { return nullptr; }
    return node->next;
}

pharmacy* list_pharmacy::Prev(pharmacy* node) { // получение предыдущего узла
    if (node == nullptr) { return nullptr; }
    if (node == head) { return nullptr; }
    pharmacy *p = head;
    while (p->next != node) {
        p = p->next;
    }
    return p;
}

pharmacy* list_pharmacy::find_node(int id_shop) { // нахождение узла по идентификатору
    pharmacy* current = head;
    while (current != nullptr && current->get_artikul() != id_shop) {
        current = current->next;
    }
    return current;
}

void list_pharmacy::add_node(pharmacy* new_shop) { // добавление узла
    if (head == nullptr) {
        head = new_shop;
    }
    else {
        new_shop->next = head;
        head = new_shop;
    }
    count_all++;
}

void list_pharmacy::delete_node(int id_shop) { // удаление узла
    pharmacy* current = head;
    while (current != nullptr) {
        if (current->get_artikul() == id_shop) {
            count_all--;
            if (current == head) {
                head = current->next;
                current->medicines->clear_list();
                delete current;
                break;
            }
            else {
                pharmacy* prev = Prev(current);
                prev->next = (current->next);
                current->medicines->clear_list();
                delete current;
                break;
            }
        }
        current = current->get_next();
    }
}

void list_pharmacy::clear_list() { // очистка списка
    head = nullptr;
    count_all = 0;
}
