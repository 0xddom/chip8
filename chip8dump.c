#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "vm.h"
#include "disass.h"

void usage(char *);

int main(int argc, char **argv) {
  VM *vm;
  int i;
  
  if (argc < 2) usage (argv[0]);

  vm = create_vm ();
  int prog_siz = init_vm (vm, argv[1]) / 2;;

  for (i = 0; i < prog_siz; i++) {
    uint16_t ins = current_ins (vm);
    printf ("%08x:  %04x  ", i + STARTADDR, ins);
    disass_ins (ins);
    next_ins (vm);
  }
  
  destroy_vm (vm);

  return 0;
}

void usage(char *s) {
  fprintf (stderr, "[USAGE] %s <filename>\n", s);
  exit (1);
}
