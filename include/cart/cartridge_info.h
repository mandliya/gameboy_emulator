#pragma once

#include "definitions.h"
#include <string>

const int title_length = 11;

namespace cart_header {
    const int entry_point = 0x100;
    const int logo = 0x104;
    const int title = 0x134;
    const int manufacturer_code = 0x13F;
    const int cgb_flag = 0x143;
    const int new_license_code = 0x144;
    const int sgb_flag = 0x146;
    const int cartridge_type = 0x147;
    const int rom_size = 0x148;
    const int ram_size = 0x149;
    const int destination_code = 0x14A;
    const int old_license_code = 0x14B;
    const int version_number = 0x14C;
    const int header_checksum = 0x14D;
    const int global_checksum = 0x14E;
}   // namespace header

enum class cartridge_type {
    ROM_ONLY,
    MBC1,
    MBC2,
    MBC3,
    MBC4,
    MBC5,
    Unknown
};

extern cartridge_type get_type(u8 type);
extern std::string describe(cartridge_type type);
extern std::string get_license(u16 old_license, u16 new_license);

enum class ROM_size {
    KB32,   // 32 KB
    KB64,   // 64 KB
    KB128,  // 128 KB
    KB256,  // 256 KB
    KB512,  // 512 KB
    MB1,    // 1 MB
    MB2,    // 2 MB
    MB4,    // 4 MB
    MB1p1,  // 1.1 MB
    MB1p2,  // 1.2 MB
    MB1p5,  // 1.5 MB
};

extern ROM_size get_rom_size(u8 rom_size);
extern std::string describe(ROM_size size);

enum class RAM_size {
    None,
    KB2,    // 2 KB
    KB8,    // 8 KB
    KB32,   // 32 KB
    KB128   // 128 KB
};

extern RAM_size get_ram_size(u8 ram_size);
extern std::string describe(RAM_size size);

enum class Destination {
    Japanese,
    Non_Japanese
};

extern Destination get_destination(u8 destination);
extern std::string describe(Destination destination);