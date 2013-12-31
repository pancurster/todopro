#include <fstream>
#include <string>
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
        *image += (it->second)->info.id;
        *image += ":";
        *image += (it->second)->info.pri;
        *image += ":";
        *image += (it->second)->info.desc;
        *image += ";\n";
    }
    return image;
}

TaskVec& SimpleFileFormat::deserialize(std::string image)
{
#if 0
    int s=0;
    int e=0;
    info_t info;

    e = image.find(":", s);
    info.id = std::stoi(image.substr(s, e));
    s = e + 1;

    e = image.find(":", s);
    info.pri = std::stoi(image.substr(s, e));
    s = e + 1;

    e = image.find(":", s);
    info.type = static_cast<TaskType>(std::stoi(image.substr(s, e)));
    s = e + 1;

    e = image.find(":", s);
    info.desc = image.substr(s, e);
    s = e + 1;

    return info;
#endif
}

