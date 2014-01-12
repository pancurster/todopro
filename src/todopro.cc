#include "todopro.h"
#include "taskmanager.h"
#include "taskview.h"
#include "userinput.h"
#include "datastore.h"

#include <iostream>
#include <memory>

const char* ToDoPro::VERSION="0.0.2";

int main(int argc, const char* argv[])
{
    std::unique_ptr<ToDoPro> tdp(new ToDoPro);
    return tdp->exec(argc, argv);
}

/*
 * Mamy tutaj prosty przeplyw:
 * 1) zaladowanie, 2) modyfikacja, 3) zapis.
 */
int ToDoPro::exec(int ac, const char* av[])
{
    (void)load();

    UserInput ui(*taskmanager, *view);
    (void)ui.commands(ac, av);

    (void)save();

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


void ToDoPro::load()
{
    DataStore<SimpleFileFormat> dstore;
    dstore.load("test.db", taskmanager->taskmain);
}

void ToDoPro::save()
{
    DataStore<SimpleFileFormat> dstore;
    dstore.save("test.db", taskmanager->taskmain);
}

