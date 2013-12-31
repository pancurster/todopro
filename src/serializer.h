#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <string>
#include <vector>

#include "task.h"

class Task;
struct info_t;

/*
 * TODO: 1) Common interface for serialization.
 *       2) Serialization Object must be part of Task Object or maybe
 *          Task Objec must inherit Serialization Interface as Behavior?
 *       3) What if we need more than one serialization method in runtime?
 *          a) How invoke correct serialization method in different
 *          runs or even, on same run more than one method of serialization?
 *          Proposition: The concrete serialization object must bother this
 *                       for sure. The problem is how to control all tasks
 *                       behavior from one place. I think it will clarify
 *                       in coding time.
 *          b) How to handle diff. ser. in one Task Object?
 *          Proposition: by asigning concrete behavior implementations
 *                       to behavior object in Task class.
 *       4) Is SerDes must be pure Interface class? Or maybe it have some
 *          common methods?
 *       5) For sure each Task need to know how to serialize it self.
 *          So acumulating serialized Tasks and saving them to file must be
 *          done in master object (TaskManager?).
 */
class SerDes {
public:
    SerDes() {};
    virtual ~SerDes() {};
    virtual std::shared_ptr<std::string> serialize(TaskMap&) = 0;
    virtual TaskVec& deserialize(std::string) = 0;
};

/*
 * File format is like *nix /etc/passwd file format.
 */
class SimpleFileFormat : public SerDes {
public:
    SimpleFileFormat ();
    ~SimpleFileFormat();
    std::shared_ptr<std::string> serialize(TaskMap&);
    TaskVec& deserialize(std::string);
private:
};

class JSONFileFormat : public SerDes {
};

class iCalendarFileFormat : public SerDes {
};

#endif //SERIALIZER_H

