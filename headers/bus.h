#pragma once

#include "common.h"


typedef struct Bus {
    uint8_t* cpu_vram;
} Bus_t;


/* Initialization */

Bus_t*  Bus_init();
void    Bus_free(Bus_t*);

/* End initialization */


/* Read/Write functions */

static const uint16_t RAM                       = 0x0000;
static const uint16_t RAM_MIRRORS_END           = 0x1FFF;
static const uint16_t PPU_REGISTERS             = 0x2000;
static const uint16_t PPU_REGISTERS_MIRRORS_END = 0x3FFF;


uint8_t     Bus_mem_read_u8(Bus_t*, uint16_t);
void        Bus_mem_write_u8(Bus_t*, uint16_t, uint8_t);
uint16_t    Bus_mem_read_u16(Bus_t*, uint16_t);
void        Bus_mem_write_u16(Bus_t*, uint16_t, uint16_t);

/* End Read/Write */