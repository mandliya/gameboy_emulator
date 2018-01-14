
### Rough/ Random thoughts on implementation.

#### Memory addresses
0xC000-0xCFFF are not yet implemented in read_memory function.
This area is Working RAM 2.
It is echoed same as 0xE000-0xFDFF for which we have read case.
Do both need to be there or just this one is enough?

#### FF0F - Interrupt Flag (R/W) <-- Not implemented yet.

  Bit 0: V-Blank  Interrupt Request (INT 40h)  (1=Request)
  Bit 1: LCD STAT Interrupt Request (INT 48h)  (1=Request)
  Bit 2: Timer    Interrupt Request (INT 50h)  (1=Request)
  Bit 3: Serial   Interrupt Request (INT 58h)  (1=Request)
  Bit 4: Joypad   Interrupt Request (INT 60h)  (1=Request)


### For MBC 1:

0000-1FFF – RAM Enable Register (1- )
2000-3FFF – ROM Bank Number
4000-5FFF – RAM Bank Number/Upper Bits of ROM Bank Number
6000-7FFF – ROM/RAM Mode Select
