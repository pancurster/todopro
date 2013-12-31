#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE todopro

#include <boost/test/auto_unit_test.hpp>
#include "../src/task.h"
#include "../src/taskmanager.h"
#include "../src/todopro.h"
#include "../src/poparser.h"

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

BOOST_AUTO_TEST_SUITE(example_must);

BOOST_AUTO_TEST_CASE(Task_object)
{
    Task t;
    BOOST_CHECK_EQUAL(t.info.id, -1);
    BOOST_CHECK_EQUAL(t.info.pri, -1);
    BOOST_CHECK_EQUAL(t.info.type, TT_OTHER);
    BOOST_CHECK_EQUAL(t.info.desc, "");
    BOOST_CHECK_EQUAL(t.info.recurent_task.size(), 0);
}

BOOST_AUTO_TEST_CASE(File_saving)
{
    //TaskManager tm;
    //tm.save2file("tasks.db", "Dupadupa");
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

