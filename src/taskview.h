#ifndef TASKVIEW_H
#define TASKVIEW_H

#include "task.h"
#include "taskmanager.h"
//class TaskMap; //TODO

class TaskView {
public:
    virtual void showTask(TaskVec&) const = 0;
};

class CliView : public TaskView {
public:
    void showTask(TaskVec& tvec) const;
    void showTask(std::shared_ptr<Task>& t) const;
    void showTask(Task* t) const;

private:
    void show_task_common(Task* t) const;
    void print_header() const ;

    enum {
        FIELD_WIDTH_ID    = 5,
        FIELD_WIDTH_PRI   = 5,
        FIELD_WIDTH_STATE = 7,
        FIELD_WIDTH_DESC  = 70
    };
};

#endif //__TASKVIEW_H__

