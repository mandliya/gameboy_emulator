#pragma once

#include <cstdlib>
#include <cstdint>

using uint = unsigned int;
using u8 = uint8_t;
using u16 = uint16_t;
using s8 = int8_t;
using s16 = int16_t;

struct NonCopyable {
    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable() = default;
};

#define fatal_error(...) \
    log_error("Fatal error @[%s, %d]", __func__, __LINE__); \
    log_error(__VA_ARGS__); \
    exit(1);

const int GAMEBOY_WIDTH = 160;
const int GAMEBOY_HEIGHT = 144;
const int CLOCK_RATE = 4194304;

enum class GBColor {
    Color0,     /* White */
    Color1,     /* Light Gray */
    Color2,     /* Dark Gray */
    Color3,     /* Black */
};

enum class Color {
    White,
    LightGray,
    DarkGray,
    Black,
};

struct BGPalette {
    Color color0 = Color::White;
    Color color1 = Color::LightGray;
    Color color2 = Color::DarkGray;
    Color color3 = Color::Black;
};

class Cycles {
public:
    Cycles(uint cycles) : m_cycles(cycles) {}
private:
    const uint m_cycles;
};