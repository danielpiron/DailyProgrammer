#include "vm.h"
#include <stdint.h>
#include <stdio.h>

// This may be an overkill, but I wanted to practice my C program organization.
uint8_t VM_fetch(VirtualMachine *vm) { return vm->memory[vm->registers.pc++]; }

void VM_tick(VirtualMachine *m) {
  uint8_t op, data;
  op = VM_fetch(m);
  switch (op) {
  case OP_NOP:
    break;
  case OP_LDA:
    m->registers.a = VM_fetch(m);
    break;
  case OP_LDB:
    m->registers.b = VM_fetch(m);
    break;
  case OP_OUTA:
    data = VM_fetch(m);
    m->ports[data] = m->registers.a;
    break;
  case OP_RLCA:
    m->registers.a = m->registers.a << 1 | m->registers.a >> 7;
    break;
  case OP_RRCA:
    m->registers.a = m->registers.a >> 1 | m->registers.a << 7;
    break;
  case OP_DJNZ:
    data = VM_fetch(m);
    if (--m->registers.b)
      m->registers.pc = data;
    break;
  case OP_HALT:
    m->running = 0;
    break;
  default:
    printf("Unrecognized op-code %02X\n", op);
    break;
  }
}

void VM_dump(VirtualMachine *m) {
  int i;
  uint8_t *p;
  printf("Registers:\n");
  printf("A: %02X, B: %02X, PC: %02X, SP: %02X\n", m->registers.a,
         m->registers.b, m->registers.pc, m->registers.sp);
  printf("Memory:\n");
  p = m->memory;
  for (i = 0; i < LED_MEMSIZE; ++i) {
    if (i && (i & 0x0F) == 0) {
      printf("\n");
    }
    printf("%02X ", p[i]);
  }
  printf("Port: %02X\n", m->ports[0]);
}

void VM_display_led(const VirtualMachine *vm, int port_number) {
  int i;
  char buffer[9];
  char *p;
  p = buffer;
  for (i = 0x80; i; i >>= 1, p++) {
    *p = (i & vm->ports[port_number]) ? '*' : '.';
  }
  *p = '\0';
  printf("%s\n", buffer);
}
