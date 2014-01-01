#include <memory>

#include "task.h"
#include "serializer.h"

Task::Task()
    : payload(new TaskPayload)
{
    payload->id     = -1;
    payload->pri    = -1;
    payload->type   = TT_OTHER;
    payload->desc   = "";
}

Task::~Task()
{

}

