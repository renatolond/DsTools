#include "logger.h"

void logger::log(int line, std::ostringstream &outstring)
{
    if ( logging == 0 ) return;
    *out << file << ":" << line << " - " << outstring.str();
    outstring.clear();
}

logger::logger()
{
    logging = const_logging;
    file = "";
    out = &std::cout;
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
