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
    dstore.load("test.db", taskmanager->m_mainlist);
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
        // Traktujemy wzorzec jako pelny klucz.
        // Jesli to nie daje rezultatu to szukamy jako czesc reprezentacji klucza
        temptask = taskmanager->findByDesc(vm["select"].as<std::string>());
        if (temptask == 0) {
            temptask = taskmanager->findByDescPartial(vm["select"].as<std::string>());
        }
        if (temptask == 0) {
            std::cout<<"Not found\n";
            return;
        }
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

    // VIEW
    if (temptask) {
        view->showTask(temptask);
    } else {
        view->showTask(taskmanager->m_mainlist);
    }
}

void ToDoPro::save()
{
    DataStore<SimpleFileFormat> dstore;
    dstore.save("test.db", taskmanager->m_mainlist);
}

