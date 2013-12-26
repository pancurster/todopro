#ifndef __SERIALIZER_H__
#define __SERIALIZER_H__

#include <string>
#include <vector>

class Task;

class SerDes {
public:
    SerDes(const std::string filename, const std::vector<Task*> &tl) {};
    virtual ~SerDes() {};
    virtual void serialize() = 0;
    virtual void deserialize() = 0;
};

class SimpleFileFormat : public SerDes {
public:
    SimpleFileFormat (const std::string, std::vector<Task*> &);
    ~SimpleFileFormat();
    void serialize();
    void deserialize();
private:
    std::vector<Task*> & task_container;
    std::string filename;
};

class JSONFileFormat : public SerDes {
};

class iCalendarFileFormat : public SerDes {
};

#endif //__SERIALIZER_H__

