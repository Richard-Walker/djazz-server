#include "irsend.h"
#include <string.h>

IRSend::IRSend(const std::string &ccf, unsigned int bitmask, unsigned int repeats) :
    m_Bitmask(bitmask),
    m_Repeats(repeats)
{
    m_Count = parseCCF(m_CCF, 256, ccf.c_str());
    if ( m_Count < 4 )
    {
        throw std::exception();
    }
    if ( m_CCF[0] != 0 )
    {
        throw std::exception();
    }
}

const unsigned int *IRSend::ccf() const
{
    return m_CCF;
}

unsigned int IRSend::count() const
{
    return m_Count;
}

unsigned char IRSend::repeats() const
{
    return m_Repeats;
}

unsigned char IRSend::bitmask() const
{
    return m_Bitmask;
}


int IRSend::parseCCF ( unsigned int CCF[], int size, const char * ccf )
{
    int bufpos = 0;

    for ( int j=0;j<size;j++)
    {
        CCF[j]=0;
    }

    int shift = 3;
    for ( unsigned int i=0;i<strlen(ccf); i++ )
    {

        char v = ccf[i];

        if ( v == ' ' )
        {
            continue;
        }

        int V;
        bool found = false;

        if ( v >= '0' && v <= '9' )
        {
            V = v - '0';
            found = true;
        }

        if ( v >= 'a' && v<='f' )
        {
            V = v - 'a' + 0x0A;
            found = true;
        }

        if ( v >= 'A' && v <='F' )
        {
            V = v - 'A' + 0x0A;
            found = true;
        }

        if ( found )
        {
            if ( shift >= 0 )
            {
                CCF[bufpos] |= V << (shift * 4);
                shift--;
                if ( shift < 0 ) {

                    // prevent zeros in CCF.
                    if ( CCF[bufpos] == 0 && bufpos > 3 )
                    {
                        CCF[bufpos] = 1;
                    }

                    bufpos++;
                    shift = 3;
                }
                if ( bufpos >= size ) return bufpos;
            }


        }

    }

    return bufpos;
}
