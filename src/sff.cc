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

    int s=0;
    int e=0;
    int len=0;
    int task_parsed=0;
    while ( (e = image.find(";", s)) != static_cast<int>(std::string::npos)) {
        len = e - s;
        line = image.substr(s, len);

        t = deserialize_single_task(line);
        if (t) {
            tvec.push_back(t);
            task_parsed += 1;
        } else {
            std::cerr << "Corrupted task\n";
        }

        s = e + strlen(";\n");
    }
    return task_parsed;
}

std::shared_ptr<Task> SimpleFileFormat::deserialize_single_task(std::string& line)
{
    size_t s=0;
    size_t e=0;
    char buf[Task::MAX_DESC_CHARACTERS];
    std::shared_ptr<Task> t(new Task);

    bool parsing_success = false;
    do {
        // ID
        if ((e = line.find(":", s)) == std::string::npos)
            break;
        strcpy(buf, line.substr(s, e).c_str());
        sscanf(buf, "%d", &t->payload->id);
        s = e + 1;

        // PRI
        if ((e = line.find(":", s)) == std::string::npos)
            break;
        strcpy(buf, line.substr(s, e).c_str());
        sscanf(buf, "%d", &t->payload->pri);
        s = e + 1;

        // TYPE
        if ((e = line.find(":", s)) == std::string::npos)
            break;
        strcpy(buf, line.substr(s, e).c_str());
        sscanf(buf, "%d", reinterpret_cast<int*>(&t->payload->type));
        s = e + 1;

        // STATE
        if ((e = line.find(":", s)) == std::string::npos)
            break;
        strcpy(buf, line.substr(s, e).c_str());
        sscanf(buf, "%d", reinterpret_cast<int*>(&t->payload->state));
        s = e + 1;

        // DESC
        e = line.find(";", s);  // mamy gwarancje ze linijka jest prawidlowo zakonczona
        t->payload->desc = line.substr(s, e);
        if (t->payload->desc.size() < 1)
            break;
        s = e + 1;

        parsing_success = true;
    } while (0);

    if (parsing_success) {
        return t;
    } else {
        std::cerr << "Error parsing line: " << line << "\n";
        return 0;
    }
}

