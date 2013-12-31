#include <memory>

#include "task.h"
#include "serializer.h"

Task::Task()
    : serdes(new SimpleFileFormat)
    /*
    : info.id(-1)
    , info.pri(-1)
    , info.type(TT_OTHER)
    , info.desc("")
    */
{
    // TODO Czy da sie to jakos lepiej zrobic?
    info.id     =-1;
    info.pri    =-1;
    info.type   =TT_OTHER;
    info.desc   ="";
}

Task::~Task()
{

}

