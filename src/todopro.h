#ifndef TODOPRO_H
#define TODOPRO_H

#include "poparser.h"   // POVars

class TaskManager;
class TaskView;
class CliView;

class ToDoPro {
public:
    ToDoPro     ();
    ~ToDoPro    ();

    // Main flow methods
    void load();
    void save();
    void commands(int ac, char* av[]);

    bool add(POVars& vm);
    bool rm(POVars& vm);
    bool modify(POVars& vm);
    int exec(int ac, char* av[]);

    TaskManager*    taskmanager;
    //TaskView*    view;
    CliView*        view;

    static const char* VERSION;
private:

};

#endif //TODOPRO_H

