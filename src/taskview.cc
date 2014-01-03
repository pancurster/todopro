#include "taskview.h"
#include "task.h"

#include <iostream>
#include <iomanip>

const char* CliView::K_BOLD="\x1B[1m";
const char* CliView::K_NO_STYLE="\x1B[0m";
const char* CliView::K_BLACK_ON_WHITE="\x1B[37;40m";
const char* CliView::K_WHITE_ON_BLACK="\x1B[30;44m";

void CliView::show(TaskMap& tmap) const
{
    this->print_header();
    int color=0;
    for(TaskMap::iterator it=tmap.begin(); it!=tmap.end(); ++it, color^=1) {

        if (color) std::cout << CliView::K_BLACK_ON_WHITE;
        else       std::cout << CliView::K_WHITE_ON_BLACK;

        showTask(it->second);

        std::cout << CliView::K_NO_STYLE << "\n";
    }
    std::cout << "\n";
}

void CliView::print_header() const
{
    std::cout << CliView::K_BOLD;
    std::cout << std::setw(STYLE_FIELD_WIDTH_ID)    << std::left << "Id";
    std::cout << std::setw(STYLE_FIELD_WIDTH_PRI)   << std::left << "Pri";
    std::cout << std::setw(STYLE_FIELD_WIDTH_DESC)  << std::left << "Desc" << CliView::K_NO_STYLE << "\n";
}

void CliView::showTask(std::shared_ptr<Task>& t) const
{
    show_task_common(t.get());
}

void CliView::showTask(Task* t) const
{
    show_task_common(t);
}

void CliView::show_task_common(Task* t) const
{
#if 1
    ssize_t len=0;
    std::string str = "";

    str = std::to_string(t->payload->id);
    len += str.size();
    std::cout<< std::setw(5)<< std::left << str;

    str = std::to_string(t->payload->pri);
    len += str.size();
    std::cout<< std::setw(5)<< str;

    str = t->payload->desc;
    len += str.size();
    std::cout << std::setfill(' ') << std::setw(72) << str;

#endif
#if 0
    std::string str = "";
    str += std::to_string(t->payload->id) += "   ";
    str += std::to_string(t->payload->pri) += "   ";
    str += t->payload->desc;
    std::cout << str;
    return str.size();
#endif
#if 0
    std::cout
        << t->payload->id << "   "
        << t->payload->pri << "   "
        << t->payload->desc;
#endif
#if 0
    static int i=0;
    if (i)
        printf("\x1B[37;40m" "%d   %d   %s\x1B[0m\n",t->payload->id, t->payload->pri, t->payload->desc.c_str());
    else
        printf("\x1B[30;47m" "%d   %d   %s\x1B[0m\n",t->payload->id, t->payload->pri, t->payload->desc.c_str());

    i ^= 1;
#endif
}

