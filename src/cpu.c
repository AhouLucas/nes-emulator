#include "../headers/cpu.h"


OpcodeEntry opcode_table[256] = {
    [0x69] = {.instruction = CPU_ADC, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0x65] = {.instruction = CPU_ADC, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0x75] = {.instruction = CPU_ADC, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 4},
    [0x6D] = {.instruction = CPU_ADC, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},
    [0x7D] = {.instruction = CPU_ADC, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0x79] = {.instruction = CPU_ADC, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 4},
    [0x61] = {.instruction = CPU_ADC, .mode = ADDR_MODE_INDIRECT_X,     .len = 2, .cycles = 6},
    [0x71] = {.instruction = CPU_ADC, .mode = ADDR_MODE_INDIRECT_Y,     .len = 2, .cycles = 5},

    [0x4B] = {.instruction = CPU_ALR, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},

    [0x0B] = {.instruction = CPU_ANC, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0x2B] = {.instruction = CPU_ANC, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},

    [0x29] = {.instruction = CPU_AND, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0x25] = {.instruction = CPU_AND, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0x35] = {.instruction = CPU_AND, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 4},
    [0x2D] = {.instruction = CPU_AND, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},
    [0x3D] = {.instruction = CPU_AND, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0x39] = {.instruction = CPU_AND, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 4},
    [0x21] = {.instruction = CPU_AND, .mode = ADDR_MODE_INDIRECT_X,     .len = 2, .cycles = 6},
    [0x31] = {.instruction = CPU_AND, .mode = ADDR_MODE_INDIRECT_Y,     .len = 2, .cycles = 5},

    [0x6B] = {.instruction = CPU_ARR, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},

    [0x0A] = {.instruction = CPU_ASL, .mode = ADDR_MODE_ACCUMULATOR,    .len = 1, .cycles = 2},
    [0x06] = {.instruction = CPU_ASL, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 5},
    [0x16] = {.instruction = CPU_ASL, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 6},
    [0x0E] = {.instruction = CPU_ASL, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 6},
    [0x1E] = {.instruction = CPU_ASL, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 7},

    [0xCB] = {.instruction = CPU_AXS, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},

    [0x90] = {.instruction = CPU_BCC, .mode = ADDR_MODE_RELATIVE,       .len = 2, .cycles = 2},

    [0xB0] = {.instruction = CPU_BCS, .mode = ADDR_MODE_RELATIVE,       .len = 2, .cycles = 2},

    [0xF0] = {.instruction = CPU_BEQ, .mode = ADDR_MODE_RELATIVE,       .len = 2, .cycles = 2},

    [0x24] = {.instruction = CPU_BIT, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0x2C] = {.instruction = CPU_BIT, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},

    [0x30] = {.instruction = CPU_BMI, .mode = ADDR_MODE_RELATIVE,       .len = 2, .cycles = 2},

    [0xD0] = {.instruction = CPU_BNE, .mode = ADDR_MODE_RELATIVE,       .len = 2, .cycles = 2},

    [0x10] = {.instruction = CPU_BPL, .mode = ADDR_MODE_RELATIVE,       .len = 2, .cycles = 2},

    [0x50] = {.instruction = CPU_BVC, .mode = ADDR_MODE_RELATIVE,       .len = 2, .cycles = 2},

    [0x70] = {.instruction = CPU_BVS, .mode = ADDR_MODE_RELATIVE,       .len = 2, .cycles = 2},

    [0x18] = {.instruction = CPU_CLC, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0xD8] = {.instruction = CPU_CLD, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0x58] = {.instruction = CPU_CLI, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0xB8] = {.instruction = CPU_CLV, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0xC9] = {.instruction = CPU_CMP, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0xC5] = {.instruction = CPU_CMP, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0xD5] = {.instruction = CPU_CMP, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 4},
    [0xCD] = {.instruction = CPU_CMP, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},
    [0xDD] = {.instruction = CPU_CMP, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0xD9] = {.instruction = CPU_CMP, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 4},
    [0xC1] = {.instruction = CPU_CMP, .mode = ADDR_MODE_INDIRECT_X,     .len = 2, .cycles = 6},
    [0xD1] = {.instruction = CPU_CMP, .mode = ADDR_MODE_INDIRECT_Y,     .len = 2, .cycles = 5},

    [0xE0] = {.instruction = CPU_CPX, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0xE4] = {.instruction = CPU_CPX, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0xEC] = {.instruction = CPU_CPX, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},

    [0xC0] = {.instruction = CPU_CPY, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0xC4] = {.instruction = CPU_CPY, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0xCC] = {.instruction = CPU_CPY, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},

    [0xC7] = {.instruction = CPU_DCP, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 5},
    [0xD7] = {.instruction = CPU_DCP, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 6},
    [0xCF] = {.instruction = CPU_DCP, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 6},
    [0xDF] = {.instruction = CPU_DCP, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 7},
    [0xDB] = {.instruction = CPU_DCP, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 7},
    [0xC3] = {.instruction = CPU_DCP, .mode = ADDR_MODE_INDIRECT_X,     .len = 2, .cycles = 8},
    [0xD3] = {.instruction = CPU_DCP, .mode = ADDR_MODE_INDIRECT_Y,     .len = 2, .cycles = 8},

    [0xC6] = {.instruction = CPU_DEC, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 5},
    [0xD6] = {.instruction = CPU_DEC, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 6},
    [0xCE] = {.instruction = CPU_DEC, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 6},
    [0xDE] = {.instruction = CPU_DEC, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 7},

    [0xCA] = {.instruction = CPU_DEX, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0x88] = {.instruction = CPU_DEY, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0x49] = {.instruction = CPU_EOR, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0x45] = {.instruction = CPU_EOR, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0x55] = {.instruction = CPU_EOR, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 4},
    [0x4D] = {.instruction = CPU_EOR, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},
    [0x5D] = {.instruction = CPU_EOR, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0x59] = {.instruction = CPU_EOR, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 4},
    [0x41] = {.instruction = CPU_EOR, .mode = ADDR_MODE_INDIRECT_X,     .len = 2, .cycles = 6},
    [0x51] = {.instruction = CPU_EOR, .mode = ADDR_MODE_INDIRECT_Y,     .len = 2, .cycles = 5},

    [0x0C] = {.instruction = CPU_IGN, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},
    [0x1C] = {.instruction = CPU_IGN, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0x3C] = {.instruction = CPU_IGN, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0x5C] = {.instruction = CPU_IGN, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0x7C] = {.instruction = CPU_IGN, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0xDC] = {.instruction = CPU_IGN, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0xFC] = {.instruction = CPU_IGN, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0x04] = {.instruction = CPU_IGN, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0x44] = {.instruction = CPU_IGN, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0x64] = {.instruction = CPU_IGN, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0x14] = {.instruction = CPU_IGN, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 4},
    [0x34] = {.instruction = CPU_IGN, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 4},
    [0x54] = {.instruction = CPU_IGN, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 4},
    [0x74] = {.instruction = CPU_IGN, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 4},
    [0xD4] = {.instruction = CPU_IGN, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 4},
    [0xF4] = {.instruction = CPU_IGN, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 4},

    [0xE6] = {.instruction = CPU_INC, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 5},
    [0xF6] = {.instruction = CPU_INC, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 6},
    [0xEE] = {.instruction = CPU_INC, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 6},
    [0xFE] = {.instruction = CPU_INC, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 7},

    [0xE8] = {.instruction = CPU_INX, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0xC8] = {.instruction = CPU_INY, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0xE7] = {.instruction = CPU_ISC, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 5},
    [0xF7] = {.instruction = CPU_ISC, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 6},
    [0xEF] = {.instruction = CPU_ISC, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 6},
    [0xFF] = {.instruction = CPU_ISC, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 7},
    [0xFB] = {.instruction = CPU_ISC, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 7},
    [0xE3] = {.instruction = CPU_ISC, .mode = ADDR_MODE_INDIRECT_X,     .len = 2, .cycles = 8},
    [0xF3] = {.instruction = CPU_ISC, .mode = ADDR_MODE_INDIRECT_Y,     .len = 2, .cycles = 8},

    [0x4C] = {.instruction = CPU_JMP, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 3},
    [0x6C] = {.instruction = CPU_JMP, .mode = ADDR_MODE_INDIRECT,       .len = 3, .cycles = 5},

    [0x20] = {.instruction = CPU_JSR, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 6},

    [0xBB] = {.instruction = CPU_LAS, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 4},

    [0xA7] = {.instruction = CPU_LAX, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0xB7] = {.instruction = CPU_LAX, .mode = ADDR_MODE_ZERO_PAGE_Y,    .len = 2, .cycles = 4},
    [0xAF] = {.instruction = CPU_LAX, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},
    [0xBF] = {.instruction = CPU_LAX, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 4},
    [0xA3] = {.instruction = CPU_LAX, .mode = ADDR_MODE_INDIRECT_X,     .len = 2, .cycles = 6},
    [0xB3] = {.instruction = CPU_LAX, .mode = ADDR_MODE_INDIRECT_Y,     .len = 2, .cycles = 5},

    [0xA9] = {.instruction = CPU_LDA, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0xA5] = {.instruction = CPU_LDA, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0xB5] = {.instruction = CPU_LDA, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 4},
    [0xAD] = {.instruction = CPU_LDA, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},
    [0xBD] = {.instruction = CPU_LDA, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0xB9] = {.instruction = CPU_LDA, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 4},
    [0xA1] = {.instruction = CPU_LDA, .mode = ADDR_MODE_INDIRECT_X,     .len = 2, .cycles = 6},
    [0xB1] = {.instruction = CPU_LDA, .mode = ADDR_MODE_INDIRECT_Y,     .len = 2, .cycles = 5},
    
    [0xA2] = {.instruction = CPU_LDX, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0xA6] = {.instruction = CPU_LDX, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0xB6] = {.instruction = CPU_LDX, .mode = ADDR_MODE_ZERO_PAGE_Y,    .len = 2, .cycles = 4},
    [0xAE] = {.instruction = CPU_LDX, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},
    [0xBE] = {.instruction = CPU_LDX, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 4},

    [0xA0] = {.instruction = CPU_LDY, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0xA4] = {.instruction = CPU_LDY, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0xB4] = {.instruction = CPU_LDY, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 4},
    [0xAC] = {.instruction = CPU_LDY, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},
    [0xBC] = {.instruction = CPU_LDY, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},

    [0x4A] = {.instruction = CPU_LSR, .mode = ADDR_MODE_ACCUMULATOR,    .len = 1, .cycles = 2},
    [0x46] = {.instruction = CPU_LSR, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 5},
    [0x56] = {.instruction = CPU_LSR, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 6},
    [0x4E] = {.instruction = CPU_LSR, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 6},
    [0x5E] = {.instruction = CPU_LSR, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 7},

    [0xAB] = {.instruction = CPU_LXA, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},

    [0x1A] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0x3A] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0x5A] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0x7A] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0xDA] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0xEA] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0xFA] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0x02] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0x12] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0x32] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0x42] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0x52] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0x62] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0x72] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0x92] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0xB2] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0xD2] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0xF2] = {.instruction = CPU_NOP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},
    [0x0C] = {.instruction = CPU_NOP, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},
    [0x1C] = {.instruction = CPU_NOP, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0x3C] = {.instruction = CPU_NOP, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0x5C] = {.instruction = CPU_NOP, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0x7C] = {.instruction = CPU_NOP, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0xDC] = {.instruction = CPU_NOP, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0xFC] = {.instruction = CPU_NOP, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},

    [0x09] = {.instruction = CPU_ORA, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0x05] = {.instruction = CPU_ORA, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0x15] = {.instruction = CPU_ORA, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 4},
    [0x0D] = {.instruction = CPU_ORA, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},
    [0x1D] = {.instruction = CPU_ORA, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0x19] = {.instruction = CPU_ORA, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 4},
    [0x01] = {.instruction = CPU_ORA, .mode = ADDR_MODE_INDIRECT_X,     .len = 2, .cycles = 6},
    [0x11] = {.instruction = CPU_ORA, .mode = ADDR_MODE_INDIRECT_Y,     .len = 2, .cycles = 5},

    [0x48] = {.instruction = CPU_PHA, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 3},

    [0x08] = {.instruction = CPU_PHP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 3},

    [0x68] = {.instruction = CPU_PLA, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 4},

    [0x28] = {.instruction = CPU_PLP, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 4},

    [0x27] = {.instruction = CPU_RLA, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 5},
    [0x37] = {.instruction = CPU_RLA, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 6},
    [0x2F] = {.instruction = CPU_RLA, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 6},
    [0x3F] = {.instruction = CPU_RLA, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 7},
    [0x3B] = {.instruction = CPU_RLA, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 7},
    [0x23] = {.instruction = CPU_RLA, .mode = ADDR_MODE_INDIRECT_X,     .len = 2, .cycles = 8},
    [0x33] = {.instruction = CPU_RLA, .mode = ADDR_MODE_INDIRECT_Y,     .len = 2, .cycles = 8},

    [0x2A] = {.instruction = CPU_ROL, .mode = ADDR_MODE_ACCUMULATOR,    .len = 1, .cycles = 2},
    [0x26] = {.instruction = CPU_ROL, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 5},
    [0x36] = {.instruction = CPU_ROL, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 6},
    [0x2E] = {.instruction = CPU_ROL, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 6},
    [0x3E] = {.instruction = CPU_ROL, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 7},

    [0x6A] = {.instruction = CPU_ROR, .mode = ADDR_MODE_ACCUMULATOR,    .len = 1, .cycles = 2},
    [0x66] = {.instruction = CPU_ROR, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 5},
    [0x76] = {.instruction = CPU_ROR, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 6},
    [0x6E] = {.instruction = CPU_ROR, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 6},
    [0x7E] = {.instruction = CPU_ROR, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 7},

    [0x67] = {.instruction = CPU_RRA, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 5},
    [0x77] = {.instruction = CPU_RRA, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 6},
    [0x6F] = {.instruction = CPU_RRA, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 6},
    [0x7F] = {.instruction = CPU_RRA, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 7},
    [0x7B] = {.instruction = CPU_RRA, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 7},
    [0x63] = {.instruction = CPU_RRA, .mode = ADDR_MODE_INDIRECT_X,     .len = 2, .cycles = 8},
    [0x73] = {.instruction = CPU_RRA, .mode = ADDR_MODE_INDIRECT_Y,     .len = 2, .cycles = 8},

    [0x40] = {.instruction = CPU_RTI, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 6},

    [0x60] = {.instruction = CPU_RTS, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 6},

    [0x87] = {.instruction = CPU_SAX, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0x97] = {.instruction = CPU_SAX, .mode = ADDR_MODE_ZERO_PAGE_Y,    .len = 2, .cycles = 4},
    [0x83] = {.instruction = CPU_SAX, .mode = ADDR_MODE_INDIRECT_X,     .len = 2, .cycles = 6},
    [0x8F] = {.instruction = CPU_SAX, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},

    [0xE9] = {.instruction = CPU_SBC, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0xEB] = {.instruction = CPU_SBC, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0xE5] = {.instruction = CPU_SBC, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0xF5] = {.instruction = CPU_SBC, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 4},
    [0xED] = {.instruction = CPU_SBC, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},
    [0xFD] = {.instruction = CPU_SBC, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 4},
    [0xF9] = {.instruction = CPU_SBC, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 4},
    [0xE1] = {.instruction = CPU_SBC, .mode = ADDR_MODE_INDIRECT_X,     .len = 2, .cycles = 6},
    [0xF1] = {.instruction = CPU_SBC, .mode = ADDR_MODE_INDIRECT_Y,     .len = 2, .cycles = 5},

    [0x38] = {.instruction = CPU_SEC, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0xF8] = {.instruction = CPU_SED, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0x78] = {.instruction = CPU_SEI, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0x80] = {.instruction = CPU_SKB, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0x82] = {.instruction = CPU_SKB, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0x89] = {.instruction = CPU_SKB, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0xC2] = {.instruction = CPU_SKB, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},
    [0xE2] = {.instruction = CPU_SKB, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},

    [0x07] = {.instruction = CPU_SLO, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 5},
    [0x17] = {.instruction = CPU_SLO, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 6},
    [0x0F] = {.instruction = CPU_SLO, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 6},
    [0x1F] = {.instruction = CPU_SLO, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 7},
    [0x1B] = {.instruction = CPU_SLO, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 7},
    [0x03] = {.instruction = CPU_SLO, .mode = ADDR_MODE_INDIRECT_X,     .len = 2, .cycles = 8},
    [0x13] = {.instruction = CPU_SLO, .mode = ADDR_MODE_INDIRECT_Y,     .len = 2, .cycles = 8},

    [0x47] = {.instruction = CPU_SRE, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 5},
    [0x57] = {.instruction = CPU_SRE, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 6},
    [0x4F] = {.instruction = CPU_SRE, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 6},
    [0x5F] = {.instruction = CPU_SRE, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 7},
    [0x5B] = {.instruction = CPU_SRE, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 7},
    [0x43] = {.instruction = CPU_SRE, .mode = ADDR_MODE_INDIRECT_X,     .len = 2, .cycles = 8},
    [0x53] = {.instruction = CPU_SRE, .mode = ADDR_MODE_INDIRECT_Y,     .len = 2, .cycles = 8},

    [0x85] = {.instruction = CPU_STA, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0x95] = {.instruction = CPU_STA, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 4},
    [0x8D] = {.instruction = CPU_STA, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},
    [0x9D] = {.instruction = CPU_STA, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 5},
    [0x99] = {.instruction = CPU_STA, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 5},
    [0x81] = {.instruction = CPU_STA, .mode = ADDR_MODE_INDIRECT_X,     .len = 2, .cycles = 6},
    [0x91] = {.instruction = CPU_STA, .mode = ADDR_MODE_INDIRECT_Y,     .len = 2, .cycles = 6},

    [0x86] = {.instruction = CPU_STX, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0x96] = {.instruction = CPU_STX, .mode = ADDR_MODE_ZERO_PAGE_Y,    .len = 2, .cycles = 4},
    [0x8E] = {.instruction = CPU_STX, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},

    [0x84] = {.instruction = CPU_STY, .mode = ADDR_MODE_ZERO_PAGE,      .len = 2, .cycles = 3},
    [0x94] = {.instruction = CPU_STY, .mode = ADDR_MODE_ZERO_PAGE_X,    .len = 2, .cycles = 4},
    [0x8C] = {.instruction = CPU_STY, .mode = ADDR_MODE_ABSOLUTE,       .len = 3, .cycles = 4},

    [0x9E] = {.instruction = CPU_SHX, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 5},

    [0x9C] = {.instruction = CPU_SHY, .mode = ADDR_MODE_ABSOLUTE_X,     .len = 3, .cycles = 5},

    [0xAA] = {.instruction = CPU_TAX, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0xA8] = {.instruction = CPU_TAY, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0xBA] = {.instruction = CPU_TSX, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0x8A] = {.instruction = CPU_TXA, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0x9A] = {.instruction = CPU_TXS, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0x98] = {.instruction = CPU_TYA, .mode = ADDR_MODE_IMPLICIT,       .len = 1, .cycles = 2},

    [0x8B] = {.instruction = CPU_XAA, .mode = ADDR_MODE_IMMEDIATE,      .len = 2, .cycles = 2},

    [0x9B] = {.instruction = CPU_XAS, .mode = ADDR_MODE_ABSOLUTE_Y,     .len = 3, .cycles = 5},
};

