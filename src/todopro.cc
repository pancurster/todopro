#include <iostream>
#include <memory>

#include <boost/program_options.hpp>

#include "types.h"
#include "todopro.h"
#include "poparser.h"
#include "taskmanager.h"
#include "taskview.h"
#include "task.h"

ToDoPro* tdp;

ToDoPro::ToDoPro()
    : taskmanager(new TaskManager)
    , view(new CliView)
{
}

ToDoPro::~ToDoPro()
{
}

int ToDoPro::exec(int ac, char* av[])
{
    POParser vm(ac, av);

    if (vm.count("add")) {
        tdp->taskmanager->add(&vm);

    } else if (vm.count("help")) {
        std::cout << vm.main_desc << std::endl;
        exit(0);

    } else {
        tdp->view->show();
    }

    return 0;
}

int main(int argc, char* argv[])
{
    std::unique_ptr<ToDoPro> tdp(new ToDoPro);
    return tdp->exec(argc, argv);
}

