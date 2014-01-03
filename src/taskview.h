#ifndef __TASKVIEW_H__
#define __TASKVIEW_H__

#include "task.h"

class TaskView {
public:
    virtual void show(TaskMap&) const = 0;
};

class CliView : public TaskView {
public:
    void show(TaskMap& tmap) const;
    void showTask(std::shared_ptr<Task>& t) const;
    void showTask(Task* t) const;

private:
    void show_task_common(Task* t) const;
    void print_header() const ;

    static const char* K_BOLD;
    static const char* K_NO_STYLE;
    static const char* K_BLACK_ON_WHITE;
    static const char* K_WHITE_ON_BLACK;

    enum {
        STYLE_FIELD_WIDTH_ID    = 5,
        STYLE_FIELD_WIDTH_PRI   = 5,
        STYLE_FIELD_WIDTH_DESC  = 70
    };
};

#endif //__TASKVIEW_H__
