#include "../headers/cpu.h"


OpcodeEntry_t opcode_table[256] = {
    [0x69] = {.instruction.void_instruction = CPU_ADC, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_IMMEDIATE,     .len = 2, .cycles = 2},
    [0x65] = {.instruction.void_instruction = CPU_ADC, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE,     .len = 2, .cycles = 3},
    [0x75] = {.instruction.void_instruction = CPU_ADC, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE_X,   .len = 2, .cycles = 4},
    [0x6D] = {.instruction.void_instruction = CPU_ADC, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE,      .len = 3, .cycles = 4},
    [0x7D] = {.instruction.void_instruction = CPU_ADC, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE_X,    .len = 3, .cycles = 4},
    [0x79] = {.instruction.void_instruction = CPU_ADC, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE_Y,    .len = 3, .cycles = 4},
    [0x61] = {.instruction.void_instruction = CPU_ADC, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_INDIRECT_X,    .len = 2, .cycles = 6},
    [0x71] = {.instruction.void_instruction = CPU_ADC, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_INDIRECT_Y,    .len = 2, .cycles = 5},

    [0x29] = {.instruction.void_instruction = CPU_AND, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_IMMEDIATE,     .len = 2, .cycles = 2},
    [0x25] = {.instruction.void_instruction = CPU_AND, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE,     .len = 2, .cycles = 3},
    [0x35] = {.instruction.void_instruction = CPU_AND, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE_X,   .len = 2, .cycles = 4},
    [0x2D] = {.instruction.void_instruction = CPU_AND, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE,      .len = 3, .cycles = 4},
    [0x3D] = {.instruction.void_instruction = CPU_AND, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE_X,    .len = 3, .cycles = 4},
    [0x39] = {.instruction.void_instruction = CPU_AND, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE_Y,    .len = 3, .cycles = 4},
    [0x21] = {.instruction.void_instruction = CPU_AND, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_INDIRECT_X,    .len = 2, .cycles = 6},
    [0x31] = {.instruction.void_instruction = CPU_AND, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_INDIRECT_Y,    .len = 2, .cycles = 5},

    [0x0A] = {.instruction.void_instruction = CPU_ASL_ACC,  .type = INSTRUCTION_TYPE_VOID,  .mode = ADDR_MODE_ACCUMULATOR,   .len = 1, .cycles = 2},
    [0x06] = {.instruction.u8_instruction   = CPU_ASL,      .type = INSTRUCTION_TYPE_U8  ,  .mode = ADDR_MODE_ZERO_PAGE,     .len = 2, .cycles = 5},
    [0x16] = {.instruction.u8_instruction   = CPU_ASL,      .type = INSTRUCTION_TYPE_U8  ,  .mode = ADDR_MODE_ZERO_PAGE_X,   .len = 2, .cycles = 6},
    [0x0E] = {.instruction.u8_instruction   = CPU_ASL,      .type = INSTRUCTION_TYPE_U8  ,  .mode = ADDR_MODE_ABSOLUTE,      .len = 3, .cycles = 6},
    [0x06] = {.instruction.u8_instruction   = CPU_ASL,      .type = INSTRUCTION_TYPE_U8  ,  .mode = ADDR_MODE_ABSOLUTE_X,    .len = 3, .cycles = 7},

    [0xC6] = {.instruction.u8_instruction = CPU_DEC, .type = INSTRUCTION_TYPE_U8, .mode = ADDR_MODE_ZERO_PAGE,     .len = 2, .cycles = 5},
    [0xD6] = {.instruction.u8_instruction = CPU_DEC, .type = INSTRUCTION_TYPE_U8, .mode = ADDR_MODE_ZERO_PAGE_X,   .len = 2, .cycles = 6},
    [0xCE] = {.instruction.u8_instruction = CPU_DEC, .type = INSTRUCTION_TYPE_U8, .mode = ADDR_MODE_ABSOLUTE,      .len = 3, .cycles = 6},
    [0xDE] = {.instruction.u8_instruction = CPU_DEC, .type = INSTRUCTION_TYPE_U8, .mode = ADDR_MODE_ABSOLUTE_X,    .len = 3, .cycles = 7},

    [0xCA] = {.instruction.void_instruction = CPU_DEX, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_IMPLICIT,      .len = 1, .cycles = 2},

    [0x88] = {.instruction.void_instruction = CPU_DEY, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_IMPLICIT,      .len = 1, .cycles = 2},

    [0x49] = {.instruction.void_instruction = CPU_EOR, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_IMMEDIATE,     .len = 2, .cycles = 2},
    [0x45] = {.instruction.void_instruction = CPU_EOR, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE,     .len = 2, .cycles = 3},
    [0x55] = {.instruction.void_instruction = CPU_EOR, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE_X,   .len = 2, .cycles = 4},
    [0x4D] = {.instruction.void_instruction = CPU_EOR, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE,      .len = 3, .cycles = 4},
    [0x5D] = {.instruction.void_instruction = CPU_EOR, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE_X,    .len = 3, .cycles = 4},
    [0x59] = {.instruction.void_instruction = CPU_EOR, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE_Y,    .len = 3, .cycles = 4},
    [0x41] = {.instruction.void_instruction = CPU_EOR, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_INDIRECT_X,    .len = 2, .cycles = 6},
    [0x51] = {.instruction.void_instruction = CPU_EOR, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_INDIRECT_Y,    .len = 2, .cycles = 5},

    [0xE6] = {.instruction.u8_instruction = CPU_INC, .type = INSTRUCTION_TYPE_U8, .mode = ADDR_MODE_ZERO_PAGE,     .len = 2, .cycles = 5},
    [0xF6] = {.instruction.u8_instruction = CPU_INC, .type = INSTRUCTION_TYPE_U8, .mode = ADDR_MODE_ZERO_PAGE_X,   .len = 2, .cycles = 6},
    [0xEE] = {.instruction.u8_instruction = CPU_INC, .type = INSTRUCTION_TYPE_U8, .mode = ADDR_MODE_ABSOLUTE,      .len = 3, .cycles = 6},
    [0xFE] = {.instruction.u8_instruction = CPU_INC, .type = INSTRUCTION_TYPE_U8, .mode = ADDR_MODE_ABSOLUTE_X,    .len = 3, .cycles = 7},

    [0xE8] = {.instruction.void_instruction = CPU_INX, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_IMPLICIT,      .len = 1, .cycles = 2},

    [0xC8] = {.instruction.void_instruction = CPU_INY, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_IMPLICIT,      .len = 1, .cycles = 2},

    [0xA9] = {.instruction.void_instruction = CPU_LDA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_IMMEDIATE,     .len = 2, .cycles = 2},
    [0xA5] = {.instruction.void_instruction = CPU_LDA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE,     .len = 2, .cycles = 3},
    [0xB5] = {.instruction.void_instruction = CPU_LDA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE_X,   .len = 2, .cycles = 4},
    [0xAD] = {.instruction.void_instruction = CPU_LDA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE,      .len = 3, .cycles = 4},
    [0xBD] = {.instruction.void_instruction = CPU_LDA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE_X,    .len = 3, .cycles = 4},
    [0xB9] = {.instruction.void_instruction = CPU_LDA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE_Y,    .len = 3, .cycles = 4},
    [0xA1] = {.instruction.void_instruction = CPU_LDA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_INDIRECT_X,    .len = 2, .cycles = 6},
    [0xB1] = {.instruction.void_instruction = CPU_LDA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_INDIRECT_Y,    .len = 2, .cycles = 5},
    
    [0xA2] = {.instruction.void_instruction = CPU_LDX, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_IMMEDIATE,     .len = 2, .cycles = 2},
    [0xA6] = {.instruction.void_instruction = CPU_LDX, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE,     .len = 2, .cycles = 3},
    [0xB6] = {.instruction.void_instruction = CPU_LDX, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE_Y,   .len = 2, .cycles = 4},
    [0xAE] = {.instruction.void_instruction = CPU_LDX, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE,      .len = 3, .cycles = 4},
    [0xBE] = {.instruction.void_instruction = CPU_LDX, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE_Y,    .len = 3, .cycles = 4},

    [0xA0] = {.instruction.void_instruction = CPU_LDY, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_IMMEDIATE,     .len = 2, .cycles = 2},
    [0xA4] = {.instruction.void_instruction = CPU_LDY, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE,     .len = 2, .cycles = 3},
    [0xB4] = {.instruction.void_instruction = CPU_LDY, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE_X,   .len = 2, .cycles = 4},
    [0xAC] = {.instruction.void_instruction = CPU_LDY, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE,      .len = 3, .cycles = 4},
    [0xBC] = {.instruction.void_instruction = CPU_LDY, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE_X,    .len = 3, .cycles = 4},

    [0x4A] = {.instruction.void_instruction = CPU_LSR_ACC,  .type = INSTRUCTION_TYPE_VOID,  .mode = ADDR_MODE_ACCUMULATOR,   .len = 1, .cycles = 2},
    [0x46] = {.instruction.u8_instruction   = CPU_LSR,      .type = INSTRUCTION_TYPE_U8,    .mode = ADDR_MODE_ZERO_PAGE,     .len = 2, .cycles = 5},
    [0x56] = {.instruction.u8_instruction   = CPU_LSR,      .type = INSTRUCTION_TYPE_U8,    .mode = ADDR_MODE_ZERO_PAGE_X,   .len = 2, .cycles = 6},
    [0x4E] = {.instruction.u8_instruction   = CPU_LSR,      .type = INSTRUCTION_TYPE_U8,    .mode = ADDR_MODE_ABSOLUTE,      .len = 3, .cycles = 6},
    [0x5E] = {.instruction.u8_instruction   = CPU_LSR,      .type = INSTRUCTION_TYPE_U8,    .mode = ADDR_MODE_ABSOLUTE_X,    .len = 3, .cycles = 7},

    [0x09] = {.instruction.void_instruction = CPU_ORA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_IMMEDIATE,     .len = 2, .cycles = 2},
    [0x05] = {.instruction.void_instruction = CPU_ORA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE,     .len = 2, .cycles = 3},
    [0x15] = {.instruction.void_instruction = CPU_ORA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE_X,   .len = 2, .cycles = 4},
    [0x0D] = {.instruction.void_instruction = CPU_ORA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE,      .len = 3, .cycles = 4},
    [0x1D] = {.instruction.void_instruction = CPU_ORA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE_X,    .len = 3, .cycles = 4},
    [0x19] = {.instruction.void_instruction = CPU_ORA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE_Y,    .len = 3, .cycles = 4},
    [0x01] = {.instruction.void_instruction = CPU_ORA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_INDIRECT_X,    .len = 2, .cycles = 6},
    [0x11] = {.instruction.void_instruction = CPU_ORA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_INDIRECT_Y,    .len = 2, .cycles = 5},

    [0x08] = {.instruction.void_instruction = CPU_PHP, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_IMPLICIT,      .len = 1, .cycles = 3},

    [0x68] = {.instruction.void_instruction = CPU_PLA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_IMPLICIT,      .len = 1, .cycles = 4},

    [0x28] = {.instruction.void_instruction = CPU_PLP, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_IMPLICIT,      .len = 1, .cycles = 4},

    [0x2A] = {.instruction.void_instruction = CPU_ROL_ACC,  .type = INSTRUCTION_TYPE_VOID,  .mode = ADDR_MODE_ACCUMULATOR,   .len = 1, .cycles = 2},
    [0x26] = {.instruction.u8_instruction   = CPU_ROL,      .type = INSTRUCTION_TYPE_U8,    .mode = ADDR_MODE_ZERO_PAGE,     .len = 2, .cycles = 5},
    [0x36] = {.instruction.u8_instruction   = CPU_ROL,      .type = INSTRUCTION_TYPE_U8,    .mode = ADDR_MODE_ZERO_PAGE_X,   .len = 2, .cycles = 6},
    [0x2E] = {.instruction.u8_instruction   = CPU_ROL,      .type = INSTRUCTION_TYPE_U8,    .mode = ADDR_MODE_ABSOLUTE,      .len = 3, .cycles = 6},
    [0x3E] = {.instruction.u8_instruction   = CPU_ROL,      .type = INSTRUCTION_TYPE_U8,    .mode = ADDR_MODE_ABSOLUTE_X,    .len = 3, .cycles = 7},

    [0x6A] = {.instruction.void_instruction = CPU_ROR_ACC,  .type = INSTRUCTION_TYPE_VOID,  .mode = ADDR_MODE_ACCUMULATOR,   .len = 1, .cycles = 2},
    [0x66] = {.instruction.u8_instruction   = CPU_ROR,      .type = INSTRUCTION_TYPE_U8,    .mode = ADDR_MODE_ZERO_PAGE,     .len = 2, .cycles = 5},
    [0x76] = {.instruction.u8_instruction   = CPU_ROR,      .type = INSTRUCTION_TYPE_U8,    .mode = ADDR_MODE_ZERO_PAGE_X,   .len = 2, .cycles = 6},
    [0x6E] = {.instruction.u8_instruction   = CPU_ROR,      .type = INSTRUCTION_TYPE_U8,    .mode = ADDR_MODE_ABSOLUTE,      .len = 3, .cycles = 6},
    [0x7E] = {.instruction.u8_instruction   = CPU_ROR,      .type = INSTRUCTION_TYPE_U8,    .mode = ADDR_MODE_ABSOLUTE_X,    .len = 3, .cycles = 7},

    [0xE9] = {.instruction.void_instruction = CPU_SBC, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_IMMEDIATE,     .len = 2, .cycles = 2},
    [0xE5] = {.instruction.void_instruction = CPU_SBC, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE,     .len = 2, .cycles = 3},
    [0xF5] = {.instruction.void_instruction = CPU_SBC, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE_X,   .len = 2, .cycles = 4},
    [0xED] = {.instruction.void_instruction = CPU_SBC, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE,      .len = 3, .cycles = 4},
    [0xFD] = {.instruction.void_instruction = CPU_SBC, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE_X,    .len = 3, .cycles = 4},
    [0xF9] = {.instruction.void_instruction = CPU_SBC, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE_Y,    .len = 3, .cycles = 4},
    [0xE1] = {.instruction.void_instruction = CPU_SBC, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_INDIRECT_X,    .len = 2, .cycles = 6},
    [0xF1] = {.instruction.void_instruction = CPU_SBC, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_INDIRECT_Y,    .len = 2, .cycles = 5},

    [0x85] = {.instruction.void_instruction = CPU_STA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE,     .len = 2, .cycles = 3},
    [0x95] = {.instruction.void_instruction = CPU_STA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ZERO_PAGE_X,   .len = 2, .cycles = 4},
    [0x8D] = {.instruction.void_instruction = CPU_STA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE,      .len = 3, .cycles = 4},
    [0x9D] = {.instruction.void_instruction = CPU_STA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE_X,    .len = 3, .cycles = 5},
    [0x99] = {.instruction.void_instruction = CPU_STA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_ABSOLUTE_Y,    .len = 3, .cycles = 5},
    [0x81] = {.instruction.void_instruction = CPU_STA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_INDIRECT_X,    .len = 2, .cycles = 6},
    [0x91] = {.instruction.void_instruction = CPU_STA, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_INDIRECT_Y,    .len = 2, .cycles = 6},

    [0xAA] = {.instruction.void_instruction = CPU_TAX, .type = INSTRUCTION_TYPE_VOID, .mode = ADDR_MODE_IMPLICIT,      .len = 1, .cycles = 2},
};

