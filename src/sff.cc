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
    size_t s=0;
    size_t e=0;
    char buf[Task::MAX_DESC_CHARACTERS];
    std::shared_ptr<Task> t(new Task);

    std::stringstream ss;
    bool parsing_success = false;
    do {
        // ID
        if ((e = line.find(":", s)) == std::string::npos)
            break;
        ss.str(line.substr(s, e));
        ss >> t->payload->id;
        s = e + 1;

        // PRI
        if ((e = line.find(":", s)) == std::string::npos)
            break;
        ss.str(line.substr(s, e));
        ss >> t->payload->pri;
        s = e + 1;

        // TYPE
        if ((e = line.find(":", s)) == std::string::npos)
            break;
        ss.str(line.substr(s, e));
        int temp;
        ss >> temp;
        t->payload->type = static_cast<Task::TaskType>(temp);
        s = e + 1;

        // STATE
        if ((e = line.find(":", s)) == std::string::npos)
            break;
        ss.str(line.substr(s, e));
        ss >> temp;
        t->payload->state = static_cast<Task::TaskState>(temp);
        s = e + 1;

        // DESC
        e = line.find(";", s);
        e -= 1;
        t->payload->desc = line.substr(s, e);
        if (t->payload->desc.size() < 1)
            break;

        parsing_success = true;
    } while (0);

    if (parsing_success) {
        return t;
    } else {
        std::cerr << "Error parsing line: " << line << "\n";
        return 0;
    }
}

