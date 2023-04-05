#ifndef FARM_H
#define FARM_H

#include <QString>

class Farm
{
private:
    QString artikul;
    QString name;
    QString illness;
    QString category;

    static int count_all;

public:
    Farm(QString m_artikul = "0", QString m_name = "farm", QString m_illness = "none", QString m_category = "Vit");

    virtual ~Farm() = default;

    QString get_artikul();
    QString get_name();
    QString get_illness();
    QString get_category();

    static int get_count_all() { return count_all; }

    virtual QString get_first() = 0;
    virtual QString get_second() = 0;
};


class Vitamins: public Farm {
private:
    QString age;
    QString sezon;

    static int count_vitamins;
public:
    Vitamins(QString m_artikul = "0", QString m_name = "farm", QString m_illness = "none", QString m_age = "18", QString m_sezon = "summer");

    ~Vitamins() = default;

    QString get_first();
    QString get_second();

    static int get_count_vitamins() { return count_vitamins; }
};


class Antibiotic: public Farm {
private:
    QString recept;
    QString days;

    static int count_antibiotics;
public:
    Antibiotic(QString m_artikul = "0", QString m_name = "farm", QString m_illness = "none", QString m_recept = "false", QString m_days = "week");

    ~Antibiotic() = default;

    QString get_first();
    QString get_second();

    static int get_count_antibiotics() { return count_antibiotics; }
};


#endif // FARM_H
