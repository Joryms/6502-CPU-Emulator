#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Relative addressing mode") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Word PC;
    Word address;
    Location expected;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0x10, 0x30, 0x50, 0x70, 0x90,
            0xB0, 0xD0, 0xF0
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == REL);
        }
    };

    SECTION("returns proper address for random PC") {

        PC = random<Word>(0x1000, 0x3FFF);
        expected = Location(PC);

        cpu.PC = PC;

        REQUIRE(cpu.Locate(REL) == expected);
        REQUIRE(cpu.PC == PC + 1);
    };
}