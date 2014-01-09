#include "taskfixture.h"
#include "../../src/task.h"
#include <boost/test/auto_unit_test.hpp>
#include <memory>

TaskFixture::TaskFixture()
    : sptask(new Task)
{
    BOOST_TEST_MESSAGE("setup TaskFixture");

    sptask->payload->id  = 666;
    sptask->payload->pri = 777;
    sptask->payload->type = TT_TASK;
    sptask->payload->desc = "Very important task";
    sptask->payload->state = TS_PENDING;
}

TaskFixture::~TaskFixture()
{
    BOOST_TEST_MESSAGE("cleaning TaskFixture");
}

