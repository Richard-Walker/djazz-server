#include "irreceiveparser.h"

IRReceiveParser::IRReceiveParser(const std::string &serial, PIR_Settings *settings) :
    m_Serial(serial),
    m_Settings(settings),
    m_Pos(0),
    m_State(0),
    m_Count(0)
{
}

bool IRReceiveParser::add(const unsigned char *data, int len)
{
    int readPos = 0;
    switch ( m_State )
    {
    case 0:

        m_Count = data[1]; // data[1] holds the number of pulse we'll get.
        m_Pos = 0;
        m_State = 1;
        readPos  = 2;
        // delibarate fallthrough.

    case 1:

        while ( readPos < len && m_Pos < m_Count && m_Pos < IR_RECEIVE_BUFFERSIZE )
        {

            m_IRReceiveBuffer[ m_Pos ] = ( data[readPos++] << 8 );
            m_IRReceiveBuffer[ m_Pos++ ] += data[readPos++];
        }

        if ( m_Pos == m_Count )
        {
            if ( m_Settings->receiveCallback )
            {
                m_Settings->receiveCallback( m_Serial.c_str(), m_IRReceiveBuffer, m_Pos, m_Settings->userData );
            }


            m_State = 0;
            return true;
        }

        return false;
    }


    return true; // means done, remove me.
}
