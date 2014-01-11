#include "todopro.h"
#include "types.h"
#include "poparser.h"
#include "taskmanager.h"
#include "taskview.h"
#include "task.h"
#include "datastore.h"

#include <boost/program_options.hpp>

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
    load();

    commands(ac, av);

    save();

    return 0;
}

ToDoPro::ToDoPro()
    : taskmanager(new TaskManager)
    , view(new CliView) { }

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

//
// Commands dispather
// TODO move this to poparser module. Divide to functions like
// 'no_action_functions', 'select_functions', 'modify_functions'
// or something like that (?).
void ToDoPro::commands(int ac, const char* av[])
{
    POParser vm(ac, av);
    std::shared_ptr<Task> temptask;

    if (vm.count("help")) {
        std::cout << vm.all << std::endl;
        return;
    }
    if (vm.count("version")) {
        std::cout << ToDoPro::VERSION << std::endl;
        return;
    }

    // CREATE/SELECT
    if (vm.count("select")) {
        std::string arg = vm["select"].as<std::string>();
        temptask = taskmanager->select(arg);

    } else if (vm.count("new")) {
        std::string arg = vm["new"].as<std::string>();
        temptask = taskmanager->create(arg);
        taskmanager->add(temptask);
    }

    // MODIFY
    if (vm.count("pri")) {
        temptask->payload->pri = vm["pri"].as<int>();
    }
    if (vm.count("desc")) {
        temptask->payload->desc = vm["desc"].as<std::string>();
    }
    if (vm.count("remove")) {
        taskmanager->del(temptask);
    }
    if (vm.count("done")) {
        taskmanager->done(temptask);
    }
    if (vm.count("deadline")) {
        //std::string tm = vm["deadline"].as<std::string>();
        // TODO
    }

    // VIEW
    if (temptask) {
        view->showTask(temptask);

    } else {
        view->showTask(taskmanager->taskmain);
    }
}

void ToDoPro::save()
{
    DataStore<SimpleFileFormat> dstore;
    dstore.save("test.db", taskmanager->taskmain);
}

