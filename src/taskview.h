#ifndef __TASKVIEW_H__
#define __TASKVIEW_H__

#include "task.h"

class TaskView {
public:
    virtual void show(TaskMap&) = 0;
};

class CliView : public TaskView {
public:
    void show(TaskMap& tmap)
    {
        std::cout << "Id  Pri  Desc\n";
        for(TaskMap::iterator it=tmap.begin(); it!=tmap.end(); ++it) {
            std::cout << (*it->second).payload->id << "  "
                      << (*it->second).payload->pri << "   "
                      << it->first << "\n";
        }
    }
};

#endif //__TASKVIEW_H__
