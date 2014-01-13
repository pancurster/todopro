#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "taskmanager.h"
#include <string>

/*
 * Common interface for serialization.
 */
class FileFormatInterface {
public:
    virtual ~FileFormatInterface() {}
    
    // Przekazujemy kontener taskow bo byc moze format pliku
    // potrzebowal bedzie calego zestawu taskow przy serializacji,
    // np. wypisanie na poczatku liczby wszystkich taskow itp.
    // @ret: serialized tasks
    virtual std::string serialize(const TaskVec&) = 0;

    // @ret: num of parsed tasks
    virtual int deserialize(std::string&, TaskVec&) = 0;
};

#endif //SERIALIZER_H

