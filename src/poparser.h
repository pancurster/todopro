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
    POParser(int ac, const char* av[]);
    ~POParser();

    po::options_description all;
    po::options_description general_desc;
    po::options_description detailed_desc;

    bool fail();

private:
    void parse_program_options(int ac, const char* av[]);
    bool m_fail;
};

#endif //POPARSER_H

