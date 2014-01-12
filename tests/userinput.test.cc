#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE todopro

#include <boost/test/auto_unit_test.hpp>
#include "../src/taskmanager.h"
#include "../src/taskview.h"
#include "../src/userinput.h"

// Czy i jak testowac CLI?

struct UserInputFixture {
    UserInputFixture()
        : tm(new TaskManager)
        , tv(new CliView)
        , ui(new UserInput(*tm, *tv))
    {
    }
    ~UserInputFixture()
    {
        delete ui;
        delete tv;
        delete tm;
    }
    TaskManager*    tm;
    TaskView*       tv;
    UserInput*      ui;
};

BOOST_AUTO_TEST_SUITE(User_Input)

BOOST_FIXTURE_TEST_CASE(version, UserInputFixture)
{
    const char* av[] = {"test", "-v"};
    ui->commands(2, av);
}

BOOST_AUTO_TEST_SUITE_END()
