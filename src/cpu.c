#include "../headers/cpu.h"

CPU_t* CPU_init() {
    CPU_t* cpu = malloc(sizeof(CPU_t));
    cpu->reg_a = 0;
    cpu->reg_x = 0;
    cpu->pc = 0;
    cpu->status = 0;
    return cpu;
}

void CPU_free(CPU_t* cpu) {
    free(cpu);
    return;
}

void CPU_interpret(CPU_t* cpu, uint8_t* program) {
    cpu->pc = 0;

    for (;;) {
        uint8_t opcode = program[cpu->pc++];

        switch (opcode) {

        // LDA (0xA9)
        case 0xA9:
            uint8_t param = program[cpu->pc++];
            CPU_LDA_0xA9(cpu, param);
            break;

        // TAX (0xAA)
        case 0xAA:
            CPU_TAX_0xAA(cpu);
            break;

        // INX (0xE8)
        case 0xE8:
            CPU_INX_0xE8(cpu);
            break;
        
        // BRK (0x00)
        case 0x00:
            return;

        default:
            break;
        }
    }
}


void CPU_LDA_0xA9(CPU_t* cpu, uint8_t value) {
    cpu->reg_a = value;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_a);
}

void CPU_TAX_0xAA(CPU_t* cpu) {
    cpu->reg_x = cpu->reg_a;
    CPU_update_zero_and_negative_flags(cpu, cpu->reg_x);
}

void CPU_INX_0xE8(CPU_t* cpu) {
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