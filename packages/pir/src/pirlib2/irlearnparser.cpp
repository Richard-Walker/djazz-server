#include "irlearnparser.h"

IRLearnParser::IRLearnParser(const std::string &serial, PIR_Settings * settings) :
    m_Modulation(0),
    m_State(0),
    m_Count(0),
    m_Serial(serial),
    m_Settings(settings)
{
}

void IRLearnParser::reset()
{
    m_Pulses.clear();
    m_State = 0;
}

bool IRLearnParser::add(const unsigned char *data, int len)
{
    int readPos = 0;

    if ( m_State == 0 )
    {
        m_Pulses.clear();
        m_Modulation = data[1];
        m_Count = data[2];
        m_State = 1;
        readPos = 4;
    }


    while (readPos < len )
    {
        unsigned int v = data[readPos++] << 8;
        v |= data[readPos++] ;
        m_Pulses.push_back(v);

        if ( m_Pulses.size() == m_Count )
        {
            // emit received(m_Pulses, m_Modulation);
            if ( m_Settings->rawLearnCallback )
            {
                m_Settings->rawLearnCallback(m_Serial.c_str(), m_Modulation, m_Pulses.data(), m_Count, m_Settings->userData);
            }
            reset();
            return true;
        }
        if ( m_Pulses.size() > m_Count )
        {
            reset();
            return true;
        }
    }

    return false;
}
