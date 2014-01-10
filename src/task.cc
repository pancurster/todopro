#include "task.h"
#include "serializer.h"

#include <memory>

Task::Task()
    : payload(new TaskPayload)
{
    payload->id     = NOT_PROPER_ID;
    payload->pri    = NOT_PROPER_PRI;
    payload->type   = TT_OTHER;
    payload->desc   = "";
    payload->state  = STATE_NOT_SET;
}

Task::~Task()
{
    delete payload;
}

