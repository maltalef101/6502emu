#include "mem.h"

void Mem::Init()
{
    {
        for (u32 i = 0; i < MAX_MEM; i++)
            m_data[i] = 0;
    }

};

Byte Mem::operator[](u32 addr) const
{
    // assert addr !> MAX_MEM
    return m_data[addr];
};

Byte& operator[](u32 addr)
{
    return m_data[addr];
}


void WriteWord(Word val, u32 addr, u32& cycles)
{
    m_data[addr]     = val & 0xFF;
    m_data[addr + 1] = (val >> 8);
    cycles -= 2;
}