CPU_t* CPU_init() {
    CPU_t* cpu = malloc(sizeof(CPU_t));
    cpu->memory = malloc(sizeof(uint8_t)*0xFFFF);
    cpu->reg_a = 0;
    cpu->reg_x = 0;
    cpu->pc = 0;
    cpu->status = 0;
    cpu->stack_pointer = STACK_RESET;
    return cpu;
}

void CPU_free(CPU_t* cpu) {
    free(cpu->memory);
    free(cpu);
    return;
}

uint8_t CPU_mem_read_u8(CPU_t* cpu, uint16_t addr) {
    return cpu->memory[addr];
}

void CPU_mem_write_u8(CPU_t* cpu, uint16_t addr, uint8_t data) {
    cpu->memory[addr] = data;
}

uint8_t CPU_stack_pop_u8(CPU_t* cpu) {
    cpu->stack_pointer++;
    return CPU_mem_read_u8(cpu, STACK + cpu->stack_pointer);
}

void CPU_stack_push_u8(CPU_t* cpu, uint8_t data) {
    CPU_mem_write_u8(cpu, STACK + cpu->stack_pointer, data);
    cpu->stack_pointer--;
}

uint16_t CPU_mem_read_u16(CPU_t* cpu, uint16_t addr) {
    uint16_t lo = CPU_mem_read_u8(cpu, addr);
    uint16_t hi = CPU_mem_read_u8(cpu, addr+1);
    return (hi<<8) | lo;
}

