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
    for(auto it=tvec.begin(); it!=tvec.end(); ++it, color^=1) {

        if (color) std::cout << Style::K_BLACK_ON_WHITE;
        else       std::cout << Style::K_WHITE_ON_BLACK;

        std::cout << show_task_common(it->get());

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
    std::cout << show_task_common(t.get()) << "\n";
}

void CliView::showTask(Task* t) const
{
    std::cout << show_task_common(t) << "\n";
}

std::string CliView::show_task_common(Task* t) const
{
    using namespace std;

    stringstream str;
    str << setw(FIELD_WIDTH_ID) << left << t->payload->id
        << setw(FIELD_WIDTH_PRI) << left << t->payload->pri 
        << setw(FIELD_WIDTH_STATE) << left << Labels::STATE_VAL[t->payload->state]
        << setw(FIELD_WIDTH_DESC) << left << t->payload->desc ;

    return str.str();
}

