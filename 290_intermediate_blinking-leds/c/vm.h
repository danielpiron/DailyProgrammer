#ifndef __VM_H__
#define __VM_H__

#include <stdint.h>
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

extern uint8_t VM_fetch(VirtualMachine *);
extern void VM_tick(VirtualMachine *);
extern void VM_dump(VirtualMachine *);
extern void VM_display_led(const VirtualMachine *, int);

#endif
