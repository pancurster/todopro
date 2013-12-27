#ifndef __TASK_H__
#define __TASK_H__

#include <list>
#include <string>

typedef int tid_t;
typedef int tprior_t;

enum {TASK_DESC_FIELDS=5};
enum TaskType {TASK, NOTE, OTHER };

class Task {
public:
    Task();
    ~Task();

    tid_t               id;
    tprior_t            pri;
    TaskType            type;
    std::string         desc;
    std::list<Task*>    recurent_task;
private:
    /*
    Task(const Task&) {}
    Task& operator=(const Task&) {}
    */
};

#endif //__TASK_H__
