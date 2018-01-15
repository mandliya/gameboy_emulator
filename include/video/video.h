#pragma once
#include "register.h"

class Video {
public:
    u8 get_control_byte();
    u8 get_scroll_y();
    u8 get_scroll_x();
    u8 get_line_y();
private:
    u8 m_control_byte;
    ByteRegister m_scroll_x;
    ByteRegister m_scroll_y;
    ByteRegister m_LY;  // Y position of the line. 
};