#include "taskview.h"
#include "taskmanager.h" //TaskMap
#include "task.h"
#include "style.h"

#include <iostream>
#include <iomanip>
#include <ostream>

CliView::CliView()
    : m_colorized_output(true)
{
}

CliView::~CliView()
{
}

void CliView::showTask(TaskVec& tvec, std::ostream& out) const
{
    // Print ID Pri and rest label names
    this->print_header(out);

    const char* second_color_style = Style::K_WHITE_ON_BLUE;
    if (m_colorized_output == false)
        second_color_style = Style::K_BLACK_ON_WHITE;

    int color=0;
    for(auto it=tvec.begin(); it!=tvec.end(); ++it, color^=1) {

        if (color) out << Style::K_BLACK_ON_WHITE;
        else       out << second_color_style;

        out << show_task_common(it->get());

        out << Style::K_NO_STYLE << "\n";
    }
    out << "\n";
}

void CliView::print_header(std::ostream& out) const
{
    out << Style::K_BOLD;
    out << std::setw(Style::FIELD_WIDTH_ID)    << std::left << Style::Labels::ID;
    out << std::setw(Style::FIELD_WIDTH_PRI)   << std::left << Style::Labels::PRI;
    out << std::setw(Style::FIELD_WIDTH_STATE) << std::left << Style::Labels::STATE;
    out << std::setw(Style::FIELD_WIDTH_DESC)  << std::left << Style::Labels::DESC
        << Style::K_NO_STYLE
        << "\n";
}

void CliView::showTask(std::shared_ptr<Task>& t, std::ostream& out) const
{
    out << show_task_common(t.get()) << "\n";
}

void CliView::showTask(Task* t, std::ostream& out) const
{
    out << show_task_common(t) << "\n";
}

void CliView::setColorizedOutput(bool colorize)
{
    m_colorized_output = colorize;
}

std::string CliView::show_task_common(Task* t) const
{
    using namespace std;

    stringstream str;
    str << setw(Style::FIELD_WIDTH_ID) << left << t->payload->id
        << setw(Style::FIELD_WIDTH_PRI) << left << t->payload->pri 
        << setw(Style::FIELD_WIDTH_STATE) << left << Style::Labels::STATE_VAL[t->payload->state]
        << setw(Style::FIELD_WIDTH_DESC) << left << t->payload->desc ;

    return str.str();
}

