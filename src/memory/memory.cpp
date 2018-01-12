#include "memory.h"
#include "boot.h"
#include "log.h"
#include "video.h"
#include <cstdlib>

Memory::Memory(Cartridge& cartridge, CPU& cpu, Video& video):
    m_cartridge {cartridge},
    m_cpu {cpu},
    m_video {video}
{
    m_memory = std::vector<u8>(0x10000);
}

boot is_boot_rom_active() const
{
    /* Writing the value of 1 to the address 0xFF50 unmaps the boot ROM */
    return read(0xFF50) != 0x01;
}

u8 Memory::read(const Address& address) const
{
    if (address.in_range(0x0, 0x7FFF)) {
        // If boot rom is active.
        if (address.in_range(0x0, 0xFF) && is_boot_rom_active()) {
            return bootDMG[address.value()];
        }
        return m_cartridge.read(address);
    }

    // VRAM from 0x8000 to 0x9FFF.
    if (address.in_range(0x8000, 0x9FFF)) {
        return memory_read(address);
    }

    // Cartridge RAM
    if (address.in_range(0xA000, 0xBFFF)) {
        log_unimplemented("Attempt to read from Cartridge RAM")
        return memory_read(address);
    }

    // Game Boy’s working RAM bank 1 (0xD000 - 0xDFFF)
    if (address.in_range(0xD000, 0xDFFF)) {
        return memory_read(address);
    }

    // Mirrored memory area, (0xE000-0xFDFF) echoes (0xC000 – 0xDDFF)
    if (address.in_range(0xE000, 0xFDFF)) {
        auto mirror_address = Address(address.value - 0x2000);
        return memory_read(mirror_address);
    }

    // FE00-FE9F Sprite Attribute Table (OAM)
    if (address.in_range(0xFE00, 0xFE9F)) {
         return memory_read(address);
    }

    // Devices Mappings. Used to access I/O devices
    if (address.in_range(0xFF00, 0xFF7F)) {
        return read_io(address);
    }

    // High RAM Area (0xFF80 - 0xFFFE) / Zero Page Ram
    if (address.in_range(0xFF80, 0xFFFE)) {
        return memory_read(address);
    }

    // Interrupt enable register
    if (address == 0xFFFF) {
        return m_cpu.interrupt_register.value();
    }

    fatal_error("Attempted to read unmapped memory address 0x%X", address.value());
}