#include "todopro.h"
#include "taskmanager.h"
#include "taskview.h"
#include "userinput.h"
#include "datastore.h"
#include "sff.h"

#include <iostream>
#include <memory>

const char* ToDoPro::VERSION="0.0.2";
const char* ToDoPro::DEF_FILENAME = "test.db";

int main(int argc, const char* argv[])
{
    std::unique_ptr<ToDoPro> tdp(new ToDoPro);
    return tdp->exec(argc, argv);
}

int ToDoPro::exec(int ac, const char* av[])
{
    load();

    modify(ac, av);

    save();

    return 0;
}

ToDoPro::ToDoPro()
    : taskmanager(new TaskManager)
    , view(new CliView)
{
}

ToDoPro::~ToDoPro()
{
    delete view;
    delete taskmanager;
}

void ToDoPro::modify(int ac, const char* av[])
{
    UserInput ui(*taskmanager, *view);
    bool ret = ui.commands(ac, av);
    if (ret == false) {
        std::cerr << "Error modifying tasks\n";
    }
}

void ToDoPro::load()
{
    DataStore<SimpleFileFormat> dstore(DEF_FILENAME);
    bool ret = dstore.load(taskmanager->taskmain);
    if (ret == false) {
        std::cerr << "Error loading tasks\n";
    }
}

void ToDoPro::save()
{
    DataStore<SimpleFileFormat> dstore(DEF_FILENAME);
    bool ret = dstore.save(taskmanager->taskmain);
    if (ret == false) {
        std::cerr << "Error saving tasks\n";
    }
}

