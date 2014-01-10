#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE todopro

#include <boost/test/auto_unit_test.hpp>
#include "../src/task.h"
#include <type_traits>

BOOST_AUTO_TEST_SUITE(Task_module_test);

BOOST_AUTO_TEST_CASE(Task_initialization)
{
    Task t;
    BOOST_CHECK_EQUAL(t.payload->id, Task::NOT_PROPER_ID);
    BOOST_CHECK_EQUAL(t.payload->pri, Task::NOT_PROPER_PRI);
    BOOST_CHECK_EQUAL(t.payload->type, Task::TT_OTHER);
    BOOST_CHECK_EQUAL(t.payload->desc.compare(""), 0);
    BOOST_CHECK_EQUAL(t.payload->state, Task::STATE_NOT_SET);
}

BOOST_AUTO_TEST_CASE(Task_no_copy_allowed)
{
    /*
    static_assert(std::is_copy_constructible<Task>::value == true,
            "Copy constructor not implemented");
    */
}

BOOST_AUTO_TEST_SUITE_END()

