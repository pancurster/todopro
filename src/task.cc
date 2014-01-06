#include "task.h"
#include "serializer.h"

#include <memory>

Task::Task()
    : payload(new TaskPayload)
{
    payload->id     = -1;
    payload->pri    = -1;
    payload->type   = TT_OTHER;
    payload->desc   = "";
    payload->state  = TS_NOSTATE;
}

Task::~Task()
{
    delete payload;
}

