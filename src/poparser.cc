#include "poparser.h"

#include <boost/program_options.hpp>

POParser::POParser(int ac, const char* av[])
    : all("Usage: tdp [options]\nOptions")
    , general_desc("General operations")
    , detailed_desc("Task modify options (require \"select\" option use)")
{
    parse_program_options(ac, av);
}

POParser::~POParser()
{
}

/*
 * All HARD WORK is here.
 */
void POParser::parse_program_options(int ac, const char* av[])
{
    namespace po = boost::program_options;

    // Positional options is option without 'dash something'(-something).
    // So we chose what option will be positional.
    po::positional_options_description p;
    p.add("select", -1);

    // Adding posible options.
    // First string in pair is a option name. After ',' comes short name.
    // Second string is option description. We use this description in help.
    general_desc.add_options()
        ("new,n",       po::value<std::string>(), "add new task [arg - madatory description]")
        ("select,s",    po::value<std::string>(), "select task to modify or show details")
        ("list,l",      po::value<std::string>(), "list task by selected filter")
        ;
    detailed_desc.add_options()
        ("done,d",      "set task as done")
        ("remove,r",    "remove task")
        ("pri,p",       po::value<int>(), "set priority")
        ("deadline",    "set deadline")
        ("desc",        "set description [default no parameter flag]")
        ;
    all.add_options()
        ("help,h",      "help msg")
        ("version,v",   "print version")
        ;

    all.add(general_desc).add(detailed_desc);
    // TODO passing *this to base type method is ok?
    po::store(po::command_line_parser(ac, av).
                options(all).
                positional(p).
                style(po::command_line_style::unix_style).
                run(), *this);

    po::notify(*this);
}

