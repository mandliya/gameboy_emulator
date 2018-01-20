#pragma once
#include "register.h"

class Video {
public:
    u8 get_control_byte();
    void set_control_byte(u8 byte);
    u8 get_scroll_y();
    void set_scroll_y(u8 byte);
    u8 get_scroll_x();
    void set_scroll_x(u8 byte);
    u8 get_line_y();
    void set_line_y(u8 byte);
    u8 get_bg_palette();
    void set_bg_palette(u8 byte);
private:
    u8 m_control_byte;
    ByteRegister m_scroll_x;
    ByteRegister m_scroll_y;
    ByteRegister m_LY;  // Y position of the line. 
    ByteRegister m_bg_palette;  // background palette
};