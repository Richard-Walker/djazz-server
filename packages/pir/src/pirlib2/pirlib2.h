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

/*! \mainpage PIRLIB2
 * \section introduction Introduction
 *
 * This is the MIT licensed open source library for the
 * Promixis PIR-1 and PIR-4. This library has been tested on Windows
 * and Linux. It supports sending IR codes, receiving IR signals and
 * learning IR signals.
 *
 * \section windows_notes Windows Notes
 *
 * On Windows compilation requires hid.lib, a x86 and x64 version of
 * this library can be found in buildExtras, place them in the appropriate
 * spot when building the Qt version.
 *
 * The precompiled version of pirlib2_example.exe requires the Visual
 * Studio 2010 redistributables.
 *
 * Windows x86:
 * http://www.microsoft.com/en-us/download/details.aspx?id=5555
 *
 * Windows x64:
 * http://www.microsoft.com/en-us/download/details.aspx?id=14632
 *
 * \section linux_notes Linux Notes
 *
 * On Linux the udev daemon typically sets the access permissions
 * of USB-HID devices to 600 for user root. This means that regular
 * users are not able to access the devices. This library accesses
 * the PIR-1 and PIR-4 through /dev/hidraw* and thus we need udev to
 * adjust permission on this.
 *
 * Easiest way to do this is by creating a file called
 *
\verbatim
/etc/udev/rules.d/99-usb-pir.rules
\endverbatim
 *
 * inside that file add
 *
\verbatim
SUBSYSTEM=="hidraw", ATTRS{idVendor}=="20a0", ATTRS{idProduct}=="413f", MODE="0666"
SUBSYSTEM=="hidraw", ATTRS{idVendor}=="20a0", ATTRS{idProduct}=="4155", MODE="0666"
\endverbatim
 *
 * Then reload the rules with
\verbatim
udevadm control --reload-rules
\endverbatim
 *
 * Last step is to now unplug and replug the PIR-1 / PIR-4 so it can get the
 * new permissions.
 *
 * \section c_api C API
 * The C api can be found here pirlib2.h
 *
 * \section cpp_api C++ API
 * The C++ api can be found here Manager
 *
 * \section example Example
 *
\code{.cpp}
#include "pirlib2.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void printUsage()
{
    printf("PIR-1 / PIR-4 Library Example.\n");
    printf("Copyright (c) 2014 Promixis, LLC\n\n");
    printf("pir usage:\n");
    printf("pir send PIR_SERIAL_OR_ALL CCF BITMASK REPEATS\n");
    printf("pir blink PIR_SERIAL_OR_ALL\n");
    printf("pir list\n");
    printf("\nExample send from any attached PIR-1 or PIR-4:\n");
    printf("./pir_example send all \"0000 006E 0000 0022 0156 00A9 0014 0014 0014 0040 0014 0040 0014 0040 0014 0014 0014 0040 0014 0040 0014 0014 0014 0040 0014 0014 0014 0014 0014 0014 0014 0040 0014 0014 0014 0014 0014 0040 0014 0040 0014 0014 0014 0040 0014 0040 0014 0040 0014 0014 0014 0014 0014 0014 0014 0014 0014 0040 0014 0014 0014 0014 0014 0014 0014 0040 0014 0040 0014 0040 0014 05EF\" 1 2\n\n");
}

int main(int argc, char ** argv)
{


    if ( argc < 2 )
    {
        printUsage();
        return 0;
    }


    PIR_Settings s;
    memset(&s,0,sizeof(PIR_Settings));
    s.size = sizeof(PIR_Settings);

    if ( pir_open(&s) != 0 )
    {
        printUsage();
        printf("Error Opening HID layer.");
        return -1;
    }

    bool ok = false;
    int res = -1;

    if ( strcmp(argv[1], "send" ) == 0 && argc == 6 )
    {
        const char * serial = argv[2];
        const char * ccf = argv[3];
        int bitmask = atoi( argv[4]);
        int repeats = atoi( argv[5]);

        if ( strcmp(serial, "all") == 0 )
        {
            serial = "";
        }

        res = pir_sendCCF(serial, ccf, bitmask, repeats);
        ok = true;
    }

    if ( strcmp(argv[1], "blink") == 0 && argc == 3 )
    {
        const char * serial = argv[2];
        if ( strcmp(serial, "all") == 0 )
        {
            printf("blink does not support \"all\"\n");
        }
        else
        {
            res = pir_blink(serial,5);
            ok = true;
        }
    }

    if ( strcmp(argv[1], "list") == 0 && argc == 2 )
    {
        char buffer[1024];
        pir_list1(buffer, 1024);
        printf("PIR-1: %s\n", buffer);
        pir_list4(buffer, 1024);
        printf("PIR-4: %s\n", buffer);
        ok = true;
        res = 0;
    }

    pir_close();

    if ( !ok )
    {
        printUsage();
    }

    return res;
}

\endcode
 *
 * \section license License
 * \copyright (c) 2014, Promixis, LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the
 * following conditions are met:
 *
 * 1. Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials
 * provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * \file pirlib2.h Main C interface of the library.
 *
 *
 */

