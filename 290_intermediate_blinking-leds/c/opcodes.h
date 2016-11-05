#ifndef __OPCODES_H__
#define __OPCODES_H__

enum VM_OPCODE {
  OP_NOP = 0,
  OP_LDA,
  OP_LDB,
  OP_OUTA,
  OP_RLCA,
  OP_RRCA,
  OP_DJNZ,
  OP_HALT
};

#endif