void CPU_mem_write_u16(CPU_t* cpu, uint16_t addr, uint16_t data) {
    uint8_t hi = data>>8;
    uint8_t lo = data & 0xFF;
    CPU_mem_write_u8(cpu, addr, lo);
    CPU_mem_write_u8(cpu, addr+1, hi);
}

uint16_t CPU_stack_pop_u16(CPU_t* cpu) {
    uint8_t lo = CPU_stack_pop_u8(cpu), hi = CPU_stack_pop_u8(cpu);
    return (hi<<8) | lo;
}

void CPU_stack_push_u16(CPU_t* cpu, uint16_t data) {
    uint8_t hi = data >> 8;
    uint8_t lo = data & 0xFF;
    CPU_stack_push_u8(cpu, hi);
    CPU_stack_push_u8(cpu, lo);
}

uint16_t CPU_get_operand_addr(CPU_t* cpu, AddressingMode_t mode) {
    uint8_t pos;
    uint16_t base;
    uint8_t lo, hi;
    uint8_t ptr;
    uint16_t deref_base;

    switch (mode)
    {
    case ADDR_MODE_IMMEDIATE:
        return cpu->pc;
    case ADDR_MODE_ZERO_PAGE:
        return CPU_mem_read_u16(cpu, cpu->pc);
    case ADDR_MODE_ABSOLUTE:
        return CPU_mem_read_u16(cpu, cpu->pc);
    case ADDR_MODE_ZERO_PAGE_X:
        pos = CPU_mem_read_u8(cpu, cpu->pc);
        return pos + cpu->reg_x;
    case ADDR_MODE_ZERO_PAGE_Y:
        pos = CPU_mem_read_u8(cpu, cpu->pc);
        return pos + cpu->reg_y;
    case ADDR_MODE_ABSOLUTE_X:
        base = CPU_mem_read_u16(cpu, cpu->pc);
        return base + ((uint16_t)cpu->reg_x);
    case ADDR_MODE_ABSOLUTE_Y:
        base = CPU_mem_read_u16(cpu, cpu->pc);
        return base + ((uint16_t)cpu->reg_y);
    case ADDR_MODE_INDIRECT_X:
        base = CPU_mem_read_u8(cpu, cpu->pc);
        ptr = (uint8_t)base + cpu->reg_x;
        lo = CPU_mem_read_u8(cpu, ptr);
        hi = CPU_mem_read_u8(cpu, ptr+1);
        return ((uint16_t) hi)<<8 | ((uint16_t) lo);
    case ADDR_MODE_INDIRECT_Y:
        base = CPU_mem_read_u8(cpu, cpu->pc);
        lo = CPU_mem_read_u8(cpu, base);
        hi = CPU_mem_read_u8(cpu, base+1);
        deref_base = ((uint16_t) hi)<<8 | ((uint16_t) lo);
        return deref_base + ((uint16_t) cpu->reg_y);
    default:
        printf("Unknown Addressing mode\n");
        exit(EXIT_FAILURE);
        break;
    }
}