#ifndef PIRLIB2_H
#define PIRLIB2_H

#include "pirlib2_global.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! \def PIR_ARRIVED_STATUS
 * PIR-1 or PIR-4 has arrived
 */

/*! \def PIR_REMOVED_STATUS
 * PIR-1 or PIR-4 was removed
 */
#define PIR_ARRIVED_STATUS  1
#define PIR_REMOVED_STATUS  2


/*! \def PIR_ARRIVED_STATUS
 *  \def PIR_REMOVED_STATUS
 */

/*! \typedef void (*fStatusCB)
 *  \brief Callback called when the status of the PIR-1 driver is affected.
 *  \details For example when a new PIR-1 arrives.
 *
 *  PIR_ARRIVED_STATUS if a new PIR-1 arrives.
 *  PIR_REMOVED_STATUS if a PIR-1 is removed.
 * \param serial serial number of PIR
 * \param status PIR_ARRIVED_STATUS or PIR_REMOVED_STATUS
 * \param userData userData element from PIR_Settings
 */
typedef void (*fStatusCB) ( const char * serial, unsigned char status, void * userData);

/*! \typedef void (*fIrReceivedCB)
 * \brief Called when an IR signal is received in non-learn mode.
 *
 * fIrReceivedCB is called when an IR code is received. Note that the received code is NOT
 * an CCF code and must be compared 'fuzzy'.
 * \param serial serial number of PIR
 * \param pulses pulses is a array of pulse lenghts.
 * \param pulseCount pulseCount is the number of elements in the pulses array.
 * \param userData userData element from PIR_Settings
 */
typedef void (*fIrReceivedCB) ( const char * serial, const unsigned int * pulses, unsigned int pulseCount, void * userData);

/*! \typedef void (*fIrSentCB)
 * \brief fIrSentCB is called when an IR code was sent.
 * \param serial serial number of PIR
 * \param status, 0 = OK otherwise error.
 * \param userData userData element from PIR_Settings
*/
typedef void (*fIrSentCB) ( const char * serial, unsigned char status, void * userData );


/*! \typedef void (*fIrRawLearnCB)
 * \brief fIrRawLearnCB is called when an IR code is received in LEARN mode.
 * \param serial serial number of PIR
 * \param modulation is the modulation frequency of the signal.
 * \param pulses is the array that holds the pulse lenghts
 * \param pulseCount is the number of elements in the buffer.
 * \param userData userData element from PIR_Settings
*/
typedef void (*fIrRawLearnCB) ( const char * serial, unsigned int modulation, const unsigned int * pulses, unsigned int pulseCount, void * userData );


/*! \def PIR_BUTTON_IDLE
 * Idle Button
 */
/*! \def PIR_BUTTON_DOWN
 * Button is being pressed
 */
/*! \def PIR_BUTTON_REPEAT
 * Button is held down
 */
/*! \def PIR_BUTTON_UP
 * Button was released
 */
#define PIR_BUTTON_IDLE     0
#define PIR_BUTTON_DOWN     1
#define PIR_BUTTON_REPEAT   2
#define PIR_BUTTON_UP       3

/*! \typedef void (*fButtonCB)
 * \brief fButtonCB is called on a button event.
 *
 * \param serial serial number of PIR
 * \param button1 current event number, PIR_BUTTON_DOWN, PIR_BUTTON_IDLE, PIR_BUTTON_REPEAT or PIR_BUTTON_UP
 * \param button1 current event number, PIR_BUTTON_DOWN, PIR_BUTTON_IDLE, PIR_BUTTON_REPEAT or PIR_BUTTON_UP
 * \param button2 current event number, PIR_BUTTON_DOWN, PIR_BUTTON_IDLE, PIR_BUTTON_REPEAT or PIR_BUTTON_UP
 * \param button3 current event number, PIR_BUTTON_DOWN, PIR_BUTTON_IDLE, PIR_BUTTON_REPEAT or PIR_BUTTON_UP
 * \param button4 current event number, PIR_BUTTON_DOWN, PIR_BUTTON_IDLE, PIR_BUTTON_REPEAT or PIR_BUTTON_UP
 * \param userData userData element from PIR_Settings
 */
typedef void (*fButtonCB) ( const char * serial, int button1, int button2, int button3, int button4, void * userData );

/*! \brief the Settings structure.
 *
 */
typedef struct {
    //! \brief fill with sizeof(PIR_Settings)
    int size;
    //! \brief called when IR signal is done sending.
    fIrSentCB sendCallback;
    //! \brief called when an PIR arrives or is removed.
    fStatusCB statusCallback;
    //! \brief called when an IR signal is recevied in normal mode.
    fIrReceivedCB receiveCallback;
    //! \brief called when a button is pressed on a PIR-1.
    fButtonCB buttonCallback;
    //! \brief called when an IR signal is received in learn mode.
    fIrRawLearnCB rawLearnCallback;
    void * unused;
    //! \brief data needed by caller of pir library, passed by into all callbacks.
    void * userData;
} PIR_Settings;

