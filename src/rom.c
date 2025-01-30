#include "../headers/rom.h"

ROM* ROM_init(uint8_t* raw) {
    for (int i = 0; i < 4; i++) {
        if (raw[i] != NES_TAG[i]) {
            printf("Error invalid ROM : File is not in iNES file format\n");
            exit(EXIT_FAILURE);
        }
    }

    uint8_t mapper = (raw[7] & 0b11110000) | (raw[6] >> 4);

    uint8_t ines_ver = (raw[7] >> 2) & 0b11;
    if (ines_ver != 0) {
        printf("NES2.0 format is not supported\n");
        exit(EXIT_FAILURE);
    }

    bool four_screen = (raw[6] & 0b1000) != 0;
    bool vertical_mirroring = (raw[6] & 0b1) != 0;
    Mirroring screen_mirroring;
    if (four_screen) screen_mirroring = FOUR_SCREEN;
    else if (!four_screen && vertical_mirroring) screen_mirroring = VERTICAL;
    else if (!four_screen && !vertical_mirroring) screen_mirroring = HORIZONTAL;

    size_t prg_rom_size = raw[4] * PRG_ROM_PAGE_SIZE;
    size_t chr_rom_size = raw[5] * CHR_ROM_PAGE_SIZE;

    bool skip_trainer = (raw[6] & 0b100) != 0;

    size_t prg_rom_start = 16 + (skip_trainer ? 512 : 0);
    size_t chr_rom_start = prg_rom_start + prg_rom_size;

    ROM* rom = malloc(sizeof(ROM));

    rom->prg_ROM = malloc(sizeof(uint8_t) * prg_rom_size);
    rom->chr_ROM = malloc(sizeof(uint8_t) * chr_rom_size);
    memcpy(rom->prg_ROM, raw + prg_rom_start, prg_rom_size);
    memcpy(rom->chr_ROM, raw + chr_rom_start, chr_rom_size);
    rom->prg_rom_size = prg_rom_size;
    rom->chr_rom_size = chr_rom_size;
    rom->mapper = mapper;
    rom->screen_mirroring = screen_mirroring;
    
    return rom;
}

void ROM_free(ROM* rom) {
    free(rom->prg_ROM);
    free(rom->chr_ROM);
    free(rom);
}