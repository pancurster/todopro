#include "userinput.h"
#include "poparser.h"
#include "taskmanager.h"
#include "taskview.h"
#include "todopro.h"

#include <iostream>
#include <memory>

UserInput::UserInput(TaskManager& tm, const TaskView& tv)
    : taskmanager(tm)
    , taskview(tv)
{
}

UserInput::~UserInput()
{
}

bool UserInput::commands(int ac, const char* av[]) const
{
    POParser vm(ac, av);
    if (vm.fail()) {
        return false;
    }

    std::shared_ptr<Task> temptask;

    if (vm.count("help")) {
        std::cout << vm.all << std::endl;
        return true;
    }
    if (vm.count("version")) {
        std::cout << ToDoPro::VERSION << std::endl;
        return true;
    }

    // CREATE/SELECT
    if (vm.count("select")) {
        std::string arg = vm["select"].as<std::string>();
        temptask = taskmanager.select(arg);

    } else if (vm.count("new")) {
        std::string arg = vm["new"].as<std::string>();
        temptask = taskmanager.create(arg);
        taskmanager.add(temptask);

    } else {
        // OK. No select, no create, we can only show and THE END.
        taskview.showTask(taskmanager.taskmain);
        return true;
    }

    // MODIFY
    if (vm.count("pri")) {
        temptask->payload->pri = vm["pri"].as<int>();
    }
    if (vm.count("desc")) {
        temptask->payload->desc = vm["desc"].as<std::string>();
    }
    if (vm.count("remove")) {
        taskmanager.del(temptask);
    }
    if (vm.count("done")) {
        taskmanager.done(temptask);
    }
    if (vm.count("deadline")) {
        //std::string taskmanager = vm["deadline"].as<std::string>();
        // TODO
    }

    // VIEW
    if (temptask) {
        taskview.showTask(temptask);

    } else {
        taskview.showTask(taskmanager.taskmain);
    }

    return true;
}
