#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "vm.h"

void usage(char *);

int main(int argc, char **argv) {
  VM *vm;

  if (argc < 2) usage (argv[0]);

  vm = create_vm ();
  init_vm (vm, argv[1]);
  
  destroy_vm (vm);

  return 0;
}

void usage(char *s) {
  fprintf (stderr, "[USAGE] %s <filename>\n", s);
  exit (1);
}