CPU* CPU_init(Bus* bus) {
    CPU* cpu = malloc(sizeof(CPU));
    cpu->reg_a = 0;
    cpu->reg_x = 0;
    cpu->pc = 0;
    cpu->status = 0b100100;
    cpu->stack_pointer = STACK_RESET;

    cpu->bus = bus;
    return cpu;
}

void CPU_free(CPU* cpu) {
    Bus_free(cpu->bus);
    free(cpu);
    return;
}

uint8_t CPU_mem_read_u8(CPU* cpu, uint16_t addr) {
    return Bus_mem_read_u8(cpu->bus, addr);
}

void CPU_mem_write_u8(CPU* cpu, uint16_t addr, uint8_t data) {
    Bus_mem_write_u8(cpu->bus, addr, data);
}

uint8_t CPU_stack_pop_u8(CPU* cpu) {
    cpu->stack_pointer++;
    return CPU_mem_read_u8(cpu, STACK + cpu->stack_pointer);
}

void CPU_stack_push_u8(CPU* cpu, uint8_t data) {
    CPU_mem_write_u8(cpu, STACK + cpu->stack_pointer, data);
    cpu->stack_pointer--;
}

uint16_t CPU_mem_read_u16(CPU* cpu, uint16_t addr) {
    return Bus_mem_read_u16(cpu->bus, addr);
}

