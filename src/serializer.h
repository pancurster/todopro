#ifndef __SERIALIZER_H__
#define __SERIALIZER_H__

#include <string>

template <class T>
class Serializer {
public:
    Serializer(const T&) = 0;
    virtual ~Serializer() = 0;
    virtual std::string operator()()= 0;
    virtual std::string getOutput() = 0;
};

template <class T>
class FileSerializer : public Serializer<T> {
public:
    FileSerializer (const T&);
    virtual ~FileSerializer();
    std::string operator()();
    std::string getOutput();
private:
    T task_container;
};

#endif //__SERIALIZER_H__

