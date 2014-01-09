#include "poparser.h"
#include "task.h"
#include "serializer.h"
#include "taskmanager.h"

#include <cassert>

#include <fstream>
#include <map>
#include <memory>
#include <algorithm>

TaskManager::TaskManager()
{
}

// TODO Is passing reference to shared_ptr is ok?
bool TaskManager::add(std::shared_ptr<Task>& t)
{
    // Generating id is simple. We increment bigest id number
    // of already stored tasks.
    t->payload->id = get_highest_task_id() + 1;

    taskmain.push_back(t);

    return true; //TODO
}

int TaskManager::get_highest_task_id()
{
    struct MaxValue {
        MaxValue() : maxValue(0) {}
        MaxValue(const MaxValue& l) { this->maxValue = l.maxValue; }
        void operator()(std::shared_ptr<Task>& p) {
            if (p->payload->id > maxValue)
                maxValue = p->payload->id;
        }
        int maxValue;
    };

    MaxValue fun(std::for_each(taskmain.begin(), taskmain.end(), MaxValue()));
    return fun.maxValue;
}

bool TaskManager::del(std::shared_ptr<Task>& t)
{
    // The cost is higher than erasing from map but other way
    // we must consider synchronizing to 'maintask' container, so: cost,
    TaskVec::iterator item = std::find(taskmain.begin(), taskmain.end(), t);
    taskmain.erase(item);

    return true;
}

bool TaskManager::done(std::shared_ptr<Task>& t)
{
    t->payload->state = TS_DONE;
    return true;
}

int TaskManager::get_default_pri()
{
    return DEFAULT_PRI;
}

std::shared_ptr<Task> TaskManager::createEmptyTask()
{
    std::shared_ptr<Task> t(new Task);

    t->payload->id = 0;
    t->payload->pri = get_default_pri();

    return t;
}

std::shared_ptr<Task> TaskManager::findByDesc(std::string desc)
{
    if (taskbydesc.size() == 0) {
        taskbydesc.fillFromVec(taskmain);
    }
    return taskbydesc[desc];
}

std::shared_ptr<Task> TaskManager::findByDescPartial(std::string descpart)
{
    //TODO chyba trzeba zastosowac wlasna funkcje compare zeby to bylo szybkie
    std::string key;
    for (TaskMap::iterator it=taskbydesc.begin(); it != taskbydesc.end(); ++it) {
        key = it->first;
        if (key.find(descpart) != std::string::npos)
            return it->second;
    }
    return 0;
}

std::shared_ptr<Task> TaskManager::findById(std::string id)
{
    if (std::isdigit(id.c_str()[0])) {
        int num = std::atoi(id.c_str());
        return findById(num);
    }
    return 0;
}

std::shared_ptr<Task> TaskManager::findById(int id)
{
    if (taskbyid.size() == 0) {
        taskbyid.fillFromVec(taskmain);
    }
    return taskbyid[id];
}