void CPU_mem_write_u16(CPU* cpu, uint16_t addr, uint16_t data) {
    Bus_mem_write_u16(cpu->bus, addr, data);
}

uint16_t CPU_stack_pop_u16(CPU* cpu) {
    uint8_t lo = CPU_stack_pop_u8(cpu), hi = CPU_stack_pop_u8(cpu);
    return (hi<<8) | lo;
}

void CPU_stack_push_u16(CPU* cpu, uint16_t data) {
    uint8_t hi = data >> 8;
    uint8_t lo = data & 0xFF;
    CPU_stack_push_u8(cpu, hi);
    CPU_stack_push_u8(cpu, lo);
}

uint16_t CPU_get_operand_addr(CPU* cpu, AddressingMode mode) {
    uint8_t pos;
    uint8_t base8;
    uint16_t base16;
    uint8_t lo, hi;
    uint16_t ptr;
    uint16_t deref_base;

    switch (mode) {
        case ADDR_MODE_IMMEDIATE:
            return cpu->pc;

        case ADDR_MODE_ZERO_PAGE:
            return CPU_mem_read_u8(cpu, cpu->pc);

        case ADDR_MODE_ABSOLUTE:
            return CPU_mem_read_u16(cpu, cpu->pc);

        case ADDR_MODE_ZERO_PAGE_X:
            pos = CPU_mem_read_u8(cpu, cpu->pc);
            return (pos + cpu->reg_x) & 0xFF; // Ensure zero page wrap-around

        case ADDR_MODE_ZERO_PAGE_Y:
            pos = CPU_mem_read_u8(cpu, cpu->pc);
            return (pos + cpu->reg_y) & 0xFF; // Ensure zero page wrap-around

        case ADDR_MODE_ABSOLUTE_X:
            base16 = CPU_mem_read_u16(cpu, cpu->pc);
            return base16 + cpu->reg_x;

        case ADDR_MODE_ABSOLUTE_Y:
            base16 = CPU_mem_read_u16(cpu, cpu->pc);
            return base16 + cpu->reg_y;

        case ADDR_MODE_INDIRECT_X:
            base8 = CPU_mem_read_u8(cpu, cpu->pc);
            ptr = (base8 + cpu->reg_x) & 0xFF; // Ensure zero page wrap-around
            lo = CPU_mem_read_u8(cpu, ptr);
            hi = CPU_mem_read_u8(cpu, (ptr + 1) & 0xFF); // Ensure zero page wrap-around
            return ((uint16_t)hi << 8) | lo;

        case ADDR_MODE_INDIRECT_Y:
            base8 = CPU_mem_read_u8(cpu, cpu->pc);
            lo = CPU_mem_read_u8(cpu, base8);
            hi = CPU_mem_read_u8(cpu, (base8 + 1) & 0xFF); // Ensure zero page wrap-around
            deref_base = ((uint16_t)hi << 8) | lo;
            return deref_base + cpu->reg_y;

        default:
            fprintf(stderr, "Unsupported addressing mode: %d\n", mode);
            exit(EXIT_FAILURE);
    }
}

