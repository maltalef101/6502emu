#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"

namespace CPU {

void ProcessorStatus::setAllToZero() { C = Z = I = D = B = V = N = 0; }; // sets all statusflags to zero

}
