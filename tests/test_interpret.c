#include "../headers/common.h"
#include "../headers/cpu.h"


void test_0xA9_LDA_immediate_load_data() {
    CPU_t* cpu = CPU_init();

    CPU_interpret(cpu, (uint8_t[]){0xa9, 0x05, 0x00});

    assert(cpu->reg_a == 0x05);
    assert((cpu->status & 0b00000010) == 0b00);
    assert((cpu->status & 0b10000000) == 0);

    CPU_free(cpu);
}

void test_0xA9_LDA_zero_flag() {
    CPU_t* cpu = CPU_init();

    CPU_interpret(cpu, (uint8_t[]){0xa9, 0x00, 0x00});

    assert((cpu->status & 0b00000010) == 0b10);

    CPU_free(cpu);
}

void test_0xAA_TAX_move_a_to_x() {
    CPU_t* cpu = CPU_init();

    cpu->reg_a = 10;
    CPU_interpret(cpu, (uint8_t[]){0xaa, 0x00});

    assert(cpu->reg_x == 10);

    CPU_free(cpu);
}

void test_0xE8_INX_overflow() {
    CPU_t* cpu = CPU_init();

    cpu->reg_x = 0xFF;
    CPU_interpret(cpu, (uint8_t[]){0xE8, 0xE8, 0x00});

    assert(cpu->reg_x == 1);

    CPU_free(cpu);
}

void test_simple_5_instructions_program() {
    CPU_t* cpu = CPU_init();

    CPU_interpret(cpu, (uint8_t[]){0xa9, 0xc0, 0xaa, 0xe8, 0x00});

    assert(cpu->reg_x == 0xC1);

    CPU_free(cpu);
}

int main(int argc, char const *argv[]){
    
    test_0xA9_LDA_immediate_load_data();
    test_0xA9_LDA_zero_flag();
    test_0xAA_TAX_move_a_to_x();
    test_0xE8_INX_overflow();
    test_simple_5_instructions_program();

    return 0;
}
