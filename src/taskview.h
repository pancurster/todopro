#ifndef TASKVIEW_H
#define TASKVIEW_H

#include "task.h"
#include "taskmanager.h"
#include <string>
#include <ostream>

class TaskView {
public:
    virtual ~TaskView() {}
    virtual void showTask(TaskVec&, std::ostream&) const = 0;
    virtual void showTask(std::shared_ptr<Task>& t, std::ostream&) const = 0;
    virtual void showTask(Task* t, std::ostream&) const = 0;
};

class CliView : public TaskView {
public:
    CliView();
    ~CliView();
    void showTask(TaskVec& tvec, std::ostream&) const;
    void showTask(std::shared_ptr<Task>& t, std::ostream&) const;
    void showTask(Task* t, std::ostream&) const;

    void setColorizedOutput(bool);

protected:
    std::string show_task_common(Task* t) const;
    void print_header(std::ostream&) const ;

    bool m_colorized_output;

};

#endif //__TASKVIEW_H__

