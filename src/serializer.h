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
    
    // Przekazujemy kontener taskow bo byc moze format pliku
    // potrzebowal bedzie calego zestawu taskow przy serializacji,
    // np. wypisanie na poczatku liczby wszystkich taskow itp.
    // @ret: serialized tasks
    virtual std::string serialize(const TaskVec&) = 0;

    // @ret: task parsed
    virtual int deserialize(std::string&, TaskVec&) = 0;
};

/*
 * File format like *nix /etc/passwd.
 */
class SimpleFileFormat : public FileFormatInterface {
public:
    SimpleFileFormat ();
    ~SimpleFileFormat();
    std::string serialize(const TaskVec&);
    int deserialize(std::string&, TaskVec&);
private:
    // @ret: sp to deserialized task, 0 - in case of error
    std::shared_ptr<Task> deserialize_single_task(std::string& line);
};

class JSONFileFormat : public FileFormatInterface {
};

class iCalendarFileFormat : public FileFormatInterface {
};

#endif //SERIALIZER_H

