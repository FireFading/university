#include "farm.h"

Farm::Farm(QString m_artikul, QString m_name, QString m_illness, QString m_category):
    artikul(m_artikul), name(m_name), illness(m_illness), category(m_category) { count_all++; }
QString Farm::get_artikul() { return artikul; }
QString Farm::get_name() { return name; }
QString Farm::get_illness() { return illness; }
QString Farm::get_category() { return category; }

Vitamins::Vitamins(QString m_artikul, QString m_name, QString m_illness, QString m_age, QString m_sezon):
    Farm(m_artikul, m_name, m_illness, "Vit"), age(m_age), sezon(m_sezon) { count_vitamins++; }
QString Vitamins::get_first() { return age; }
QString Vitamins::get_second() { return sezon; }

Antibiotic::Antibiotic(QString m_artikul, QString m_name, QString m_illness, QString m_recept, QString m_days):
    Farm(m_artikul, m_name, m_illness, "Bio"), recept(m_recept), days(m_days) { count_antibiotics++; }
QString Antibiotic::get_first() { return recept; }
QString Antibiotic::get_second() { return days; }
