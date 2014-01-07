#ifndef TASK_H
#define TASK_H

#include <list>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <ctime>


class SerDes;
class Task;

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
        std::time_t         start_time;
        std::time_t         end_time;
    }* payload;

private:
    Task(const Task&);
    Task& operator=(const Task&);
};

#endif //TASK_H

