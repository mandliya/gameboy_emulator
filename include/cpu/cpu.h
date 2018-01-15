#pragma once

#include "definitions.h"
#include "register.h"

class CPU {
public:
    u8 get_interrupt_flag();
    void set_interrupt_flag(u8 byte);
private:
    ByteRegister interrupt_enable_reg;
    ByteRegister interrupt_flag_reg;
};