void CPU_reset(CPU* cpu) {
    cpu->reg_a = 0;
    cpu->reg_x = 0;
    cpu->reg_y = 0;
    cpu->status = 0b100100;
    cpu->stack_pointer = STACK_RESET;
    cpu->pc = CPU_mem_read_u16(cpu, 0xFFFC);
}

void CPU_load_and_run(CPU* cpu, uint8_t* program, size_t program_size) {
    CPU_load(cpu, program, program_size);
    CPU_reset(cpu);
    CPU_run(cpu);
}

void CPU_load(CPU* cpu, uint8_t* program, size_t program_size) {
    for (uint16_t i = 0; i < program_size; i++) {
        CPU_mem_write_u8(cpu, 0x0000 + i, program[i]);
    }
    CPU_mem_write_u16(cpu, 0xFFFC, 0x8000);
}

void CPU_run(CPU* cpu) {
    for (;;) {
        uint8_t opcode = CPU_mem_read_u8(cpu, cpu->pc);
        cpu->pc++;
        uint16_t pc_state = cpu->pc;

        if (opcode == 0x00) return;

        OpcodeEntry entry = opcode_table[opcode];

        entry.instruction(cpu, entry.mode);

        if (pc_state == cpu->pc) {
            cpu->pc += (uint16_t) entry.len - 1;
        }
    }
}


