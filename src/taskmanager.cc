#include <fstream>
#include <map>
#include <memory>

#include "task.h"
#include "poparser.h"
#include "serializer.h"
#include "taskmanager.h"

TaskManager::TaskManager()
{
}

bool TaskManager::add(std::shared_ptr<Task>& t)
{
    m_mainlist.insert(std::make_pair(t->payload->desc, t));
}

bool TaskManager::add(POVars& vm)
{
    std::shared_ptr<Task> t(new Task);

    if (vm.count("pri")) {
        t->payload->pri = vm["pri"].as<int>();
    }
    if (vm.count("desc")) {
        t->payload->desc = vm["desc"].as<std::string>();
    } else {
        return false;
    }

    //TODO: why clang show error here?
    m_mainlist.insert(
                      std::pair<std::string, std::shared_ptr<Task>>(
                          vm["desc"].as<std::string>(),
                          t)
                     );

    return true; //TODO
}

int TaskManager::get_new_task_id()
{
    m_task_highest_id += 1;
    return m_task_highest_id;
}

int TaskManager::get_default_pri()
{
    return DEFAULT_PRI;
}

std::shared_ptr<Task> TaskManager::createEmptyTask()
{
    std::shared_ptr<Task> t(new Task);

    t->payload->id = get_new_task_id();
    t->payload->pri = get_default_pri();

    return t;
}

std::shared_ptr<Task> TaskManager::findByDesc(std::string desc)
{
    TaskMap::iterator task_item_it;
    task_item_it = m_mainlist.find(desc);

    if (task_item_it != m_mainlist.end()) {
        return task_item_it->second;
    } else {
        // XXX czy to jest poprawne?
        return 0;
    }
}

std::shared_ptr<Task> TaskManager::findByDescPartial(std::string descpart)
{
    //TODO chyba trzeba zastosowac wlasna funkcje compare zeby to bylo szybkie
    std::string key;
    for (TaskMap::iterator it=m_mainlist.begin(); it != m_mainlist.end(); ++it) {
        key = it->first;
        if (key.find(descpart) != -1)
            return it->second;
    }
    return 0;
}


