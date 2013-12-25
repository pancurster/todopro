#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE todopro

#include <boost/test/auto_unit_test.hpp>
#include "../src/task.h"

BOOST_AUTO_TEST_SUITE(example_must);

BOOST_AUTO_TEST_CASE(Task_object)
{
    Task t;
    BOOST_CHECK_EQUAL(t.id, -1);
    BOOST_CHECK_EQUAL(t.priority, -1);
    BOOST_CHECK_EQUAL(t.type, OTHER);
    BOOST_CHECK_EQUAL(t.description, "");
    BOOST_CHECK_EQUAL(t.recurent_task.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

