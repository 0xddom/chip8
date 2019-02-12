#ifndef _VM_H
#define _VM_H

#include <stdint.h>

#define MEMSIZ 4096
#define REGSIZ 16
#define STARTADDR 512

// VM Instructions
#define CLS  0x00e0
#define RET  0x00ee
#define JP   0x1000
#define CALL 0x2000
#define SE   0x3000
#define SNE  0x4000
#define TEST 0x5000
#define LD   0x6000
#define ADD  0x7000
#define LDR  0x0000
#define OR   0x0001
#define AND  0x0002
#define XOR  0x0003
#define ADDR 0x0004
#define SUBR 0x0005
#define SHR  0x0006
#define SUBN 0x0007
#define SHL  0x000e
#define SNER 0x9000
#define LDI  0xa000
#define JPR  0xb000
#define RND  0xc000
#define DRW  0xd000
#define SKP  0x009e
#define SKNP 0x00a1
#define LDDT 0x0007
#define LDK  0x000a
#define LDDTSET 0x0015
#define LDST 0x0018
#define ADDI 0x001e
#define LD2  0x0029
#define LD3  0x0033
#define LD5  0x0055
#define LD6  0x0065
// End of instructions

typedef struct {
  uint8_t mem[MEMSIZ];
  uint8_t v[REGSIZ];
  uint16_t i;
  uint8_t sp;
  uint16_t pc;
  int aborted;
} VM;

typedef void (*ins_handler)(VM*);

VM *create_vm();
int init_vm(VM *, char *);
void destroy_vm(VM *);
uint16_t current_ins(VM *);
void next_ins(VM *);
ins_handler parse_ins(uint16_t);

// VM Instruction handlers
void illegal_ins(VM *); //
void system_ins(VM *); // SYS addr
void clear_display(VM *); // CLS
void return_sub(VM *); // RET
void jump_addr(VM *); // JP addr
void call_sub(VM *);  // CALL addr
void skip_next_if_equal(VM *); // SE Vx, byte
void skip_next_if_not_equal(VM *); // SNE Vx, byte
void skip_next_reg(VM *); // SE Vx, Vy
void load_byte_in_reg(VM *); // LD Vx, byte
void add_byte_to_reg(VM *); // ADD Vx, byte
void load_reg_in_reg(VM *); // LD Vx, Vy
void or_registers(VM *); // OR Vx, Vy
void and_registers(VM *); // AND Vx, Vy
void xor_registers(VM *); // XOR Vx, Vy
void add_registers_with_carry(VM *); // ADD Vx, Vy

// End of vm instruction handlers

#endif
