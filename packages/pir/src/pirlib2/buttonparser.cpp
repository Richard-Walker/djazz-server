#include "buttonparser.h"

ButtonParser::ButtonParser(const std::string &serial, PIR_Settings *settings) :
    m_Serial(serial),
    m_Settings(settings)
{
}

bool ButtonParser::add(const unsigned char *data, int len)
{
    if ( len < 5 )
    {
        return true;
    }

    int pos = 1;
    int cnt = data[pos++];

    if ( cnt == 0  )
    {
        // no buttons reporting in.
        return true;
    }

    int buttons[4] = { 0,0,0,0 };

    for ( int i=0;i<cnt;i++)
    {
        int button = data[pos++] -1;
        int press = data[pos++];
        if ( button < 0 || button > 3 )
        {
            continue;
        }
        buttons[button] = press;

    }

    if ( m_Settings->buttonCallback )
    {
        m_Settings->buttonCallback(m_Serial.c_str(),buttons[0],buttons[1],buttons[2],buttons[3], m_Settings->userData );
    }

    return true;
}
