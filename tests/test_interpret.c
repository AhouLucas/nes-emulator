#include "../headers/common.h"
#include "../headers/cpu.h"


void test_0xA9_LDA_immediate_load_data() {
    CPU_t* cpu = CPU_init();

    CPU_load_and_run(cpu, (uint8_t[]){0xa9, 0x05, 0x00}, 3);

    assert(cpu->reg_a == 0x05);
    assert((cpu->status & 0b00000010) == 0b00);
    assert((cpu->status & 0b10000000) == 0);

    CPU_free(cpu);
}

void test_0xA9_LDA_zero_flag() {
    CPU_t* cpu = CPU_init();

    CPU_load_and_run(cpu, (uint8_t[]){0xa9, 0x00, 0x00}, 3);

    assert((cpu->status & 0b00000010) == 0b10);

    CPU_free(cpu);
}

void test_0xA5_LDA_from_memory() {
    CPU_t* cpu = CPU_init();

    CPU_mem_write_u8(cpu, 0x10, 0x55);

    CPU_load_and_run(cpu, (uint8_t[]){0xA5, 0x10, 0x00}, 3);

    assert(cpu->reg_a == 0x55);

    CPU_free(cpu);
}

void test_0xAA_TAX_move_a_to_x() {
    CPU_t* cpu = CPU_init();

    CPU_load_and_run(cpu, (uint8_t[]){0xa9, 10, 0xaa, 0x00}, 4);

    assert(cpu->reg_x == 10);

    CPU_free(cpu);
}

void test_simple_5_instructions_program() {
    CPU_t* cpu = CPU_init();

    CPU_load_and_run(cpu, (uint8_t[]){0xa9, 0xc0, 0xaa, 0xe8, 0x00}, 5);

    assert(cpu->reg_x == 0xC1);

    CPU_free(cpu);
}

int main(int argc, char const *argv[]){
    
    test_0xA9_LDA_immediate_load_data();
    test_0xA9_LDA_zero_flag();
    test_0xA5_LDA_from_memory();
    test_0xAA_TAX_move_a_to_x();
    test_simple_5_instructions_program();

    return 0;
}
