#ifndef __TODOPRO_H__
#define __TODOPRO_H__

#include "types.h"

class TaskManager;
class TaskView;

class ToDoPro {
public:
    ToDoPro();
    ~ToDoPro();

    int exec(int ac, char* av[]);

    TaskManager* taskmanager;
    TaskView*    view;
private:
};

#endif //__TODOPRO_H__
