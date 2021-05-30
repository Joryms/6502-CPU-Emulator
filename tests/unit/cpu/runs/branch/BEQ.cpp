#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("BEQ Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>(0x1000, 0x3FFF);
    Byte value = random<Byte>();
    Bit Z = random<Bit>();

    // Local Vars

    Byte OPCode;
    Word address;
    Byte displacement;

    // Configure CPU

    cpu.Z = Z;
    cpu.PC = PC;

    SECTION("REL addressing mode test config") {

        // Config

        OPCode = 0xF0;
        address = PC + 1;

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;
    mem[address] = value;

    // Run based on section parameters

    cpu.Run();

    // Displacement

    isSet(Z) ? displacement = value : displacement = 0;

    // Assertions

    REQUIRE(cpu.PC == (PC + 2 + (Signed) displacement));

}