void CPU_ADC(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    CPU_add_to_register_a(cpu, value);
}

void CPU_ALR(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);

    CPU_set_register_a(cpu, cpu->reg_a & data);
    CPU_LSR(cpu, ADDR_MODE_ACCUMULATOR);
}

void CPU_ANC(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);

    CPU_set_register_a(cpu, data & cpu->reg_a);

    if (CPU_get_status_flag(cpu, NEGATIVE_FLAG)) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, CARRY_FLAG);
    }
}

void CPU_AND(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    CPU_set_register_a(cpu, cpu->reg_a & value);
}

void CPU_ARR(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);
    CPU_set_register_a(cpu, cpu->reg_a & data);
    CPU_ROR(cpu, ADDR_MODE_ACCUMULATOR);

    uint8_t bit5 = (cpu->reg_a >> 5) & 1;
    uint8_t bit6 = (cpu->reg_a >> 6) & 1;

    if (bit6) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, CARRY_FLAG);
    }

    if (bit5 ^ bit6) {
        CPU_set_status_flag(cpu, OVERFLOW_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, OVERFLOW_FLAG);
    }

    CPU_update_zero_and_negative_flags(cpu, cpu->reg_a);
}

void CPU_ASL(CPU* cpu, AddressingMode mode) {

    uint16_t addr;
    uint8_t data;

    if (mode == ADDR_MODE_ACCUMULATOR) {
        data = cpu->reg_a;
    }
    else {
        addr = CPU_get_operand_addr(cpu, mode);
        data = CPU_mem_read_u8(cpu, addr);
    }

    if ((data >> 7) == 1) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, CARRY_FLAG);
    }

    data = data << 1;

    if (mode == ADDR_MODE_ACCUMULATOR) {
        CPU_set_register_a(cpu, data);
    }
    else {
        CPU_mem_write_u8(cpu, addr, data);
        CPU_update_zero_and_negative_flags(cpu, data);
    }

}


