#ifndef TASK_H
#define TASK_H

#include <list>
#include <vector>
#include <map>
#include <string>
#include <memory>


class SerDes;
class Task;


typedef int tid_t;
typedef int tprior_t;
typedef std::vector<std::shared_ptr<Task>> TaskVec;
typedef std::map<std::string, std::shared_ptr<Task>> TaskMap;


enum {TASK_DESC_FIELDS=5};
enum TaskType {TT_TASK, TT_NOTE, TT_OTHER};



class Task {
public:
    Task();
    ~Task();

    struct TaskPayload {
        int                 id;
        int                 pri;
        TaskType            type;
        std::string         desc;
        std::list<Task*>    recurent_task;
    }* payload;

private:
    Task(const Task&);
    Task& operator=(const Task&);
};

#endif //TASK_H

