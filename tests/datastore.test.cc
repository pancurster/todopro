#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE todopro

#include <boost/test/auto_unit_test.hpp>
#include <string>
#include <fstream>
#include "../src/serializer.h"
#include "../src/task.h"
#include "../src/taskmanager.h"

struct FakeFileFormat : public FileFormatInterface {
    FakeFileFormat()
    {
    }
    std::string serialize(const TaskVec&)
    {
        return s;
    }
    int deserialize(std::string&, TaskVec&)
    {
    }
    std::string s;
};

BOOST_AUTO_TEST_SUITE(Datastore_Test);

BOOST_AUTO_TEST_CASE(function_save)
{
    DataStore<FakeFileFormat> saver;
    // Fakeujemy to co wyplowa serializer
    std::string dupajasia = "Dupa Jasia";
    FakeFileFormat* const fff = dynamic_cast<FakeFileFormat*>(saver.getFFObj());
    fff->s = dupajasia;

    // zapis do pliku
    TaskVec fakeVec;    // fakeowy kontener
    const std::string filename = "test_dupajasia.db";
    bool ret = saver.save(filename, fakeVec);
    BOOST_CHECK_EQUAL(ret, true);

    // sprawdzanie niezaleznymi funkcjami zawartosci pliku
    std::ifstream file;
    file.open(filename, std::ifstream::in);
    BOOST_CHECK_EQUAL(file.good(), true);
    char buf[100];
    memset(buf, 0, 100);
    // + 10 bo moze zapisaly sie jakies smieci?
    file.read(buf, dupajasia.size() + 1 + 10);
    BOOST_CHECK_EQUAL(dupajasia.compare(buf), 0);
    file.close();
}

BOOST_AUTO_TEST_SUITE_END()

