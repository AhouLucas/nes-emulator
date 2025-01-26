#include "../headers/bus.h"


Bus_t* Bus_init() {
    Bus_t* bus = malloc(sizeof(Bus_t));
    bus->cpu_vram = malloc(sizeof(uint8_t)*0x0800);
    return bus;
}

void Bus_free(Bus_t* bus) {
    free(bus->cpu_vram);
    free(bus);
    return;
}


uint8_t Bus_mem_read_u8(Bus_t* bus, uint16_t addr) {
    switch (addr) {
        case RAM ... RAM_MIRRORS_END:
            uint16_t mirror_down_addr = addr & 0b0000011111111111;
            return bus->cpu_vram[mirror_down_addr];
            break;
        case PPU_REGISTERS ... PPU_REGISTERS_MIRRORS_END:
            uint16_t mirror_down_addr = addr & 0b0010000000000111;
            printf("PPU is not supported yet !\n");
            exit(EXIT_FAILURE);
        default:
            printf("Ignoring mem access at 0x%x\n", addr);
            return 0;
    }
}

void Bus_mem_write_u8(Bus_t* bus, uint16_t addr, uint8_t data) {
    switch (addr) {
        case RAM ... RAM_MIRRORS_END:
            uint16_t mirror_down_addr = addr & 0b0000011111111111;
            bus->cpu_vram[mirror_down_addr] = data;
            break;
        case PPU_REGISTERS ... PPU_REGISTERS_MIRRORS_END:
            uint16_t mirror_down_addr = addr & 0b0010000000000111;
            printf("PPU is not supported yet !\n");
            exit(EXIT_FAILURE);
        default:
            printf("Ignoring mem access at 0x%x\n", addr);
            return 0;
    }
}

uint16_t Bus_mem_read_u16(Bus_t* bus, uint16_t addr) {
    uint16_t lo = mem_read_u8(bus, addr);
    uint16_t hi = mem_read_u8(bus, addr+1);

    return (hi << 8) | lo;
}

void Bus_mem_write_u16(Bus_t* bus, uint16_t addr, uint16_t data) {
    uint8_t lo = data & 0xFF;
    uint8_t hi = data >> 8;
    mem_write_u8(bus, addr, lo);
    mem_write_u8(bus, addr + 1, hi);
}