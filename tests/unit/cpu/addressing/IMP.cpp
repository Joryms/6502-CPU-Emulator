#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Implied addressing mode") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word PC;
    Word address;
    Location expected;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[27] = { 
            0x00, 0x18, 0xD8, 0x58, 0xB8, 
            0x48, 0x08, 0x68, 0x28, 0x40,
            0x60, 0x38, 0xF8, 0x78, 0xAA,
            0xA8, 0xBA, 0x8A, 0x9A, 0x98,
            0x0A, 0x4A, 0xCA,
            0x88, 0xE8, 0xC8, 0xEA
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == IMP);
        }
    };

    SECTION("returns proper address for random PC") {

        expected = Location();

        REQUIRE(cpu.Locate(IMP) == expected);
    };
}