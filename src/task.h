#ifndef __TASK_H__
#define __TASK_H__

#include <list>
#include <string>

typedef int tid_t;
typedef int tprior_t;

enum task_type {TASK, NOTE, OTHER };

class Task {
public:
    Task();
    ~Task();

    tid_t               id;
    tprior_t            priority;
    task_type           type;
    std::string         description;
    std::list<Task*>    recurent_task;
private:
    /*
    Task(const Task&) {}
    Task& operator=(const Task&) {}
    */
};

#endif //__TASK_H__
