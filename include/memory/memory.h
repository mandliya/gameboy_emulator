#pragma once

#include "address.h"
#include "cartridge.h"
#include <vector>

class Video;
class CPU;

class Memory {
public:
    Memory(Cartridge& cartridge, CPU& cpu, Video& video);
    u8 read(const Address& address) const;
    void write(const Address& address, u8 byte);

private:
    bool is_boot_rom_active() const;
    u8 read_io(const Address& address) const;
    void write_io(const Address& address, u8 byte);

    u8 memory_read(const Address& address) const;
    void memory_write(const Address& address, u8 byte);

    Cartridge& m_cartridge;
    CPU& m_cpu;
    Video& m_video;
    std::vector<u8> m_memory;
};