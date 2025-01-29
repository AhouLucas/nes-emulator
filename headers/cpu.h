#pragma once
#include "common.h"
#include "bus.h"


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

typedef struct CPU {
    uint16_t pc;
    uint8_t status;
    uint8_t stack_pointer;
    uint8_t reg_a;
    uint8_t reg_x;
    uint8_t reg_y;
    Bus_t* bus;
} CPU_t;


typedef enum {
    CARRY_FLAG          = 0b00000001,
    ZERO_FLAG           = 0b00000010,
    INTERRUPT_DISABLE   = 0b00000100,
    DECIMAL_MODE        = 0b00001000,
    BREAK               = 0b00010000,
    BREAK2              = 0b00100000,
    OVERFLOW_FLAG       = 0b01000000,
    NEGATIVE_FLAG       = 0b10000000,
} StatusFlag_t;


typedef enum {
    ADDR_MODE_ACCUMULATOR,
    ADDR_MODE_IMMEDIATE,
    ADDR_MODE_ZERO_PAGE,
    ADDR_MODE_ZERO_PAGE_X,
    ADDR_MODE_ZERO_PAGE_Y,
    ADDR_MODE_RELATIVE,
    ADDR_MODE_ABSOLUTE,
    ADDR_MODE_ABSOLUTE_X,
    ADDR_MODE_ABSOLUTE_Y,
    ADDR_MODE_INDIRECT,
    ADDR_MODE_INDIRECT_X,
    ADDR_MODE_INDIRECT_Y,
    ADDR_MODE_IMPLICIT,
} AddressingMode_t;


/* Initialization */

CPU_t*  CPU_init();
void    CPU_free(CPU_t*);

/* End initialization */


/* Instruction processing */

typedef enum InstructionType {
    INSTRUCTION_TYPE_VOID,
    INSTRUCTION_TYPE_U8,
} InstructionType_t;

typedef union CPU_Instruction {
    void (*void_instruction)(CPU_t*, AddressingMode_t);
    uint8_t (*u8_instruction)(CPU_t*, AddressingMode_t);
} CPU_Instruction;

typedef struct OpcodeEntry {
    CPU_Instruction     instruction;
    InstructionType_t   type;
    AddressingMode_t    mode;
    uint8_t             len;
    uint8_t             cycles;
} OpcodeEntry_t;

extern OpcodeEntry_t opcode_table[256];

// Read-Write helpers

#define STACK       0x0100
#define STACK_RESET 0x00FD

uint8_t     CPU_mem_read_u8(CPU_t*, uint16_t);
void        CPU_mem_write_u8(CPU_t*, uint16_t, uint8_t);
uint8_t     CPU_stack_pop_u8(CPU_t*);
void        CPU_stack_push_u8(CPU_t*, uint8_t);

uint16_t    CPU_mem_read_u16(CPU_t*, uint16_t);
void        CPU_mem_write_u16(CPU_t*, uint16_t, uint16_t);
uint16_t    CPU_stack_pop_u16(CPU_t*);
void        CPU_stack_push_u16(CPU_t*, uint16_t);

uint16_t CPU_get_operand_addr(CPU_t*, AddressingMode_t);

// Program execution

void CPU_reset(CPU_t*);
void CPU_load_and_run(CPU_t*, uint8_t*, size_t);
void CPU_load(CPU_t*, uint8_t*, size_t);
void CPU_run(CPU_t*);

// Instructions

