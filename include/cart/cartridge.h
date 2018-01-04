#pragma once

#include "cartridge_info.h"
#include "address.h"
#include <vector>
#include <string>

class Cartridge {
public:
    Cartridge(const std::string& filename);
    u8 read(const Address& address);
    std::string game_title() const;
    
private:
    std::vector<u8> m_data;
    std::string m_title;
    cartridge_type m_type;
    Destination m_destination;
    ROM_size m_rom_size;
    RAM_size m_ram_size;
    std::string m_license_code;
    u8 m_version;
    u16 m_header_checksum;
    u16 m_global_checksum;
    bool m_supports_cgb;
    bool m_supports_sgb;
};