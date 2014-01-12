#ifndef TODOPRO_H
#define TODOPRO_H

class TaskManager;
class TaskView;

class ToDoPro {
public:
    ToDoPro     ();
    ~ToDoPro    ();

    // Main flow methods
    void load();
    void save();

    int exec(int ac, const char* av[]);

    TaskManager*    taskmanager;
    TaskView*       view;

    static const char* VERSION;
private:

};

#endif //TODOPRO_H

