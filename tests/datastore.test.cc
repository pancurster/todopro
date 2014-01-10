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
        : s(""), d("")
    {
    }
    std::string serialize(const TaskVec&)
    {
        return s;
    }
    int deserialize(std::string& image, TaskVec&)
    {
        // Nie testuje tutaj metody fileformat->deserialize
        // tylko interfejsy i obiekt typu DataStore.
        // Zastepuje wiec metode deserialize ktora jes wywolywana z wnetrza load
        // fakowa metoda ktora przypisze mi do zmiennej 'd' to co odczytaly
        // mechanizmy DataStore.
        d = image;
    }
    std::string s;
    std::string d;
};

BOOST_AUTO_TEST_SUITE(Datastore_Test)

const std::string dupajasia = "Dupa Jasia";
const std::string filename = "test_dupajasia.db";
TaskVec fakeVec;    // fakeowy kontener
BOOST_AUTO_TEST_CASE(function_save)
{
    DataStore<FakeFileFormat> saver;
    // Fakeujemy to co wyplowa serializer
    FakeFileFormat* const fff = dynamic_cast<FakeFileFormat*>(saver.getFFObj());
    fff->s = dupajasia;

    // zapis do pliku
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

BOOST_AUTO_TEST_CASE(function_load)
{
    // write some testing dato in to file
    std::ofstream file;
    file.open(filename, std::ostream::out);
    BOOST_CHECK_EQUAL(file.good(), true);
    file.write(dupajasia.c_str(), dupajasia.size());
    file.close();

    // check is stdlib file read methods work...
    std::ifstream infile;
    infile.open(filename, std::istream::in);
    char* buf = new char[100];
    memset(buf, 0, 100);
    infile.read(buf, dupajasia.size());
    infile.close();
    BOOST_REQUIRE_EQUAL(dupajasia.compare(buf), 0);

    // if so, test our class loader/reader
    DataStore<FakeFileFormat> loader;
    FakeFileFormat* const fff = dynamic_cast<FakeFileFormat*>(loader.getFFObj());

    // test is our mock value is properly initialized
    BOOST_CHECK_EQUAL(fff->d.compare(""), 0);

    loader.load(filename, fakeVec);

    BOOST_TEST_MESSAGE(fff->d);
    BOOST_CHECK_EQUAL(dupajasia.compare(fff->d), 0);
}

BOOST_AUTO_TEST_SUITE_END()

