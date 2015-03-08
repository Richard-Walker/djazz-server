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

#ifndef PIR_H
#define PIR_H

#include <list>
#include <functional>

#include "ipir.h"
#include "hidapi.h"
#include "pirlib2.h"
#include "iparser.h"
#include "irsend.h"
#include "boolsig.h"


extern "C" {
#include "pt.h"
}


class PIR : public IPIR
{
public:
    typedef std::function< void( const std::string &serial ) > PIRClosedCallback;

    PIR( const std::string & serial, unsigned int version, IPIR::Type type, const std::string & path, PIR_Settings * settings, PIRClosedCallback closed );
    // calling the destructor on PIR will _NOT_ trigger the closedCallback
    ~PIR();

    std::string serial() const;
    unsigned int version() const;
    std::string path() const;

    bool sendCCF(const std::string ccf, unsigned char bitmask, unsigned char repeats);
    bool blink(unsigned char count);
    bool learn();
    bool cancelLearn();

    IPIR::Type type() const;
    void waitForStartup();


private:
    std::string m_Serial;
    unsigned int m_Version;
    IPIR::Type m_Type;
    std::string m_Path;
    PIR_Settings * m_Settings;
    PIRClosedCallback m_ClosedCallback;
    hid_device * m_Device;
    pthread_t m_Thread;
    pthread_mutex_t m_Mutex;
    pthread_mutex_t m_FunctionQueueMutex;
    bool m_ExitThread;
    bool m_IrSending;
    BoolSig m_StartupSignal;
    IParserPtr m_CurrentParser;
    IParserPtr m_SendIRParser;
    IParserPtr m_UnknownParser;
    IParserPtr m_ReceiveParser;
    IParserPtr m_ButtonParser;
    IParserPtr m_IRLearnParser;

    typedef std::function<void()> QueuedFunction;
    std::list<QueuedFunction> m_QueuedFunctions;
    std::list<IRSendPtr> m_QueuedIrSignals;

    static void *_proc( void * attr );
    void proc();

    void startCCFSend(const IRSend *send);
    void queue( QueuedFunction f );
    void irSendingDone();
    size_t functionQueueSize();

};
typedef std::shared_ptr<PIR> PIRPtr;

#endif // PIR_H

