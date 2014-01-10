#ifndef TASK_H
#define TASK_H

#include <list>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <ctime>


class Task;

class Task {
public:
    Task();
    ~Task();

    enum TaskType { TT_TASK, TT_NOTE, TT_OTHER };
    enum {
        TASK_DESC_FIELDS    = 5,
        MAX_DESC_CHARACTERS = 120,
        NOT_PROPER_ID       = -1,
        NOT_PROPER_PRI      = -1
    };
    enum TaskState {
        STATE_NOT_SET = 0,
        STATE_PENDING = 1,
        STATE_SUSPEND = 2,
        STATE_DONE    = 3
    };

    struct TaskPayload {
        int                 id;
        int                 pri;
        TaskType            type;
        std::string         desc;
        TaskState           state;
        std::time_t         start_time;
        std::time_t         end_time;
        std::list<std::shared_ptr<Task>> recurent_task;
    }* payload;

private:
    Task(const Task&);
    Task& operator=(const Task&);
};

#endif //TASK_H

