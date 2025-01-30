#pragma once

#include "common.h"
#include "rom.h"


typedef struct {
    uint8_t* cpu_vram;
    ROM* rom;
} Bus;


/* Initialization */

Bus*    Bus_init();
void    Bus_free(Bus*);

/* End initialization */


/* Read/Write functions */

#define RAM                         0x0000
#define RAM_MIRRORS_END             0x1FFF
#define PPU_REGISTERS               0x2000
#define PPU_REGISTERS_MIRRORS_END   0x3FFF

uint8_t     Bus_read_prg_rom(Bus*, uint16_t);
uint8_t     Bus_mem_read_u8(Bus*, uint16_t);
void        Bus_mem_write_u8(Bus*, uint16_t, uint8_t);
uint16_t    Bus_mem_read_u16(Bus*, uint16_t);
void        Bus_mem_write_u16(Bus*, uint16_t, uint16_t);

/* End Read/Write */