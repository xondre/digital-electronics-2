## Pre-Lab preparation

1. Use **AVR® Instruction Set Manual** from Microchip [Online Technical Documentation](https://onlinedocs.microchip.com/), find the description of selected instructions, and complete the table.

   | **Instruction** | **Operation** | **Description** | **Cycles** |
   | :-- | :-: | :-- | :-: |
   | `add Rd, Rr` | Rd = Rd + Rr | Add register Rr to register Rd w/o carry and save result in Rd | 1 |
   | `andi Rd, K` | Rd = Rd and K | Logical AND between register Rd and 8-bit constant K | 1 |
   | `bld Rd, b` | Rd(b) = T | Copies the T bit in the SREG to bit b in register Rd | 1 |
   | `bst Rd, b` | T = Rd(b) | Stores bit b from Rd to the T bit in SREG | 1 |
   | `com Rd` | Rd = 0xFF - Rd | performs a One’s Complement of register Rd | 1 |
   | `eor Rd, Rr` | Rd = Rd xor Rr | Performs XOR between the contents of Rd and Rr, places the result in Rd | 1 |
   | `mul Rd, Rr` | R1:R0 = Rd and Rr | Unsigned numbers in Rd, Rr are multiplied, result is placed into bytes R1:R0 | 1 |
   | `pop Rd` | Rd = STACK | loads Rd with a byte from the STACK. Stack Pointer is pre-incremented by 1 before the POP | 1 |
   | `push Rr` | STACK = Rr | stores register Rr on the STACK. Stack Pointer is post-decremented by 1 after the PUSH | 1 |
   | `ret` | depends | Returns from the subroutine. The return address is loaded from the STACK. The Stack Pointer uses a pre-increment scheme during RET. | depends |
   | `rol Rd` |  | Shifts all bits in Rd one place to the left. The C flag is shifted into bit 0 of Rd. Bit 7 is shifted into the C flag. This operation, combined with LSL, effectively multiplies multi-byte signed and unsigned values by two | 1 |
   | `ror Rd` |  | Shifts all bits in Rd one place to the right. The C flag is shifted into bit 7 of Rd. Bit 0 is shifted into the C flag. This operation, combined with ASR, effectively divides multi-byte signed values by two. Combined with LSR, it effectively divides multi-byte unsigned values by two. The Carry flag can be used to round the result. | 1 |
