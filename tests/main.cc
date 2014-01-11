#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE todopro

#include <boost/test/auto_unit_test.hpp>
#include "../src/task.h"
#include "../src/taskmanager.h"
#include "../src/todopro.h"
#include "../src/poparser.h"
#include "../src/datastore.h"
#include "../src/taskview.h"

#include "simplefileformat.test.cc"
#include "taskmanager.test.cc"
#include "datastore.test.cc"
#include "task.test.cc"

struct MyFixture {
    MyFixture()
        : tdp(new ToDoPro)
    {
        BOOST_TEST_MESSAGE("setup fixture");
    }
    ~MyFixture()
    {
        BOOST_TEST_MESSAGE("teardown fixture");
        delete tdp;
    }
    ToDoPro* tdp;
};

BOOST_AUTO_TEST_SUITE(example_must)

BOOST_AUTO_TEST_CASE(File_saving)
{
    std::shared_ptr<Task> t(new Task);
    t->payload->id = 1;
    t->payload->pri = 3;
    t->payload->desc = "Very important task";
    TaskVec tvec;
    tvec.push_back(t);
    BOOST_CHECK_EQUAL(tvec.size(), 1);
    DataStore<SimpleFileFormat> dstore;
    dstore.save("test.db", tvec);
    TaskVec tinvec;
    dstore.load("test.db", tinvec);
    BOOST_CHECK_EQUAL(tinvec.size(), 1);
}

BOOST_AUTO_TEST_CASE_EXPECTED_FAILURES(failure_test, 2)

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Cli_view_test)

BOOST_FIXTURE_TEST_CASE(test_with_fixture, MyFixture)
{
    BOOST_CHECK(tdp);
    const char* av[] = {"tdp", "dupa jasio"};
    POParser vm(2, av);
    BOOST_CHECK_EQUAL(tdp->exec(2, av), 0);
}


BOOST_FIXTURE_TEST_CASE(single_task_view, MyFixture)
{
    std::shared_ptr<Task> t = tdp->taskmanager->create("test task");
    tdp->view->showTask(t);
    tdp->view->showTask(t.get());
}

BOOST_AUTO_TEST_SUITE_END()

