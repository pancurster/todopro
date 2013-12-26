#ifndef __TODOPRO_H__
#define __TODOPRO_H__

#include "types.h"

class TaskManager;
class CliView;

class ToDoPro {
public:
    int exec(int ac, char* av[]);

    TaskManager taskmanager;
    CliView     view;
private:
    void parse_program_options(int ac, char* av[], povars &vm);
};

#endif //__TODOPRO_H__
