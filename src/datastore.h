#ifndef DATASTORE_H
#define DATASTORE_H

#include <string>
#include <fstream>

#include "serializer.h"
#include "task.h"

#include <boost/scoped_ptr.hpp>

template <class T>
class DataStore {
public:
    DataStore(const std::string& filename);
    ~DataStore();

    bool save(const TaskVec& task_container) const;
    bool load(TaskVec& task_container) const;
    FileFormatInterface* getFFObj() const;

private:
    bool save_to_file(const std::string& in_buff) const;
    bool read_from_file(std::string& image) const;

    boost::scoped_ptr<FileFormatInterface> file_format;
    std::string m_filename;
};

template <class T>
DataStore<T>::DataStore(const std::string& filename)
    : file_format(new T)
    , m_filename(filename)
{
}


template <class T>
DataStore<T>::~DataStore()
{
}


template <class T>
bool DataStore<T>::save(const TaskVec& task_container) const
{
    std::string serout = file_format->serialize(task_container);
    return save_to_file(serout);
}


template <class T>
bool DataStore<T>::load(TaskVec& task_container) const
{
    std::string image;

    bool ret = read_from_file(image);
    if (!ret)
        return false;

    return file_format->deserialize(image, task_container);
}

template <class T>
inline FileFormatInterface* DataStore<T>::getFFObj() const
{
    return file_format.get();
}


template <class T>
bool DataStore<T>::save_to_file(const std::string& in_buff) const
{
    std::ofstream file(m_filename, std::ofstream::out);
    if (file.fail())
        return false;

    file.write(in_buff.c_str(), in_buff.size());
    file.close();
    return true;
}


template <class T>
bool DataStore<T>::read_from_file(std::string& image) const
{
    std::ifstream file(m_filename, std::ifstream::in);
    if (!file.good()) {
        std::cout << "No task database file\n";
        image = "";
        return true;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    image = buffer.str();

    file.close();
    return true;
}

#endif //DATASTORE_H