void CPU_AXS(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);
    uint8_t result = cpu->reg_a & cpu->reg_x;
    result -= data;
    
    if (data <= (cpu->reg_a & cpu->reg_x)) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    
    CPU_update_zero_and_negative_flags(cpu, result);
    cpu->reg_x = result;
}

void CPU_BCC(CPU* cpu, AddressingMode mode) {
    CPU_branch(cpu, CPU_get_status_flag(cpu, CARRY_FLAG) == 0);
}

void CPU_BCS(CPU* cpu, AddressingMode mode) {
    CPU_branch(cpu, CPU_get_status_flag(cpu, CARRY_FLAG) == 1);
}

void CPU_BEQ(CPU* cpu, AddressingMode mode) {
    CPU_branch(cpu, CPU_get_status_flag(cpu, ZERO_FLAG) == 1);
}

void CPU_BIT(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);
    uint8_t and = cpu->reg_a & data;

    if (and == 0) {
        CPU_set_status_flag(cpu, ZERO_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, ZERO_FLAG);
    }

    if ((data & 0b10000000) > 0) {
        CPU_set_status_flag(cpu, NEGATIVE_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, NEGATIVE_FLAG);
    }

    if ((data & 0b01000000) > 0) {
        CPU_set_status_flag(cpu, OVERFLOW_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, OVERFLOW_FLAG);
    }
}

void CPU_BMI(CPU* cpu, AddressingMode mode) {
    CPU_branch(cpu, CPU_get_status_flag(cpu, NEGATIVE_FLAG) == 1);
}

void CPU_BNE(CPU* cpu, AddressingMode mode) {
    CPU_branch(cpu, CPU_get_status_flag(cpu, ZERO_FLAG) == 0);
}

void CPU_BPL(CPU* cpu, AddressingMode mode) {
    CPU_branch(cpu, CPU_get_status_flag(cpu, NEGATIVE_FLAG) == 0);
}

void CPU_BVC(CPU* cpu, AddressingMode mode) {
    CPU_branch(cpu, CPU_get_status_flag(cpu, OVERFLOW_FLAG) == 0);
}

void CPU_BVS(CPU* cpu, AddressingMode mode) {
    CPU_branch(cpu, CPU_get_status_flag(cpu, OVERFLOW_FLAG) == 1);
}

void CPU_CLC(CPU* cpu, AddressingMode mode) {
    CPU_clear_status_flag(cpu, CARRY_FLAG);
}

void CPU_CLD(CPU* cpu, AddressingMode mode) {
    CPU_clear_status_flag(cpu, DECIMAL_MODE);
}

void CPU_CLI(CPU* cpu, AddressingMode mode) {
    CPU_clear_status_flag(cpu, INTERRUPT_DISABLE);
}

void CPU_CLV(CPU* cpu, AddressingMode mode) {
    CPU_clear_status_flag(cpu, OVERFLOW_FLAG);
}

void CPU_CMP(CPU* cpu, AddressingMode mode) {
    CPU_compare(cpu, mode, cpu->reg_a);
}

void CPU_CPX(CPU* cpu, AddressingMode mode) {
    CPU_compare(cpu, mode, cpu->reg_x);
}

void CPU_CPY(CPU* cpu, AddressingMode mode) {
    CPU_compare(cpu, mode, cpu->reg_y);
}

void CPU_DCP(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);
    data--;
    CPU_mem_write_u8(cpu, addr, data);

    if (data <= cpu->reg_a) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_a - data);
}

void CPU_DEC(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);
    data--;
    CPU_mem_write_u8(cpu, addr, data);
    CPU_update_zero_and_negative_flags(cpu, data);
}

void CPU_DEX(CPU* cpu, AddressingMode mode) {
    cpu->reg_x--;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_x);
}

void CPU_DEY(CPU* cpu, AddressingMode mode) {
    cpu->reg_y--;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_y);
}

void CPU_EOR(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    CPU_set_register_a(cpu, cpu->reg_a ^ value);
}

void CPU_IGN(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    CPU_mem_read_u8(cpu, addr); // Read the byte and ignore it
}

void CPU_INC(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);
    data++;
    CPU_mem_write_u8(cpu, addr, data);
    CPU_update_zero_and_negative_flags(cpu, data);
}

void CPU_INX(CPU* cpu, AddressingMode mode) {
    cpu->reg_x++;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_x);
}

void CPU_INY(CPU* cpu, AddressingMode mode) {
    cpu->reg_y++;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_y);
}

void CPU_ISC(CPU* cpu, AddressingMode mode) {
    CPU_INC(cpu, mode);
    CPU_SBC(cpu, mode);
}

