#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "vm.h"

int main(int argc, char *argv[])
{
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


  VM_dump(&vm);
  while (vm.running) {
    temp = vm.ports[0];
    VM_tick(&vm);
    if (vm.ports[0] != temp)
      VM_display_led(&vm, 0);
  }
  VM_dump(&vm);
}
