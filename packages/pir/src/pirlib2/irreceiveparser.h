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

#ifndef IRRECEIVEPARSER_H
#define IRRECEIVEPARSER_H

#include "iparser.h"
#include "pirlib2.h"
#include <string>

#define IR_RECEIVE_BUFFERSIZE 256


// Parser for the IR receive function on the PIR-1
// returns array with pulse times
// Use fuzzy matching
class IRReceiveParser : public IParser
{
    std::string m_Serial;
    PIR_Settings * m_Settings;
    unsigned int m_IRReceiveBuffer[IR_RECEIVE_BUFFERSIZE];
    unsigned int m_Pos;
    unsigned int m_State;
    unsigned int m_Count;
public:
    IRReceiveParser(const std::string & serial, PIR_Settings * settings);
    virtual bool add( const unsigned char * data, int len );
};

#endif // IRRECEIVEPARSER_H
