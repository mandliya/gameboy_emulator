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
    Color0,     /* Alpha */
    Color1,     /* Red */
    Color2,     /* Green */
    Color3,     /* Blue */
};

enum class Color {
    Alpha,
    Red,
    Green,
    Blue,
};

struct BGPalette {
    Color color0 = Color::Alpha;
    Color color1 = Color::Red;
    Color color2 = Color::Green;
    Color color3 = Color::Blue;
};

enum class GBKeys {
    Right_key = 0,
    Left_key = 1,
    Up_key = 2,
    Down_key = 3,
    A_key = 4,
    B_key = 5,
    Select_key = 6,
    Start_key = 7
};

class Cycles {
public:
    Cycles(uint cycles) : m_cycles(cycles) {}
private:
    const uint m_cycles;
};