#include <iostream>
#include <memory>

#include <boost/program_options.hpp>

#include "types.h"
#include "todopro.h"
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
    POVars vm;
    parse_program_options(ac, av, vm);

    if (vm.count("add")) {
        tdp->taskmanager->add(&vm);
    } else {
        tdp->view->show();
    }

    return 0;
}

void ToDoPro::parse_program_options(int ac, char* av[], POVars &vm)
{
    namespace po = boost::program_options;

    po::options_description desc("Usage: tdp [options]\nOptions");
    desc.add_options()
        ("help,h",  "help msg")
        ("add,a",   "add task")
        ("pri,p",   "set priority")
        ("task,t",  "add task [default]")
        ("note,n",  "add note")
        ("dead,d",  "set deadline")
        ;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    // Help can be handled here
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        exit(0);
    }
}

int main(int argc, char* argv[])
{
    std::unique_ptr<ToDoPro> tdp(new ToDoPro);
    return tdp->exec(argc, argv);
}

