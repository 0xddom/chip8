#include "vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

VM *create_vm() {
  VM *vm = (VM*)malloc (sizeof (VM));

  if (vm == NULL) {
    fprintf (stderr, "Failed to init the VM\n");
    exit (2);
  }
  return vm;
}

int init_vm(VM *vm, char *romfn) {
  int i, readed;
  FILE *f;
  
  if (!strcmp ("-", romfn)) f = stdin;
  else f = fopen (romfn, "rb");

  if (f == NULL) {
    fprintf (stderr, "Failed to load ROM: %s\n", romfn);
    exit (3);
  }

  readed = fread (vm->mem + STARTADDR, 1, MEMSIZ - STARTADDR, f);
  if (readed <= 0) {
    fprintf (stderr, "Failed to read ROM: %s\n", romfn);
    fclose (f);
    exit (4);
  }

  if (f != stdin) fclose (f);
  
  vm->i = 0;
  vm->pc = STARTADDR;
  vm->sp = 0; // XXX: Set this to the real stack
  vm->aborted = 0;

  for (i = 0; i < REGSIZ; i++) vm->v[i] = 0;

  return readed;
  
}

void next_ins(VM *vm) {
  vm->pc += 2;
}

void destroy_vm(VM *vm) {
  if (vm != NULL) free (vm);
}

uint16_t current_ins(VM *vm) {
  uint8_t hi = vm->mem[vm->pc];
  uint8_t lo = vm->mem[vm->pc + 1];

  return (hi << 8) + lo;
}


