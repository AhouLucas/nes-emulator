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

typedef struct {
    uint16_t pc;
    uint8_t status;
    uint8_t stack_pointer;
    uint8_t reg_a;
    uint8_t reg_x;
    uint8_t reg_y;
    Bus* bus;
} CPU;


typedef enum {
    CARRY_FLAG          = 0b00000001,
    ZERO_FLAG           = 0b00000010,
    INTERRUPT_DISABLE   = 0b00000100,
    DECIMAL_MODE        = 0b00001000,
    BREAK               = 0b00010000,
    BREAK2              = 0b00100000,
    OVERFLOW_FLAG       = 0b01000000,
    NEGATIVE_FLAG       = 0b10000000,
} StatusFlag;


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
} AddressingMode;


/* Initialization */

CPU*    CPU_init(Bus*);
void    CPU_free(CPU*);

/* End initialization */


/* Instruction processing */

typedef void (*CPU_Instruction)(CPU*, AddressingMode);

typedef struct OpcodeEntry {
    CPU_Instruction     instruction;
    AddressingMode      mode;
    uint8_t             len;
    uint8_t             cycles;
} OpcodeEntry;

extern OpcodeEntry opcode_table[256];

// Read-Write helpers

#define STACK       0x0100
#define STACK_RESET 0x00FD

uint8_t     CPU_mem_read_u8(CPU*, uint16_t);
void        CPU_mem_write_u8(CPU*, uint16_t, uint8_t);
uint8_t     CPU_stack_pop_u8(CPU*);
void        CPU_stack_push_u8(CPU*, uint8_t);

uint16_t    CPU_mem_read_u16(CPU*, uint16_t);
void        CPU_mem_write_u16(CPU*, uint16_t, uint16_t);
uint16_t    CPU_stack_pop_u16(CPU*);
void        CPU_stack_push_u16(CPU*, uint16_t);

uint16_t CPU_get_operand_addr(CPU*, AddressingMode);

// Program execution

void CPU_reset(CPU*);
void CPU_load_and_run(CPU*, uint8_t*, size_t);
void CPU_load(CPU*, uint8_t*, size_t);
void CPU_run(CPU*);

// Instructions

void CPU_ADC(CPU*, AddressingMode);
void CPU_ALR(CPU*, AddressingMode);
void CPU_AND(CPU*, AddressingMode);
void CPU_ANC(CPU*, AddressingMode);
void CPU_ARR(CPU*, AddressingMode);
void CPU_ASL(CPU*, AddressingMode);
void CPU_AXS(CPU*, AddressingMode);
void CPU_BCC(CPU*, AddressingMode);
void CPU_BCS(CPU*, AddressingMode);
void CPU_BEQ(CPU*, AddressingMode);
void CPU_BIT(CPU*, AddressingMode);
void CPU_BMI(CPU*, AddressingMode);
void CPU_BNE(CPU*, AddressingMode);
void CPU_BPL(CPU*, AddressingMode);
void CPU_BVC(CPU*, AddressingMode);
void CPU_BVS(CPU*, AddressingMode);
void CPU_CLC(CPU*, AddressingMode);
void CPU_CLD(CPU*, AddressingMode);
void CPU_CLI(CPU*, AddressingMode);
void CPU_CLV(CPU*, AddressingMode);
void CPU_CMP(CPU*, AddressingMode);
void CPU_CPX(CPU*, AddressingMode);
void CPU_CPY(CPU*, AddressingMode);
void CPU_DCP(CPU*, AddressingMode);
void CPU_DEC(CPU*, AddressingMode);
void CPU_DEX(CPU*, AddressingMode);
void CPU_DEY(CPU*, AddressingMode);
void CPU_EOR(CPU*, AddressingMode);
void CPU_IGN(CPU*, AddressingMode);
void CPU_INC(CPU*, AddressingMode);
void CPU_INX(CPU*, AddressingMode);
void CPU_INY(CPU*, AddressingMode);
void CPU_ISC(CPU*, AddressingMode);
void CPU_JMP(CPU*, AddressingMode);
void CPU_JSR(CPU*, AddressingMode);
void CPU_LDA(CPU*, AddressingMode);
void CPU_LDX(CPU*, AddressingMode);
void CPU_LDY(CPU*, AddressingMode);
void CPU_LSR(CPU*, AddressingMode);
void CPU_LSR(CPU*, AddressingMode);
void CPU_LXA(CPU*, AddressingMode);
void CPU_NOP(CPU*, AddressingMode);
void CPU_ORA(CPU*, AddressingMode);
void CPU_PHA(CPU*, AddressingMode);
void CPU_PHP(CPU*, AddressingMode);
void CPU_PLA(CPU*, AddressingMode);
void CPU_PLP(CPU*, AddressingMode);
void CPU_ROL(CPU*, AddressingMode);
void CPU_ROL(CPU*, AddressingMode);
void CPU_ROR(CPU*, AddressingMode);
void CPU_ROR(CPU*, AddressingMode);
void CPU_RTI(CPU*, AddressingMode);
void CPU_RTS(CPU*, AddressingMode);
void CPU_SAX(CPU*, AddressingMode);
void CPU_SBC(CPU*, AddressingMode);
void CPU_SEC(CPU*, AddressingMode);
void CPU_SED(CPU*, AddressingMode);
void CPU_SEI(CPU*, AddressingMode);
void CPU_SKB(CPU*, AddressingMode);
void CPU_STA(CPU*, AddressingMode);
void CPU_STX(CPU*, AddressingMode);
void CPU_STY(CPU*, AddressingMode);
void CPU_TAX(CPU*, AddressingMode);
void CPU_TAY(CPU*, AddressingMode);
void CPU_TSX(CPU*, AddressingMode);
void CPU_TXA(CPU*, AddressingMode);
void CPU_TXS(CPU*, AddressingMode);
void CPU_TYA(CPU*, AddressingMode);

// CPU instructions helpers

uint8_t CPU_get_status_flag(CPU*, StatusFlag);
void CPU_set_status_flag(CPU*, StatusFlag);
void CPU_clear_status_flag(CPU*, StatusFlag);
void CPU_update_zero_and_negative_flags(CPU*, uint8_t);
void CPU_set_register_a(CPU*, uint8_t);
void CPU_add_to_register_a(CPU*, uint8_t);
void CPU_compare(CPU*, AddressingMode, uint8_t);
void CPU_branch(CPU*, bool);

/* End Instruction processing */