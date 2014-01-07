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

const char* ToDoPro::VERSION="0.0.1";

int main(int argc, char* argv[])
{
    std::unique_ptr<ToDoPro> tdp(new ToDoPro);
    return tdp->exec(argc, argv);
}

/*
 * Mamy tutaj prosty przeplyw:
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
void ToDoPro::commands(int ac, char* av[])
{
    POParser vm(ac, av);
    std::shared_ptr<Task> temptask;
    bool new_task_ready_to_add = false;

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

        // 1) Try select by ID
        // 2) Try select by desc (parameter is whole key)
        // 3) Try select by desc (parameter is substr of key)
        do {
            std::string arg = vm["select"].as<std::string>();

            if (temptask = taskmanager->findById(arg))
                break;
            if (temptask = taskmanager->findByDesc(arg))
                break;
            if (temptask = taskmanager->findByDescPartial(arg))
                break;

            if (temptask == 0) {
                std::cout<<"Not found\n";
                return;
            }
        } while (0);
    } else if (vm.count("new")) {
        std::cout<<"Creating empty task... ";
        temptask = taskmanager->createEmptyTask();
        temptask->payload->desc = vm["new"].as<std::string>();
        new_task_ready_to_add = true;
        std::cout<<"done\n";
    }

    // MODIFY
    if (vm.count("pri")) {
        temptask->payload->pri = vm["pri"].as<int>();
    }

    if (vm.count("desc")) {
        std::cout<<"Setting desc... ";
        temptask->payload->desc = vm["desc"].as<std::string>();
        std::cout<<"done\n";
    }

    if (new_task_ready_to_add) {
        std::cout<<"adding new task\n";
        taskmanager->add(temptask);
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

