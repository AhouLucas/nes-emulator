#ifndef CPU_H
#define CPU_H

#include "common.h"

typedef struct {
    uint16_t pc;
    uint8_t status;
    uint8_t reg_a;
    uint8_t reg_x;
} CPU_t;


/* Initialization */

CPU_t* CPU_init(void);
void CPU_free(CPU_t*);

/* End initialization */


/* Instruction processing */

void CPU_interpret(CPU_t*, uint8_t*);


// Instructions
void CPU_LDA_0xA9(CPU_t*, uint8_t);
void CPU_TAX_0xAA(CPU_t*);
void CPU_INX_0xE8(CPU_t*);

// Flag update
void CPU_update_zero_and_negative_flags(CPU_t*, uint8_t);

/* End Instruction processing */
#endif