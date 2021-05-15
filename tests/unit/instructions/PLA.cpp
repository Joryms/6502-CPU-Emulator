#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("PLA instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Byte X;
    Byte address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x68
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == PLA);
        }
    };
}