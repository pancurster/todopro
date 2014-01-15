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
#include "../src/sff.h"

#include "simplefileformat.test.cc"
#include "taskmanager.test.cc"
#include "datastore.test.cc"
#include "task.test.cc"
#include "userinput.test.cc"

struct MyFixture {
    MyFixture()
        : tdp(new ToDoPro)
        , TEST_DB_NAME("test.db")
    {
        BOOST_TEST_MESSAGE("setup fixture");
    }
    ~MyFixture()
    {
        BOOST_TEST_MESSAGE("teardown fixture");
        delete tdp;
    }
    ToDoPro* tdp;
    const std::string TEST_DB_NAME;
};

BOOST_AUTO_TEST_SUITE(example_must)
BOOST_FIXTURE_TEST_CASE(File_saving, MyFixture)
{
    std::shared_ptr<Task> t(new Task);
    t->payload->id = 1;
    t->payload->pri = 3;
    t->payload->type = (Task::TaskType)0;
    t->payload->state = (Task::TaskState)0;
    t->payload->desc = "Very important task";
    TaskVec tvec;
    tvec.push_back(t);
    BOOST_CHECK_EQUAL(tvec.size(), 1);

    DataStore<SimpleFileFormat> dstore(TEST_DB_NAME);
    dstore.save(tvec);

    std::ifstream f(TEST_DB_NAME, std::ifstream::in);    
    // czy plik istnieje?
    BOOST_CHECK_EQUAL(f.good(), true);
    std::string line;
    std::getline(f, line);
    BOOST_CHECK(line.compare("1:3:0:0:Very important task"));
    f.close();

    TaskVec tinvec;
    bool ret = dstore.load(tinvec);
    BOOST_CHECK(ret);
    BOOST_CHECK_EQUAL(tinvec.size(), 1);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Cli_view_test)
BOOST_FIXTURE_TEST_CASE(test_with_fixture, MyFixture)
{
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

