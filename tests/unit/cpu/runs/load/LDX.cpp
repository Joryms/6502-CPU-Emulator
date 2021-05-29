#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("LDX Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>();
    Byte value = random<Byte>();

    // Local Vars

    Word address;
    Byte addressOfAddress;
    Byte OPCode;
    Byte Y;

    // Configure CPU

    cpu.PC = PC;

    SECTION("AB addressing mode test config") {

        // Config

        OPCode = 0xAE;
        address = random<Word>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address >> 8;
        mem[PC + 2] = address;

    };

    SECTION("ABY addressing mode test config") {

        // Config

        OPCode = 0xBE;
        address = random<Word>();
        Y = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = (address - Y) >> 8;
        mem[PC + 2] = address - Y;

        // Config Register

        cpu.Y = Y;

    };

    SECTION("IMM addressing mode test config") {

        // Config

        OPCode = 0xA2;
        address = PC + 1;

    };

    SECTION("ZP addressing mode test config") {

        // Config

        OPCode = 0xA6;
        address = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address;

    };

    SECTION("ZPY addressing mode test config") {

        // Config

        OPCode = 0xB6;
        address = random<Byte>();
        Y = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address - Y;

        // Config Register

        cpu.Y = Y;

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;
    mem[address] = value;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(cpu.X == value);
    REQUIRE(cpu.N == isNegative(value));
    REQUIRE(cpu.Z == isZero(value));

}