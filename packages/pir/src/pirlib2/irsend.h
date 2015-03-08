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

#ifndef IRSEND_H
#define IRSEND_H

#include <string>
#include <memory>

// IR Send container. if the target is busy, this class is
// used to store the IR signal info.
class IRSend
{
    unsigned int m_CCF[256];
    unsigned int m_Count;
    unsigned char m_Bitmask;
    unsigned char m_Repeats;

public:
    IRSend( const std::string & ccf, unsigned int bitmask, unsigned int repeats);
    const unsigned int * ccf() const;
    unsigned int count() const;
    unsigned char repeats() const;
    unsigned char bitmask() const;

protected:
    int parseCCF(unsigned int CCF[], int size, const char *ccf);
};
typedef std::shared_ptr<IRSend> IRSendPtr;
#endif // IRSEND_H
