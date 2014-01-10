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
        delete tm;
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

BOOST_AUTO_TEST_SUITE(TaskManager_test)

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
    BOOST_CHECK_EQUAL(t->payload->state, Task::STATE_NOT_SET);
    tm->done(t);
    BOOST_CHECK_EQUAL(t->payload->state, Task::STATE_DONE);
}

BOOST_FIXTURE_TEST_CASE(task_erase, TaskManagerFixture)
{
    std::shared_ptr<Task> t = addOneTask("test erase");
    BOOST_CHECK_EQUAL(tm->taskmain.size(), 1);
    tm->del(t);
    BOOST_CHECK_EQUAL(tm->taskmain.size(), 0);
}

BOOST_FIXTURE_TEST_CASE(task_find_by_id, TaskManagerFixture)
{
    Task* t = addOneTask("test findById").get();
    t->payload->id = 666;
    Task* tt = tm->findById(t->payload->id).get();
    BOOST_CHECK_EQUAL(t, tt);
    tt = tm->findById(555).get();
    //BOOST_CHECK_EQUAL(tt.get(), static_cast<Task*>(0));

    // parametr str
    tt = tm->findById("666").get();
    BOOST_CHECK_EQUAL(t, tt);
    tt = tm->findById("555").get();
    BOOST_CHECK_NE(t, tt);
}

BOOST_FIXTURE_TEST_CASE(task_find_by_desc, TaskManagerFixture)
{
    Task* t = addOneTask("opis").get();
    Task* tt = tm->findByDesc("opis").get();
    BOOST_CHECK_EQUAL(t, tt);
    tt=0;
    tt = tm->findByDesc("zlooo").get();
    BOOST_CHECK_NE(t, tt);
    tt=0;
}
BOOST_FIXTURE_TEST_CASE(task_find_by_desc_partial, TaskManagerFixture)
{
    Task* t = addOneTask("opis").get();
    Task* tt = tm->findByDescPartial("op").get();
    BOOST_CHECK_EQUAL(t, tt);
    tt=0;
    tt = tm->findByDescPartial("zl").get();
    BOOST_CHECK_NE(t, tt);
    tt=0;
}

BOOST_FIXTURE_TEST_CASE(TaskManager_select, TaskManagerFixture)
{
    Task* const t = addOneTask("test select").get();
    t->payload->id = 666;

    // select po ID
    Task* tt = tm->select("666").get();
    BOOST_CHECK_EQUAL(t, tt);
    tt = tm->select("444").get();
    BOOST_CHECK_NE(t, tt);

    // by desc (cale)
    tt = tm->select("test select").get();
    BOOST_CHECK_EQUAL(t, tt);
    tt = tm->select("nono").get();
    BOOST_CHECK_NE(t, tt);

    // by desc part
    tt = tm->select("sel").get();
    BOOST_CHECK_EQUAL(t, tt);
    tt = tm->select("china").get();
    BOOST_CHECK_NE(t, tt);
}

BOOST_AUTO_TEST_SUITE_END()

