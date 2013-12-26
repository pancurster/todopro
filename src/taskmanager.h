#ifndef __TASKLIST_H__
#define __TASKLIST_H__

#include <map>

class Task;

class TaskManager {
    public:
        void add(Task*);
    private:
        std::map<std::string, Task*> m_mainlist;
};

#endif //__TASKLIST_H__
