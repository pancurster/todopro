#ifndef TASKLIST_H
#define TASKLIST_H

#include <map>
#include <unordered_map>
#include <memory>

#include "poparser.h"
#include "task.h"

typedef std::vector<std::shared_ptr<Task>> TaskVec;

#if 0
template <class KEY>
class TaskMapFabric : public std::map<KEY, std::shared_ptr<Task>> {
public:
    TaskMapFabric()
        : std::map<KEY, std::shared_ptr<Task>>()
        , fieldtype("id")
    { }
    void fillFromVec(TaskVec& tv)
    {
        for (TaskVec::iterator it=tv.begin(); it != tv.end(); ++it) {
            this->insert(make_pair(getKeyValue(it), *it));
        }
    }
private:
    std::string fieldtype;
    KEY getKeyValue(TaskVec::iterator& it)
    {
        if (fieldtype == "id")
            return (*it)->payload->id;
        if (fieldtype == "pri")
            return (*it)->payload->pri;
        //if (fieldtype == "desc")
            //return (*it)->payload->desc;
        if (fieldtype == "state")
            return (*it)->payload->state;

        return 0;
    }
};
#endif

class TaskMapByDesc : public std::unordered_map<std::string, std::shared_ptr<Task>> {
public:
    TaskMapByDesc()
        : std::unordered_map<std::string, std::shared_ptr<Task>>()
    {}
    void fillFromVec(TaskVec& tv)
    {
        for (auto it=tv.begin(); it != tv.end(); ++it) {
            insert(make_pair((*it)->payload->desc, *it));
        }
    }
};

class TaskMapById : public std::map<int, std::shared_ptr<Task>> {
public:
    TaskMapById()
        : std::map<int, std::shared_ptr<Task>>()
    {}
    void fillFromVec(TaskVec& tv)
    {
        for (auto it=tv.begin(); it != tv.end(); ++it) {
            insert(make_pair((*it)->payload->id, *it));
        }
    }
};

class TaskManager {
public:
    TaskManager();
    ~TaskManager();
    bool add(const std::shared_ptr<Task>& t);
    bool del(const std::shared_ptr<Task>& t);
    bool done(const std::shared_ptr<Task>& t);
    std::shared_ptr<Task> findByDesc(std::string desc);
    std::shared_ptr<Task> findByDescPartial(std::string desc);
    std::shared_ptr<Task> findById(std::string id);
    std::shared_ptr<Task> findById(int id);
    std::shared_ptr<Task> createEmptyTask();
    std::shared_ptr<Task> select(std::string key);
    std::shared_ptr<Task> create(std::string desc);
    // The 'taskmain' is:
    // - base container for tasks. 
    // - fast so fit well to just show list of tasks, what is most often use case.
    // - source for other more specialized containers.
    // - guaranted to be always filled.
    TaskVec         taskmain;

    // We use strategy "be lazy", what mean, we will fill
    // more smart containers only when they are needed.
    TaskMapByDesc   taskbydesc;
    TaskMapById     taskbyid;
    //TaskMapFabric<int> taskbyid;

private:
    TaskManager(const TaskManager&);
    TaskManager& operator=(const TaskManager&);

    int get_new_task_id();
    int get_default_pri();
    int get_highest_task_id();

    enum { DEFAULT_PRI=0 };
};

#endif //TASKLIST_H

