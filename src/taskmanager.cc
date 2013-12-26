#include <map>
#include "task.h"
#include "taskmanager.h"

void TaskManager::add(Task* t)
{
    m_mainlist.insert(std::pair<std::string, Task*>(t->desc, t));
}

