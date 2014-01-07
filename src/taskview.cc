#include "taskview.h"
#include "taskmanager.h" //TaskMap
#include "task.h"

#include <iostream>
#include <iomanip>

namespace Style {

const char* K_BOLD="\x1B[1m";
const char* K_NO_STYLE="\x1B[0m";
const char* K_BLACK_ON_WHITE="\x1B[37;40m";
const char* K_WHITE_ON_BLACK="\x1B[37;44m";

}

namespace Labels {

const char* ID      = "Id";
const char* PRI     = "Pri";
const char* STATE   = "State";
const char* DESC    = "Desc";

const char* STATE_VAL[] ={
    "",
    "P",
    "S",
    "D"
};
}

void CliView::showTask(TaskVec& tvec) const
{
    // Print ID Pri and rest label names
    this->print_header();

    int color=0;
    for(TaskVec::iterator it=tvec.begin(); it!=tvec.end(); ++it, color^=1) {

        if (color) std::cout << Style::K_BLACK_ON_WHITE;
        else       std::cout << Style::K_WHITE_ON_BLACK;

        show_task_common(it->get());

        std::cout << Style::K_NO_STYLE << "\n";
    }
    std::cout << "\n";
}

void CliView::print_header() const
{
    std::cout << Style::K_BOLD;
    std::cout << std::setw(FIELD_WIDTH_ID)    << std::left << Labels::ID;
    std::cout << std::setw(FIELD_WIDTH_PRI)   << std::left << Labels::PRI;
    std::cout << std::setw(FIELD_WIDTH_STATE) << std::left << Labels::STATE;
    std::cout << std::setw(FIELD_WIDTH_DESC)  << std::left << Labels::DESC
              << Style::K_NO_STYLE
              << "\n";
}

void CliView::showTask(std::shared_ptr<Task>& t) const
{
    show_task_common(t.get());
    std::cout << "\n";
}

void CliView::showTask(Task* t) const
{
    show_task_common(t);
    std::cout << "\n";
}

// TODO Rozwazyc czy nie lepej bylo by zeby ta funkcja zwracala stringa
void CliView::show_task_common(Task* t) const
{
#if 1
    ssize_t len=0;
    std::string str = "";

    str = std::to_string(t->payload->id);
    len += str.size();
    std::cout<< std::setw(FIELD_WIDTH_ID)<< std::left << str;

    str = std::to_string(t->payload->pri);
    len += str.size();
    std::cout<< std::setw(FIELD_WIDTH_PRI)<< str;

    str = Labels::STATE_VAL[t->payload->state];
    len += str.size();
    std::cout<< std::setw(FIELD_WIDTH_STATE)<< str;

    str = t->payload->desc;
    len += str.size();
    std::cout << std::setfill(' ') << std::setw(FIELD_WIDTH_DESC) << str;

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
    static int i=0;
    if (i)
        printf("\x1B[37;40m" "%d   %d   %s\x1B[0m\n",t->payload->id, t->payload->pri, t->payload->desc.c_str());
    else
        printf("\x1B[30;47m" "%d   %d   %s\x1B[0m\n",t->payload->id, t->payload->pri, t->payload->desc.c_str());

    i ^= 1;
#endif
}

