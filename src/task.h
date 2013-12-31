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


struct info_t{
    tid_t               id;
    tprior_t            pri;
    TaskType            type;
    std::string         desc;
    std::list<Task*>    recurent_task;
};


class Task {
public:
    Task();
    ~Task();

    info_t info;
private:
    std::shared_ptr<SerDes> serdes;
};

#endif //TASK_H

