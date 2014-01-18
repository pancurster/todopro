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
#include "../src/style.h"

#include "todopro.test.cc"
#include "simplefileformat.test.cc"
#include "taskmanager.test.cc"
#include "datastore.test.cc"
#include "task.test.cc"
#include "userinput.test.cc"

