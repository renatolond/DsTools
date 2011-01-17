#include "logger.h"

void logger::log(int line, std::ostringstream &outstring)
{
    if ( logging == 0 ) return;
    *out << file << ":" << line << " - " << outstring.str();
    outstring.str(std::string());
    outstring.clear();
}

logger::logger()
{
    logging = const_logging;
    file = "";
    out = &std::cout;
}

logger::~logger()
{
    file = "";
}

//std::ostringstream &outs()
//{
//    return outstring;
//}

logger::logger(std::string f)
{
    logging = const_logging;
    file = f;
    out = &std::cout;
}
