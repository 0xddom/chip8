#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

void system_ins(VM *vm) {
  fprintf (stderr, "SYS instruction encountered. This instruction is ignored\n");
  next_ins (vm);
}

void illegal_ins(VM *vm) {
  fprintf (stderr, "Illegal instruction encountered at position "
	   "0x%08x: 0x%04x\nThe VM has aborted.", vm->pc, current_ins (vm));
  vm->aborted = 1;
}

void clear_display(VM *vm) {
  puts ("clear_display TODO");
  next_ins (vm);
}

void return_sub(VM *vm) {
  fprintf (stderr, "return_sub TODO\n");
  vm->pc += 2;
  exit (5);
}

void jump_addr(VM *vm) {
  uint16_t addr = current_ins (vm) & 0x0fff;
  vm->pc = addr;
}

void call_sub(VM *vm) {
  fprintf (stderr, "call_sub TODO\n");
  exit (5);
}

void skip_next_if_equal(VM *vm) {
  uint16_t ins = current_ins (vm);
  uint8_t x = (ins & 0x0f00) >> 8;
  uint8_t byte = (ins & 0x00ff);

  if (vm->v[x] == byte) next_ins (vm);
  next_ins (vm);
}

void skip_next_if_not_equal(VM * vm) {
  uint16_t ins = current_ins (vm);
  uint8_t x = (ins & 0x0f00) >> 8;
  uint8_t byte = (ins & 0x00ff);

  if (vm->v[x] != byte) next_ins (vm);
  next_ins (vm); 
}

void skip_next_reg(VM *vm) {
  uint16_t ins = current_ins (vm);
  uint8_t x = (ins & 0x0f00) >> 8;
  uint8_t y = (ins & 0x00f0) >> 4;

  if (vm->v[x] == vm->v[y]) next_ins (vm);
  next_ins (vm);
}

void load_byte_in_reg(VM *vm) {
  uint16_t ins = current_ins (vm);
  uint8_t x = (ins & 0x0f00) >> 8;
  uint8_t byte = (ins & 0x00ff);

  vm->v[x] = byte;
  next_ins (vm);
}

void add_byte_to_reg(VM *vm) {
  uint16_t ins = current_ins (vm);
  uint8_t x = (ins & 0x0f00) >> 8;
  uint8_t byte = (ins & 0x00ff);

  vm->v[x] += byte;
  next_ins (vm);
}

void load_reg_in_reg(VM *vm) {
  uint16_t ins = current_ins (vm);
  uint8_t x = (ins & 0x0f00) >> 8;
  uint8_t y = (ins & 0x00f0) >> 4;

  vm->v[x] = vm->v[y];
  next_ins (vm);
}

void or_registers(VM *vm) {
  uint16_t ins = current_ins (vm);
  uint8_t x = (ins & 0x0f00) >> 8;
  uint8_t y = (ins & 0x00f0) >> 4;

  vm->v[x] |= vm->v[y];
  next_ins (vm);
}

void and_registers(VM *vm) {
  uint16_t ins = current_ins (vm);
  uint8_t x = (ins & 0x0f00) >> 8;
  uint8_t y = (ins & 0x00f0) >> 4;

  vm->v[x] &= vm->v[y];
  next_ins (vm);
}

void xor_registers(VM *vm) {
  uint16_t ins = current_ins (vm);
  uint8_t x = (ins & 0x0f00) >> 8;
  uint8_t y = (ins & 0x00f0) >> 4;

  vm->v[x] ^= vm->v[y];
  next_ins (vm);
}

void add_registers_with_carry(VM *vm) {
  uint16_t ins = current_ins (vm);
  uint8_t x = (ins & 0x0f00) >> 8;
  uint8_t y = (ins & 0x00f0) >> 4;

  uint8_t vx = vm->v[x];
  uint8_t vy = vm->v[y];
  uint8_t carry = 0;
  
  uint16_t sum = vx + vy;
  if (sum > 255) {
    carry = 1;
    sum = 255;
  }
  vm->v[x] = (uint8_t)sum;
  next_ins (vm);
}
