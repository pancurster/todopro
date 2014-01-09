#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE todopro

#include <boost/test/auto_unit_test.hpp>
#include "../src/task.h"
#include "../src/taskmanager.h"
#include "../src/todopro.h"
#include "../src/poparser.h"
#include "../src/datastore.h"

/*
 * BOOST_CHECK( add( 2,2 ) == 4 );        // #1 continues on error
 * BOOST_REQUIRE( add( 2,2 ) == 4 );      // #2 throws on error
 *  if( add( 2,2 ) != 4 )
 *      BOOST_ERROR( "Ouch..." );          // #3 continues on error
 *  if( add( 2,2 ) != 4 )
 *      BOOST_FAIL( "Ouch..." );           // #4 throws on error
 */
struct MyFixture {
    MyFixture()
        : tdp(new ToDoPro)
    {
        BOOST_TEST_MESSAGE("setup fixture");
    }
    ~MyFixture()
    {
        BOOST_TEST_MESSAGE("teardown fixture");
    }
    ToDoPro* tdp;
};

struct TaskFixture {
    TaskFixture()
        : t1(new Task)
    {
        BOOST_TEST_MESSAGE("setup TaskFixture");

        t1->payload->id  = 1;
        t1->payload->pri = 1;
        t1->payload->type = TT_TASK;
        t1->payload->desc = "Very important task";
    };

    ~TaskFixture() {
        BOOST_TEST_MESSAGE("cleaning TaskFixture");
        delete t1;
    };

    Task* t1;
};

BOOST_AUTO_TEST_SUITE(example_must);

BOOST_AUTO_TEST_CASE(Task_object)
{
    Task t;
    BOOST_CHECK_EQUAL(t.payload->id, -1);
    BOOST_CHECK_EQUAL(t.payload->pri, -1);
    BOOST_CHECK_EQUAL(t.payload->type, TT_OTHER);
    BOOST_CHECK_EQUAL(t.payload->desc, "");
    BOOST_CHECK_EQUAL(t.payload->recurent_task.size(), 0);
}

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

BOOST_AUTO_TEST_CASE(failure_test)
{
    BOOST_CHECK_EQUAL(sizeof(int), sizeof(char));
    BOOST_CHECK_EQUAL(sizeof(int), sizeof(long long));
}

BOOST_FIXTURE_TEST_CASE(test_with_fixture, MyFixture)
{
    BOOST_CHECK(tdp);
    char* av[] = {"tdp", "dupa jasio"};
    POParser vm(2, av);
    BOOST_CHECK_EQUAL(tdp->exec(2, av), 0);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(Task_Class_Test)
BOOST_FIXTURE_TEST_CASE(Task_Test, TaskFixture)
{
    BOOST_CHECK_EQUAL(t1->payload->id, 1);
    t1->payload->id = 2;
    BOOST_CHECK_EQUAL(t1->payload->id, 2);
}
BOOST_AUTO_TEST_SUITE_END()

