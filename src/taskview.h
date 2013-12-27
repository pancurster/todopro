#ifndef __TASKVIEW_H__
#define __TASKVIEW_H__

class TaskView {
public:
    virtual void show() = 0;
};

class CliView : public TaskView {
public:
    void show() {}
};

#endif //__TASKVIEW_H__
