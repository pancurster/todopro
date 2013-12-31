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


ToDoPro::ToDoPro()
    : taskmanager(new TaskManager)
    , view(new CliView) { }

ToDoPro::~ToDoPro() { }

int ToDoPro::exec(int ac, char* av[])
{
    POParser vm(ac, av);

    if (vm.count("add")) {
        if (!add(vm))
            return 1;
    } else if (vm.count("help")) {
        std::cout << vm.main_desc << std::endl;
        exit(0);
    } else if (vm.count("desc")) {
        std::cout << "description:" << vm["desc"].as<std::string>() << "\n";
    } else {
        view->show();
    }

    return 0;
}

bool ToDoPro::add(POVars& vm)
{
    taskmanager->add(vm);
    DataStore<SimpleFileFormat> dstore;
    dstore.save("test.db", taskmanager->m_mainlist);
}

int main(int argc, char* argv[])
{
    std::unique_ptr<ToDoPro> tdp(new ToDoPro);
    return tdp->exec(argc, argv);
}

