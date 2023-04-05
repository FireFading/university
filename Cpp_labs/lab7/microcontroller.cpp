#include "microcontroller.h"

microcontroller::microcontroller(QString m_name, QString m_firma, QString m_year_production, int m_artikul):
    name(m_name), firma(m_firma), year_production(m_year_production), artikul(m_artikul) {}

QString microcontroller::get_name() { return name; }
QString microcontroller::get_firma() { return firma; }
QString microcontroller::get_year_production() { return year_production; }
int microcontroller::get_artikul() { return artikul; }

