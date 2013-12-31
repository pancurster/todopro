#ifndef TODOPRO_H
#define TODOPRO_H

#include "poparser.h"   // POVars

class TaskManager;
class TaskView;

class ToDoPro {
public:
    ToDoPro();
    ~ToDoPro();

    bool    add     (POVars& vm);
    bool    rm      (POVars& vm);
    bool    modify  (POVars& vm);

    int     exec    (int ac, char* av[]);

    TaskManager* taskmanager;
    TaskView*    view;
private:
};

#endif //TODOPRO_H

