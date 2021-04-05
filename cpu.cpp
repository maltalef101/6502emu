#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"

int main()
{
    CPU::CPU cpu;
    Mem::Mem mem;
    cpu.Reset(mem);
    mem[0xFFFC] = 0x20;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;
    mem[0x4242] = 0xA9;
    mem[0x4243] = 0x84;
    cpu.Exec(9, mem);
    return 0;
}