void CPU_ADC(CPU_t*, AddressingMode_t);
void CPU_AND(CPU_t*, AddressingMode_t);
uint8_t CPU_ASL(CPU_t*, AddressingMode_t);
void CPU_ASL_ACC(CPU_t*, AddressingMode_t);
void CPU_BCC(CPU_t*, AddressingMode_t);
void CPU_BCS(CPU_t*, AddressingMode_t);
void CPU_BEQ(CPU_t*, AddressingMode_t);
void CPU_BIT(CPU_t*, AddressingMode_t);
void CPU_BMI(CPU_t*, AddressingMode_t);
void CPU_BNE(CPU_t*, AddressingMode_t);
void CPU_BPL(CPU_t*, AddressingMode_t);
void CPU_BVC(CPU_t*, AddressingMode_t);
void CPU_BVS(CPU_t*, AddressingMode_t);
void CPU_CLC(CPU_t*, AddressingMode_t);
void CPU_CLD(CPU_t*, AddressingMode_t);
void CPU_CLI(CPU_t*, AddressingMode_t);
void CPU_CLV(CPU_t*, AddressingMode_t);
void CPU_CMP(CPU_t*, AddressingMode_t);
void CPU_CPX(CPU_t*, AddressingMode_t);
void CPU_CPY(CPU_t*, AddressingMode_t);
uint8_t CPU_DEC(CPU_t*, AddressingMode_t);
void CPU_DEX(CPU_t*, AddressingMode_t);
void CPU_DEY(CPU_t*, AddressingMode_t);
void CPU_EOR(CPU_t*, AddressingMode_t);
uint8_t CPU_INC(CPU_t*, AddressingMode_t);
void CPU_INX(CPU_t*, AddressingMode_t);
void CPU_INY(CPU_t*, AddressingMode_t);
void CPU_JMP(CPU_t*, AddressingMode_t);
void CPU_JSR(CPU_t*, AddressingMode_t);
void CPU_LDA(CPU_t*, AddressingMode_t);
void CPU_LDX(CPU_t*, AddressingMode_t);
void CPU_LDY(CPU_t*, AddressingMode_t);
uint8_t CPU_LSR(CPU_t*, AddressingMode_t);
void CPU_LSR_ACC(CPU_t*, AddressingMode_t);
void CPU_NOP(CPU_t*, AddressingMode_t);
void CPU_ORA(CPU_t*, AddressingMode_t);
void CPU_PHA(CPU_t*, AddressingMode_t);
void CPU_PHP(CPU_t*, AddressingMode_t);
void CPU_PLA(CPU_t*, AddressingMode_t);
void CPU_PLP(CPU_t*, AddressingMode_t);
uint8_t CPU_ROL(CPU_t*, AddressingMode_t);
void CPU_ROL_ACC(CPU_t*, AddressingMode_t);
uint8_t CPU_ROR(CPU_t*, AddressingMode_t);
void CPU_ROR_ACC(CPU_t*, AddressingMode_t);
void CPU_RTI(CPU_t*, AddressingMode_t);
void CPU_RTS(CPU_t*, AddressingMode_t);
void CPU_SBC(CPU_t*, AddressingMode_t);
void CPU_SEC(CPU_t*, AddressingMode_t);
void CPU_SED(CPU_t*, AddressingMode_t);
void CPU_SEI(CPU_t*, AddressingMode_t);
void CPU_STA(CPU_t*, AddressingMode_t);
void CPU_STX(CPU_t*, AddressingMode_t);
void CPU_STY(CPU_t*, AddressingMode_t);
void CPU_TAX(CPU_t*, AddressingMode_t);
void CPU_TAY(CPU_t*, AddressingMode_t);
void CPU_TSX(CPU_t*, AddressingMode_t);
void CPU_TXA(CPU_t*, AddressingMode_t);
void CPU_TXS(CPU_t*, AddressingMode_t);
void CPU_TYA(CPU_t*, AddressingMode_t);

// CPU instructions helpers

uint8_t CPU_get_status_flag(CPU_t*, StatusFlag_t);
void CPU_set_status_flag(CPU_t*, StatusFlag_t);
void CPU_clear_status_flag(CPU_t*, StatusFlag_t);
void CPU_update_zero_and_negative_flags(CPU_t*, uint8_t);
void CPU_set_register_a(CPU_t*, uint8_t);
void CPU_add_to_register_a(CPU_t*, uint8_t);
void CPU_compare(CPU_t*, AddressingMode_t, uint8_t);
void CPU_branch(CPU_t*, bool);

/* End Instruction processing */