void CPU_reset(CPU_t* cpu) {
    cpu->reg_a = 0;
    cpu->reg_x = 0;
    cpu->status = 0;
    cpu->pc = CPU_mem_read_u16(cpu, 0xFFFC);
}

void CPU_load_and_run(CPU_t* cpu, uint8_t* program, size_t program_size) {
    CPU_load(cpu, program, program_size);
    CPU_reset(cpu);
    CPU_run(cpu);
}

void CPU_load(CPU_t* cpu, uint8_t* program, size_t program_size) {
    memcpy(cpu->memory+0x8000, program, program_size);
    CPU_mem_write_u16(cpu, 0xFFFC, 0x8000);
}

void CPU_run(CPU_t* cpu) {
    for (;;) {
        uint8_t opcode = CPU_mem_read_u8(cpu, cpu->pc);
        cpu->pc++;
        uint16_t pc_state = cpu->pc;

        if (opcode == 0x00) return;

        OpcodeEntry_t entry = opcode_table[opcode];
        switch (entry.type) {
        case INSTRUCTION_TYPE_VOID:
            entry.instruction.void_instruction(cpu, entry.mode);
            break;
        case INSTRUCTION_TYPE_U8:
            entry.instruction.u8_instruction(cpu, entry.mode);
            break;
        default:
            printf("Unknown instruction type\n");
            exit(EXIT_FAILURE);
            break;
        }

        if (pc_state == cpu->pc) {
            cpu->pc += (uint16_t) entry.len - 1;
        }
    }
}


