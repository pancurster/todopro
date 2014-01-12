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

TaskManager::~TaskManager()
{
}

// Passing reference to shared_ptr is ok?
// Yep: http://stackoverflow.com/a/8844924
bool TaskManager::add(const std::shared_ptr<Task>& t)
{
    if (!t)
        return false;

    // We increment bigest id number of already stored tasks.
    t->payload->id = get_highest_task_id() + 1;

    taskmain.push_back(t);

    return true;
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

bool TaskManager::del(const std::shared_ptr<Task>& t)
{
    // The cost is higher than erasing from map but other way
    // we must consider synchronizing to 'maintask' container, so: cost,
    TaskVec::iterator item = std::find(taskmain.begin(), taskmain.end(), t);
    taskmain.erase(item);

    return true;
}

bool TaskManager::done(const std::shared_ptr<Task>& t)
{
    t->payload->state = Task::STATE_DONE;
    return true;
}

int TaskManager::get_default_pri()
{
    return Task::DEFAULT_PRI;
}

std::shared_ptr<Task> TaskManager::createEmptyTask()
{
    std::shared_ptr<Task> t(new Task);

    t->payload->id = 0;
    t->payload->pri = get_default_pri();

    return t;
}

std::shared_ptr<Task> TaskManager::select(std::string key)
{
    // 1) Try select by ID
    // 2) Try select by desc (parameter is whole key)
    // 3) Try select by desc (parameter is substr of key)
    std::shared_ptr<Task> temptask;
    do {
        if (temptask = findById(key))
            break;
        if (temptask = findByDesc(key))
            break;
        if (temptask = findByDescPartial(key))
            break;
    } while (0);

    return temptask;
}

std::shared_ptr<Task> TaskManager::create(std::string desc)
{
    std::shared_ptr<Task> temptask(0);

    temptask = createEmptyTask();
    temptask->payload->desc = desc;

    return temptask;
}

std::shared_ptr<Task> TaskManager::findByDesc(std::string desc)
{
    if (taskbydesc.size() != taskmain.size()) {
        taskbydesc.fillFromVec(taskmain);
    }

    if (taskbydesc.count(desc))
        return taskbydesc[desc];
    return 0;
}

std::shared_ptr<Task> TaskManager::findByDescPartial(std::string descpart)
{
    if (taskbydesc.size() != taskmain.size()) {
        taskbydesc.fillFromVec(taskmain);
    }

    std::string key;
    for (TaskMapByDesc::iterator it=taskbydesc.begin();
            it != taskbydesc.end(); ++it)
    {
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
    if (taskbyid.size() != taskmain.size()) {
        taskbyid.fillFromVec(taskmain);
    }
    if (taskbyid.count(id))
        return taskbyid[id];
    return 0;
}

