#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "opcodes.h"

#define LED_MEMSIZE 64

typedef struct {
  struct {
    uint8_t a, b, pc, sp;
  } registers;
  uint8_t memory[LED_MEMSIZE];
  uint8_t ports[1];
  int running;
} VirtualMachine;

// This may be an overkill, but I wanted to practice my C program organization.
uint8_t VM_fetch(VirtualMachine *vm) { return vm->memory[vm->registers.pc++]; }


void tick(VirtualMachine *m)
{
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

void dump(VirtualMachine *m) {
  int i;
  uint8_t *p;
  printf("Registers:\n");
  printf("A: %02X, B: %02X, PC: %02X, SP: %02X\n",
    m->registers.a,
    m->registers.b,
    m->registers.pc,
    m->registers.sp
    );
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


void display_led(const VirtualMachine *vm, int port_number) {
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


int main(int argc, char *argv[]) {
  VirtualMachine vm;
  uint8_t temp;
  memset(&vm, 0, sizeof(vm));
  /*   ld b,3 */
  vm.memory[0] = OP_LDB;
  vm.memory[1] = 3;
/* triple: */
/*   ld a,126 */
  vm.memory[2] = OP_LDA;
  vm.memory[3] = 126;
/*   out (0),a */
  vm.memory[4] = OP_OUTA;
  vm.memory[5] = 0;
/*   ld a,60 */
  vm.memory[6] = OP_LDA;
  vm.memory[7] = 60;
/*   out (0),a */
  vm.memory[8] = OP_OUTA;
  vm.memory[9] = 0;
/*   ld a,24 */
  vm.memory[10] = OP_LDA;
  vm.memory[11] = 24;
/*   out (0),a */
  vm.memory[12] = OP_OUTA;
  vm.memory[13] = 0;
/*   djnz triple  */
  vm.memory[14] = OP_DJNZ;
  vm.memory[15] = 2;
  vm.memory[16] = OP_HALT;
  vm.running = 1;


  dump(&vm);
  while (vm.running) {
    temp = vm.ports[0];
    tick(&vm);
    if (vm.ports[0] != temp)
      display_led(&vm, 0);
  }
  dump(&vm);
}