void CPU_JMP(CPU* cpu, AddressingMode mode) {
    switch (mode) {
    case ADDR_MODE_ABSOLUTE:
        cpu->pc = CPU_mem_read_u16(cpu, cpu->pc);
        break;
    case ADDR_MODE_INDIRECT:
        uint16_t addr = CPU_mem_read_u16(cpu, cpu->pc);
        uint16_t indirect_ref = CPU_mem_read_u16(cpu, addr);
        if (addr & 0xFF == 0xFF) {
            uint8_t lo = CPU_mem_read_u8(cpu, addr);
            uint8_t hi = CPU_mem_read_u8(cpu, addr & 0xFF00);
            indirect_ref = (hi << 8) | lo;
        }
        
        cpu->pc = indirect_ref;
        break;
    default:
        printf("Invalid addressing mode for JMP\n");
        exit(EXIT_FAILURE);
        break;
    }
}

void CPU_JSR(CPU* cpu, AddressingMode mode) {
    CPU_stack_push_u16(cpu, cpu->pc + 2 - 1);
    uint16_t addr = CPU_mem_read_u16(cpu, cpu->pc);
    cpu->pc = addr;
}

void CPU_LAS(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);

    uint8_t result = cpu->stack_pointer & data;

    CPU_set_register_a(cpu, result);
    cpu->reg_x = result;
    cpu->stack_pointer = result;
}

void CPU_LAX(CPU* cpu, AddressingMode mode) {
    CPU_LDA(cpu, mode);
    CPU_TAX(cpu, mode);
}

void CPU_LDA(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    CPU_set_register_a(cpu, value);
}

void CPU_LDX(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    cpu->reg_x = value;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_x);
}

void CPU_LDY(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    cpu->reg_y = value;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_y);
}

void CPU_LSR(CPU* cpu, AddressingMode mode) {
    uint16_t addr;
    uint8_t data;

    if (mode == ADDR_MODE_ACCUMULATOR) {
        data = cpu->reg_a;
    }
    else {
        addr = CPU_get_operand_addr(cpu, mode);
        data = CPU_mem_read_u8(cpu, addr);
    }


    if ((data & 0x01) == 1) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, CARRY_FLAG);
    }

    data = data >> 1;

    if (mode == ADDR_MODE_ACCUMULATOR) {
        CPU_set_register_a(cpu, data);
    }
    else {
        CPU_mem_write_u8(cpu, addr, data);
        CPU_update_zero_and_negative_flags(cpu, data);
    }
}


void CPU_LXA(CPU* cpu, AddressingMode mode) {
    CPU_LDA(cpu, mode);
    CPU_TAX(cpu, mode);
}

void CPU_NOP(CPU* cpu, AddressingMode mode) {
    return;
}

void CPU_ORA(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    CPU_set_register_a(cpu, cpu->reg_a | value);
}

void CPU_PHA(CPU* cpu, AddressingMode mode) {
    CPU_stack_push_u8(cpu, cpu->reg_a);
}

void CPU_PHP(CPU* cpu, AddressingMode mode) {
    CPU_stack_push_u8(cpu, cpu->status | BREAK | BREAK2);
}

void CPU_PLA(CPU* cpu, AddressingMode mode) {
    uint8_t data = CPU_stack_pop_u8(cpu);
    CPU_set_register_a(cpu, data);
}

void CPU_PLP(CPU* cpu, AddressingMode mode) {
    uint8_t data = CPU_stack_pop_u8(cpu);
    cpu->status = data;
    CPU_clear_status_flag(cpu, BREAK);
    CPU_set_status_flag(cpu, BREAK2);
}

void CPU_RLA(CPU* cpu, AddressingMode mode) {
    CPU_ROL(cpu, mode);
    CPU_AND(cpu, mode);
}

void CPU_ROL(CPU* cpu, AddressingMode mode) {
    uint16_t addr;
    uint8_t data;

    if (mode == ADDR_MODE_ACCUMULATOR) {
        data = cpu->reg_a;
    }
    else {
        addr = CPU_get_operand_addr(cpu, mode);
        data = CPU_mem_read_u8(cpu, addr);
    }

    uint8_t carry = CPU_get_status_flag(cpu, CARRY_FLAG);

    if ((data >> 7) == 1) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, CARRY_FLAG);
    }

    data = (data << 1) | carry;

    if (mode == ADDR_MODE_ACCUMULATOR) {
        CPU_set_register_a(cpu, data);
    }
    else {
        CPU_mem_write_u8(cpu, addr, data);
        CPU_update_zero_and_negative_flags(cpu, data);
    }
}


void CPU_ROR(CPU* cpu, AddressingMode mode) {
    uint16_t addr;
    uint8_t data;

    if (mode == ADDR_MODE_ACCUMULATOR) {
        data = cpu->reg_a;
    }
    else {
        addr = CPU_get_operand_addr(cpu, mode);
        data = CPU_mem_read_u8(cpu, addr);
    }

    uint8_t carry = CPU_get_status_flag(cpu, CARRY_FLAG);

    if ((data & 0x01) == 1) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, CARRY_FLAG);
    }

    data = (data >> 1) | (carry << 7);

    if (mode == ADDR_MODE_ACCUMULATOR) {
        CPU_set_register_a(cpu, data);
    }
    else {
        CPU_mem_write_u8(cpu, addr, data);
        CPU_update_zero_and_negative_flags(cpu, data);
    }
}

void CPU_RRA(CPU* cpu, AddressingMode mode) {
    CPU_ROR(cpu, mode);
    CPU_ADC(cpu, mode);
}

void CPU_RTS(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_stack_pop_u16(cpu);
    cpu->pc = addr + 1;
}

void CPU_RTI(CPU* cpu, AddressingMode mode) {
    uint8_t status = CPU_stack_pop_u8(cpu);
    cpu->status = status;
    CPU_clear_status_flag(cpu, BREAK);
    CPU_set_status_flag(cpu, BREAK2);
    cpu->pc = CPU_stack_pop_u16(cpu);
}

