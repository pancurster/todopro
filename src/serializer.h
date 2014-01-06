#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "taskmanager.h"
#include <string>
#include <vector>

class Task;

/*
 * Common interface for serialization.
 */
class FileFormatInterface {
public:
    virtual ~FileFormatInterface() {};
    virtual std::shared_ptr<std::string> serialize(TaskMap&) = 0;
    virtual void deserialize(std::string&, TaskMap&) = 0;
};

/*
 * File format like *nix /etc/passwd.
 */
class SimpleFileFormat : public FileFormatInterface {
public:
    SimpleFileFormat ();
    ~SimpleFileFormat();
    std::shared_ptr<std::string> serialize(TaskMap&);
    void deserialize(std::string&, TaskMap&);
private:
    std::shared_ptr<Task> deserialize_line(std::string& line);
};

class JSONFileFormat : public FileFormatInterface {
};

class iCalendarFileFormat : public FileFormatInterface {
};

#endif //SERIALIZER_H

