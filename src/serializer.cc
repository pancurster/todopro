#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <memory>

#include "task.h"
#include "serializer.h"


SimpleFileFormat::SimpleFileFormat() { }

SimpleFileFormat::~SimpleFileFormat() { }

std::shared_ptr<std::string> SimpleFileFormat::serialize(TaskMap& tvec)
{
    std::shared_ptr<std::string> image(new std::string);
    for (TaskMap::iterator it=tvec.begin(); it != tvec.end(); ++it) {
        *image += std::to_string((it->second)->payload->id);
        *image += ":";
        *image += std::to_string((it->second)->payload->pri);
        *image += ":";
        *image += (it->second)->payload->desc;
        *image += ";\n";
    }
    return image;
}

void SimpleFileFormat::deserialize(std::string& image, TaskMap& tmap)
{
    std::shared_ptr<Task> t;
    std::string line;

    int s=0;
    int e=0;
    int len=0;
    while ( (e = image.find(";", s)) != std::string::npos) {
        len = e - s;
        line = image.substr(s, len);

        t = deserialize_line(line); //XXX
        tmap.insert(std::pair<std::string, std::shared_ptr<Task>>(t->payload->desc, t));

        s = e + strlen(";\n");
    }
}

std::shared_ptr<Task> SimpleFileFormat::deserialize_line(std::string& line)
{
    int s=0;
    int e=0;
    char buf[50];
    std::shared_ptr<Task> t(new Task);

    e = line.find(":", s);
    strcpy(buf, line.substr(s, e).c_str());
    sscanf(buf, "%d", &t->payload->id);
    s = e + 1;

    e = line.find(":", s);
    strcpy(buf, line.substr(s, e).c_str());
    sscanf(buf, "%d", &t->payload->pri);
    s = e + 1;

    /*
    e = line.find(":", s);
    payload.type = static_cast<TaskType>(std::stoi(line.substr(s, e)));
    s = e + 1;
    */

    e = line.find(":", s);
    t->payload->desc = line.substr(s, e);
    s = e + 1;

    return t;
}

