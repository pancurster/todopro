#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE todopro

#include <boost/test/auto_unit_test.hpp>
#include "../src/taskmanager.h"
#include <string>

struct TaskManagerFixture {
    TaskManagerFixture()
        : tm(new TaskManager)
    {
        BOOST_TEST_MESSAGE("setup taskmanager fixture");
    }
    ~TaskManagerFixture()
    {
        BOOST_TEST_MESSAGE("teardown taskmanager fixture");
    }
    std::shared_ptr<Task> addOneTask(std::string desc)
    {
        std::shared_ptr<Task> task = tm->createEmptyTask();
        task->payload->desc = desc;
        tm->add(task);
        return task;
    }
    TaskManager* tm;
};

BOOST_AUTO_TEST_SUITE(TaskManager_test);

BOOST_FIXTURE_TEST_CASE(get_highest_task_id, TaskManagerFixture)
{
    std::shared_ptr<Task> task = tm->createEmptyTask();
    BOOST_CHECK_EQUAL(task->payload->id, 0);
    task->payload->desc = "desc1";
    tm->add(task);
    BOOST_CHECK_EQUAL(task->payload->id, 1);
    std::shared_ptr<Task> task2 = tm->createEmptyTask();
    task2->payload->desc = "desc2";
    tm->add(task2);
    BOOST_CHECK_EQUAL(task2->payload->id, 2);
}

BOOST_FIXTURE_TEST_CASE(task_done, TaskManagerFixture)
{
    std::shared_ptr<Task> t = addOneTask("test done");
    BOOST_CHECK_EQUAL(t->payload->state, TS_NOSTATE);
    tm->done(t);
    BOOST_CHECK_EQUAL(t->payload->state, TS_DONE);
}

BOOST_AUTO_TEST_SUITE_END()