void CPU_ADC(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    CPU_add_to_register_a(cpu, value);
}

uint8_t CPU_ASL(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);

    if ((data >> 7) == 1) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, CARRY_FLAG);
    }

    data = data << 1;

    CPU_mem_write_u8(cpu, addr, data);
    CPU_update_zero_and_negative_flags(cpu, data);
    return data;
}

void CPU_ASL_ACC(CPU_t* cpu, AddressingMode_t mode) {
    uint8_t data = cpu->reg_a;

    if ((data >> 7) == 1) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, CARRY_FLAG);
    }

    data = data << 1;
    CPU_set_register_a(cpu, data);
}

void CPU_AND(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    CPU_set_register_a(cpu, cpu->reg_a & value);
}

uint8_t CPU_DEC(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);
    data--;
    CPU_mem_write_u8(cpu, addr, data);
    CPU_update_zero_and_negative_flags(cpu, data);
    return data;
}

void CPU_DEX(CPU_t* cpu, AddressingMode_t mode) {
    cpu->reg_x--;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_x);
}

void CPU_DEY(CPU_t* cpu, AddressingMode_t mode) {
    cpu->reg_y--;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_y);
}

void CPU_EOR(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    CPU_set_register_a(cpu, cpu->reg_a ^ value);
}

uint8_t CPU_INC(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);
    data++;
    CPU_mem_write_u8(cpu, addr, data);
    CPU_update_zero_and_negative_flags(cpu, data);
    return data;
}

