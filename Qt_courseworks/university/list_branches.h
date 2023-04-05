#ifndef LIST_BRANCHES_H
#define LIST_BRANCHES_H
#include <QString>
#include <branch.h>

class List_branches // список филиалов
{
private:
    Branch *Head;
    int count;
    void add(Branch *B);

    static int count_branches;

public:
    List_branches();

    void add_branch(QString &name1, QString &index1, QString &region1, QString &city1, QString &street1, QString &house1, QString &number1);
    void del(QString name);

    Branch *get_head();
    int get_count();

    void set_head(Branch *Obj);
    void set_count(int count1);

    Branch* follow(Branch* node);
    Branch* prev(Branch* node);
    Branch* last_node();

    static int get_count_branches() { return count_branches; }

    void new_university();
};

#endif // LIST_BRANCHES_H
