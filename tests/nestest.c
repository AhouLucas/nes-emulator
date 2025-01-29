#include "../headers/cpu.h" // Include your NES emulator header


typedef struct expected_state {
    uint16_t pc;
    uint8_t reg_a;
    uint8_t reg_x;
    uint8_t reg_y;
    uint8_t status;
    uint8_t stack_pointer;
} expected_state;


// Function to parse a line from the nestest.log file
// Function to parse a line and store the result in a CpuState struct
int parse_log_line(const char *line, expected_state *state) {
    // parse program counter (4 first bytes)
    if (sscanf(line, "%04hx", &state->pc) != 1) {
        return 0;
    }
    
    // parse register A (50th and 51st bytes)
    if (sscanf(line + 50, "%02hhx", &state->reg_a) != 1) {
        return 0;
    }

    // parse register X (55th and 56th bytes)
    if (sscanf(line + 55, "%02hhx", &state->reg_x) != 1) {
        return 0;
    }

    // parse register Y (60th and 61st bytes)
    if (sscanf(line + 60, "%02hhx", &state->reg_y) != 1) {
        return 0;
    }

    // parse status register (65th and 66th bytes)
    if (sscanf(line + 65, "%02hhx", &state->status) != 1) {
        return 0;
    }

    // parse stack pointer (71st and 72nd bytes)
    if (sscanf(line + 71, "%02hhx", &state->stack_pointer) != 1) {
        return 0;
    }

    return 1;
}


// Function to execute the next instruction in the nestest suite
void nes_step(CPU_t* cpu) {
    uint8_t opcode = CPU_mem_read_u8(cpu, cpu->pc);
    cpu->pc++;
    uint16_t pc_state = cpu->pc;

    if (opcode == 0x00) return;

    OpcodeEntry_t entry = opcode_table[opcode];

    switch (entry.type) {
    case INSTRUCTION_TYPE_VOID:
        entry.instruction.void_instruction(cpu, entry.mode);
        break;
    case INSTRUCTION_TYPE_U8:
        entry.instruction.u8_instruction(cpu, entry.mode);
        break;
    default:
        printf("Unknown instruction type\n");
        exit(EXIT_FAILURE);
        break;
    }

    if (pc_state == cpu->pc) {
        cpu->pc += (uint16_t) entry.len - 1;
    }
}

// Function to run the nestest suite
void run_nestest(const char *log_file_path) {
    FILE *log_file = fopen(log_file_path, "r");
    if (!log_file) {
        perror("Failed to open log file");
        return;
    }

    char line[256];
    expected_state expected_state = {.pc = 0, .reg_a = 0, .reg_x = 0, .reg_y = 0, .status = 0, .stack_pointer = 0x00FD};

    // Initialize the ROM and CPU
    // Read byte from nestest.nes into an array of uint8_t
    // Open the ROM file
    FILE *rom_file = fopen("tests/nestest.nes", "rb");
    if (!rom_file) {
        perror("Failed to open ROM file");
        fclose(log_file);
        return;
    }

    // Determine the size of the ROM file
    fseek(rom_file, 0, SEEK_END);
    long rom_size = ftell(rom_file);
    fseek(rom_file, 0, SEEK_SET);

    // Allocate memory for the ROM
    uint8_t *rom_data = (uint8_t *)malloc(rom_size);
    if (!rom_data) {
        fprintf(stderr, "Failed to allocate memory for ROM\n");
        fclose(rom_file);
        fclose(log_file);
        return;
    }

    // Read the ROM file into the array
    size_t bytes_read = fread(rom_data, sizeof(uint8_t), rom_size, rom_file);
    if (bytes_read != rom_size) {
        fprintf(stderr, "Failed to read the entire ROM file\n");
        free(rom_data);
        fclose(rom_file);
        fclose(log_file);
        return;
    }
    fclose(rom_file);

    // Initialize the bus and load the ROM
    ROM_t *rom = ROM_init(rom_data);
    Bus_t *bus = Bus_init(rom);
    CPU_t *cpu = CPU_init(bus);

    // Load the program into the CPU and reset it
    CPU_reset(cpu);
    cpu->pc = 0xC000;

    int counter = 1;

    // count number of lines in the log file
    int lines = 0;
    while (fgets(line, sizeof(line), log_file)) {
        lines++;
    }

    // Reset the log file to the beginning
    fseek(log_file, 0, SEEK_SET);

    while (fgets(line, sizeof(line), log_file)) {
        // Parse the expected state from the log file
        if (!parse_log_line(line, &expected_state)) {
            fprintf(stderr, "Failed to parse log line\n");
            break;
        }


        printf("Test (%d / %d) [%.2f\%]", counter, lines, (float)counter / lines * 100);

        // Compare the actual state with the expected state
        if (cpu->pc != expected_state.pc || cpu->reg_a != expected_state.reg_a || cpu->reg_x != expected_state.reg_x || cpu->reg_y != expected_state.reg_y || cpu->status != expected_state.status || cpu->stack_pointer != expected_state.stack_pointer) {
            printf(" ❌\n");
            printf("Expected: PC:%04X A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
                expected_state.pc,
                expected_state.reg_a, 
                expected_state.reg_x, 
                expected_state.reg_y, 
                expected_state.status, 
                expected_state.stack_pointer);
            
            printf("Actual:   PC:%04X A:%02X X:%02X Y:%02X P:%02X SP:%02X\n\n",
                cpu->pc,
                cpu->reg_a, 
                cpu->reg_x, 
                cpu->reg_y, 
                cpu->status, 
                cpu->stack_pointer);

            // Print counter with percentage of passed tests
            printf("Tests passed: %d\n", counter);
            printf("Percentage passed: %.2f%%\n", (float)counter / lines * 100);
            break;
        }

        printf(" ✅\n\n");
        counter++;

        // Execute the next instruction
        nes_step(cpu);
    }

    fclose(log_file);
}

int main() {
    run_nestest("tests/nestest.log");
    return 0;
}