#ifndef DATASTORE_H
#define DATASTORE_H

#include <string>
#include <fstream>

#include "serializer.h"
#include "task.h"


template <class T>
class DataStore {
public:
    DataStore();
    ~DataStore();

    bool save(const std::string& filename, TaskVec& task_container);
    bool load(const std::string& filename, TaskVec& task_container);
    FileFormatInterface* getFFObj();
    FileFormatInterface* setFFObj(FileFormatInterface* f);

private:
    bool save_to_file(const std::string& filename, std::string in_buff);
    bool read_from_file(const std::string& filename, std::string& image);

    FileFormatInterface* file_format;
};

template <class T>
DataStore<T>::DataStore()
    : file_format(new T) { }


template <class T>
DataStore<T>::~DataStore()
{
    delete file_format;
}


template <class T>
bool DataStore<T>::save(const std::string& filename, TaskVec& task_container)
{
    std::string serout = file_format->serialize(task_container);
    save_to_file(filename, serout);
    return true; //TODO
}


template <class T>
bool DataStore<T>::load(const std::string& filename, TaskVec& task_container)
{
    std::string image;

    read_from_file(filename, image);
    file_format->deserialize(image, task_container);
    return true; //TODO
}

template <class T>
FileFormatInterface* DataStore<T>::getFFObj()
{
    return file_format;
}

template <class T>
FileFormatInterface* DataStore<T>::setFFObj(FileFormatInterface* f)
{
    delete file_format;
    file_format = f;
    return file_format;
}


template <class T>
bool DataStore<T>::save_to_file(const std::string& filename, std::string in_buff)
{
    std::ofstream file;
    file.open(filename, std::ofstream::out);
    file.write(in_buff.c_str(), in_buff.size());
    file.close();
    return file.fail();
}


template <class T>
bool DataStore<T>::read_from_file(const std::string& filename, std::string& image)
{
    std::ifstream file;
    file.open(filename, std::ifstream::in);
    if (!file.good()) {
        std::cout << "No file\n";
        image = "";
        return true;
    }
    file.seekg(0, file.end);
    int len = file.tellg();
    file.seekg(0, file.beg);
    char* buf = new char[len+1];
    file.read(buf, len);
    file.close();
    image = buf;
    delete[] buf;
    return true;
}

#endif //DATASTORE_H

