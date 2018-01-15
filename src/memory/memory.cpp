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

bool Memory::is_boot_rom_active() const
{
    /* Writing the value of 1 to the address 0xFF50 unmaps the boot ROM */
    return read(0xFF50) != 0x01;
}

u8 Memory::memory_read(const Address& address)
{
    return m_memory.at(address.value);
}

void Memory::memory_write(const Address& address, u8 byte)
{
    m_memory.at(address.value()) = byte;
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
        return m_cpu.interrupt_enable_reg.value();
    }

    fatal_error("Attempted to read from unmapped memory address 0x%X", address.value());
}

void Memory::write(const Address& address, const u8 byte)
{
    if (address.in_range(0x0000, 0x7FFF)) {
        log_warning("WARNING: Trying to write to cartridge rom at address %04X- value: 0x%X",
            address.value(), byte);
        return;
    }

    // VRAM from 0x8000 to 0x9FFF.
    if (address.in_range(0x8000, 0x9FFF)) {
        memory_write(address, byte);
        return;
    }

    // Cartridge RAM
    if (address.in_range(0xA000, 0xBFFF)) {
        memory_write(address, byte);
        return;
    }

    // Game Boy’s working RAM bank 1 (0xD000 - 0xDFFF)
    if (address.in_range(0xD000, 0xDFFF)) {
        memory_write(address, byte);
    }

    // Mirrored memory area, (0xE000-0xFDFF) echoes (0xC000 – 0xDDFF)
    if (address.in_range(0xE000, 0xFDFF)) {
        log_warning("Trying to write to mirrored memory area");
        auto mirror_address = Address(address.value - 0x2000);
        memory_write(mirror_address, byte);
        return;
    }

    // FE00-FE9F Sprite Attribute Table (OAM)
    if (address.in_range(0xFE00, 0xFE9F)) {
        memory_write(address, byte);
        return;
    }

    // Devices Mappings. Used to access I/O devices
    if (address.in_range(0xFF00, 0xFF7F)) {
        write_io(address, byte);
        return;
    }

    // High RAM Area (0xFF80 - 0xFFFE) / Zero Page Ram
    if (address.in_range(0xFF80, 0xFFFE)) {
        memory_write(address, byte);
    }

    // Interrupt enable register
    if (address == 0xFFFF) {
        m_cpu.interrupt_enable_reg.set(byte);
        return;
    }

    fatal_error("Attempted to write to unmapped memory address 0x%X", address.value());
}

u8 Memory::read_io(const Address& address)
{
    switch(address.value()) {
        // Joypad register
        case 0xFF00:
            // TODO
            return 0xFF;

        // Serial transfer data
        case 0xFF01:
            // TODO
            return 0xFF;

        // Serial transfer control 
        case 0xFF02:
            // TODO
            return 0xFF;

        // Interrupt flag register
        case 0xFF0F:
            return m_cpu.get_interrupt_flag();
        
        // Control byte;
        case 0xFF40:
            return m_video.get_control_byte();
        
        // LCD stat register
        case 0xFF41:
            // TODO
            return 0xFF;

        // Scroll Y value
        case 0xFF42:
            return m_video.get_scroll_y();

        // Current scan line number in register LY
        case 0xFF44:
            return m_video.get_line_y();

        // Prepare speed switch register
        case 0xFF4D:
            // TODO
            return 0x0;

        // Disable boot rom switch register
        case 0xFF50:
            return memory_read(address);

        default:
            log_error("Read from an unknown IO address 0x%X", address.value());
            exit(1);
    }
}

void Memory::write_io(const Address& address, const u8 byte)
{
    switch(address.value()) {

        // Joypad
        case 0xFF00:
            // TODO
            return;

        // serial transfer data
        case 0xFF01:
            // TODO
            return;

        // Serial tranfer data
        case 0xFF02:
            // TODO
            return;

        // Time Control
        case 0xFF07:
            // TODO
            return;

        // CPU interrupt flag set
        case 0xFF0F:
            m_cpu.set_interrupt_flag(byte);
            return;

        // Audio channel 1 : Tone and sweep
        case 0xFF10:
        case 0xFF11:
        case 0xFF12:
        case 0xFF13:
        case 0xFF14:
            // TODO
            return;

        // Audio channel 2: Tone
        case 0xFF16:
        case 0xFF17:
        case 0xFF18:
        case 0xFF19:
            // TODO
            return;

        // Audio channel 3: Wave output
        case 0xFF1A:
        case 0xFF1B:
        case 0xFF1C:
        case 0xFF1D:
        case 0xFF1E:
            // TODO
            return;

        // Audio channel 4: Noise
        case 0xFF20:
        case 0xFF21:
        case 0xFF22:
        case 0xFF23:
            // TODO 
            return;

        // Audio sound control registers
        case 0xFF24:
            // TODO
            // Write to channel control address
            return;
        
        case 0xFF25:
            // TODO
            // Write to selection of sound output (Not sure)
            return;
        
        case 0xFF26:
            // TODO
            return;

        // More needs to be added.
    }
}

