/*

PIR-1/PIR-4 Driver v2

Copyright (c) 2014, Promixis, LLC
All rights reserved.

Redistribution and use in source and binary forms, with or
without modification, are permitted provided that the
following conditions are met:

1. Redistributions of source code must retain the above
copyright notice, this list of conditions and the following
disclaimer.

2. Redistributions in binary form must reproduce the above
copyright notice, this list of conditions and the following
disclaimer in the documentation and/or other materials
provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <list>

#include "pirlib2.h"
#include "pir.h"
#include "pt.h"


/*! \class Manager
 * \brief Contains the PIR-1/PIR-4 objects currently available on the system.
 */
class Manager
{

public:

    typedef std::list<PIRPtr> PIRList;

    //! \brief Constructor
    Manager(PIR_Settings * settings);
    //! \brief Destructor
    ~Manager();
    //! \brief Initialization, checkDevices is permformed at this point.
    bool init();

    /*! \brief Sends a CCF code
     *  \param serial the serial number of the PIR to use of empty for all attached PIRs.
     *  \param ccf the pronto CCF to send.
     *  \param bitmask combination of bits 1 = back of PIR, 2 = front panel for pir-1
     *  \param bitmask = 1, 2, 4 or 8 respectively for ports 1,2,3 or 4 on PIR-4
     *  \param repeats the number of times to run the repeat part of the CCF
     *  \returns true on success, false on failure.
     */
    bool sendCCF( const std::string & serial, const std::string ccf, unsigned char bitmask, unsigned char repeats );

    //! \brief returns the PIR object for specific serial
    IPIRPtr findPIR( const std::string & serial );

    //! \brief runs the PIR-1 / PIR-4 device detection routine. New devices may appear at this point.
    void checkDevices();

    //! \brief start learning on the specified PIR-1
    bool learn( const std::string & serial );
    //! \brief cancels learning on the specified PIR-1
    bool cancelLearn( const std::string & serial );

    //! \brief returns a comma separated list of serial numbers of available PIR's with requested type.
    std::string pirList( PIR::Type type );

private:
    PIR_Settings m_Settings;
    PIRList m_PIRList;
    pthread_mutex_t m_Mutex;

    void closedCallback(const std::string & serial );
    void addPIR( PIRPtr p );
    PIRPtr findPIRLocked( const std::string & serial );
};

#endif // MANAGER_H
