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
    std::string image;
    for (TaskVec::const_iterator it=tvec.begin(); it != tvec.end(); ++it) {
        image += std::to_string((*it)->payload->id);
        image += ":";
        image += std::to_string((*it)->payload->pri);
        image += ":";
        image += std::to_string((*it)->payload->state);
        image += ":";
        image += (*it)->payload->desc;
        image += ";\n";
    }
    return image;
}

void SimpleFileFormat::deserialize(std::string& image, TaskVec& tvec)
{
    std::shared_ptr<Task> t;
    std::string line;

    int s=0;
    int e=0;
    int len=0;
    while ( (e = image.find(";", s)) != static_cast<int>(std::string::npos)) {
        len = e - s;
        line = image.substr(s, len);

        t = deserialize_line(line); //XXX
        tvec.push_back(t);

        s = e + strlen(";\n");
    }
}

std::shared_ptr<Task> SimpleFileFormat::deserialize_line(std::string& line)
{
    size_t s=0;
    size_t e=0;
    char buf[TASK_MAX_DESC_CHARACTERS];
    std::shared_ptr<Task> t(new Task);

    bool parsing_success = false;
    do {
        if ((e = line.find(":", s)) == std::string::npos)
            break;
        strcpy(buf, line.substr(s, e).c_str());
        sscanf(buf, "%d", &t->payload->id);
        s = e + 1;

        if ((e = line.find(":", s)) == std::string::npos)
            break;
        strcpy(buf, line.substr(s, e).c_str());
        sscanf(buf, "%d", &t->payload->pri);
        s = e + 1;

        if ((e = line.find(":", s)) == std::string::npos)
            break;
        strcpy(buf, line.substr(s, e).c_str());
        sscanf(buf, "%d", reinterpret_cast<int*>(&t->payload->state));
        s = e + 1;

        // Don't miss the '!=' here
        if ((e = line.find(";", s)) != std::string::npos)
            break;
        t->payload->desc = line.substr(s, e);
        s = e + 1;

        parsing_success = true;
    } while (0);

    if (parsing_success) {
        return t;
    } else {
        std::cout << "Error parsing line:\n   " << line << "\n";
        return 0;
    }
}

