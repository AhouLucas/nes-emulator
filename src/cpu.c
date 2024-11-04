#include "../headers/cpu.h"

CPU_t* CPU_init() {
    CPU_t* cpu = malloc(sizeof(CPU_t));
    cpu->memory = malloc(sizeof(uint8_t)*0xFFFF);
    cpu->reg_a = 0;
    cpu->reg_x = 0;
    cpu->pc = 0;
    cpu->status = 0;
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

uint16_t CPU_get_operand_addr(CPU_t* cpu, AddressingMode_t mode) {
    switch (mode)
    {
    case ADDR_MODE_IMMEDIATE:
        return cpu->pc;
    case ADDR_MODE_ZERO_PAGE:
        return CPU_mem_read_u16(cpu, cpu->pc);
    case ADDR_MODE_ABSOLUTE:
        return CPU_mem_read_u16(cpu, cpu->pc);
    case ADDR_MODE_ZERO_PAGE_X:
        uint8_t pos = CPU_mem_read_u8(cpu, cpu->pc);
        return pos + cpu->reg_x;
    case ADDR_MODE_ZERO_PAGE_Y:
        uint8_t pos = CPU_mem_read_u8(cpu, cpu->pc);
        return pos + cpu->reg_y;
    case ADDR_MODE_ABSOLUTE_X:
        uint16_t base = CPU_mem_read_u16(cpu, cpu->pc);
        return base + ((uint16_t)cpu->reg_x);
    case ADDR_MODE_ABSOLUTE_Y:
        uint16_t base = CPU_mem_read_u16(cpu, cpu->pc);
        return base + ((uint16_t)cpu->reg_y);
    case ADDR_MODE_INDIRECT_X:
        uint8_t base = CPU_mem_read_u8(cpu, cpu->pc);
        uint8_t ptr = (uint8_t)base + cpu->reg_x;
        uint8_t lo = CPU_mem_read_u8(cpu, ptr);
        uint8_t hi = CPU_mem_read_u8(cpu, ptr+1);
        return ((uint16_t) hi)<<8 | ((uint16_t) lo);
    case ADDR_MODE_INDIRECT_Y:
        uint8_t base = CPU_mem_read_u8(cpu, cpu->pc);
        uint8_t lo = CPU_mem_read_u8(cpu, base);
        uint8_t hi = CPU_mem_read_u16(cpu, base+1);
        uint16_t deref_base = ((uint16_t) hi)<<8 | ((uint16_t) lo);
        return deref_base + ((uint16_t) cpu->reg_y);
    default:
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

        switch (opcode) {

        // LDA (0xA9)
        case 0xA9:
            uint8_t param = CPU_mem_read_u8(cpu, cpu->pc);
            cpu->pc++;
            CPU_LDA(cpu, param);
            break;

        // TAX (0xAA)
        case 0xAA:
            CPU_TAX(cpu);
            break;

        // INX (0xE8)
        case 0xE8:
            CPU_INX(cpu);
            break;
        
        // BRK (0x00)
        case 0x00:
            return;

        default:
            break;
        }
    }
}


void CPU_LDA(CPU_t* cpu, uint8_t value) {
    cpu->reg_a = value;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_a);
}

void CPU_TAX(CPU_t* cpu) {
    cpu->reg_x = cpu->reg_a;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_x);
}

void CPU_INX(CPU_t* cpu) {
    cpu->reg_x++;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_x);
}

void CPU_update_zero_and_negative_flags(CPU_t* cpu, uint8_t result) {
    if (result == 0) {
        cpu->status |= 0b00000010;
    }
    else {
        cpu->status &= 0b11111101;
    }

    if ((result & 0b10000000) != 0) {
        cpu->status |= 0b10000000;
    }
    else {
        cpu->status &= 0b01111111;
    }
}