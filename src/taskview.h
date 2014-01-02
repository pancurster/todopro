#ifndef __TASKVIEW_H__
#define __TASKVIEW_H__

#include "task.h"

class TaskView {
public:
    virtual void show(TaskMap&) = 0;
};

class CliView : public TaskView {
public:
    void show(TaskMap& tmap);
    void showTask(std::shared_ptr<Task>& t);
    void showTask(Task* t);

private:
    void show_task_common(Task* t);

    static const char* KBOLD;
    static const char* KNORM;
    static const char* KREV;
};

#endif //__TASKVIEW_H__
