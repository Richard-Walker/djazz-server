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

#ifndef IPIR_H
#define IPIR_H

#include <string>
#include <memory>

/*! \class IPIR
 *  \brief The PIR interface class.
 */
class IPIR
{
public:
    IPIR();    
    virtual ~IPIR();

    //! \enum Type
    enum Type { PIR1, PIR4 };

    /*! \brief Returns the serial number
     *
     * PIR serial numbers are hexadecimal strings of 16 characters.
     * \returns serial number
     *
     */
    virtual std::string serial() const = 0;
    /*! \brief Returns the firmware version number
     *
     * New firmware revisions can be uploaded to the PIR's.
     * \returns version number of firmware.
     */
    virtual unsigned int version() const = 0;

    /*! \brief sends CCF code.
     *
     * CCF codes are the IR codes formatted according to the Pronto CCF format. This library
     * only supports CCF-RAW codes.
     *
     * Multiple code can be sent in quick succesion without waiting for fIrSentCB callback. Internally
     * the library will queue the CCF codes.
     *
     * \param ccf Pronto CCF string.
     * \param bitmask combination of bits 1 = back of PIR, 2 = front panel for pir-1
     * \param bitmask = 1, 2, 4 or 8 respectively for ports 1,2,3 or 4 on PIR-4
     * \param repeats = number of times to repeat the ir signal.
     * \return 0 = success
     * \return < 0 = error
     */
    virtual bool sendCCF(const std::string ccf, unsigned char bitmask, unsigned char repeats) = 0;
    /*! \brief blinks the LED on the PIR-1
     * \param count number of times to blink.
     */
    virtual bool blink(unsigned char count) = 0;
    /*! \brief returns the Type of the PIR
     * \returns Type ( either PIR-1 or PIR-4 )
     */
    virtual Type type() const = 0;

    /*! \brief starts learn mode on a PIR-1
     *  \returns true on success false on error.
    */
    virtual bool learn() = 0;
    /*! \brief ends learn mode on a PIR-1
     * \returns true on success false on error.
     */
    virtual bool cancelLearn() = 0;
};

/*! \typedef std::shared_ptr<IPIR>IPIRPtr
 * The shared pointer PIR type.
 */
typedef std::shared_ptr<IPIR>IPIRPtr;

#endif // IPIR_H