void CPU_INX(CPU_t* cpu, AddressingMode_t mode) {
    cpu->reg_x++;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_x);
}

void CPU_INY(CPU_t* cpu, AddressingMode_t mode) {
    cpu->reg_y++;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_y);
}


void CPU_LDA(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);

    cpu->reg_a = value;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_a);
}

void CPU_LDX(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    cpu->reg_x = value;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_x);
}

void CPU_LDY(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    cpu->reg_y = value;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_y);
}

uint8_t CPU_LSR(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);

    if ((data & 0x01) == 1) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, CARRY_FLAG);
    }

    data = data >> 1;
    CPU_mem_write_u8(cpu, addr, data);
    CPU_update_zero_and_negative_flags(cpu, data);
    return data;
}

void CPU_LSR_ACC(CPU_t* cpu, AddressingMode_t mode) {
    uint8_t data = cpu->reg_a;

    if ((data & 0x01) == 1) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, CARRY_FLAG);
    }

    data = data >> 1;
    CPU_set_register_a(cpu, data);
}

void CPU_ORA(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    CPU_set_register_a(cpu, cpu->reg_a | value);
}

void CPU_PHP(CPU_t* cpu, AddressingMode_t mode) {
    CPU_stack_push_u8(cpu, cpu->status | BREAK | BREAK2);
}

