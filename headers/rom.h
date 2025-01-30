#pragma once
#include "common.h"

static const uint8_t NES_TAG[] = {0x4E, 0x45, 0x53, 0x1A};
#define PRG_ROM_PAGE_SIZE 16384
#define CHR_ROM_PAGE_SIZE 8192

typedef enum {
    VERTICAL,
    HORIZONTAL,
    FOUR_SCREEN,
} Mirroring;

typedef struct {
    uint8_t* prg_ROM;
    uint8_t* chr_ROM;
    size_t prg_rom_size;
    size_t chr_rom_size;
    uint8_t mapper;
    Mirroring screen_mirroring;
} ROM;


ROM* ROM_init(uint8_t*);
void ROM_free(ROM*);