void CPU_SAX(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    CPU_mem_write_u8(cpu, addr, cpu->reg_a & cpu->reg_x);
}

void CPU_SBC(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    CPU_add_to_register_a(cpu, ~value);
}

void CPU_SEC(CPU* cpu, AddressingMode mode) {
    CPU_set_status_flag(cpu, CARRY_FLAG);
}

void CPU_SED(CPU* cpu, AddressingMode mode) {
    CPU_set_status_flag(cpu, DECIMAL_MODE);
}

void CPU_SEI(CPU* cpu, AddressingMode mode) {
    CPU_set_status_flag(cpu, INTERRUPT_DISABLE);
}

void CPU_SKB(CPU* cpu, AddressingMode mode) {
    CPU_get_operand_addr(cpu, mode); // Read the operand but do nothing with it
}

void CPU_SLO(CPU* cpu, AddressingMode mode) {
    CPU_ASL(cpu, mode);
    CPU_ORA(cpu, mode);
}

void CPU_SRE(CPU* cpu, AddressingMode mode) {
    CPU_LSR(cpu, mode);
    CPU_EOR(cpu, mode);
}

void CPU_STA(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    CPU_mem_write_u8(cpu, addr, cpu->reg_a);
}

void CPU_STX(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    CPU_mem_write_u8(cpu, addr, cpu->reg_x);
}

void CPU_STY(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    CPU_mem_write_u8(cpu, addr, cpu->reg_y);
}

void CPU_SHX(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t result = cpu->reg_x & ( ((uint8_t) (addr >> 8)) + 1 );
    CPU_mem_write_u8(cpu, addr, result);
}

void CPU_SHY(CPU* cpu, AddressingMode mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t result = cpu->reg_y & ( ((uint8_t) (addr >> 8)) + 1 );
    CPU_mem_write_u8(cpu, addr, result);
}

void CPU_TAX(CPU* cpu, AddressingMode mode) {
    cpu->reg_x = cpu->reg_a;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_x);
}

void CPU_TAY(CPU* cpu, AddressingMode mode) {
    cpu->reg_y = cpu->reg_a;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_y);
}

void CPU_TSX(CPU* cpu, AddressingMode mode) {
    cpu->reg_x = cpu->stack_pointer;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_x);
}

void CPU_TXA(CPU* cpu, AddressingMode mode) {
    cpu->reg_a = cpu->reg_x;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_a);
}

void CPU_TXS(CPU* cpu, AddressingMode mode) {
    cpu->stack_pointer = cpu->reg_x;
}

void CPU_TYA(CPU* cpu, AddressingMode mode) {
    cpu->reg_a = cpu->reg_y;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_a);
}

void CPU_XAA(CPU* cpu, AddressingMode mode) {
    cpu->reg_a = cpu->reg_x;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_a);
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);
    CPU_set_register_a(cpu, cpu->reg_a & data);
}

void CPU_XAS(CPU* cpu, AddressingMode mode) {
    cpu->stack_pointer = cpu->reg_x & cpu->reg_a;
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t result = cpu->stack_pointer & ( ((uint8_t) (addr >> 8)) + 1 );
    CPU_mem_write_u8(cpu, addr, result);
}



uint8_t CPU_get_status_flag(CPU* cpu, StatusFlag flag) {
    return (cpu->status & flag) != 0;
}

void CPU_set_status_flag(CPU* cpu, StatusFlag flag) {
    cpu->status |= flag;
}

void CPU_clear_status_flag(CPU* cpu, StatusFlag flag) {
    cpu->status &= ~flag;
}

void CPU_update_zero_and_negative_flags(CPU* cpu, uint8_t result) {
    if (result == 0) {
        CPU_set_status_flag(cpu, ZERO_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, ZERO_FLAG);
    }

    if ((result & 0b10000000) != 0) {
        CPU_set_status_flag(cpu, NEGATIVE_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, NEGATIVE_FLAG);
    }
}

void CPU_set_register_a(CPU* cpu, uint8_t value) {
    cpu->reg_a = value;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_a);
}

void CPU_add_to_register_a(CPU* cpu, uint8_t value) {
    uint16_t sum = ((uint16_t) cpu->reg_a) + ((uint16_t) value) + ((uint16_t) (cpu->status & 0b00000001));

    uint16_t carry = sum > 0xFF;
    
    if (carry) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, CARRY_FLAG);
    }

    uint8_t result = (uint8_t) sum;

    if (((value ^ result) & (result ^ cpu->reg_a) & 0x80) != 0) {
        CPU_set_status_flag(cpu, OVERFLOW_FLAG);
    } 
    else {
        CPU_clear_status_flag(cpu, OVERFLOW_FLAG);
    }

    CPU_set_register_a(cpu, result);
}

void CPU_compare(CPU* cpu, AddressingMode mode, uint8_t compare_with) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);

    if (data <= compare_with) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, CARRY_FLAG);
    }

    CPU_update_zero_and_negative_flags(cpu, compare_with - data);
}

void CPU_branch(CPU* cpu, bool condition) {
    if (condition) {
        int8_t jump = (int8_t) CPU_mem_read_u8(cpu, cpu->pc);
        uint16_t jump_addr = cpu->pc + 1 + ((uint16_t) jump);

        cpu->pc = jump_addr;
    }
}