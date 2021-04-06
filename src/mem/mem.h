#ifndef MEM_H_
#define MEM_H_

#include "../types/types.h"

namespace Mem {

class Mem
{
private:
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte m_ata[MAX_MEM];

public:

    void Init();

    // read 1 byte
    Byte operator[](u32) const;

    // write 1 byte
    Byte& operator[](u32);

    // write 1 word (2 bytes)
    void WriteWord(Word, u32, u32&);
};

};

#endif // MEM_H_
