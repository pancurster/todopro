#include "poparser.h"

#include <boost/program_options.hpp>

POParser::POParser(int ac, char* av[])
    : main_desc("Usage: tdp [options]\nOptions") // TODO this must be here?
{
    parse_program_options(ac, av);
}

POParser::~POParser()
{
}

void POParser::parse_program_options(int ac, char* av[])
{
    namespace po = boost::program_options;

    main_desc.add_options()
        ("help,h",  "help msg")
        ("add,a",   "add task")
        ("pri,p",   "set priority")
        ("task,t",  "add task [default]")
        ("note,n",  "add note")
        ("dead,d",  "set deadline")
        ;
    // XXX passing *this to base type method is ok?
    po::store(po::parse_command_line(ac, av, main_desc), *this);
    po::notify(*this);
}

