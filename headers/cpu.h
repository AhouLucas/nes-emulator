#ifndef CPU_H
#define CPU_H

#include "common.h"


/// # Status Register (P) http://wiki.nesdev.com/w/index.php/Status_flags
///
///  7 6 5 4 3 2 1 0
///  N V _ B D I Z C
///  | |   | | | | +--- Carry Flag
///  | |   | | | +----- Zero Flag
///  | |   | | +------- Interrupt Disable
///  | |   | +--------- Decimal Mode (not used on NES)
///  | |   +----------- Break Command
///  | +--------------- Overflow Flag
///  +----------------- Negative Flag
///

typedef struct {
    uint8_t* memory;
    uint16_t pc;
    uint8_t status;
    uint8_t stack_pointer;
    uint8_t reg_a;
    uint8_t reg_x;
    uint8_t reg_y;
} CPU_t;

const uint16_t STACK = 0x0100;
const uint8_t STACK_RESET = 0xFD;


typedef enum {
    CARRY_FLAG          = 0b00000001,
    ZERO_FLAG           = 0b00000010,
    INTERRUPT_DISABLE   = 0b00000100,
    DECIMAL_MODE        = 0b00001000,
    BREAK_COMMAND       = 0b00010000,
    BREAK_FLAG          = 0b00010000,
    OVERFLOW_FLAG       = 0b01000000,
    NEGATIVE_FLAG       = 0b10000000,
} StatusFlag_t;


typedef enum {
    ADDR_MODE_IMMEDIATE,
    ADDR_MODE_ZERO_PAGE,
    ADDR_MODE_ZERO_PAGE_X,
    ADDR_MODE_ZERO_PAGE_Y,
    ADDR_MODE_ABSOLUTE,
    ADDR_MODE_ABSOLUTE_X,
    ADDR_MODE_ABSOLUTE_Y,
    ADDR_MODE_INDIRECT_X,
    ADDR_MODE_INDIRECT_Y,
    ADDR_MODE_IMPLICIT,
} AddressingMode_t;


/* Initialization */

CPU_t* CPU_init(void);
void CPU_free(CPU_t*);

/* End initialization */


/* Instruction processing */

typedef void (*CPU_Instruction)(CPU_t*, AddressingMode_t);

typedef struct {
    CPU_Instruction instruction;
    AddressingMode_t mode;
} OpcodeEntry;

// Read-Write helpers
uint8_t CPU_mem_read_u8(CPU_t*, uint16_t);
void CPU_mem_write_u8(CPU_t*, uint16_t, uint8_t);
uint16_t CPU_mem_read_u16(CPU_t*, uint16_t);
void CPU_mem_write_u16(CPU_t*, uint16_t, uint16_t);

uint16_t CPU_get_operand_addr(CPU_t*, AddressingMode_t);

// Program execution
void CPU_reset(CPU_t*);
void CPU_load_and_run(CPU_t*, uint8_t*, size_t);
void CPU_load(CPU_t*, uint8_t*, size_t);
void CPU_run(CPU_t*);

// Instructions
void CPU_AND(CPU_t*, AddressingMode_t);
void CPU_EOR(CPU_t*, AddressingMode_t);
void CPU_LDA(CPU_t*, AddressingMode_t);
void CPU_LDX(CPU_t*, AddressingMode_t);
void CPU_LDY(CPU_t*, AddressingMode_t);
void CPU_ORA(CPU_t*, AddressingMode_t);
void CPU_STA(CPU_t*, AddressingMode_t);
void CPU_TAX(CPU_t*);
void CPU_INX(CPU_t*);
void CPU_INY(CPU_t*);

// CPU state update
void CPU_set_status_flag(CPU_t*, StatusFlag_t);
void CPU_clear_status_flag(CPU_t*, StatusFlag_t);
void CPU_update_zero_and_negative_flags(CPU_t*, uint8_t);
void CPU_set_register_a(CPU_t*, uint8_t);
void CPU_add_to_register_a(CPU_t*, uint8_t);

/* End Instruction processing */
#endif