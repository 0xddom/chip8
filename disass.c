#include "vm.h"
#include <stdio.h>

void disass_ins(uint16_t ins) {  
  if (ins == CLS) { puts ("CLS"); return; }
  if (ins == RET) { puts ("RET"); return; }

  switch (ins & 0xf000) {
  case LD: {
    uint8_t x = (ins & 0x0f00) >> 8;
    uint8_t b = ins & 0x00ff;
    printf ("LD V%x, 0x%02x\n", x, b);
    return;
  }
  case LDI: {
    uint16_t addr = (ins & 0x0fff);
    printf ("LD I, 0x%04x\n", addr);
    return;
  }
  case DRW: {
    uint8_t x = (ins & 0x0f00) >> 8;
    uint8_t y = (ins & 0x00f0) >> 4;
    uint8_t n = (ins & 0x000f);
    printf ("DRW 0x%02x, 0x%02x, 0x%02x\n", x, y, n);
    return;
  }
  case CALL: {
    uint16_t addr = (ins & 0x0fff);
    printf ("CALL 0x%04x\n", addr);
    return;
  }
  case 0xf000: {
    switch (ins & 0x00ff) {
    case LDDT: {
      uint8_t x = (ins & 0x0f00) >> 8;
      printf ("LD V%x, DT\n", x);
      return;
    }
    case LDK: {
      uint8_t x = (ins & 0x0f00) >> 8;
      printf ("LD V%x, K\n", x);
      return;
    }
    case LDDTSET: {
      uint8_t x = (ins & 0x0f00) >> 8;
      printf ("LD DT, V%x\n", x);
      return;
    }
    case LDST: {
      uint8_t x = (ins & 0x0f00) >> 8;
      printf ("LD ST, V%x\n", x);
      return;
    }
    case ADDI: {
      uint8_t x = (ins & 0x0f00) >> 8;
      printf ("ADD I, V%x\n", x);
      return;
    }
    case LD2: {
      uint8_t x = (ins & 0x0f00) >> 8;
      printf ("LD F, V%x\n", x);
      return;
    }
    case LD3: {
      uint8_t x = (ins & 0x0f00) >> 8;
      printf ("LD B, V%x\n", x);
      return;
    }
    case LD5: {
      uint8_t x = (ins & 0x0f00) >> 8;
      printf ("LD [I], V%x\n", x);
      return;
    }
    case LD6: {
      uint8_t x = (ins & 0x0f00) >> 8;
      printf ("LD V%x, [I]\n", x);
      return;
    }
    }
  }
  case SE: {
    uint8_t x = (ins & 0x0f00) >> 8;
    uint8_t b = (ins & 0x00ff);
    printf ("SE V%x, 0x%02x\n", x, b);
    return;
  }
  case JP: {
    uint16_t addr = (ins & 0x0fff);
    printf ("JP 0x%04x\n", addr);
    return;
  }
  case RND: {
    uint8_t x = (ins & 0x0f00) >> 8;
    uint8_t byte = (ins & 0x00ff);
    printf ("RND V%x, 0x%02x\n", x, byte);
    return;
  }
  case ADD: {
    uint8_t x = (ins & 0x0f00) >> 8;
    uint8_t byte = (ins & 0x00ff);
    printf ("ADD V%x, 0x%02x\n", x, byte);
    return;
  }
  case 0xe000: {
    uint8_t x = (ins & 0x0f00) >> 8;
    switch (ins & 0x00ff) {
    case SKP: {
      printf ("SKP V%x\n", x);
      return;
    }
    case SKNP: {
      printf ("SNKP V%x\n", x);
      return;
    }
    }
  }
  case 0x8000: {
    uint8_t x = (ins & 0x0f00) >> 8;
    uint8_t y = (ins & 0x00f0) >> 4;
    switch (ins & 0x000f) {
    case LDR: {
      printf ("LD V%x, V%x\n", x, y);
      return;
    }
    case OR: {
      printf ("OR V%x, V%x\n", x, y);
      return;
    }
    case AND: {
      printf ("AND V%x, V%x\n", x, y);
      return;
    }
    case XOR: {
      printf ("XOR V%x, V%x\n", x, y);
      return;
    }
    case ADDR: {
      printf ("ADD V%x, V%x\n", x, y);
      return;
    }
    case SUBR: {
      printf ("SUB V%x, V%x\n", x, y);
      return;
    }
    case SHR: {
      printf ("SHR V%x, V%x\n", x, y);
      return;
    }
    case SUBN: {
      printf ("SUBN V%x, V%x\n", x, y);
      return;
    }
    case SHL: {
      printf ("SHL V%x, V%x\n", x, y);
      return;
    }
    }
  }
  case 0x0000: {
    uint16_t addr = (ins & 0x0fff);
    printf ("SYS 0x%04x\n", addr);
    return;
  }
  case SNE: {
    uint8_t x = (ins & 0x0f00) >> 8;
    uint8_t byte = (ins & 0x00ff);
    printf ("SNE V%x, 0x%02x\n", x, byte);
    return;
  }
  }

  puts ("\x1b[31munk\x1b[0m");
}
