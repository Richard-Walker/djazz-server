#include "pirlib2.h"
#include "manager.h"

#include <string.h>

#include <stdio.h>

static Manager * gManager = 0;

PIRLIB2SHARED_EXPORT int pir_open( PIR_Settings * settings )
{
    try
    {
        gManager = new Manager(settings);
        gManager->init();
    }
    catch ( std::exception )
    {
        return -1;
    }

    return 0;
}

PIRLIB2SHARED_EXPORT int pir_close()
{
    if ( gManager == 0 )
    {
        return 0;
    }

    delete gManager;
    gManager = 0;
    return 0;
}


PIRLIB2SHARED_EXPORT int pir_sendCCF ( const char * serial, const char * ccf, int bitmask, unsigned char repeats )
{
    if ( gManager == 0 )
    {
        return -1;
    }

    return gManager->sendCCF(serial, ccf, bitmask, repeats) ? 0 : -1;
}


PIRLIB2SHARED_EXPORT unsigned int pir_list1(char *buffer, unsigned int size)
{
    if ( gManager == 0 )
    {
        return -1;
    }

    std::string list = gManager->pirList(PIR::PIR1);

    if ( size == 0 )
    {
        return (int)list.length() + 1;
    }

    if ( list.length() + 1 > size )
    {
        buffer[0] = 0;
        return (int)list.length() + 1;
    }
    memcpy(buffer, list.c_str(), list.length() );
    buffer[list.length()] = 0;
    return (int)list.length() + 1;
}


unsigned int pir_list4(char *buffer, unsigned int size)
{
    if ( gManager == 0 )
    {
        return -1;
    }

    std::string list = gManager->pirList(PIR::PIR4);

    if ( size == 0 )
    {
        return (int)list.length() + 1;
    }

    if ( list.length() + 1 > size )
    {
        buffer[0] = 0;
        return (int)list.length() + 1;
    }
    memcpy(buffer, list.c_str(), list.length() );
	buffer[list.length()] = 0;
    return (int)list.length() + 1;
}


PIRLIB2SHARED_EXPORT int pir_version(const char *serial)
{
    if ( gManager == 0 )
    {
        return -1;
    }

    IPIRPtr p = gManager->findPIR(serial);
    if (!p)
    {
        return -1;
    }

    return p->version();
}


PIRLIB2SHARED_EXPORT int pir_blink(const char *serial, unsigned char count)
{
    if ( gManager == 0 )
    {
        return -1;
    }

    IPIRPtr p = gManager->findPIR(serial);
    if (!p)
    {
        return -1;
    }

    return p->blink(count) ? 0 : -1;
}


PIRLIB2SHARED_EXPORT int pir_type(const char *serial)
{
    if ( gManager == 0 )
    {
        return -1;
    }

    IPIRPtr p = gManager->findPIR(serial);
    if (!p)
    {
        return -1;
    }

    return p->type() == PIR::PIR1 ? PIR_PIR_1 : PIR_PIR_4;
}


PIRLIB2SHARED_EXPORT int pir_detect()
{
    if ( gManager == 0 )
    {
        return -1;
    }

    gManager->checkDevices();

    return 0;
}

PIRLIB2SHARED_EXPORT int pir_learn( const char * serial )
{
    if ( gManager == 0 )
    {
        return -1;
    }

    gManager->learn(serial);

    return 0;
}

PIRLIB2SHARED_EXPORT int pir_cancelLearn( const char * serial )
{
    if ( gManager == 0 )
    {
        return -1;
    }

    gManager->cancelLearn(serial);

    return 0;
}
