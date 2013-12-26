#include <fstream>
#include <string>
#include <bits/basic_string.h>

#include "task.h"
#include "serializer.h"

SimpleFileFormat::SimpleFileFormat(const std::string filename,
                                   std::vector<Task*> &tl)
    : SerDes(filename, tl)
    , filename(filename)
    , task_container(tl)
{
}

SimpleFileFormat::~SimpleFileFormat()
{

}

void SimpleFileFormat::serialize()
{
    std::ofstream file;
    file.open(filename.c_str(), std::ifstream::out);
    for (std::vector<Task*>::const_iterator i = task_container.begin();
         i != task_container.end();
         i++)
    {
        file << (*i)->id << ":"
             << (*i)->pri << ":"
             << (*i)->desc << ";"
             << "\n";
    }
    file.close();
}

void SimpleFileFormat::deserialize()
{
    int s=0;
    int e=0;
    Task* t;
    std::string buf="";
    std::string token="";
    std::ifstream file;
    file.open(filename.c_str(), std::ifstream::in);

    while (std::getline(file, buf)) {
        t = new Task;

        e = buf.find(":", s);
        t->id = std::stoi(buf.substr(s, e));
        s = e + 1;

        e = buf.find(":", s);
        t->pri = std::stoi(buf.substr(s, e));
        s = e + 1;

        e = buf.find(":", s);
        t->type = static_cast<task_type>(std::stoi(buf.substr(s, e)));
        s = e + 1;

        e = buf.find(":", s);
        t->desc = buf.substr(s, e);
        s = e + 1;

        task_container.push_back(t);
    }
}

