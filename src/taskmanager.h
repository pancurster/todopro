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
        void add(Task*);
        bool add(POVars& vm);
        bool save();

        TaskMap m_mainlist;
    private:
};

#endif //TASKLIST_H

