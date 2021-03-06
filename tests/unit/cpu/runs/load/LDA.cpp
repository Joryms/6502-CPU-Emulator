#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("LDA Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>(0x1000, 0x3FFF);
    Byte value = random<Byte>();

    // Local Vars

    Word address;
    Byte addressOfAddress;
    Byte OPCode;
    Byte X;
    Byte Y;

    // Configure CPU

    cpu.PC = PC;

    SECTION("AB addressing mode test config") {

        // Config

        OPCode = 0xAD;
        address = random<Word>(0x5000, 0x7FFF);

        // Memory config for absolute addressing mode

        mem[PC + 1] = address >> 8;
        mem[PC + 2] = address;

    };

    SECTION("ABX addressing mode test config") {

        // Config

        OPCode = 0xBD;
        address = random<Word>(0x5000, 0x7FFF);
        X = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = (address - X) >> 8;
        mem[PC + 2] = address - X;

        // Config Register

        cpu.X = X;

    };

    SECTION("ABY addressing mode test config") {

        // Config

        OPCode = 0xB9;
        address = random<Word>(0x5000, 0x7FFF);
        Y = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = (address - Y) >> 8;
        mem[PC + 2] = address - Y;

        // Config Register

        cpu.Y = Y;

    };

    SECTION("IMM addressing mode test config") {

        // Config

        OPCode = 0xA9;
        address = PC + 1;

    };

    SECTION("IDX addressing mode test config") {

        // Config

        OPCode = 0xA1;
        addressOfAddress = random<Byte>();
        address = random<Word>(0x5000, 0x7FFF);
        X = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = addressOfAddress;
        mem[addressOfAddress + X] = address >> 8;
        mem[addressOfAddress + X + 1] = address;

        // Config Register

        cpu.X = X;

    };

    SECTION("IDY addressing mode test config") {

        // Config

        OPCode = 0xB1;
        addressOfAddress = random<Byte>();
        address = random<Word>(0x5000, 0x7FFF);
        Y = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = addressOfAddress;
        mem[addressOfAddress] = (address - Y) >> 8;
        mem[addressOfAddress + 1] = address - Y;

        // Config Register

        cpu.Y = Y;

    };

    SECTION("ZP addressing mode test config") {

        // Config

        OPCode = 0xA5;
        address = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address;

    };

    SECTION("ZPX addressing mode test config") {

        // Config

        OPCode = 0xB5;
        address = random<Byte>();
        X = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address - X;

        // Config Register

        cpu.X = X;

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;
    mem[address] = value;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(cpu.A == value);
    REQUIRE(cpu.N == isNegative(value));
    REQUIRE(cpu.Z == isZero(value));

}