#ifndef TASK_H
#define TASK_H

#include <list>
#include <vector>
#include <map>
#include <string>
#include <memory>


class SerDes;
class Task;

typedef std::vector<std::shared_ptr<Task>> TaskVec;
typedef std::map<std::string, std::shared_ptr<Task>> TaskMap;

enum {
    TASK_DESC_FIELDS=6,
    TASK_MAX_DESC_CHARACTERS=120
};

enum TaskType {
    TT_TASK,
    TT_NOTE,
    TT_OTHER
};

enum TaskState {
    TS_NOSTATE=0,
    TS_PENDING=1,
    TS_SUSPEND=2,
    TS_DONE=3
};

class Task {
public:
    Task();
    ~Task();

    struct TaskPayload {
        int                 id;
        int                 pri;
        TaskType            type;
        std::string         desc;
        TaskState           state;
        std::list<Task*>    recurent_task;
    }* payload;

private:
    Task(const Task&);
    Task& operator=(const Task&);
};

#endif //TASK_H

