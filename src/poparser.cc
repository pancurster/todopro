#include "poparser.h"

#include <boost/program_options.hpp>

POParser::POParser(int ac, char* av[])
    : main_desc("Usage: tdp [options]\nOptions") // TODO must be here?
{
    parse_program_options(ac, av);
}

POParser::~POParser()
{
}

/*
 * All HARD WORK is here.
 */
void POParser::parse_program_options(int ac, char* av[])
{
    namespace po = boost::program_options;

    // Positional options is option without 'dash something'(-something).
    // So we chose what option will be positional.
    po::positional_options_description p;
    p.add("desc", -1);

    // Adding posible options.
    // First string in pair is a option name. After ',' comes short name.
    // Second string is option description. We use this description in help.
    main_desc.add_options()
        ("help,h",  "help msg")
        ("add,a",   "add task")
        ("pri,p",   "set priority")
        ("task,t",  "add task [default]")
        ("note,n",  "add note")
        ("dead,d",  "set deadline")
        ("desc,s",  "set description [default no parameter flag]")
        ;

    // TODO passing *this to base type method is ok?
    po::store(po::command_line_parser(ac, av).
                options(main_desc).
                positional(p).
                run(), *this);

    po::notify(*this);
}

