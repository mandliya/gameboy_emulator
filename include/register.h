#pragma once

#include "definitions.h"

class ByteRegister : NonCopyable {
public:
    virtual ~ByteRegister() = default;
    virtual void set(u8 value);
    void reset();
    u8 value() const;

    bool check_bit(u8 bit) const;
    void set_bit_to(u8 bit, bool set);

    void increment();
    void decrement();
    bool operator==(u8 other) const;

protected:
    u8 val;
};

class FlagRegister : public ByteRegister {
public:
    void set(u8 new_value) override;
    void set_flag_zero(bool set);
    void set_flag_substract(bool set);
    void set_flag_half_carry(bool set);
    void set_flag_carry(bool set);

    bool flag_zero() const;
    bool flag_substract() const;
    bool flag_half_carry() const;
    bool flag_carry() const;

    u8 flag_zero_value() const;
    u8 flag_substract_value() const;
    u8 flag_half_carry_value() const;
    u8 flag_carry_value() const;
};

class WordValue {
public:
    virtual ~WordValue() = default;
    virtual void set(u16 new_value) = 0;
    virtual u16 value() const = 0;
    virtual u8 low() const = 0;
    virtual u8 high() const = 0;
};

class WordRegister : public WordValue {
public:
    void set(u16 new_value) override;
    u16 value() const override;
    u8 low() const override;
    u8 high() const override;
    void increment();
    void decrement();
private:
    u16 val;
};

class RegisterPair : public WordValue, NonCopyable {
public:
    RegisterPair(ByteRegister& high, ByteRegister& low);
    void set(u16 word) override;
    u16 value() const override;
    u8 low() const override;
    u8 high() const override;
    void increment();
    void decrement();

private:
    ByteRegister& high_byte;
    ByteRegister& low_byte;
};