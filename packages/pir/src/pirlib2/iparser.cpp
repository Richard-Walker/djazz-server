#include "iparser.h"

IParser::IParser()
{
}


UnknownParser::UnknownParser()
{
}

bool UnknownParser::add(const unsigned char * data, int len )
{    
    (void)data;
    (void)len;
    return true;
}
