.global _start
.global save_registers
.global restore_registers
.section .text
_start:
save_registers:
  stwu 1, -0x200(1)
# gprs
  stw 0, 0x00(1)
  stw 2, 0x04(1)
  stw 3, 0x08(1)
  stw 4, 0x0c(1)
  stw 5, 0x10(1)
  stw 6, 0x14(1)
  stw 7, 0x18(1)
  stw 8, 0x1c(1)
  stw 9, 0x20(1)
  stw 10, 0x24(1)
  stw 11, 0x28(1)
  stw 12, 0x2c(1)
  stw 13, 0x30(1)
  stw 14, 0x34(1)
  stw 15, 0x38(1)
  stw 16, 0x3c(1)
  stw 17, 0x40(1)
  stw 18, 0x44(1)
  stw 19, 0x48(1)
  stw 20, 0x4c(1)
  stw 21, 0x50(1)
  stw 22, 0x54(1)
  stw 23, 0x58(1)
  stw 24, 0x5c(1)
  stw 25, 0x60(1)
  stw 26, 0x64(1)
  stw 27, 0x68(1)
  stw 28, 0x6c(1)
  stw 29, 0x70(1)
  stw 30, 0x74(1)
  stw 31, 0x78(1)
# floats
  stfd 0, 0x7c(1)
  stfd 1, 0x84(1)
  stfd 2, 0x8c(1)
  stfd 3, 0x94(1)
  stfd 4, 0x9c(1)
  stfd 5, 0xa4(1)
  stfd 6, 0xac(1)
  stfd 7, 0xb4(1)
  stfd 8, 0xbc(1)
  stfd 9, 0xc4(1)
  stfd 10, 0xcc(1)
  stfd 11, 0xd4(1)
  stfd 12, 0xdc(1)
  stfd 13, 0xe4(1)
  stfd 14, 0xec(1)
  stfd 15, 0xf4(1)
  stfd 16, 0xfc(1)
  stfd 17, 0x104(1)
  stfd 18, 0x10c(1)
  stfd 19, 0x114(1)
  stfd 20, 0x11c(1)
  stfd 21, 0x124(1)
  stfd 22, 0x12c(1)
  stfd 23, 0x134(1)
  stfd 24, 0x13c(1)
  stfd 25, 0x144(1)
  stfd 26, 0x14c(1)
  stfd 27, 0x154(1)
  stfd 28, 0x15c(1)
  stfd 29, 0x164(1)
  stfd 30, 0x16c(1)
  stfd 31, 0x174(1)
# special regs
  mflr 0
  stw 0, 0x178(1)
  mfctr 0
  stw 0, 0x17c(1)
  mfxer 0
  stw 0, 0x180(1)
  mfcr 0
  stw 0, 0x184(1)
  mffs 0
  stfd 0, 0x188(1)

# jank broken compiler workaround?
  stwu 1, -0x800(1)

.size save_registers, .-save_registers

restore_registers:

  addi 1, 1, 0x800

  lwz 0, 0x178(1)
  mtlr 0
  lwz 0, 0x17c(1)
  mtctr 0
  lwz 0, 0x180(1)
  mtxer 0
  lwz 0, 0x184(1)
  mtcr 0
  lfd 0, 0x188(1)
  mtfsf 0, 0

  lwz 0, 0x00(1)
  lwz 2, 0x04(1)
  lwz 3, 0x08(1)
  lwz 4, 0x0c(1)
  lwz 5, 0x10(1)
  lwz 6, 0x14(1)
  lwz 7, 0x18(1)
  lwz 8, 0x1c(1)
  lwz 9, 0x20(1)
  lwz 10, 0x24(1)
  lwz 11, 0x28(1)
  lwz 12, 0x2c(1)
  lwz 13, 0x30(1)
  lwz 14, 0x34(1)
  lwz 15, 0x38(1)
  lwz 16, 0x3c(1)
  lwz 17, 0x40(1)
  lwz 18, 0x44(1)
  lwz 19, 0x48(1)
  lwz 20, 0x4c(1)
  lwz 21, 0x50(1)
  lwz 22, 0x54(1)
  lwz 23, 0x58(1)
  lwz 24, 0x5c(1)
  lwz 25, 0x60(1)
  lwz 26, 0x64(1)
  lwz 27, 0x68(1)
  lwz 28, 0x6c(1)
  lwz 29, 0x70(1)
  lwz 30, 0x74(1)
  lwz 31, 0x78(1)

  lfd 0, 0x7c(1)
  lfd 1, 0x84(1)
  lfd 2, 0x8c(1)
  lfd 3, 0x94(1)
  lfd 4, 0x9c(1)
  lfd 5, 0xa4(1)
  lfd 6, 0xac(1)
  lfd 7, 0xb4(1)
  lfd 8, 0xbc(1)
  lfd 9, 0xc4(1)
  lfd 10, 0xcc(1)
  lfd 11, 0xd4(1)
  lfd 12, 0xdc(1)
  lfd 13, 0xe4(1)
  lfd 14, 0xec(1)
  lfd 15, 0xf4(1)
  lfd 16, 0xfc(1)
  lfd 17, 0x104(1)
  lfd 18, 0x10c(1)
  lfd 19, 0x114(1)
  lfd 20, 0x11c(1)
  lfd 21, 0x124(1)
  lfd 22, 0x12c(1)
  lfd 23, 0x134(1)
  lfd 24, 0x13c(1)
  lfd 25, 0x144(1)
  lfd 26, 0x14c(1)
  lfd 27, 0x154(1)
  lfd 28, 0x15c(1)
  lfd 29, 0x164(1)
  lfd 30, 0x16c(1)
  lfd 31, 0x174(1)

  addi 1, 1, 0x200

.size restore_registers, .-restore_registers
