#include "medicine.h"

medicine::medicine(QString m_category, QString m_iid, QString m_price, QString m_firma, QString m_age, medicine* m_next, int m_current):
    next(m_next), category(m_category), iid(m_iid), price(m_price), firma(m_firma),  age(m_age), current(m_current)
{
    current = number_medicines; // уникальный идентификатор для последующего удобного поиска
    number_medicines++;
} // конструктор


// получение данных из приватных полей
QString medicine::get_category() { return category; }
QString medicine::get_iid() { return iid; }
QString medicine::get_price() { return price; }
QString medicine::get_firma() { return firma; }
QString medicine::get_age() { return age; }
medicine* medicine::get_next() { return next; }

int medicine::get_current() { return current; }

// установка новых данных в приватные поля
void medicine::set_category(QString m_category) { category = m_category; }
void medicine::set_iid(QString m_iid) { iid = m_iid; }
void medicine::set_price(QString m_price) { price = m_price; }
void medicine::set_firma(QString m_firma) { firma = m_firma; }
void medicine::set_age(QString m_age) { age = m_age; }
void medicine::set_next(medicine* m_next) { next = m_next; }

void medicine::set_data(QString m_iid, QString m_price, QString m_firma, QString m_age) {
    iid = m_iid;
    price = m_price;
    firma = m_firma;
    age = m_age;
}


vitamins::vitamins(QString m_iid, QString m_price, QString m_firma, QString m_age, QString m_season, QString m_type, QString m_time):
    medicine("Vitamins", m_iid, m_price, m_firma, m_age, nullptr, 0), season(m_season), type(m_type), time(m_time)
{ number_vitamins++; }

// получение данных из приватных полей
QString vitamins::get_optional() {
    QString optional = season + ", " + type + ", " + time;
    return optional;
}

QString vitamins::get_first() { return season; }
QString vitamins::get_second() { return type; }
QString vitamins::get_third() { return time; }

void vitamins::set_data_medicine(QString m_iid, QString m_price, QString m_firma, QString m_age, QString m_season, QString m_type, QString m_time) { // установка данных в приватные поля
    medicine::set_data(m_iid, m_price, m_firma, m_age);
    season = m_season;
    type = m_type;
    time = m_time;
}


antibiotic::antibiotic(QString m_iid, QString m_price, QString m_firma, QString m_age, QString m_period, QString m_danger, QString m_country):
    medicine("Antibiotic", m_iid, m_price, m_firma, m_age, nullptr, 0), period(m_period), danger(m_danger), country(m_country)
{ number_antibiotics++; }

// получение данных из приватных полей
QString antibiotic::get_optional() {
    QString optional = period + ", " + danger + ", " + country;
    return optional;
}

QString antibiotic::get_first() { return period; }
QString antibiotic::get_second() { return country; }
QString antibiotic::get_third() { return danger; }

void antibiotic::set_data_medicine(QString m_iid, QString m_price, QString m_firma, QString m_age, QString m_period, QString m_danger, QString m_country) { // установка данных в приватные поля
    medicine::set_data(m_iid, m_price, m_firma, m_age);
    period = m_period;
    danger = m_danger;
    country = m_country;
}


antipyretic::antipyretic(QString m_iid, QString m_price, QString m_firma, QString m_age, QString m_power, QString m_substance, QString m_concentration):
    medicine("Antipyretic", m_iid, m_price, m_firma, m_age, nullptr, 0), power(m_power), substance(m_substance), concentration(m_concentration)
{ number_antipyretic++; }

// получение данных из приватных полей
QString antipyretic::get_optional() {
    QString optional = power + ", " + substance + ", " + concentration;
    return optional;
}

QString antipyretic::get_first() { return power; }
QString antipyretic::get_second() { return substance; }
QString antipyretic::get_third() { return concentration; }


void antipyretic::set_data_medicine(QString m_iid, QString m_price, QString m_firma, QString m_age, QString m_power, QString m_substance, QString m_concentration) { // установка данных в приватные поля
     medicine::set_data(m_iid, m_price, m_firma, m_age);
     power = m_power;
     substance = m_substance;
     concentration = m_concentration;
}


medicine_list::medicine_list(medicine* m_head, int m_count, int m_count_vitamins, int m_count_antibiotics, int m_count_antipyretic):
    head(m_head), count(m_count), count_vitamins(m_count_vitamins), count_antibiotics(m_count_antibiotics), count_antipyretic(m_count_antipyretic)
{
    count = 0;
    count_antibiotics = 0;
    count_antipyretic = 0;
    count_vitamins = 0;
    head = nullptr;
}

void medicine_list::clear_list() { // очистка списка
    head = nullptr;
    count_vitamins = 0;
    count_antibiotics = 0;
    count_antipyretic = 0;
    count = 0;
}

// получение данных приватных полей
int medicine_list::get_count() { return count; }
int medicine_list::get_count_vitamins() { return count_vitamins; }
int medicine_list::get_count_antibiotics() { return count_antibiotics; }
int medicine_list::get_count_antipyretic() { return count_antipyretic; }
medicine* medicine_list::get_head() { return head; }

medicine* medicine_list::Follow(medicine* node) { // получение следующего узла
    if (node == nullptr) { return nullptr; }
    return node->next;
}
medicine* medicine_list::Prev(medicine* node) { // получение предыдущего узла
    if (node == nullptr) { return nullptr; }
    if (node == head) { return nullptr; }
    medicine *p = head;
    while (p->next != node) {
        p = p->next;
    }
    return p;
}
medicine* medicine_list::Last_node() { // получение последнего узла
    medicine* p = head;
    while (Follow(p) != nullptr) { p = Follow(p); }
    return p;
}

medicine* medicine_list::find_node(int id_product) { // нахождение узла по идентификатору
    medicine* current = head;
    while (current != nullptr && current->get_current() != id_product) {
        current = current->next;
    }
    return current;
}

void medicine_list::add_node(medicine* new_node) { // добавление узла
    if (head == nullptr) {
        head = new_node;
    }
    else {
        new_node->next = head;
        head = new_node;
    }
    count++;
    if (new_node->get_category() == "Vitamins") { count_vitamins++; }
    if (new_node->get_category() == "Antibiotic") { count_antibiotics++; }
    if (new_node->get_category() == "Antipyretic") { count_antipyretic++; }
}

void medicine_list::delete_node(int id_product) { // удаление узла
    medicine* current_product = head;
    while (current_product != nullptr) {
        if (current_product->get_current() == id_product) {
            if (current_product->get_category() == "Vitamins") { count_vitamins--; }
            else {
                if (current_product->get_category() == "Antibiotic") { count_antibiotics--; }
                else { count_antipyretic--; }
            }
            count--;
            if (current_product == head) {
                head = current_product->next;
                delete current_product;
                break;
            }
            else {
                medicine* prev = Prev(current_product);
                prev->next = (current_product->next);
                delete current_product;
                break;
            }
        }
        current_product = current_product->get_next();
    }
}
