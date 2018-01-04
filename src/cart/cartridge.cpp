#include "cartridge.h"
#include "files.h"
#include "log.h"

Cartridge::Cartridge(const std::string& filename)
{
    // read the data
    auto data = read_bytes(filename);
    log_info("Loaded %d KB data from file: %s", data.size() / 1024, filename.c_str());

    // copy the cartridge rom data
    m_data = std::vector<u8>(data.begin(), data.end());

    // get type
    u8 type_code = m_data[cart_header::cartridge_type];
    m_type = get_type(type_code);

    // get version
    m_version = m_data[cart_header::version_number];
    
    // get rom size
    u8 rom_size_code = m_data[cart_header::rom_size];
    m_rom_size = get_rom_size(rom_size_code);

    // get ram size
    u8 ram_size_code = m_data[cart_header::ram_size];
    m_ram_size = get_ram_size(ram_size_code);

    // get game title
    char game_title[title_length];
    for (int i = 0; i < title_length; ++i) {
        game_title[i] = static_cast<char>(m_data[cart_header::title + i]);
    }
    m_title = std::string(game_title);

    log_info("Title:\t\t%s (version: %d)", m_title.c_str(), m_version);
    log_info("Cartridge:\t\t%s", describe(m_type).c_str());
    log_info("ROM size:\t\t%s", describe(m_rom_size).c_str());
    log_info("RAM size:\t\t%s", describe(m_ram_size).c_str());
}

u8 Cartridge::read(const Address& address)
{
    // TODO: validation needed
    return m_data[address.value()];
}

std::string game_title() const
{
    return m_title;
}
