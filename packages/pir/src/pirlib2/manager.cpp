#include "manager.h"
#include <string.h>
#include "hidapi.h"


void Manager::checkDevices()
{
    struct hid_device_info *devs, *cur_dev;

    devs = hid_enumerate(0,0);
    cur_dev = devs;
    for (cur_dev=devs;cur_dev;cur_dev = cur_dev->next)
    {
        if ( cur_dev->vendor_id != 0x20a0 )
        {
            continue;
        }
        if ( cur_dev->usage_page == 1 && cur_dev->usage == 6 )
        {
            // this is the keyboard interface. SKIP SKIP.
            continue;
        }

        std::string serial;

        // this only works because PIR serials are HEXADECIMAL characters only, no non ansi.
        int i = 0;
        while ( cur_dev->serial_number[i] != 0 )
        {
            char c[2];
            c[1] = 0;
            c[0] = cur_dev->serial_number[i] & 0xff;
            serial.append( c );
            i++;
        }


        if ( cur_dev->product_id == 0x413f && (cur_dev->interface_number == 0||cur_dev->interface_number == -1) && !findPIR(serial) )
        {
            try
            {
                PIR * pir = new PIR(serial, cur_dev->release_number, PIR::PIR1, cur_dev->path, &m_Settings, std::bind(&Manager::closedCallback, this, std::placeholders::_1) );                		
                addPIR( PIRPtr( pir ));
                pir->waitForStartup();
                if ( m_Settings.statusCallback )
                {
                    m_Settings.statusCallback(serial.c_str(), PIR_ARRIVED_STATUS, m_Settings.userData);
                }
                continue;
            }
            catch ( std::exception )
            {
            }

        }

        if ( cur_dev->product_id == 0x4155 && (cur_dev->interface_number == 0||cur_dev->interface_number == -1)&& !findPIR(serial) )
        {
            try
            {
                PIR * pir = new PIR(serial, cur_dev->release_number, PIR::PIR4, cur_dev->path, &m_Settings,std::bind(&Manager::closedCallback, this, std::placeholders::_1) );
                addPIR( PIRPtr(pir) );
                pir->waitForStartup();
                if ( m_Settings.statusCallback )
                {
                    m_Settings.statusCallback(serial.c_str(), PIR_ARRIVED_STATUS, m_Settings.userData);
                }
                continue;
            }
            catch ( std::exception )
            {
            }
        }
    }

    hid_free_enumeration(devs);
}

bool Manager::learn(const std::string &serial)
{
    IPIRPtr p = findPIR(serial);
    if ( p )
    {
        p->learn();
        return true;
    }
    return false;
}

bool Manager::cancelLearn(const std::string &serial)
{
    IPIRPtr p = findPIR(serial);
    if ( p )
    {
        p->cancelLearn();
        return true;
    }
    return false;
}

std::string Manager::pirList(PIR::Type type)
{
    pthread_mutex_lock(&m_Mutex);

    std::string list;

    Manager::PIRList::const_iterator i = m_PIRList.begin();
    Manager::PIRList::const_iterator end = m_PIRList.end();


    while ( i!= end )
    {
        if ( (*i)->type() != type )
        {
            i++;
            continue;
        }
        const std::string & serial = (*i)->serial();

        if ( list.length() == 0 )
        {
            list = serial;
        }
        else
        {
            list += ",";
            list += serial;
        }
        i++;
    }

    pthread_mutex_unlock(&m_Mutex);

    return list;
}


PIRPtr Manager::findPIRLocked(const std::string &serial)
{
    PIRList::iterator i = m_PIRList.begin();
    while ( i != m_PIRList.end() )
    {
        if ( (*i)->serial() == serial )
        {
            return *i;
        }

        i++;
    }
    return PIRPtr();
}


IPIRPtr Manager::findPIR(const std::string &serial)
{
    pthread_mutex_lock(&m_Mutex);
    PIRPtr p = findPIRLocked(serial);
    pthread_mutex_unlock(&m_Mutex);
    return p;
}


void Manager::closedCallback(const std::string &serial)
{    
    IPIRPtr p = findPIR(serial);
    if ( p )
    {        
        pthread_mutex_lock(&m_Mutex);        
        PIRPtr p2 = std::static_pointer_cast<PIR>(p);
        m_PIRList.remove(p2);
        pthread_mutex_unlock(&m_Mutex);
    }
    if ( m_Settings.statusCallback )
    {
        m_Settings.statusCallback(serial.c_str(), PIR_REMOVED_STATUS, m_Settings.userData);
    }
}

void Manager::addPIR(PIRPtr p)
{
    pthread_mutex_lock(&m_Mutex);
    m_PIRList.push_back(p);
    pthread_mutex_unlock(&m_Mutex);
}



Manager::Manager(PIR_Settings *settings)
{
	hid_init();
    pthread_mutex_init(&m_Mutex, 0);
	
    if ( settings != 0 )
    {
        if ( settings->size != sizeof( PIR_Settings ))
        {
            throw std::exception();
        }

        memcpy(&m_Settings, settings, settings->size );
    }
    else
    {
        memset(&m_Settings, 0, sizeof( PIR_Settings ));
    }

}

Manager::~Manager()
{    
    pthread_mutex_lock(&m_Mutex);
    m_PIRList.clear();    
    hid_exit();    
    pthread_mutex_destroy(&m_Mutex);    
}

bool Manager::init()
{
    checkDevices();
    return true;
}

bool Manager::sendCCF(const std::string &serial, const std::string ccf, unsigned char bitmask, unsigned char repeats)
{
    if ( serial.length() > 0 )
    {
        IPIRPtr p = findPIR(serial);
        if ( p )
        {
            return p->sendCCF(ccf, bitmask, repeats);
        }

        return false;
    }
    else
    {
        pthread_mutex_lock(&m_Mutex);
        PIRList::iterator i = m_PIRList.begin();
        while ( i != m_PIRList.end() )
        {
            if ( !(*i)->sendCCF( ccf, bitmask, repeats ) )
            {
                pthread_mutex_unlock(&m_Mutex);
                return false;
            }
            i++;
        }

        pthread_mutex_unlock(&m_Mutex);

        return true;
    }
}
