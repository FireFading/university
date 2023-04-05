#include "list_branches.h"

void List_branches::add(Branch *B)
{
    if (Head == nullptr) {
        B->set_next(B);
        Head = B;
    }
    else {
        B->set_next(Head);
        last_node()->set_next(B);
        Head = B;
    }
    count_branches++;
    count++;
}

List_branches::List_branches()
{
    Head = nullptr;
    count = 0;

}

void List_branches::add_branch(QString &name1, QString &index1, QString &region1, QString &city1, QString &street1, QString &house1, QString &number1)
{
    Branch *B = new Branch(name1, index1, region1, city1, street1, house1, number1);
    add(B);
}

void List_branches::del(QString name)
{
    Branch* B = Head;
    if (count != 1)
    {
        while (B->get_name() != name)
        {
            B = follow(B);
        }
        Branch* replace = prev(B);
        if (B == Head)
        {
            Head = B->get_next();
            last_node()->set_next(Head);
        }
        replace->set_next(B->get_next());
    }
    else
        Head = nullptr;
    delete B;
    count_branches--;
    count--;
}

Branch* List_branches::follow(Branch* node)
{
    return node->get_next();
}

Branch* List_branches::prev(Branch* node)
{
    Branch* p = Head;
    while (follow(p) != node) {
        p = follow(p);
    }
    return p;
}

Branch* List_branches::last_node()
{
    Branch* p = Head;
    while(follow(p) != Head) {
        p = follow(p);
    }
    return p;
}

void List_branches::new_university()
{
    count = 0;
    count_branches = 0;
    Head->get_list()->get_head()->clear_staff();
    Head = nullptr;
}

Branch* List_branches::get_head() { return Head; }
void List_branches::set_head(Branch *Obj) { Head = Obj; }
int List_branches::get_count() { return count; }
void List_branches::set_count(int count1) { count = count1; }
