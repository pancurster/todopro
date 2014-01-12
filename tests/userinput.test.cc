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
    void add_task(std::string desc)
    {
        std::shared_ptr<Task> t = tm->createEmptyTask();
        t->payload->desc = desc;
        tm->add(t);
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

BOOST_FIXTURE_TEST_CASE(help, UserInputFixture)
{
    const char* av[] = {"test", "-h"};
    ui->commands(2, av);
}

BOOST_FIXTURE_TEST_CASE(select, UserInputFixture)
{
    // Expected failure
    const char* av[] = {"t", "-s"};
    ui->commands(2, av);

    // No exist
    const char* av2[] = {"t", "-s", "Bocian"};
    ui->commands(3, av2);

    add_task("Bocian");
    
    // Now ok.
    ui->commands(3, av2);
}

BOOST_FIXTURE_TEST_CASE(new_command, UserInputFixture)
{
    const char* av[] = {"t", "-n", "Zaba"};
    ui->commands(3, av);
    std::shared_ptr<Task> t = tm->findByDesc("Zaba");
    BOOST_CHECK(t);
}

BOOST_FIXTURE_TEST_CASE(priority, UserInputFixture)
{
    // Expected only show
    const char* av[] = {"t", "-p", "2"};
    ui->commands(3, av);

    add_task("Zlota Rybka");
    const char* av2[] = {"t", "-s", "Zlota", "-p", "2"};
    ui->commands(5, av2);
    std::shared_ptr<Task> t = tm->findByDescPartial("Rybka");
    BOOST_CHECK(t);
}

BOOST_FIXTURE_TEST_CASE(description, UserInputFixture)
{
    add_task("Zlota");
    const char* av[] = {"t", "-s", "Zlota", "--desc", "\"Srebrna foka\""};
    bool ret = ui->commands(5, av);
    BOOST_CHECK(ret);
}

BOOST_FIXTURE_TEST_CASE(remove, UserInputFixture)
{
    add_task("Pingwin");
    const char* av[] = {"t", "-s", "Ping", "-r"};
    bool ret = ui->commands(4, av);
    BOOST_CHECK(ret);
}

BOOST_FIXTURE_TEST_CASE(done, UserInputFixture)
{
    add_task("Wielblad");
    const char* av[] = {"t", "-s", "Wiel", "-d"};
    bool ret = ui->commands(4, av);
    BOOST_REQUIRE(ret);
    std::shared_ptr<Task> t = tm->findByDescPartial("Wiel");
    BOOST_CHECK(t);
    BOOST_CHECK_EQUAL(t->payload->state, Task::STATE_DONE);
}

BOOST_AUTO_TEST_SUITE_END()
