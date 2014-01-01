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

