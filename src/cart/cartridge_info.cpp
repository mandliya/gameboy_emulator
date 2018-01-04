#include "cartridge_info.h"
#include "log.h"

cartridge_type  get_type(u8 type)
{
    switch(type) {
        case 0x00:
        case 0x08:
        case 0x09:
            return cartridge_type::ROM_ONLY;

        case 0x01:
        case 0x02:
        case 0x03:
        case 0xFF:
            return cartridge_type::MBC1;
        
        case 0x05:
        case 0x06:
            return cartridge_type::MBC2;
        
        case 0x0F:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
            return cartridge_type::MBC3;

        case 0x15:
        case 0x16:
        case 0x17:
            return cartridge_type::MBC4;

        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
            return cartridge_type::MBC5;

        case 0x0B:
        case 0x0C:
        case 0x0D:
        case 0x20:
        case 0x22:
        case 0xFC:
        case 0xFD:
        case 0xFE:
            return cartridge_type::Unknown;

        default:
            log_error("Unknown cartridge type %X", type);
            return cartridge_type::Unknown;
    }
}

std::string describe(cartridge_type type)
{
    switch(type) {
        case cartridge_type::ROM_ONLY:
            return "ROM ONLY";
        case cartridge_type::MBC1:
            return "MBC1";
        case cartridge_type::MBC2:
            return "MBC2";
        case cartridge_type::MBC3:
            return "MBC3";
        case cartridge_type::MBC4:
            return "MBC4";
        case cartridge_type::MBC5:
            return "MBC5";
        case cartridge_type::Unknown:
            return "Unknown";
    }
}

std::string get_license(u16 old_license, u16 new_license)
{
    log_error("License is not implemented");
    return "NOT IMPLEMENTED";
}

ROM_size get_rom_size(u8 size_code)
{
    switch(size_code) {
        case 0x00:
            return ROM_size::KB32;
        case 0x01:
            return ROM_size::KB64;
        case 0x02:
            return ROM_size::KB128;
        case 0x03:
            return ROM_size::KB32;
        case 0x04:
            return ROM_size::KB32;
        case 0x05:
            return ROM_size::MB1;
        case 0x06:
            return ROM_size::MB2;
        case 0x07:
            return ROM_size::MB4;
        case 0x52:
            return ROM_size::MB1p1;
        case 0x53:
            return ROM_size::MB1p2;
        case 0x54:
            return ROM_size::MB1p5;
        default:
            log_error("Unknown rom size: %X", size_code);
            return ROM_size::KB32;
    }
}

std::string describe(ROM_size size)
{
    switch(size) {
        case 0x00:
            return "32 KB (No ROM Banking)";
        case 0x01:
            return "64 KB (4 Banks)";
        case 0x02:
            return "128 KB (8 Banks)";
        case 0x03:
            return "256 KB (16 Banks)";
        case 0x04:
            return "512 KB (32 Banks)";
        case 0x05:
            return "1 MB (64 Banks)";
        case 0x06:
            return "2 MB (128 Banks)";
        case 0x07:
            return "4 MB (256 Banks)";
        case 0x52:
            return "1.1 MB (72 Banks)";
        case 0x53:
            return "1.2 MB (80 Banks)";
        case 0x54:
            return "1.5 MB (96 Banks)";
    }
}

RAM_size get_ram_size(u8 size_code)
{
    switch(size_code) {
        case 0x00:
            return RAM_size::None;
        case 0x01:
            return RAM_size::KB2;
        case 0x02:
            return RAM_size::KB8;
        case 0x03:
            return RAM_size::KB32;
        case 0x04:
            return RAM_size::KB128;
        default:
            log_error("Unknown RAM SIZE: %X", size_code);
            return RAM_size::None;
    }
}

std::string describe(RAM_size size)
{
    switch(size) {
        case RAM_size::None:
            return "NO RAM";
        case RAM_size::KB2:
            return "RAM: 2 KB";
        case RAM_size::KB8:
            return "RAM: 8 KB";
        case RAM_size::KB32:
            return "RAM: 32 KB";
        case RAM_size::KB128:
            return "RAM: 128 KB";
        default:
            log_error("Unknown RAM Size: %X", size);
            return "Unknown RAM Size";
    }
}

Destination get_destination(u8 destination)
{
    switch(destination) {
        case 0x00:
            return Destination::Japanese;
        case 0x01:
            return Destination::Non_Japanese;
        default:
            log_error("Unknown destination: %X", destination);
            return Destination::Non_Japanese;
    }
}

std::string describe(Destination destination)
{
    switch(destination) {
        case Destination::Japanese:
            return "Japanese";
        case Destination::Non_Japanese:
            return "Non-Japanese";
    }
}