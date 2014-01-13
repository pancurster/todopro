#ifndef SIMPLE_FILE_FORMAT_H
#define SIMPLE_FILE_FORMAT_H

#include "serializer.h"
#include "taskmanager.h"
#include <string>

class FileFormatInterface;
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

#endif // SIMPLE_FILE_FORMAT_H

