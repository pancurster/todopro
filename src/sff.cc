#include "sff.h"
#include "serializer.h"
#include "task.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <memory>

SimpleFileFormat::SimpleFileFormat() { }

SimpleFileFormat::~SimpleFileFormat() { }

std::string SimpleFileFormat::serialize(const TaskVec& tvec)
{
    std::stringstream image;
    for (auto it=tvec.begin(); it != tvec.end(); ++it) {
        image << (*it)->payload->id     << ":"
              << (*it)->payload->pri    << ":"
              << (*it)->payload->type   << ":"
              << (*it)->payload->state  << ":"
              << (*it)->payload->desc   << ";\n";
    }
    return image.str();
}

int SimpleFileFormat::deserialize(std::string& image, TaskVec& tvec)
{
    std::shared_ptr<Task> t;
    std::string line;

    int task_parsed=0;

    std::istringstream ss(image);
    while (std::getline(ss, line)) {

        t = deserialize_single_task(line);
        if (t) {
            tvec.push_back(t);
            task_parsed += 1;
        } else {
            std::cerr << "Corrupted task\n";
        }
    }
    return task_parsed;
}

std::shared_ptr<Task> SimpleFileFormat::deserialize_single_task(std::string& line)
{
    std::shared_ptr<Task> t(new Task);
    bool parsing_success = true;

    int type, state;
    char c[5]= {0};
    std::stringstream ss(line);

    ss  >> t->payload->id   >> c[0]
        >> t->payload->pri  >> c[1]
        >> type             >> c[2]
        >> state            >> c[3];

    t->payload->type = static_cast<Task::TaskType>(type);
    t->payload->state = static_cast<Task::TaskState>(state);

    // and, at the end, take description of task.
    // Can't find sexy construction to fetch from ss
    // a string with whitespaces.
    std::string desc = ss.str();
    size_t e = desc.rfind(";");
    size_t s = desc.rfind(":");
    s += 1;
    t->payload->desc = desc.substr(s, e-s);


    if (std::strcmp("::::", c) != 0)
        parsing_success = false;
    if (t->payload->desc.size() == 0)
        parsing_success = false;

    if (parsing_success) {
        return t;
    } else {
        std::cerr << "Error parsing line: " << line << "\n";
        return 0;
    }
}

