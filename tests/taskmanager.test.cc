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
    // Task added with description like: "'pattern'[num]"
    void addManyTasks(int howmany, std::string pattern)
    {
        std::stringstream tname;
        for (int i=0; i<howmany; ++i) {
            tname.str("");
            tname << pattern << i;
            addOneTask(tname.str());
        }
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

BOOST_FIXTURE_TEST_CASE(task_add, TaskManagerFixture)
{
    std::shared_ptr<Task> task = tm->createEmptyTask();
    BOOST_CHECK_EQUAL(tm->add(task), true);
    
    task.reset();
    BOOST_CHECK_EQUAL(tm->add(task), false);
}

BOOST_FIXTURE_TEST_CASE(add_two_tasks, TaskManagerFixture)
{
    std::shared_ptr<Task> task1 = addOneTask("zadanie 1");
    std::shared_ptr<Task> task2 = addOneTask("zadanie 2");

    // sprawdzanie czy dziala inkrementacja id
    BOOST_CHECK_NE(task1->payload->id, task2->payload->id);

}

BOOST_FIXTURE_TEST_CASE(add_many_more_task, TaskManagerFixture)
{
    int TASK_NUM = 10;

    addManyTasks(TASK_NUM, std::string("task nr: "));
    BOOST_CHECK_EQUAL(tm->taskmain.size(), TASK_NUM);

    // Check: they exist and we can fetch them
    std::shared_ptr<Task> t;
    std::stringstream tname;
    for (int i=0; i<TASK_NUM; ++i) {
        tname.str("");
        tname << "task nr: " << i;
        t = tm->findByDesc(tname.str());
        BOOST_CHECK(t.get());
        // Check size of dict AFTER first find query. We synchronize
        // dict to taskVec in lazy scheme - on first query.
        BOOST_CHECK_EQUAL(tm->taskbydesc.size(), TASK_NUM);
    }
}

BOOST_FIXTURE_TEST_CASE(rm_many_tasks, TaskManagerFixture)
{
    int TASK_NUM = 10;

    addManyTasks(TASK_NUM, std::string("task_"));

    std::stringstream tname;
    std::shared_ptr<Task> t;
    for (int i=0; i<TASK_NUM; ++i) {
        tname.str("");
        tname << "task_" << i;
        t = tm->select(tname.str());
        tm->del(t);
    }
    // Everything was removed?
    BOOST_CHECK_EQUAL(tm->taskmain.size(), 0);
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

