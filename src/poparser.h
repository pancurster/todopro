#ifndef POPARSER_H
#define POPARSER_H

#include <boost/program_options.hpp>

namespace po = boost::program_options;
typedef po::variables_map POVars;

/*
 * POParser - Program Options Parser
 *
 * We use here Boost library.
 */
class POParser : public POVars {
public:
    POParser(int ac, char* av[]);
    ~POParser();

    po::options_description main_desc;

private:
    void parse_program_options(int ac, char* av[]);
};

#endif //POPARSER_H

