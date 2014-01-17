#ifndef TODOPRO_H
#define TODOPRO_H

#include <boost/scoped_ptr.hpp>

class TaskManager;
class TaskView;

class ToDoPro {
public:
    ToDoPro     ();
    ~ToDoPro    ();

    // Main flow methods
    void load();
    void modify(int ac, const char* av[]);
    void save();

    int exec(int ac, const char* av[]);

    boost::scoped_ptr<TaskManager>  taskmanager;
    boost::scoped_ptr<TaskView>     view;

    static const char* VERSION;
    static const char* DEF_FILENAME;
private:
    std::string get_file_db_name();
};

#endif //TODOPRO_H

