#ifndef DATASTORE_H
#define DATASTORE_H

#include <string>
#include <fstream>

#include "serializer.h"
#include "task.h"

template <class T>
class DataStore {
public:
    DataStore()
        : serdes(new T)
    {
    }

    ~DataStore() {};

    bool save(std::string filename, TaskMap& task_container)
    {
        std::shared_ptr<std::string> serout = serdes->serialize(task_container);
        save_to_file(filename, *serout);
        return true; //TODO
    }

    bool load()
    {
    }

    bool export_data()
    {
    }

private:
    bool save_to_file(std::string filename, std::string in_buff)
    {
        std::ofstream file;
        file.open(filename, std::ofstream::out);
        file.write(in_buff.c_str(), in_buff.size());
        file.close();
        return file.fail();
    }

    std::shared_ptr<SerDes> serdes;
};

#endif //DATASTORE_H

