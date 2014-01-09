#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE todopro

#include <boost/test/auto_unit_test.hpp>
#include "../src/taskmanager.h"
#include "../src/serializer.h"
#include "../src/task.h"
#include "fixtures/taskfixture.h"
#include <string>

BOOST_AUTO_TEST_SUITE(SimpleFileFormat_Test)

BOOST_FIXTURE_TEST_CASE(serialize_deserialize, TaskFixture)
{
    // przygotowanie testu i serializacja...
    SimpleFileFormat sff;
    TaskVec tvec;
    tvec.push_back(sptask);
    std::string ser = sff.serialize(tvec);

    // i teraz deserializacja...
    TaskVec in_tvec;
    sff.deserialize(ser, in_tvec);
    std::shared_ptr<Task> at = in_tvec[0];

    // i sprawdzanie...
    BOOST_CHECK_EQUAL(at->payload->id, sptask->payload->id);
    BOOST_CHECK_EQUAL(at->payload->pri, sptask->payload->pri);
    BOOST_CHECK_EQUAL(at->payload->type, sptask->payload->type);
    BOOST_CHECK_EQUAL(at->payload->desc, sptask->payload->desc);
    BOOST_CHECK_EQUAL(at->payload->state, sptask->payload->state);
}

BOOST_FIXTURE_TEST_CASE(corrupted_file_deserialize, TaskFixture)
{
    // Zaden z przykladow uszkodzonych taskow nie powinien
    // byc dodany do vec
    TaskVec vec;
    SimpleFileFormat sff;
    std::string corr_file = "";
    int i = sff.deserialize(corr_file, vec);
    BOOST_CHECK_EQUAL(i, 0);

    corr_file = "1;";
    i = sff.deserialize(corr_file, vec);
    BOOST_CHECK_EQUAL(i, 0);

    corr_file = "1:;";
    i = sff.deserialize(corr_file, vec);
    BOOST_CHECK_EQUAL(i, 0);

    corr_file = "1:22;";
    i = sff.deserialize(corr_file, vec);
    BOOST_CHECK_EQUAL(i, 0);

    corr_file = "1:22:;";
    i = sff.deserialize(corr_file, vec);
    BOOST_CHECK_EQUAL(i, 0);

    corr_file = "1:22:33:;";
    i = sff.deserialize(corr_file, vec);
    BOOST_CHECK_EQUAL(i, 0);

    corr_file = "1:22:33:44:;";
    i = sff.deserialize(corr_file, vec);
    BOOST_CHECK_EQUAL(i, 0);

    corr_file = "1;";
    i = sff.deserialize(corr_file, vec);
    BOOST_CHECK_EQUAL(i, 0);

    corr_file = "dupa jasio";
    i = sff.deserialize(corr_file, vec);
    BOOST_CHECK_EQUAL(i, 0);
}

BOOST_AUTO_TEST_SUITE_END()