/*! \fn int pir_open( PIR_Settings * settings )
 *  \brief Opens the PIR Library. This must be called only once.
 *  \param settings PIR_Settings structure.
 *  \return 0 on success.
 *  \return < 0 on error.
 *
 * The PIR_Settings struct contents is copied so there is no need
 * to keep the object around after pir_open
 *
 * \section Example
 *
 * This example opens the library without any callbacks registered.
 *
\code{.c}
PIR_Settings s;
memset(&s, 0, sizeof(PIR_Settings));
s.size = sizeof( PIR_Settings );
pir_open(&s);
\endcode
  */
PIRLIB2SHARED_EXPORT int pir_open( PIR_Settings * settings );

/*! \fn int pir_close()
 * \brief Close the library
 * \returns 0 on success.
 */
PIRLIB2SHARED_EXPORT int pir_close();


/*! \fn int pir_sendCCF ( const char * serial, const char * ccf, int port, unsigned char repeats )
 *  \brief Transmit a CCF code
 *
 * CCF codes are the IR codes formatted according to the Pronto CCF format. This library
 * only supports CCF-RAW codes.
 *
 * Multiple code can be sent in quick succesion without waiting for fIrSentCB callback. Internally
 * the library will queue the CCF codes.
 *
 * \param serial the serial number of the PIR to use for sending or 0 ( or "" ) for all attached PIRs.
 * \param ccf Pronto CCF string.
 * \param bitmask combination of bits 1 = back of PIR, 2 = front panel for pir-1
 * \param bitmask = 1, 2, 4 or 8 respectively for ports 1,2,3 or 4 on PIR-4
 * \param repeats = number of times to repeat the ir signal.
 * \return 0 = success
 * \return < 0 = error
*/
PIRLIB2SHARED_EXPORT int pir_sendCCF ( const char * serial, const char * ccf, int bitmask, unsigned char repeats ) ;

/*! \fn unsigned int pir_list1 ( char * buffer, unsigned int size )
 * \brief Get a comma separated list of PIR-1 serial numbers.
 * \param buffer allocated by caller
 * \param size size of buffer
 * \returns the number of characters required in the buffer to hold the full
 * string. If this number is larger then you have passed in size adjust your buffer
 * and call again.
 */
PIRLIB2SHARED_EXPORT unsigned int pir_list1 ( char * buffer, unsigned int size );


/*! \fn unsigned int pir_list4 ( char * buffer, unsigned int size )
 * \brief Get a comma separated list of PIR-4 serial numbers.
 * \param buffer allocated by caller
 * \param size size of buffer
 * \returns the number of characters required in the buffer to hold the full
 * string. If this number is larger then you have passed in size adjust your buffer
 * and call again.
 */
PIRLIB2SHARED_EXPORT unsigned int pir_list4 ( char * buffer, unsigned int size );

/*! \fn int pir_version ( const char * serial )
 * \brief Returns the firmware version of the attached PIR
 * \param serial serial number of the PIR-1 to query.
 * \returns version of firmware on success (>0)
 * \returns < 0 on error.
 */
PIRLIB2SHARED_EXPORT int pir_version ( const char * serial );


/*! \fn int pir_blink( const char * serial, unsigned char count )
 * \brief Blinks the LED on the attached PIR-1
 * \param serial serial number of the PIR-1 to query.
 * \param count the number of times to blink.
 * \returns 0 on success
 * \returns < 0 on error
 */
PIRLIB2SHARED_EXPORT int pir_blink( const char * serial, unsigned char count );

/*! \def PIR_PIR_1
 * PIR-1
 * */
/*! \def PIR_PIR_4
 * PIR-4
 * */
#define PIR_PIR_1   1
#define PIR_PIR_4   4



/*! \fn int pir_type( const char * serial )
 * \brief Returns the type
 * \param serial serial number of the PIR-1 to query.
 * \returns PIR_PIR_1 or PIR_PIR_4 on success
 * \returns < 0 on error
 */
PIRLIB2SHARED_EXPORT int pir_type( const char * serial );


/*! \fn int pir_detect( )
 * \brief Looks for attached PIR-1 or PIR-4 devices. This library
 * runs this code on startup but after that the calling code is
 * responsible for periodically running this.
 *
 * \returns 0 on success
 * \returns < 0 on error
 */
PIRLIB2SHARED_EXPORT int pir_detect( );


/*! \fn int pir_learn( const char * serial )
 * \brief starts learn mode
 *
 * \param serial serial number of PIR-1 to use for learning.
 * \returns 0 on success
 * \returns < 0 on error
 */
PIRLIB2SHARED_EXPORT int pir_learn( const char * serial );

/*! \fn int pir_cancelLearn( const char * serial )
 * \brief starts learn mode
 *
 * \param serial number of PIR-1 to stop learning.
 * \returns 0 on success
 * \returns < 0 on error
 */
PIRLIB2SHARED_EXPORT int pir_cancelLearn( const char * serial );

#ifdef __cplusplus
}
#endif


#endif // PIRLIB2_H
