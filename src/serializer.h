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
    virtual std::shared_ptr<std::string> serialize(TaskVec&) = 0;
    virtual void deserialize(std::string&, TaskVec&) = 0;
};

/*
 * File format like *nix /etc/passwd.
 */
class SimpleFileFormat : public FileFormatInterface {
public:
    SimpleFileFormat ();
    ~SimpleFileFormat();
    std::shared_ptr<std::string> serialize(TaskVec&);
    void deserialize(std::string&, TaskVec&);
private:
    std::shared_ptr<Task> deserialize_line(std::string& line);
};

class JSONFileFormat : public FileFormatInterface {
};

class iCalendarFileFormat : public FileFormatInterface {
};

#endif //SERIALIZER_H

