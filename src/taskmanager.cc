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

void TaskManager::add(Task* t)
{
}

bool TaskManager::add(POVars& vm)
{
    std::shared_ptr<Task> t(new Task);

    if (vm.count("pri")) {
        t->info.pri = vm["pri"].as<int>();
    }
    if (vm.count("desc")) {
        t->info.desc = vm["desc"].as<std::string>();
    } else {
        return false;
    }

    //TODO: why clang shows here error?
    m_mainlist.insert(
                      std::pair<std::string, std::shared_ptr<Task>>(
                          vm["desc"].as<std::string>(),
                          t)
                     );

    return true; //TODO
}