void CPU_PLA(CPU_t* cpu, AddressingMode_t mode) {
    uint8_t data = CPU_stack_pop_u8(cpu);
    CPU_set_register_a(cpu, data);
}

void CPU_PLP(CPU_t* cpu, AddressingMode_t mode) {
    uint8_t data = CPU_stack_pop_u8(cpu);
    cpu->status = data;
    CPU_clear_status_flag(cpu, BREAK);
    CPU_set_status_flag(cpu, BREAK2);
}

uint8_t CPU_ROL(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);
    uint8_t carry = CPU_get_status_flag(cpu, CARRY_FLAG);

    if ((data >> 7) == 1) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, CARRY_FLAG);
    }

    data = (data << 1) | carry;
    CPU_mem_write_u8(cpu, addr, data);
    CPU_update_zero_and_negative_flags(cpu, data);
    return data;
}

void CPU_ROL_ACC(CPU_t* cpu, AddressingMode_t mode) {
    uint8_t data = cpu->reg_a;
    uint8_t carry = CPU_get_status_flag(cpu, CARRY_FLAG);

    if ((data >> 7) == 1) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, CARRY_FLAG);
    }

    data = (data << 1) | carry;
    CPU_set_register_a(cpu, data);
}

uint8_t CPU_ROR(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t data = CPU_mem_read_u8(cpu, addr);
    uint8_t carry = CPU_get_status_flag(cpu, CARRY_FLAG);

    if ((data & 0x01) == 1) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, CARRY_FLAG);
    }

    data = (data >> 1) | (carry << 7);
    CPU_mem_write_u8(cpu, addr, data);
    CPU_update_zero_and_negative_flags(cpu, data);
    return data;
}

void CPU_ROR_ACC(CPU_t* cpu, AddressingMode_t mode) {
    uint8_t data = cpu->reg_a;
    uint8_t carry = CPU_get_status_flag(cpu, CARRY_FLAG);

    if ((data & 0x01) == 1) {
        CPU_set_status_flag(cpu, CARRY_FLAG);
    }
    else {
        CPU_clear_status_flag(cpu, CARRY_FLAG);
    }

    data = (data >> 1) | (carry << 7);
    CPU_set_register_a(cpu, data);
}

void CPU_SBC(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    CPU_add_to_register_a(cpu, ~value);
}

void CPU_STA(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    CPU_mem_write_u8(cpu, addr, cpu->reg_a);
}

void CPU_TAX(CPU_t* cpu, AddressingMode_t mode) {
    cpu->reg_x = cpu->reg_a;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_x);
}


uint8_t CPU_get_status_flag(CPU_t* cpu, StatusFlag_t flag) {
    return (cpu->status & flag) != 0;
}

void CPU_set_status_flag(CPU_t* cpu, StatusFlag_t flag) {
    cpu->status |= flag;
}

void CPU_clear_status_flag(CPU_t* cpu, StatusFlag_t flag) {
    cpu->status &= ~flag;
}

void CPU_update_zero_and_negative_flags(CPU_t* cpu, uint8_t result) {
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

void CPU_set_register_a(CPU_t* cpu, uint8_t value) {
    cpu->reg_a = value;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_a);
}

void CPU_add_to_register_a(CPU_t* cpu, uint8_t value) {
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