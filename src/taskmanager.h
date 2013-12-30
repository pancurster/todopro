#ifndef __TASKLIST_H__
#define __TASKLIST_H__

#include <map>

#include "poparser.h"

class Task;

class TaskManager {
    public:
        void add(Task*);
        void add(POVars* vm);
    private:
        std::map<std::string, Task*> m_mainlist;
};

#endif //__TASKLIST_H__
