#include "sendirparser.h"

SendIRParser::SendIRParser(const std::string &serial, PIR_Settings *settings, SendDoneCallback cb) :
    m_Serial(serial),
    m_Settings(settings),
    m_Callback(cb)
{

}

bool SendIRParser::add(const unsigned char *data, int len)
{
    if ( len < 2 )
    {
        return true;
    }

    if ( m_Callback )
    {
        m_Callback();
    }

    if ( m_Settings->sendCallback )
    {
        m_Settings->sendCallback( m_Serial.c_str(), data[1], m_Settings->userData );
    }
    return true;
}
