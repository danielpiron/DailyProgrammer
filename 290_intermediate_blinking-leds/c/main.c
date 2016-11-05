#include "vm.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  VirtualMachine vm;
  uint8_t temp;
  memset(&vm, 0, sizeof(vm));

  uint8_t program[] = {OP_LDB,  3,  OP_LDA,  126, OP_OUTA, 0,
                       OP_LDA,  60, OP_OUTA, 0,   OP_LDA,  24,
                       OP_OUTA, 0,  OP_DJNZ, 2,   OP_HALT};

  VM_load_program(&vm, program, 17);
  vm.running = 1;

  VM_dump(&vm);
  while (vm.running) {
    temp = vm.ports[0];
    VM_tick(&vm);
    if (vm.ports[0] != temp)
      VM_display_led(&vm, 0);
  }
  VM_dump(&vm);
}
