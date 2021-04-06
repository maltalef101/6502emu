#ifndef MEM_H_
#define MEM_H_

#include <types/types.h>

namespace Mem {

class Mem
{
public:

    void Init()
    {
        for (u32 i = 0; i < MAX_MEM; i++)
            m_data[i] = 0;
    };

    // read 1 byte
    Byte operator[](u32 addr) const { return m_data[addr]; };

    // write 1 byte
    Byte& operator[](u32 addr) { return m_data[addr]; };

    // write 1 word (2 bytes)
    void WriteWord(Word val, u32 addr, u32& cycles)
    {
        m_data[addr]     = val & 0xFF;
        m_data[addr + 1] = (val >> 8);
        cycles -= 2;
    }

private:
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte m_data[MAX_MEM];
};

};

#endif // MEM_H_
