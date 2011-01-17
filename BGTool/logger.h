#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <sstream>

const int const_logging = 0; // NOT LOGGING!

class logger
{
    int logging;
    std::ostream *out;
    std::string file;
    public:
    logger(std::string f);
    logger();
    ~logger();
    void log(int line, std::ostringstream &outstring);
//    std::ostringstream &outs();
};

#endif // LOGGER_H
