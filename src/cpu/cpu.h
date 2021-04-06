#ifndef CPU_H_
#define CPU_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "../types/types.h"

#include "../mem/mem.h"

namespace CPU {

struct ProcessorStatus  // Status flags
{
    Bit C;          // Carry flag
    Bit Z;          // Zero flag
    Bit I;          // Interrupt disable
    Bit D;          // Decimal mode
    Bit B;          // Break command
    Bit V;          // Overflow flag
    Bit N;          // Negative flag

    void setAllToZero();
};

class CPU
{
public:
    /* reset operation */
    void Reset(Mem::Mem& mem)
    {
        /* set all to zero */
        CPU::m_PC = 0xFFFC;
        CPU::m_SP = 0x0100;
        m_A = m_X = m_Y = 0;

        m_PS.setAllToZero();

        mem.Init();
    };

    /* Load/ Store operations */

    void Exec(u32 cycles, Mem::Mem &mem)
    {
        while (cycles > 0) {
            Byte inst = FetchByte(cycles, mem);
            switch (inst)
            {
            case INS_LDA_IM: { m_LDA_IM(cycles, mem); break; }
            case INS_LDA_ZP: { m_LDA_ZP(cycles, mem); break; }
            case INS_LDA_ZPX: { m_LDA_ZPX(cycles, mem); break; }
            case INS_JSR: { m_JSR(cycles, mem); break; }
            default: { printf("[ERROR] :: Insruction \"%us\" not handled.\n", inst); }
            }
        };
    };

    ProcessorStatus getPS() const { return m_PS; };

private:
    /* internals */
    Word m_PC;                    // program counter
    Word m_SP;                    // stack pointer
    Byte m_A;                     // accumulator

    Byte m_X, m_Y;                  // Registers
    ProcessorStatus m_PS;         // ProcessorStatus flags

    /* opcodes */
    static constexpr Byte
                    /* LDA */
                    INS_LDA_IM  = 0xA9,
                    INS_LDA_ZP  = 0xA5,
                    INS_LDA_ZPX = 0xB5,
    /**/
                    INS_JSR     = 0x20;

    Byte FetchByte(u32& cycles, Mem::Mem& mem)
    {
        Byte data = mem[m_PC];
        m_PC++;
        cycles--;
        return data;
    };

    Word FetchWord(u32& cycles, Mem::Mem& mem)
    {
        // 6502 is little endian
        Word data = mem[m_PC];
        m_PC++;

        data |= (mem[m_PC] << 8);
        m_PC++;

        cycles -= 2;

        return data;
    };

    Byte ReadByte(u32& cycles, Byte addr, Mem::Mem& mem)
    {
        Byte data = mem[addr];
        cycles--;
        return data;
    };

    // Sets the Z (Zero) and N (Negative) accordingly when operating on LDA
    void SetLDAStatus() {  m_PS.Z = (m_A == 0); m_PS.N = (m_A & 0b10000000) > 0;}

    /* instructions */
    void m_LDA_IM(u32 cycles, Mem::Mem& mem)
    {
        Byte val = FetchByte(cycles, mem);          // gets the value from memory
        m_A = val;                                  // loads the value to the A register
        SetLDAStatus();
    };

    void m_LDA_ZP(u32 cycles, Mem::Mem& mem)
    {
        Byte zeroPageAddr = FetchByte(cycles, mem);       // get the address of the ZeroPage
        m_A = ReadByte(cycles, zeroPageAddr, mem);        // get the value of the ZeroPage and load it into the A register

        SetLDAStatus();
    };

    void m_LDA_ZPX(u32 cycles, Mem::Mem& mem)
    {
        Byte zeroPageAddr = FetchByte(cycles, mem);       // get the address of the ZeroPage
        zeroPageAddr += m_X;                              //
        cycles--;
        m_A = ReadByte(cycles, zeroPageAddr, mem);
    }

    void m_JSR(u32 cycles, Mem::Mem& mem)
    {
        Word subRoutAddr = FetchWord(cycles, mem);        // get the subroutine address
        mem.WriteWord(m_PC - 1, m_SP, cycles);            // pushes the return address -1 on to the stack
        m_PC = subRoutAddr;
        cycles--;
    }
};

};

#endif
