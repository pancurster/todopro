#include "todopro.h"
#include "taskmanager.h"
#include "taskview.h"
#include "userinput.h"
#include "datastore.h"
#include "sff.h"

#include <iostream>
#include <memory>
#include <cstdlib>

const char* ToDoPro::VERSION="0.0.3";
const char* ToDoPro::DEF_FILENAME = ".todopro.db";

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

std::string ToDoPro::get_file_db_name()
{
    char* phome = std::getenv("HOME");
    std::stringstream home("");
    home << phome << "/" << DEF_FILENAME;

    return home.str();
}

