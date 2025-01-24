#include "../headers/cpu.h"


OpcodeEntry opcode_table[256] = {
    [0x29] = {CPU_AND, ADDR_MODE_IMMEDIATE},
    [0x25] = {CPU_AND, ADDR_MODE_ZERO_PAGE},
    [0x35] = {CPU_AND, ADDR_MODE_ZERO_PAGE_X},
    [0x2D] = {CPU_AND, ADDR_MODE_ABSOLUTE},
    [0x3D] = {CPU_AND, ADDR_MODE_ABSOLUTE_X},
    [0x39] = {CPU_AND, ADDR_MODE_ABSOLUTE_Y},
    [0x21] = {CPU_AND, ADDR_MODE_INDIRECT_X},
    [0x31] = {CPU_AND, ADDR_MODE_INDIRECT_Y},

    [0x49] = {CPU_EOR, ADDR_MODE_IMMEDIATE},
    [0x45] = {CPU_EOR, ADDR_MODE_ZERO_PAGE},
    [0x55] = {CPU_EOR, ADDR_MODE_ZERO_PAGE_X},
    [0x4D] = {CPU_EOR, ADDR_MODE_ABSOLUTE},
    [0x5D] = {CPU_EOR, ADDR_MODE_ABSOLUTE_X},
    [0x59] = {CPU_EOR, ADDR_MODE_ABSOLUTE_Y},
    [0x41] = {CPU_EOR, ADDR_MODE_INDIRECT_X},
    [0x51] = {CPU_EOR, ADDR_MODE_INDIRECT_Y},

    [0xE8] = {CPU_INX, ADDR_MODE_IMPLICIT},

    [0xC8] = {CPU_INY, ADDR_MODE_IMPLICIT},

    [0xA9] = {CPU_LDA, ADDR_MODE_IMMEDIATE},
    [0xA5] = {CPU_LDA, ADDR_MODE_ZERO_PAGE},
    [0xB5] = {CPU_LDA, ADDR_MODE_ZERO_PAGE_X},
    [0xAD] = {CPU_LDA, ADDR_MODE_ABSOLUTE},
    [0xBD] = {CPU_LDA, ADDR_MODE_ABSOLUTE_X},
    [0xB9] = {CPU_LDA, ADDR_MODE_ABSOLUTE_Y},
    [0xA1] = {CPU_LDA, ADDR_MODE_INDIRECT_X},
    [0xB1] = {CPU_LDA, ADDR_MODE_INDIRECT_Y},
    
    [0xA2] = {CPU_LDX, ADDR_MODE_IMMEDIATE},
    [0xA6] = {CPU_LDX, ADDR_MODE_ZERO_PAGE},
    [0xB6] = {CPU_LDX, ADDR_MODE_ZERO_PAGE_Y},
    [0xAE] = {CPU_LDX, ADDR_MODE_ABSOLUTE},
    [0xBE] = {CPU_LDX, ADDR_MODE_ABSOLUTE_Y},

    [0xA0] = {CPU_LDY, ADDR_MODE_IMMEDIATE},
    [0xA4] = {CPU_LDY, ADDR_MODE_ZERO_PAGE},
    [0xB4] = {CPU_LDY, ADDR_MODE_ZERO_PAGE_X},
    [0xAC] = {CPU_LDY, ADDR_MODE_ABSOLUTE},
    [0xBC] = {CPU_LDY, ADDR_MODE_ABSOLUTE_X},

    [0x09] = {CPU_ORA, ADDR_MODE_IMMEDIATE},
    [0x05] = {CPU_ORA, ADDR_MODE_ZERO_PAGE},
    [0x15] = {CPU_ORA, ADDR_MODE_ZERO_PAGE_X},
    [0x0D] = {CPU_ORA, ADDR_MODE_ABSOLUTE},
    [0x1D] = {CPU_ORA, ADDR_MODE_ABSOLUTE_X},
    [0x19] = {CPU_ORA, ADDR_MODE_ABSOLUTE_Y},
    [0x01] = {CPU_ORA, ADDR_MODE_INDIRECT_X},
    [0x11] = {CPU_ORA, ADDR_MODE_INDIRECT_Y},

    [0x85] = {CPU_STA, ADDR_MODE_ZERO_PAGE},
    [0x95] = {CPU_STA, ADDR_MODE_ZERO_PAGE_X},
    [0x8D] = {CPU_STA, ADDR_MODE_ABSOLUTE},
    [0x9D] = {CPU_STA, ADDR_MODE_ABSOLUTE_X},
    [0x99] = {CPU_STA, ADDR_MODE_ABSOLUTE_Y},
    [0x81] = {CPU_STA, ADDR_MODE_INDIRECT_X},
    [0x91] = {CPU_STA, ADDR_MODE_INDIRECT_Y},

    [0xAA] = {CPU_TAX, ADDR_MODE_IMPLICIT},
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
    cpu->pc++;
    return cpu->memory[addr];
}

void CPU_mem_write_u8(CPU_t* cpu, uint16_t addr, uint8_t data) {
    cpu->memory[addr] = data;
}

uint16_t CPU_mem_read_u16(CPU_t* cpu, uint16_t addr) {
    cpu->pc += 2;
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

        if (opcode == 0x00) return;

        OpcodeEntry entry = opcode_table[opcode];
        if (entry.instruction != NULL) {
            entry.instruction(cpu, entry.mode);
        }
        else {
            printf("Unknown or unimplemented instruction (skipped)\n");   
        }
    }
}


void CPU_AND(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    CPU_set_register_a(cpu, cpu->reg_a & value);
}

void CPU_EOR(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    CPU_set_register_a(cpu, cpu->reg_a ^ value);
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

void CPU_ORA(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    uint8_t value = CPU_mem_read_u8(cpu, addr);
    CPU_set_register_a(cpu, cpu->reg_a | value);
}

void CPU_STA(CPU_t* cpu, AddressingMode_t mode) {
    uint16_t addr = CPU_get_operand_addr(cpu, mode);
    CPU_mem_write_u8(cpu, addr, cpu->reg_a);
}

void CPU_TAX(CPU_t* cpu) {
    cpu->reg_x = cpu->reg_a;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_x);
}

void CPU_INX(CPU_t* cpu) {
    cpu->reg_x++;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_x);
}

void CPU_INY(CPU_t* cpu) {
    cpu->reg_y++;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_y);
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