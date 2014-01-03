#ifndef TASKLIST_H
#define TASKLIST_H

#include <map>
#include <memory>

#include "poparser.h"
#include "task.h"

class TaskManager {
public:
    TaskManager();
    ~TaskManager();
    bool add(std::shared_ptr<Task>& t);
    bool add(POVars& vm);
    bool save();
    std::shared_ptr<Task> findByDesc(std::string desc);
    std::shared_ptr<Task> findByDescPartial(std::string desc);
    std::shared_ptr<Task> createEmptyTask();

    TaskMap m_mainlist;

private:
    TaskManager(const TaskManager&);
    TaskManager& operator=(const TaskManager&);

    int get_new_task_id();
    int get_default_pri();

    enum { DEFAULT_PRI=0 };

    int m_task_highest_id;
};

#endif //TASKLIST_H

