#include "taskview.h"
#include "task.h"

#include <iostream>

const char* CliView::KBOLD="\x1B[1m";
const char* CliView::KNORM="\x1B[0m";
const char* CliView::KREV ="\x1B[30;47m";

void CliView::show(TaskMap& tmap)
{
    std::cout << CliView::KBOLD << "Id  Pri  Desc\n" << CliView::KNORM;

    int color=0;
    for(TaskMap::iterator it=tmap.begin(); it!=tmap.end(); ++it, color^=1) {

        if (color) std::cout << CliView::KREV;
        showTask(it->second);
        if (color) std::cout << CliView::KNORM;
    }
    std::cout << "\n";
}

void CliView::showTask(std::shared_ptr<Task>& t)
{
    show_task_common(t.get());
}

void CliView::showTask(Task* t)
{
    show_task_common(t);
}

void CliView::show_task_common(Task* t)
{
    std::cout
        << t->payload->id << "   "
        << t->payload->pri << "   "
        << t->payload->desc << "\n";
}

