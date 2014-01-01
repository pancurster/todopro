#include <iostream>
#include <memory>

#include <boost/program_options.hpp>

#include "types.h"
#include "todopro.h"
#include "poparser.h"
#include "taskmanager.h"
#include "taskview.h"
#include "task.h"
#include "datastore.h"


int main(int argc, char* argv[])
{
    std::unique_ptr<ToDoPro> tdp(new ToDoPro);
    return tdp->exec(argc, argv);
}

/*
 * Na tym poziomie wykonania programu mozemy przyjac ze jedyne abstrakcje
 * z jakimi mamy do czynienia modeluja prosty przeplyw:
 * 1) zaladowanie, 2) modyfikacja, 3) zapis.
 */
int ToDoPro::exec(int ac, char* av[])
{
    load();

    commands(ac, av);

    save();

    return 0;
}

ToDoPro::ToDoPro()
    : taskmanager(new TaskManager)
    , view(new CliView) { }

ToDoPro::~ToDoPro() { }


bool ToDoPro::add(POVars& vm)
{
    taskmanager->add(vm);
}

void ToDoPro::load()
{
    DataStore<SimpleFileFormat> dstore;
    dstore.load("test.db", taskmanager->m_mainlist);
}

void ToDoPro::commands(int ac, char* av[])
{
    POParser vm(ac, av);

    if (vm.count("add")) {
        add(vm);
    } else if (vm.count("help")) {
        std::cout << vm.main_desc << std::endl;
        exit(0);
    } else if (vm.count("desc")) {
        std::cout << "description:" << vm["desc"].as<std::string>() << "\n";
    }

    view->show(taskmanager->m_mainlist);
}

void ToDoPro::save()
{
    DataStore<SimpleFileFormat> dstore;
    dstore.save("test.db", taskmanager->m_mainlist);
}

