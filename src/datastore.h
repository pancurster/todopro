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

    bool save(const std::string& filename, const TaskVec& task_container) const;
    bool load(const std::string& filename, TaskVec& task_container) const;
    FileFormatInterface* getFFObj() const;

private:
    bool save_to_file(const std::string& filename, const std::string in_buff) const;
    bool read_from_file(const std::string& filename, std::string& image) const;

    FileFormatInterface* file_format;
};

template <class T>
DataStore<T>::DataStore()
    : file_format(new T)
{
}


template <class T>
DataStore<T>::~DataStore()
{
    delete file_format;
}


template <class T>
bool DataStore<T>::save(const std::string& filename, const TaskVec& task_container) const
{
    std::string serout = file_format->serialize(task_container);
    return save_to_file(filename, serout);
}


template <class T>
bool DataStore<T>::load(const std::string& filename, TaskVec& task_container) const
{
    std::string image;

    bool ret = read_from_file(filename, image);
    if (!ret)
        return false;

    return file_format->deserialize(image, task_container);
}

template <class T>
inline FileFormatInterface* DataStore<T>::getFFObj() const
{
    return file_format;
}


template <class T>
bool DataStore<T>::save_to_file(const std::string& filename, const std::string in_buff) const
{
    std::ofstream file(filename, std::ofstream::out);
    if (file.fail())
        return false;

    file.write(in_buff.c_str(), in_buff.size());
    file.close();
    return true;
}


template <class T>
bool DataStore<T>::read_from_file(const std::string& filename, std::string& image) const
{
    std::ifstream file(filename, std::ifstream::in);
    if (!file.good()) {
        std::cout << "No task database file\n";
        image = "";
        return true;
    }

    // Find how much characters in file
    std::filebuf* pbuf = file.rdbuf();
    std::size_t size = pbuf->pubseekoff(0, file.end, file.in);
    pbuf->pubseekpos(0, file.in);

    // Prepare buffer...
    char* buf = new char[size+1];
    memset(buf, 0, size+1);

    // and read to it
    pbuf->sgetn(buf, size);
    image = buf;

    file.close();
    delete[] buf;
    return true;
}

#endif //DATASTORE_H

